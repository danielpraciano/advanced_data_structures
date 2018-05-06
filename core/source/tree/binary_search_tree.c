#include <tree/binary_search_tree.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct bst_entry {
    int64_t key_;
    void *value_;
};

struct bst_node {
    Entry *entry_;
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
    } else if (key <= parent->entry_->key_) {
        node->parent = parent;
        parent->left = node;
    } else {
        node->parent  = parent;
        parent->right = node;
    }
}

Node* _search(Node *root, int64_t key) {
    Node *parent = NULL, *node = root;

    while (node != NULL && node->entry_->key_ != key) {
        parent = node;

        if (key < node->entry_->key_)
            node = node->left;
        else
            node = node->right;
    }

    return node != NULL ? node : parent;
}

const void *const bst_search(const BinarySearchTree *const bst, int64_t key) {
    assert(bst != NULL);

    Node *node = _search(bst->root_, key);

    if (node != NULL && node->entry_->key_ == key)
        return (const void *const) node->entry_->value_;

    return NULL;
}

void _remove(Node **root, int64_t key) {
    Node *node = _search(*root, key);

    if (node != NULL && node->entry_->key_ == key) {
        if (node->left == NULL && node->right == NULL) {
            if (node->parent == NULL) {
                root = NULL;
            } else {
                if (node == node->parent->left)
                    node->parent->left  = NULL;
                else
                    node->parent->right = NULL;
            }
        } else if (node->left != NULL && node->right == NULL) {
            node->left->parent  = node->parent;

            if (node->parent == NULL) {
                root = &node->left;
            } else {
                if (node == node->parent->left)
                    node->parent->left  = node->left;
                else
                    node->parent->right = node->left;
            }
        } else if (node->left == NULL && node->right != NULL) {
            node->right->parent  = node->parent;

            if (node->parent == NULL) {
                root = &node->right;
            } else {
                if (node == node->parent->left)
                    node->parent->left  = node->right;
                else
                    node->parent->right = node->right;
            }
        } else {
            void *removed_value = node->entry_->value_;
            Node *succ = _successor(node);
            assert(succ != NULL);

            node->entry_->key_   = succ->entry_->key_;
            node->entry_->value_ = succ->entry_->value_;

            succ->entry_->value_ = removed_value;

            _remove(&succ, succ->entry_->key_);

            node = NULL;
        }

        node_free(node);
    }
}

void bst_remove(BinarySearchTree *const bst, int64_t key) {
    assert(bst != NULL);

    _remove(&bst->root_, key);
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
        Node *parent = node->parent, *child = (Node*) node;

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

        *result = succ->entry_->key_;
    }

    return result;
}

void pre_recursive_print(const Node *const node) {
    if (node != NULL) {
        printf("%d ", node->entry_->key_);
        pre_recursive_print(node->left);
        pre_recursive_print(node->right);
    }
}

void bst_pre_order_print(const BinarySearchTree *const bst) {
    printf("\n Keys in pre-order: ");
    pre_recursive_print(bst->root_);
    printf("\n");
}

void in_recursive_print(const Node *const node) {
    if (node != NULL) {
        in_recursive_print(node->left);
        printf("%d ", node->entry_->key_);
        in_recursive_print(node->right);
    }
}

void  bst_in_order_print(const BinarySearchTree *const bst) {
    printf("\n Keys in-order: ");
    in_recursive_print(bst->root_);
    printf("\n");
}

void pos_recursive_print(const Node *const node) {
    if (node != NULL) {
        pos_recursive_print(node->left);
        pos_recursive_print(node->right);
        printf("%d ", node->entry_->key_);
    }
}

void bst_pos_order_print(const BinarySearchTree *const bst) {
    printf("\n Keys in pos-order:");
    pos_recursive_print(bst->root_);
    printf("\n");
}

void node_free(Node *node) {
    if (node != NULL) {
        if (node->entry_->value_ != NULL)
            free(node->entry_->value_);

        free(node->entry_);
        free(node);
    }
}

void recursive_node_free(Node *node) {
    if (node != NULL) {
        recursive_node_free(node->left);
        recursive_node_free(node->right);
        node_free(node);
    }
}

void bst_free(BinarySearchTree *bst) {
    recursive_node_free(bst->root_);
}
