#include <tree/b_plus_tree.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct bp_entry {
    int64_t key_;
    void *pointer; // leaf: data; inner: node
};

struct bp_leaf_node {
    size_t amount_;
    InnerNode *parent;
    Entry *entries_;
    LeafNode *right;
};

struct bp_inner_node {
    size_t amount_;
    InnerNode *parent;//, *siblings;
    void *first_pointer;
    Entry *entries_;
};

struct bp_t {
    size_t order_, depth_;
    InnerNode *root_;
    LeafNode *leftmost_leaf;
};


//void print_tree(BPlusTree *bp) {
//    void* queue[10000];
//    int front = 0, rear = 1, i;

//    queue[front]  = (void*) bp->root_;
//    queue[rear++] = (void*) bp->root_->first_pointer;

//    while (front != rear) {
//        InnerNode *node = (InnerNode*) queue[front++];

//        printf("\n");

//        for (i = 0; i < node->amount_; i++) {
////            if (i == 0)
////                queue[rear++] = (void*) node->first_pointer;

//            printf("%d ", node->entries_[i].key_);

////            queue[rear++] = (void*) node->entries_[i].pointer;
//        }

//        printf("\n");

//    }
//}

void print_all_entries(BPlusTree *bp) {
    size_t i;
    LeafNode *leaf;

    printf("\n");

    for (i = 0; i < bp->root_->amount_; i++)
        printf("%d ", bp->root_->entries_[i].key_);

    printf("-----");
    printf("\n");

    for (leaf = bp->leftmost_leaf; leaf != NULL; leaf = leaf->right) {
        for (i = 0; i < leaf->amount_; i++)
            printf("%d ", leaf->entries_[i].key_);

        printf("\n");
    }

    printf("\n");
}

Entry* entry_create(int64_t key, void *pointer) {
    Entry *new_entry = (Entry*) calloc(1ul, sizeof(Entry));

    assert(new_entry != NULL);

    new_entry->key_    = key;
    new_entry->pointer = pointer;

    return new_entry;
}

LeafNode* leaf_create(InnerNode *const parent, LeafNode *const right, size_t order) {
    LeafNode *new_leaf    = (LeafNode*) malloc(sizeof(LeafNode));
    Entry    *new_entries = (Entry*)    calloc(2 * order, sizeof(Entry));

    assert(new_leaf != NULL && new_entries != NULL);

    new_leaf->amount_  = 0;
    new_leaf->parent   = parent;
    new_leaf->entries_ = new_entries;
    new_leaf->right    = right;

    return new_leaf;
}

int8_t leaf_overflow(const LeafNode *const node, size_t order) {
    return node->amount_ >= 2 * order;
}

int8_t leaf_insert(LeafNode *const node, size_t order, Entry *entry) {
    int8_t is_overflow = leaf_overflow(node, order);
    size_t i, j;

    if (is_overflow)
        return 0;

    for (i = 0; i < node->amount_ && node->entries_[i].key_ < entry->key_; i++);

    for (j = node->amount_; j > i ; j--)
        node->entries_[j] = node->entries_[j - 1];

    node->entries_[i].key_    = entry->key_;
    node->entries_[i].pointer = entry->pointer;
    node->amount_++;

    return 1;
}

LeafNode* leaf_split(BPlusTree *const bp, LeafNode *node) {
    size_t i;
    LeafNode *new_leaf = leaf_create(node->parent, node->right, bp->order_);

    node->right = new_leaf;

    for (i = bp->order_; i < 2 * bp->order_; i++) {
        leaf_insert(new_leaf, bp->order_, &node->entries_[i]);
        node->amount_--;
    }

    return new_leaf;
}

InnerNode* inner_create(InnerNode *const parent, size_t order) {
    InnerNode *new_inner  = (InnerNode*) malloc(sizeof(InnerNode));
    Entry    *new_entries = (Entry*)     calloc(2 * order, sizeof(Entry));

    assert(new_inner != NULL && new_entries != NULL);

    new_inner->amount_       = 0;
    new_inner->parent        = parent;
    new_inner->first_pointer = NULL;
    new_inner->entries_      = new_entries;

    return new_inner;
}

int8_t inner_overflow(const InnerNode *const node, size_t order) {
    return node->amount_ >= 2 * order;
}

int8_t inner_insert(InnerNode *const node, size_t order, Entry *entry) {
    assert (node->amount_ > 0); // first_child is already ok!

    int8_t is_overflow = inner_overflow(node, order);
    size_t i, j;

    if (is_overflow)
        return 0;

    for (i = 0; i < node->amount_ && node->entries_[i].key_ < entry->key_; i++);

    for (j = node->amount_; j > i ; j--)
        node->entries_[j] = node->entries_[j - 1];

    node->entries_[i].key_    = entry->key_;
    node->entries_[i].pointer = entry->pointer;
    node->amount_++;

    return 1;
}

InnerNode* inner_split(BPlusTree *const bp, InnerNode *node, Entry *entry) {
    InnerNode *new_inner = inner_create(node->parent, bp->order_);
    size_t i, j;
    Entry all_entries[2 * bp->order_ + 1];

    for (i = 0; i < 2 * bp->order_; i++)
        all_entries[i] = node->parent->entries_[i];

    for (i = 0; i < 2 * bp->order_ && entry->key_ > all_entries[i].key_; i++);

    for (j = 2 * bp->order_ - 1; j >= i; j--)
        all_entries[j + 1] = all_entries[j];

    all_entries[i].key_    = entry->key_;
    all_entries[i].pointer = entry->pointer;

    i = (2 * bp->order_ + 1) / 2;

    node->amount_ = 0;

    for (j = 0; j < i; j++)
        node->entries_[node->amount_++] = all_entries[j];

    new_inner->entries_[0] = all_entries[i + 1];
    new_inner->amount_++;

    new_inner->first_pointer = all_entries[i].pointer;

    for (j = i + 2; j < 2 * bp->order_ + 1; j++)
        new_inner->entries_[new_inner->amount_++] = all_entries[j];

    return new_inner;
}

void recursive_insert(BPlusTree *const bp, void *node, size_t node_depth, Entry *entry) {
    if (bp->depth_ == node_depth) {
        LeafNode *node_to_ins = (LeafNode*) node;

        if (!leaf_insert(node_to_ins, bp->order_, entry)) {
            LeafNode *new_leaf     = leaf_split(bp, node_to_ins);
            Entry *new_inner_entry = entry_create(new_leaf->entries_[0].key_, (void*) new_leaf);

            if (entry->key_ < new_inner_entry->key_)
                leaf_insert(node_to_ins, bp->order_, entry);
            else
                leaf_insert(new_leaf, bp->order_, entry);

            if (!inner_insert(node_to_ins->parent, bp->order_, new_inner_entry))
                recursive_insert(bp, node_to_ins->parent, node_depth - 1, new_inner_entry);
        }

    } else {
        InnerNode *node_to_ins = (InnerNode*) node;

        if (!inner_insert(node_to_ins, bp->order_, entry)) {
            InnerNode *new_inner = inner_create(node_to_ins->parent, bp->order_);
            size_t i, j;
            Entry all_entries[2 * bp->order_ + 1];

            for (i = 0; i < 2 * bp->order_; i++)
                all_entries[i] = node_to_ins->entries_[i];

            for (i = 0; i < 2 * bp->order_ && entry->key_ > all_entries[i].key_; i++);

            for (j = 2 * bp->order_ - 1; j >= i; j--)
                all_entries[j + 1] = all_entries[j];

            all_entries[i].key_    = entry->key_;
            all_entries[i].pointer = entry->pointer;

            i = (2 * bp->order_ + 1) / 2;

            node_to_ins->amount_ = 0;

            for (j = 0; j < i; j++)
                node_to_ins->entries_[node_to_ins->amount_++] = all_entries[j];

            new_inner->entries_[0] = all_entries[i + 1];
            new_inner->amount_++;

            new_inner->first_pointer = all_entries[i].pointer;

            for (j = i + 2; j < 2 * bp->order_ + 1; j++)
                new_inner->entries_[new_inner->amount_++] = all_entries[j];

            if (bp->root_ == node_to_ins) {
                bp->depth_++;
                bp->root_                      = inner_create(NULL, bp->order_);
                bp->root_->entries_[0].key_    = all_entries[i].key_;
                bp->root_->entries_[0].pointer = (void*) new_inner;
                bp->root_->amount_++;
                bp->root_->first_pointer       = (void*) node_to_ins;

                node_to_ins->parent = bp->root_;
                new_inner->parent   = bp->root_;
            } else {
                Entry *new_inner_entry = entry_create(all_entries[i].key_, (void*) new_inner);

                recursive_insert(bp, node_to_ins->parent, node_depth - 1, new_inner_entry);
            }
        }
    }
}

LeafNode* _bp_search(InnerNode *root, size_t depth, int64_t key) {
    InnerNode *next_node = root;
    size_t level, i;

    if (next_node == NULL)
        return NULL;

    for (level = 0; level < depth; level++) {
        assert (next_node != NULL);

        for (i = 0; i < next_node->amount_ && key >= next_node->entries_[i].key_; i++);

        if (i == 0)
            next_node = (InnerNode*) next_node->first_pointer;
        else
            next_node = (InnerNode*) next_node->entries_[i - 1].pointer;
    }

    return (LeafNode*) next_node;
}

void _bp_remove(LeafNode *node, int64_t key) {
    if (node != NULL) {
        size_t i, j;

        for (i = 0; i < node->amount_ && key != node->entries_[i].key_; i++);

        while (i < node->amount_ && key == node->entries_[i].key_) {
            for (j = i + 1; j < node->amount_; j++)
                node->entries_[j - 1] = node->entries_[j];

            if (key != node->entries_[i].key_)
                i++;

            node->amount_--;
        }
    }
}


BPlusTree* bp_create(size_t order) {
    assert(order > 0);

    BPlusTree *bp = (BPlusTree*) malloc(sizeof(BPlusTree));

    assert(bp != NULL);

    bp->order_        = order;
    bp->depth_        = 0;
    bp->root_         = NULL;
    bp->leftmost_leaf = NULL;

    return bp;
}

void bp_insert(BPlusTree *const bp, int64_t key, const void *const value, size_t nbytes) {
    assert(bp != NULL);

    void *datum_ptr = malloc(sizeof(nbytes));

    assert (datum_ptr != NULL);

    Entry *new_leaf_entry = entry_create(key, datum_ptr);

    memcpy(new_leaf_entry->pointer, value, nbytes);

    if (bp->depth_ == 0) {
        bp->depth_ = 1;

        bp->root_                      = inner_create(NULL, bp->order_);
        bp->root_->entries_[0].key_    = key;
        bp->root_->entries_[0].pointer = (void*) leaf_create(bp->root_, NULL, bp->order_);
        bp->root_->amount_++;
        bp->root_->first_pointer       = leaf_create(bp->root_, bp->root_->entries_[0].pointer, bp->order_);
        bp->leftmost_leaf              = bp->root_->first_pointer;

        leaf_insert(bp->root_->entries_[0].pointer, bp->order_, new_leaf_entry);
    } else {
        LeafNode *node_to_ins = _bp_search(bp->root_, bp->depth_, key);

        recursive_insert(bp, node_to_ins, bp->depth_, new_leaf_entry);
    }
}

size_t bp_search(const BPlusTree *const bp, int64_t key, void ***values) {
    assert(bp != NULL);

    LeafNode *leaf_node = _bp_search(bp->root_, bp->depth_, key);
    size_t i, j, n_values = 0;

    if (leaf_node == NULL) {
        values = NULL;
        return 0;
    }

    for (i = 0; i < leaf_node->amount_ && key != leaf_node->entries_[i].key_; i++);

    for (; i < leaf_node->amount_ && key == leaf_node->entries_[i].key_; i++)
        n_values++;

    i -= n_values;

    *values = (void**) malloc(n_values * sizeof(void*));

    for (j = 0; j < n_values; j++)
        (*values)[j] = leaf_node->entries_[i++].pointer;

    return n_values;
}

void bp_remove(BPlusTree *const bp, int64_t key) {
    assert(bp != NULL);

    LeafNode *leaf_node = _bp_search(bp->root_, bp->depth_, key);

    _bp_remove(leaf_node, key);
}
