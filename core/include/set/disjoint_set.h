#pragma once

#include <stddef.h>
#include <stdint.h>


typedef struct disjoint_set_t DisjointSet;

DisjointSet* disjoint_set_create(size_t number_of_elements);

size_t disjoint_set_find(const DisjointSet *const dset, size_t element);

DisjointSet* disjoint_set_union(const DisjointSet *const dset, size_t lhs, size_t rhs);

int8_t disjoint_set_is_equal(const DisjointSet *const dset, size_t lhs, size_t rhs);

void disjoint_set_free(DisjointSet *dset);
