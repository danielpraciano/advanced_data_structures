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
    LeafNode **leaves;
};

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

int8_t leaf_overflow(const LeafNode *const node, size_t order) {
    return node->amount_ >= 2 * order;
}

int8_t inner_overflow(const InnerNode *const node, size_t order) {
    return node->amount_ >= 2 * order;
}

int8_t leaf_insert(LeafNode *const node, size_t order, Entry *entry) {
    int8_t is_overflow = leaf_overflow(node, order);
    size_t i, j;

    if (is_overflow)
        return 0;

    for (i = 0; i < node->amount_ && node->entries_[i].key_ < entry->key_; i++);

    for (j = node->amount_; j > i ; j--)
        node->entries_[j] = node->entries_[j - 1]; //funciona mesmo??? pois nao sao *

    node->entries_[i].key_    = entry->key_;
    node->entries_[i].pointer = entry->pointer;
    node->amount_++;

    return 1;
}

int8_t inner_insert(InnerNode *const node, size_t order, Entry *entry) {
    assert (node->amount_ > 0); // first_child is already ok!

    int8_t is_overflow = inner_overflow(node, order);
    size_t i, j;

    if (is_overflow)
        return 0;

    for (i = 0; i < node->amount_ && node->entries_[i].key_ < entry->key_; i++);

    for (j = node->amount_; j > i ; j--)
        node->entries_[j] = node->entries_[j - 1]; //funciona mesmo??? pois nao sao *

    node->entries_[i].key_    = entry->key_;
    node->entries_[i].pointer = entry->pointer;
    node->amount_++;

    return 1;
}


BPlusTree* bp_create(size_t order) {
    assert(order > 0); //desncessary!!!

    BPlusTree *bp = (BPlusTree*) malloc(sizeof(BPlusTree));

    assert(bp != NULL);

    bp->order_ = order;
    bp->depth_ = 0;
    bp->root_  = NULL;

    return bp;
}

//size_t get_entry_idx(void *node, void *pointer) {
//    InnerNode *inode = (InnerNode*) node;
//    size_t i;

//    for (i = 0; i < inode->amount_ && inode->entries_[i].pointer != pointer; i++);

//    return i;
//}

void recursive_insert(BPlusTree *const bp, void *node, size_t node_depth, Entry *entry) {
    if (bp->depth_ == node_depth) {
        LeafNode *node_to_ins = (LeafNode*) node;

        if (!leaf_insert(node_to_ins, bp->order_, entry)) {

            if (!inner_overflow(node_to_ins->parent, bp->order_)) {

                size_t i;
                LeafNode *new_leaf     = leaf_create(node_to_ins->parent, node_to_ins->right, bp->order_);
                Entry *new_inner_entry = (Entry*) malloc(sizeof(Entry));

                assert(new_inner_entry != NULL);

                new_inner_entry->key_    = node_to_ins->entries_[bp->order_].key_;
                new_inner_entry->pointer = (void*) new_leaf;

                node_to_ins->right = new_leaf;

                for (i = bp->order_; i < 2 * bp->order_; i++) {
                    leaf_insert(new_leaf, bp->order_, &node_to_ins->entries_[i]);
                    node_to_ins->amount_--;
                }

                if (entry->key_ > new_inner_entry->key_)
                    leaf_insert(new_leaf, bp->order_, entry);
                else
                    leaf_insert(node_to_ins, bp->order_, entry);

                inner_insert(node_to_ins->parent, bp->order_, new_inner_entry);

            } else {
                size_t i, j;
                LeafNode *new_leaf     = leaf_create(node_to_ins->parent, node_to_ins->right, bp->order_);
                Entry *new_inner_entry = (Entry*) malloc(sizeof(Entry));

                assert(new_inner_entry != NULL);

                new_inner_entry->key_    = node_to_ins->entries_[bp->order_].key_;
                new_inner_entry->pointer = (void*) new_leaf;

                node_to_ins->right = new_leaf;

                for (i = bp->order_; i < 2 * bp->order_; i++) {
                    leaf_insert(new_leaf, bp->order_, &node_to_ins->entries_[i]);
                    node_to_ins->amount_--;
                }

                if (entry->key_ > new_inner_entry->key_)
                    leaf_insert(new_leaf, bp->order_, entry);
                else
                    leaf_insert(node_to_ins, bp->order_, entry);

                Entry all_entries[2 * bp->order_ + 1];

                for (i = 0; i < 2 * bp->order_; i++) {
                    all_entries[i].key_    = node_to_ins->parent->entries_[i].key_;
                    all_entries[i].pointer = node_to_ins->parent->entries_[i].pointer;
                }

                for (i = 0; i < 2 * bp->order_ && all_entries[i].key_ < new_inner_entry->key_; i++);

                for (j = 2 * bp->order_ - 1; j > i; j--)
                    all_entries[j + 1] = all_entries[j]; // is ok??

                all_entries[i].key_    = new_inner_entry->key_;
                all_entries[i].pointer = new_inner_entry->pointer;

                i = (bp->order_ + 1) / 2;

                //is ok??
                InnerNode *new_inner = inner_create(node_to_ins->parent->parent, bp->order_);

                node_to_ins->parent->amount_ = 0;

                for (j = 0; j < i; j++) {
                    node_to_ins->parent->entries_[j].key_    = all_entries[j].key_;
                    node_to_ins->parent->entries_[j].pointer = all_entries[j].pointer;
                    node_to_ins->parent->amount_++;
                }

                new_inner->entries_[0].key_    = all_entries[i + 1].key_;
                new_inner->entries_[0].pointer = all_entries[i + 1].pointer;
                new_inner->amount_++;

                new_inner->first_pointer       = all_entries[i].pointer;

                for (j = i + 2; j < 2 * bp->order_ + 1; j++) {
                    new_inner->entries_[new_inner->amount_].key_    = all_entries[j].key_;
                    new_inner->entries_[new_inner->amount_].pointer = all_entries[j].pointer;
                    new_inner->amount_++;
                }

                if (bp->root_ == node_to_ins->parent) { //equivalent: depth == 0??
                    bp->depth_++;
                    bp->root_                      = inner_create(NULL, bp->order_);
                    bp->root_->entries_[0].key_    = all_entries[i].key_;
                    bp->root_->entries_[0].pointer = (void*) new_inner;
                    bp->root_->amount_++;
                    bp->root_->first_pointer       = (void*) node_to_ins->parent;

                    node_to_ins->parent->parent = new_inner->parent = bp->root_;

                } else {
                    Entry *new_inner_entry = (Entry*) malloc(sizeof(Entry));

                    assert(new_inner_entry != NULL);

                    new_inner_entry->key_    = all_entries[i].key_;
                    new_inner_entry->pointer = (void*) new_inner;

                    recursive_insert(bp, node_to_ins->parent->parent, node_depth - 1, new_inner_entry);
                }
            }
        }

    } else {
        // fazer!!!
    }
}

void bp_insert(BPlusTree *const bp, int64_t key, const void *const value, size_t nbytes) {
    assert(bp != NULL);

    Entry *new_leaf_entry = (Entry*) malloc(sizeof(Entry));

    assert(new_leaf_entry != NULL);

    new_leaf_entry->key_    = key;
    new_leaf_entry->pointer = malloc(sizeof(nbytes));
    memcpy(new_leaf_entry->pointer, value, nbytes);

    if (bp->depth_ == 0) {
        bp->depth_ = 1;

        bp->root_                      = inner_create(NULL, bp->order_);
        bp->root_->entries_[0].key_    = key;
        bp->root_->entries_[0].pointer = (void*) leaf_create(bp->root_, NULL, bp->order_);
        bp->root_->amount_++;
        bp->root_->first_pointer       = leaf_create(bp->root_, bp->root_->entries_[0].pointer, bp->order_);

        leaf_insert(bp->root_->first_pointer, bp->order_, new_leaf_entry);
    } else {
        LeafNode *node_to_ins = _bp_search(bp->root_, bp->depth_, key);
        int8_t has_overflow      = !leaf_insert(node_to_ins, bp->order_, new_leaf_entry);

        if (has_overflow)
            recursive_insert(bp, node_to_ins, bp->depth_, new_leaf_entry);
    }
}

LeafNode* _bp_search(InnerNode *root, size_t depth, int64_t key) {
    InnerNode *next_node = root;
    size_t level = 0, i;

    if (next_node == NULL)
        return NULL;

    for (level = 0; level < depth; level++) {
        assert (next_node != NULL);

        for (i = 0; i < next_node->amount_ && next_node->entries_[i].key_ > key; i++);

        if (i == 0)
            next_node = (InnerNode*) next_node->first_pointer;
        else
            next_node = (InnerNode*) next_node->entries_[i - 1].pointer;
    }

    return (LeafNode*) next_node;
}

int8_t bp_search(const BPlusTree *const bp, int64_t key, const void *value) {
    assert(bp != NULL);

    LeafNode *leaf_node = _bp_search(bp->root_, bp->depth_, key);
    size_t i;

    if (leaf_node == NULL) {
        value = NULL;
        return 0;
    }
    //tratar caso quando tenho mais de uma entrada igual!!!
    for (i = 0; i < leaf_node->amount_ && leaf_node->entries_[i].key_ != key; i++);

    value = i < leaf_node->amount_ ? leaf_node->entries_[i].pointer : NULL;

    return value == NULL ? 0 : 1;
}






//void _remove(Node **root, int64_t key) {
//    Node *node = _search(*root, key);

//    if (node != NULL && node->entry_->key_ == key) {
//        if (node->left == NULL && node->right == NULL) {
//            if (node->parent == NULL) {
//                root = NULL;
//            } else {
//                if (node == node->parent->left)
//                    node->parent->left  = NULL;
//                else
//                    node->parent->right = NULL;
//            }
//        } else if (node->left != NULL && node->right == NULL) {
//            node->left->parent  = node->parent;

//            if (node->parent == NULL) {
//                root = &node->left;
//            } else {
//                if (node == node->parent->left)
//                    node->parent->left  = node->left;
//                else
//                    node->parent->right = node->left;
//            }
//        } else if (node->left == NULL && node->right != NULL) {
//            node->right->parent  = node->parent;

//            if (node->parent == NULL) {
//                root = &node->right;
//            } else {
//                if (node == node->parent->left)
//                    node->parent->left  = node->right;
//                else
//                    node->parent->right = node->right;
//            }
//        } else {
//            void *removed_value = node->entry_->value_;
//            Node *succ = _successor(node);
//            assert(succ != NULL);

//            node->entry_->key_   = succ->entry_->key_;
//            node->entry_->value_ = succ->entry_->value_;

//            succ->entry_->value_ = removed_value;

//            _remove(&succ, succ->entry_->key_);

//            node = NULL;
//        }

//        node_free(node);
//    }
//}

//void bst_remove(BinarySearchTree *const bst, int64_t key) {
//    assert(bst != NULL);

//    _remove(&bst->root_, key);
//}

//Node* _successor(const Node *const node) {
//    Node *succ = NULL;

//    if (node == NULL)
//        return NULL;

//    succ = node->right;

//    if (succ != NULL) {
//        while (succ->left != NULL)
//            succ = succ->left;
//    } else {
//        Node *parent = node->parent, *child = (Node*) node;

//        while (parent != NULL && child == parent->right) {
//           child = parent;
//           parent = child->parent;
//        }

//        succ = parent;
//    }

//    return succ;
//}

//int64_t* bst_successor(const BinarySearchTree *const bst, int64_t key) {
//    assert(bst != NULL);

//    int64_t *result = NULL;
//    Node *node = _search(bst->root_, key);
//    Node *succ = _successor(node);

//    if (succ != NULL) {
//        result = (int64_t*) malloc(sizeof(int64_t));
//        assert(result != NULL);

//        *result = succ->entry_->key_;
//    }

//    return result;
//}

//void pre_recursive_print(const Node *const node) {
//    if (node != NULL) {
//        printf("%d ", node->entry_->key_);
//        pre_recursive_print(node->left);
//        pre_recursive_print(node->right);
//    }
//}

//void bst_pre_order_print(const BinarySearchTree *const bst) {
//    printf("\n Keys in pre-order: ");
//    pre_recursive_print(bst->root_);
//    printf("\n");
//}

//void in_recursive_print(const Node *const node) {
//    if (node != NULL) {
//        in_recursive_print(node->left);
//        printf("%d ", node->entry_->key_);
//        in_recursive_print(node->right);
//    }
//}

//void  bst_in_order_print(const BinarySearchTree *const bst) {
//    printf("\n Keys in-order: ");
//    in_recursive_print(bst->root_);
//    printf("\n");
//}

//void pos_recursive_print(const Node *const node) {
//    if (node != NULL) {
//        pos_recursive_print(node->left);
//        pos_recursive_print(node->right);
//        printf("%d ", node->entry_->key_);
//    }
//}

//void bst_pos_order_print(const BinarySearchTree *const bst) {
//    printf("\n Keys in pos-order:");
//    pos_recursive_print(bst->root_);
//    printf("\n");
//}

//void node_free(Node *node) {
//    if (node != NULL) {
//        if (node->entry_->value_ != NULL)
//            free(node->entry_->value_);

//        free(node->entry_);
//        free(node);
//    }
//}

//void recursive_node_free(Node *node) {
//    if (node != NULL) {
//        recursive_node_free(node->left);
//        recursive_node_free(node->right);
//        node_free(node);
//    }
//}

//void bst_free(BinarySearchTree *bst) {
//    recursive_node_free(bst->root_);
//}
