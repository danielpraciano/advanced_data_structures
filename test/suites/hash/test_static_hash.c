#include <stdio.h>
#include <stdlib.h>

#include <hash/static_hash_table.h>

int32_t hash_int(const StaticHashTable *const sht, const void *const key) {
    int32_t *key_int = (int32_t*) key;

    return *key_int % sht_get_size(sht);
}

int compare_int(const void *const left, const void *const right) {
    Entry *left_entry  = (Entry*) left;
//    Entry *right_entry = (Entry*) right;

    int32_t left_int  = *((int*) sht_get_key(left_entry));
    int32_t right_int = *((int*) right);

    if (left_int < right_int)
        return -1;

    if (left_int == right_int)
        return 0;

    return 1;
}

void free_int(StaticHashTable *sht) {
    //???
}

int main(int argc, char *argv[]) {
    int n = 5;
    const char *const hash_type = "Static Hash";
    void *key, *value;

    printf("Enter the param n: ");
    scanf("%d", &n);

    printf("Creating %s...\n", hash_type);

    StaticHashTable *hash = sht_create(n, hash_int, compare_int, free_int);

    printf("%s created...\n", hash_type);

    printf("Inserting key 1 and value 1 into %s...\n", hash_type);

    key = malloc(sizeof(int));
    value = malloc(sizeof(int));

    (*(int*) key) = 1;
    (*(int*) value) = 1;

    sht_insert(hash, key, value);

    printf("Key 1 and value 1 was inserted into %s...\n", hash_type);

    printf("Inserting key 2 and value 2 into %s...\n", hash_type);

    key = malloc(sizeof(int));
    value = malloc(sizeof(int));

    (*(int*) key) = 2;
    (*(int*) value) = 2;

    sht_insert(hash, key, value);

    printf("Key 2 and value 2 was inserted into %s...\n", hash_type);

    printf("Inserting key 3 and value 3 into %s...\n", hash_type);

    key = malloc(sizeof(int));
    value = malloc(sizeof(int));

    (*(int*) key) = 3;
    (*(int*) value) = 3;

    sht_insert(hash, key, value);

    printf("Key 3 and value 3 was inserted into %s...\n", hash_type);

    printf("Inserting key 4 and value 4 into %s...\n", hash_type);

    key = malloc(sizeof(int));
    value = malloc(sizeof(int));

    (*(int*) key) = 4;
    (*(int*) value) = 4;

    sht_insert(hash, key, value);

    printf("Key 4 and value 4 was inserted into %s...\n", hash_type);

    printf("Inserting key 5 and value 5 into %s...\n", hash_type);

    key = malloc(sizeof(int));
    value = malloc(sizeof(int));

    (*(int*) key) = 5;
    (*(int*) value) = 5;

    sht_insert(hash, key, value);

    printf("Key 5 and value 5 was inserted into %s...\n", hash_type);

    printf("Inserting key 6 and value 6 into %s...\n", hash_type);

    key = malloc(sizeof(int));
    value = malloc(sizeof(int));

    (*(int*) key) = 6;
    (*(int*) value) = 6;

    sht_insert(hash, key, value);

    printf("Key 6 and value 6 was inserted into %s...\n", hash_type);

    printf("Searching key 6 in %s...\n", hash_type);

    key = malloc(sizeof(int));
    value = malloc(sizeof(int));

    (*(int*) key) = 6;
    value = sht_search(hash, key);

    if (value != NULL) {
        printf("Key 6 was found and its value is %d in %s...\n", (*(int32_t*) value), hash_type);
    } else {
        printf("Key 6 wasn't found in %s...\n", hash_type);
    }

    printf("Searching key 7 in %s...\n", hash_type);

    (*(int*) key) = 7;
    value = sht_search(hash, key);

    if (value != NULL) {
        printf("Key 7 was found and its value is %d in %s...\n", (*(int32_t*) value), hash_type);
    } else {
        printf("Key 7 wasn't found in %s...\n", hash_type);
    }

    printf("Searching key 1 in %s...\n", hash_type);

    (*(int*) key) = 1;
    value = sht_search(hash, key);

    if (value != NULL) {
        printf("Key 1 was found and its value is %d in %s...\n", (*(int32_t*) value), hash_type);
    } else {
        printf("Key 1 wasn't found in %s...\n", hash_type);
    }

    printf("Removing key 1 in %s...\n", hash_type);

    sht_remove(hash, key);

    printf("Key 1 and value 1 was removed...\n", hash_type);

    printf("Searching key 1 in %s...\n", hash_type);

    (*(int*) key) = 1;
    value = sht_search(hash, key);

    if (value != NULL) {
        printf("Key 1 was found and its value is %d in %s...\n", (*(int32_t*) value), hash_type);
    } else {
        printf("Key 1 wasn't found in %s...\n", hash_type);
    }

    printf("Finally, freeing %s...\n", hash_type);

    sht_free(hash);

    printf("%s was freed...\n", hash_type);

    return EXIT_SUCCESS;
}
