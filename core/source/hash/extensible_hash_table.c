#include <hash/extensible_hash_table.h>

#include <assert.h>
#include <stdlib.h>
#include <math.h>

#include <byte.h>


struct ext_ht_entry {
    void *key;
    void *value;
};

struct ext_ht_bucket {
    int32_t local_depth_, amount_;
//    Entry *const *entries_; //funfa??
    Entry **entries_; //funfa??
};

struct ext_ht_directory {
    int32_t global_depth_;
    Bucket **buckets_;
};

struct ext_ht {
    int32_t max_per_bucket_;
    hash_function hash_f_;
    compare_function compare_f_;
    free_function free_f_;

    Directory directory_;
};


Bucket* bckt_create(int32_t local_depth, int32_t max_entries_amount) {
    Bucket *bckt = (Bucket*) malloc(sizeof(Bucket));

    assert(bckt != NULL);

    bckt->local_depth_ = local_depth;

    bckt->amount_  = 0;
//    bckt->entries_ = (Entry *const *) malloc(max_entries_amount * sizeof(Entry*));
    bckt->entries_ = (Entry **) malloc(max_entries_amount * sizeof(Entry*));

    assert(bckt->entries_ != NULL);

    return bckt;
}

ExtensibleHashTable* eht_create(int32_t max_per_bucket, hash_function hash_f, compare_function compare_f, free_function free_f) {
    int i;
    ExtensibleHashTable *eht = malloc(sizeof(ExtensibleHashTable));

    assert(eht != NULL);

    eht->max_per_bucket_       = max_per_bucket;
    eht->hash_f_               = hash_f;
    eht->compare_f_            = compare_f;
    eht->free_f_               = free_f;

    Directory dir;

    dir.global_depth_ = 1;
    dir.buckets_      = (Bucket**) malloc(2 * sizeof(Bucket*));

    assert(dir.buckets_ != NULL);

    dir.buckets_[1] = dir.buckets_[0] = bckt_create(0, max_per_bucket);

    eht->directory_    = dir;

    return eht;
}

void bckt_insert(Bucket *const bckt, const void *const key, const void *const value) {
    assert(bckt != NULL && key != NULL && value != NULL);

    Entry *entry = (Entry*) malloc(sizeof(Entry));

    assert(entry != NULL);

    entry->key   = key; //MUDAR DEPOIS, PRECISO SABER O TAMANHO DE KEY/VALUE PARA FAZER MEMCPY
    entry->value = value;

    bckt->entries_[bckt->amount_] = entry;

    bckt->amount_++;
}

void dir_double(Directory *const dir) {
    int i;
    size_t old_size = (size_t) pow(2, dir->global_depth_++);
    size_t new_size = (size_t) pow(2, dir->global_depth_);

    dir->buckets_ = (Bucket**) realloc(dir->buckets_, new_size * sizeof(Bucket*));

    assert (dir->buckets_ != NULL);

    for (i = 0; i < old_size; i++)
        dir->buckets_[old_size + i] = dir->buckets_[i];
}

void eht_recursive_split(ExtensibleHashTable *const eht, int32_t bckt_to_split_index) {
    int32_t i, j;
    Bucket *split_bckt      = eht->directory_.buckets_[bckt_to_split_index];
    Bucket *new_bckt        = bckt_create(++(split_bckt->local_depth_), eht->max_per_bucket_);
    int32_t index_to_update = ((int32_t) pow(2, eht->directory_.global_depth_ - 1)) + bckt_to_split_index;

    if (index_to_update >= (int32_t) pow(2, eht->directory_.global_depth_))
        index_to_update = bckt_to_split_index - (int32_t) pow(2, eht->directory_.global_depth_ - 1);

    eht->directory_.buckets_[index_to_update] = new_bckt;

    for (i = 0; i < split_bckt->amount_; i++) {
        int32_t hash_key   = (*(eht->hash_f_))(eht, split_bckt->entries_[i]->key);
        int32_t bckt_index = get_k_LSB(hash_key, eht->directory_.global_depth_);

        if (bckt_index != bckt_to_split_index) {
            assert(bckt_index == index_to_update);

            new_bckt->entries_[new_bckt->amount_++] = split_bckt->entries_[i];

            for (j = i + 1; j < split_bckt->amount_; j++)
                split_bckt->entries_[j - 1] =  split_bckt->entries_[j];

            split_bckt->amount_--;
        }
    }
}

void eht_insert(ExtensibleHashTable *eht, const void *const key, const void *const value) {
    int32_t hash_key   = (*(eht->hash_f_))(eht, key);
    int32_t bckt_index = get_k_LSB(hash_key, eht->directory_.global_depth_);

    assert(bckt_index >= 0); // I think this isn't necessary, but...
    assert(bckt_index < (int32_t) pow(2, eht->directory_.global_depth_));

    if (eht->directory_.buckets_[bckt_index]->amount_ == eht->max_per_bucket_) {
        if (eht->directory_.buckets_[bckt_index]->local_depth_ == eht->directory_.global_depth_) {
            dir_double(&eht->directory_);
        }

        eht_recursive_split(eht, bckt_index);
        eht_insert(eht, key, value);
    } else {
        bckt_insert(eht->directory_.buckets_[bckt_index], key, value);
    }
}

const Entry* bckt_search(const Bucket *const bckt, compare_function compare_f, const void *const key) {
    int i;
    const Entry* entry = NULL;

    for (i = 0; i < bckt->amount_ && entry == NULL; i++) {
        if ( (*compare_f)(bckt->entries_[i]->key, key) == 0 )
            entry = bckt->entries_[i]; //const Entry*
    }

    return entry;
}

const void *const eht_search(const ExtensibleHashTable *const eht, const void *const key) {
    int32_t hash_key   = (*(eht->hash_f_))(eht, key);
    int32_t bckt_index = get_k_LSB(hash_key, eht->directory_.global_depth_);

    assert(bckt_index >= 0); // I think this isn't necessary, but...
    assert(bckt_index < (int32_t) pow(2, eht->directory_.global_depth_));

    const Entry *entry = bckt_search(eht->directory_.buckets_[bckt_index], eht->compare_f_, key);

    if (entry != NULL)
        return entry->value; //const void *const

    return NULL;

}

void bckt_remove(Bucket *const bckt, compare_function compare_f, const void *const key) {
    int i, j;

    for (i = 0; i < bckt->amount_ && (*compare_f)(bckt->entries_[i]->key, key) != 0; i++);

    if (i < bckt->amount_) {
        free(bckt->entries_[i]);

        for (j = i + 1; j < bckt->amount_; j++)
            bckt->entries_[j - 1] = bckt->entries_[j];

        bckt->amount_--;
    }
}

void eht_remove(ExtensibleHashTable *eht, const void *const key) {
    const void *value = eht_search(eht, key);

    if (value != NULL) {
        int32_t hash_key   = (*(eht->hash_f_))(eht, key);
        int32_t bckt_index = get_k_LSB(hash_key, eht->directory_.global_depth_);

        bckt_remove(eht->directory_.buckets_[bckt_index], eht->compare_f_, key);
    }
}

void bckt_free(Bucket *bckt) {
    int i;

    assert (bckt != NULL);

    for (i = 0; i < bckt->amount_; i++)
        free(bckt->entries_[i]);

    free(bckt->entries_);
    free(bckt);
}

void eht_free(ExtensibleHashTable *eht) {
    int i;

    assert (eht != NULL);

    for (i = 0; i < (int) pow(2, eht->directory_.global_depth_); i++) {
        if (eht->directory_.buckets_[i] != NULL) {
            int index = ((int) pow(2, eht->directory_.global_depth_ - 1)) + i;

            if (index < (int) pow(2, eht->directory_.global_depth_) && eht->directory_.buckets_[i] == eht->directory_.buckets_[index])
                eht->directory_.buckets_[index] = NULL;

            bckt_free(eht->directory_.buckets_[i]);
        }
    }

    free(eht->directory_.buckets_);
    free(eht);
}
