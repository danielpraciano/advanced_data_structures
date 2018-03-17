#include <hash/static_hash_table.h>

#include <assert.h>
#include <stdlib.h>

#include <lists/singly_linked_list.h>

struct static_ht_entry {
    void *key;
    void *value;
};

struct static_ht {
    int32_t size;
    hash_function hash_f;
    free_function free_f;
    SinglyLinkedList **entries; // collision using linked list
};

StaticHashTable *sht_create(int32_t size, hash_function hash_f, free_function free_f) {
    StaticHashTable *sht = malloc(sizeof(StaticHashTable));

    assert(sht != NULL);

    sht->size    = size;
    sht->hash_f  = hash_f;
    sht->free_f  = free_f;
    sht->entries = calloc((size_t) size, sizeof(SinglyLinkedList*));

    assert(sht->entries != NULL);

    return sht;
}

void sht_insert(StaticHashTable *sht, const void *const key, const void *const value) {
    int32_t hash_key = (*(sht->hash_f))(sht, key);

    assert(hash_key >= 0);
    assert(hash_key < sht->size);

    SinglyLinkedList *list = sht->entries[hash_key];

    //Verificar se ja existe tal chave...

    Entry *entry = malloc(sizeof(Entry));

    entry->key   = key;
    entry->value = value;

    sht->entries[hash_key] = singly_insert(list, (void*) entry);
}

//const void *const sht_search(const StaticHashTable *const sht, const void *const key);

//void sht_remove(StaticHashTable *sht, const void *const key);

//void sht_free(StaticHashTable *sht, free_function free_f);
