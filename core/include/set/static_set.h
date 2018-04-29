#pragma once

#include <stddef.h>
#include <stdint.h>


//typedef struct static_set_entry Entry;
typedef struct static_set_t StaticSet;

StaticSet* static_set_create(size_t number_of_elements, char **elements);

void static_set_insert(StaticSet *const sset, const char *const element);

void static_set_remove(StaticSet *const sset, const char *const element);

StaticSet* static_set_union(const StaticSet *const left_sset, const StaticSet *const right_sset);

StaticSet* static_set_intersect(const StaticSet *const left_sset, const StaticSet *const right_sset);

StaticSet* static_set_difference(const StaticSet *const left_sset, const StaticSet *const right_sset);

StaticSet* static_set_complement(const StaticSet *const sset);

int8_t static_set_is_subset(const StaticSet *const left_sset, const StaticSet *const right_sset);

int8_t static_set_is_equal(const StaticSet *const left_sset, const StaticSet *const right_sset);

int8_t static_set_is_in(const StaticSet *const sset, const char *const element);

size_t static_set_get_size(const StaticSet *const sset);

void static_set_free(StaticSet *sset);
