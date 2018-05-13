#pragma once

#include <stdint.h>
#include <stdlib.h>


typedef struct bp_entry Entry;
typedef struct bp_leaf_node LeafNode;
typedef struct bp_inner_node InnerNode;
typedef struct bp_t BPlusTree;


BPlusTree* bp_create(size_t order);

void bp_insert(BPlusTree *const bp, int64_t key, const void *const value, size_t nbytes);

size_t bp_search(const BPlusTree *const bp, int64_t key, void ***values);

void bp_remove(BPlusTree *const bp, int64_t key);
