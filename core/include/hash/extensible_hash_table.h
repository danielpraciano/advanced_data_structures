#pragma once

#include <stdint.h>

#include <util.h>

typedef struct ext_ht_entry Entry;
typedef struct ext_ht_bucket Bucket;
typedef struct ext_ht_directory Directory;
typedef struct ext_ht ExtensibleHashTable;
typedef int32_t (*hash_function)(const ExtensibleHashTable *const eht, const void *const key);
typedef void (*free_function)(ExtensibleHashTable *eht);


void* eht_get_key(const Entry *const eht_entry);

void* eht_get_value(const Entry *const eht_entry);

int32_t eht_get_size(const ExtensibleHashTable *const eht);



ExtensibleHashTable *eht_create(int32_t size, hash_function hash_f, compare_function compare_f, free_function free_f);

void eht_insert(ExtensibleHashTable *eht, const void *const key, const void *const value);

const void *const eht_search(const ExtensibleHashTable *const eht, const void *const key);

void eht_remove(ExtensibleHashTable *eht, const void *const key);

void eht_free(StaticHashTable *eht);
