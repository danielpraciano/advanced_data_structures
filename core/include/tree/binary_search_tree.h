#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <util.h>

typedef struct bst_entry Entry;
typedef struct bst_node Node;
typedef struct bst_t BinarySearchTree;
typedef void (*free_function_ptr)(BinarySearchTree *bst);
typedef void (*callback_function_ptr)(Node *node);

BinarySearchTree* bst_create(free_function_ptr free_f_ptr);

void bst_insert(BinarySearchTree *const bst, int64_t key, const void *const value, size_t nbytes);

Node* _search(Node *root, int64_t key);

const void *const bst_search(const BinarySearchTree *const bst, int64_t key);

void bst_remove(BinarySearchTree *const bst, int64_t key);

Node* _successor(const BinarySearchTree *const bst, int64_t key);

int64_t bst_successor(const BinarySearchTree *const bst, int64_t key);

void pre_order_visit(BinarySearchTree *bst, callback_function_ptr callback_f_ptr);
void  in_order_visit(BinarySearchTree *bst, callback_function_ptr callback_f_ptr);
void pos_order_visit(BinarySearchTree *bst, callback_function_ptr callback_f_ptr);

void bst_free(BinarySearchTree *bst);
