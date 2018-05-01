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
    Node *parent, *left_, *right_;
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
    node->left_  = NULL;
    node->right_ = NULL;

    Node *parent = _search(bst->root_, key);

    if (parent == NULL) {
        bst->root_ = node;
    } else if (key <= parent->entry_.key_) {
        assert(node->parent->left_ == NULL && node->parent->right_ == NULL); //TIRAR
        node->parent = parent;
        parent->left_ = node;
    } else {
        assert(node->parent->left_ == NULL && node->parent->right_ == NULL); //TIRAR
        node->parent   = parent;
        parent->right_ = node;
    }
}

Node* _search(Node *root, int64_t key) {
    Node *parent = NULL, *node = root;

    while (node != NULL && node->entry_.key_ != key) {
        parent = node;

        if (key < node->entry_.key_)
            node = node->left_;
        else
            node = node->right_;
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

void bst_remove(BinarySearchTree *const bst, int64_t key) {
    assert(bst != NULL);

    Node *node = _search(bst->root_, key);

    if (node != NULL && node->entry_.key_ == key) {
        if (node->left_ == NULL && node->right_ == NULL) {
            if (node == node->parent->left_)
                node->parent->left_  = NULL;
            else
                node->parent->right_ = NULL;
        } else if (node->left_ != NULL && node->right_ == NULL) {
            node->left_->parent  = node->parent;

            if (node == node->parent->left_)
                node->parent->left_  = node->left_;
            else
                node->parent->right_ = node->left_;
        } else if (node->left_ == NULL && node->right_ != NULL) {
            node->right_->parent  = node->parent;

            if (node == node->parent->left_)
                node->parent->left_  = node->right_;
            else
                node->parent->right_ = node->right_;
        } else {
            //FALTA tratar caso quando os dois nao sao nulos, ie, existem 2 filhos!!!
        }


        if (node->parent == NULL) {
            bst->root_ = NULL;
        } else {

        }
    }

}

void eht_remove(ExtensibleHashTable *eht, const void *const key) {
    const void *value = eht_search(eht, key);

    if (value != NULL) {
        int32_t hash_key   = (*(eht->hash_f_))(eht, key);
        int32_t bckt_index = get_k_LSB(hash_key, eht->directory_.global_depth_);

        bckt_remove(eht->directory_.buckets_[bckt_index], eht->compare_f_, key);
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

