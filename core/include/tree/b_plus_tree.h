#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <util.h>

typedef struct bp_entry Entry;
typedef struct bp_leaf_node LeafNode;
typedef struct bp_inner_node InnerNode;
typedef struct bp_t BPlusTree;

//int8_t leaf_underflow(const LeafNode *const node);
//int8_t inner_underflow(const InnerNode *const node);


LeafNode* leaf_create(InnerNode *const parent, LeafNode * const right, size_t order);
InnerNode* inner_create(InnerNode *const parent, size_t order);

int8_t leaf_overflow(const LeafNode *const node, size_t order);
int8_t inner_overflow(const InnerNode *const node, size_t order);

int8_t leaf_insert(LeafNode *const node, size_t order, Entry *entry);
int8_t inner_insert(InnerNode * const node, size_t order, Entry *entry);

//void leaf_merge();
//void inner_merge();

LeafNode* leaf_split(BPlusTree *const bp, LeafNode *node);
InnerNode* inner_split(BPlusTree *const bp, InnerNode *node, Entry *entry);

void print_all_entries(BPlusTree *bp);
//void print_tree(BPlusTree *bp);


BPlusTree* bp_create(size_t order);

void bp_insert(BPlusTree *const bp, int64_t key, const void *const value, size_t nbytes);

LeafNode* _bp_search(InnerNode *root, size_t depth, int64_t key);

size_t bp_search(const BPlusTree *const bp, int64_t key, void ***values);

void _bp_remove(LeafNode *node, int64_t key);

void bp_remove(BPlusTree *const bp, int64_t key);
