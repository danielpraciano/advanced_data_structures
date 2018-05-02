#include <tree/binary_search_tree.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>


struct bst_entry {
    int64_t key_;
    void *value_;
};

struct bst_node {
    Entry entry_;
    Node *parent, *left, *right;
};

struct bst_t {
    Node *root_;
    free_function_ptr free_f_ptr;
};


BinarySearchTree* bst_create(free_function_ptr free_f_ptr) {
    BinarySearchTree *bst = (BinarySearchTree*) malloc(sizeof(BinarySearchTree));

    assert(bst != NULL);

    bst->root_      = NULL;
    bst->free_f_ptr = free_f_ptr;

    return bst;
}

void bst_insert(BinarySearchTree *const bst, int64_t key, const void *const value, size_t nbytes) {
    assert(bst != NULL);

    Entry *entry = (Entry*) malloc(sizeof(Entry));

    assert(entry != NULL);

    entry->key_   = key;
    entry->value_ = malloc(sizeof(nbytes));
    memcpy(entry->value_, value, nbytes);

    Node *node = (Node*) malloc(sizeof(Node));

    assert(node != NULL);

    node->entry_ = entry;
    node->parent = NULL;
    node->left   = NULL;
    node->right  = NULL;

    Node *parent = _search(bst->root_, key);

    if (parent == NULL) {
        bst->root_ = node;
    } else if (key <= parent->entry_.key_) {
        assert(node->parent->left == NULL && node->parent->right == NULL); //TIRAR
        node->parent = parent;
        parent->left = node;
    } else {
        assert(node->parent->left == NULL && node->parent->right == NULL); //TIRAR
        node->parent  = parent;
        parent->right = node;
    }
}

Node* _search(Node *root, int64_t key) {
    Node *parent = NULL, *node = root;

    while (node != NULL && node->entry_.key_ != key) {
        parent = node;

        if (key < node->entry_.key_)
            node = node->left;
        else
            node = node->right;
    }

    return node != NULL ? node : parent;
}

const void *const bst_search(const BinarySearchTree *const bst, int64_t key) {
    assert(bst != NULL);

    Node *node = _search(bst->root_, key);

    if (node != NULL && node->entry_.key_ == key)
        return (const void *const) node->entry_.value_;

    return NULL;
}

void _remove(Node *root, int64_t key) {
    Node *node = _search(root, key);

    if (node != NULL && node->entry_.key_ == key) {
        if (node->left == NULL && node->right == NULL) {
            if (node->parent == NULL) {
                bst->root_ = NULL; //IT'S NECESSARY MODIFIER THE POINTER OF ROOT IN THE BST, I THINK RETHINKING ALL!!!
            } else {

            }
            if (node == node->parent->left)
                node->parent->left  = NULL;
            else
                node->parent->right = NULL;
        } else if (node->left != NULL && node->right == NULL) {
            node->left->parent  = node->parent;

            if (node == node->parent->left)
                node->parent->left  = node->left;
            else
                node->parent->right = node->left;
        } else if (node->left == NULL && node->right != NULL) {
            node->right->parent  = node->parent;

            if (node == node->parent->left)
                node->parent->left  = node->right;
            else
                node->parent->right = node->right;
        } else {
            void *removed_value = node->entry_.value_;
            Node *succ = _successor(node);
            assert(succ != NULL);

            node->entry_.key_   = succ->entry_.key_;
            node->entry_.value_ = succ->entry_.value_;

            succ->entry_.value_ = removed_value;

            _remove(node->right, key);

            node = NULL;
        }

        node_free(node);
    }
}

void bst_remove(BinarySearchTree *const bst, int64_t key) {
    assert(bst != NULL);

    _remove(bst->root_, key);
}

Node* _successor(const Node *const node) {
    Node *succ = NULL;

    if (node == NULL)
        return NULL;

    succ = node->right;

    if (succ != NULL) {
        while (succ->left != NULL)
            succ = succ->left;
    } else {
        Node *parent = node->parent, *child = node;

        while (parent != NULL && child == parent->right) {
           child = parent;
           parent = child->parent;
        }

        succ = parent;
    }

    return succ;
}

int64_t* bst_successor(const BinarySearchTree *const bst, int64_t key) {
    assert(bst != NULL);

    int64_t *result = NULL;
    Node *node = _search(bst->root_, key);
    Node *succ = _successor(node);

    if (succ != NULL) {
        result = (int64_t*) malloc(sizeof(int64_t));
        assert(result != NULL);

        *result = succ->entry_.key_;
    }

    return result;
}

void node_free(Node *node) {
    if (node != NULL) {
        if (node->entry_.value_ != NULL)
            free(node->entry_.value_);

        free(node);
    }
}

void bckt_free(Bucket *bckt) {
    int i;

    assert (bckt != NULL);

    for (i = 0; i < bckt->amount_; i++)
        free(bckt->entries_[i]);

    free(bckt->entries_);
    free(bckt);
}

void eht_free(ExtensibleHashTable *eht) {
    int i;

    assert (eht != NULL);

    for (i = 0; i < (int) pow(2, eht->directory_.global_depth_); i++) {
        if (eht->directory_.buckets_[i] != NULL) {
            int index = ((int) pow(2, eht->directory_.global_depth_ - 1)) + i;

            if (index < (int) pow(2, eht->directory_.global_depth_) && eht->directory_.buckets_[i] == eht->directory_.buckets_[index])
                eht->directory_.buckets_[index] = NULL;

            bckt_free(eht->directory_.buckets_[i]);
        }
    }

    free(eht->directory_.buckets_);
    free(eht);
}

