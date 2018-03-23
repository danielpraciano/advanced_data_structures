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
    compare_function compare_f;
    free_function free_f;

    SinglyLinkedList **entries; // collision using linked list
};

void* sht_get_key(const Entry *const sht_entry) {
    assert (sht_entry != NULL);

    return sht_entry->key;
}

void* sht_get_value(const Entry *const sht_entry) {
    assert (sht_entry != NULL);

    return sht_entry->value;
}

int32_t sht_get_size(const StaticHashTable *const sht) {
    assert (sht != NULL);

    return sht->size;
}

StaticHashTable *sht_create(int32_t size, hash_function hash_f, compare_function compare_f, free_function free_f) {
    int i;
    StaticHashTable *sht = malloc(sizeof(StaticHashTable));

    assert(sht != NULL);

    sht->size       = size;
    sht->hash_f     = hash_f;
    sht->compare_f  = compare_f;
    sht->free_f     = free_f;
    sht->entries    = calloc((size_t) size, sizeof(SinglyLinkedList*));

    assert(sht->entries != NULL);

    for (i = 0; i < size; i++)
        sht->entries[i] = singly_create();

    return sht;
}

void sht_insert(StaticHashTable *sht, const void *const key, const void *const value) {
    int32_t hash_key = (*(sht->hash_f))(sht, key);

    assert(hash_key >= 0);
    assert(hash_key < sht->size);

    SinglyLinkedList *list = sht->entries[hash_key];

    //Verificar se ja existe tal chave...

    Entry *entry = malloc(sizeof(Entry));

//    entry->key   = key;
//    entry->value = value;

    entry->key   = (void*) key;
    entry->value = (void*) value;

    sht->entries[hash_key] = singly_insert(list, (void*) entry);
}

const void *const sht_search(const StaticHashTable *const sht, const void *const key) {
    int32_t hash_key = (*(sht->hash_f))(sht, key);

    assert(hash_key >= 0);
    assert(hash_key < sht->size);

    SinglyLinkedList *list = sht->entries[hash_key];

//    SinglyLinkedList *element = singly_search(list, sht->compare_f, key);
    SinglyLinkedList *element = singly_search(list, sht->compare_f, (void*) key);

//    while (element != NULL) {
//        sht_get_key(singly_get_datum(element));
//    }

    if (element != NULL)
        return sht_get_value(singly_get_datum(element));

    return NULL;

}

void sht_remove(StaticHashTable *sht, const void *const key) {
//    void *value = sht_search(sht, key);
    void *value = (void*) sht_search(sht, (void*) key);

    if (value != NULL) {
        int32_t hash_key = (*(sht->hash_f))(sht, key);

        assert(hash_key >= 0);
        assert(hash_key < sht->size);

        SinglyLinkedList *list = sht->entries[hash_key];

        sht->entries[hash_key] = singly_iterative_remove(list, sht->compare_f, value);
    }
}

void sht_free(StaticHashTable *sht) {
    int i;

    for (i = 0; i < sht->size; i++)
        singly_free(sht->entries[i]);

    free(sht);

}
