#pragma once

#include <stdint.h>

#include <util.h>

typedef struct static_ht_entry Entry;
typedef struct static_ht StaticHashTable;
typedef int32_t (*hash_function)(const StaticHashTable *const sht, const void *const key);
typedef void (*free_function)(StaticHashTable *sht);


void* sht_get_key(const Entry *const sht_entry);

void* sht_get_value(const Entry *const sht_entry);

int32_t sht_get_size(const StaticHashTable *const sht);

StaticHashTable *sht_create(int32_t size, hash_function hash_f, compare_function compare_f, free_function free_f);

void sht_insert(StaticHashTable *sht, const void *const key, const void *const value);

const void *const sht_search(const StaticHashTable *const sht, const void *const key);

void sht_remove(StaticHashTable *sht, const void *const key);

void sht_free(StaticHashTable *sht);
