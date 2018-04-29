#include <set/static_set.h>

#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

//reference: http://c-faq.com/misc/bitsets.html

#define BITMASK(b)      ( 1 << ((b) % CHAR_BIT)             )
#define BITSLOT(b)      ( (b) / CHAR_BIT                    )
#define BITSET(a, b)    ( (a)[BITSLOT(b)] |= BITMASK(b)     )
#define BITCLEAR(a, b)  ( (a)[BITSLOT(b)] &= ~BITMASK(b)    )
#define BITTEST(a, b)   ( (a)[BITSLOT(b)] & BITMASK(b)      )
#define BITNSLOTS(nb)   ( (nb + CHAR_BIT - 1) / CHAR_BIT    )

typedef unsigned char byte_t; // 1 byte = 8 bits!

//struct static_set_entry {
//    size_t id_;
//    char *element_;
//};

struct static_set_t {
    size_t number_of_elements_, number_of_bytes_;
    char **elements;
    byte_t *bytes_;
};


StaticSet* static_set_create(size_t number_of_elements, char **elements) {
    assert(elements != NULL);

    size_t i;

    StaticSet* sset = (StaticSet*) malloc(sizeof(StaticSet));

    assert(sset != NULL);

    sset->number_of_elements_ = number_of_elements;
    sset->number_of_bytes_    = (number_of_elements + 7)/8;
    sset->elements            = elements;
    sset->bytes_              = (byte_t*) calloc(sset->number_of_elements_, sizeof(byte_t));

    assert(sset->bytes_ != NULL);

    return sset;
}

void static_set_insert(StaticSet *const sset, const char *const element) {
    assert(sset != NULL && element != NULL);

    size_t i;

    for (i = 0; i < sset->number_of_elements_ && strcmp(element, sset->elements[i]) != 0; i++);

    if (i < sset->number_of_elements_)
        BITSET(sset->bytes_, i);
}

void static_set_remove(StaticSet *const sset, const char *const element) {
    assert(sset != NULL && element != NULL);

    size_t i;

    for (i = 0; i < sset->number_of_elements_ && strcmp(element, sset->elements[i]) != 0; i++);

    if (i < sset->number_of_elements_)
        BITCLEAR(sset->bytes_, i);
}

void same_elements(const StaticSet *const left_sset, const StaticSet *const right_sset) {
    assert(left_sset != NULL && right_sset != NULL && left_sset->number_of_elements_ == right_sset->number_of_elements_);

    size_t i;

    for (i = 0; i < left_sset->number_of_elements_ && strcmp(left_sset->elements[i], right_sset->elements[i]) == 0; i++);

    assert(i == left_sset->number_of_elements_);
}

StaticSet* static_set_union(const StaticSet *const left_sset, const StaticSet *const right_sset) {
    assert(left_sset != NULL && right_sset != NULL);

    same_elements(left_sset, right_sset);

    size_t i;

    StaticSet *result_sset = static_set_create(left_sset->number_of_elements_, left_sset->elements);

    for (i = 0; i < result_sset->number_of_bytes_; i++)
        result_sset->bytes_[i] = left_sset->bytes_[i] | right_sset->bytes_[i];

    return result_sset;
}

StaticSet* static_set_intersect(const StaticSet *const left_sset, const StaticSet *const right_sset) {
    assert(left_sset != NULL && right_sset != NULL);

    same_elements(left_sset, right_sset);

    size_t i;

    StaticSet *result_sset = static_set_create(left_sset->number_of_elements_, left_sset->elements);

    for (i = 0; i < result_sset->number_of_bytes_; i++)
        result_sset->bytes_[i] = left_sset->bytes_[i] & right_sset->bytes_[i];

    return result_sset;
}

StaticSet* static_set_difference(const StaticSet *const left_sset, const StaticSet *const right_sset) {
    assert(left_sset != NULL && right_sset != NULL);

    same_elements(left_sset, right_sset);

    size_t i;

    StaticSet *result_sset = static_set_create(left_sset->number_of_elements_, left_sset->elements);

    for (i = 0; i < result_sset->number_of_bytes_; i++)
        result_sset->bytes_[i] = left_sset->bytes_[i] & ~right_sset->bytes_[i];

    return result_sset;
}

StaticSet* static_set_complement(const StaticSet *const sset) {
    assert(sset != NULL);

    size_t i;

    StaticSet *result_sset = static_set_create(sset->number_of_elements_, sset->elements);

    for (i = 0; i < result_sset->number_of_bytes_; i++)
        result_sset->bytes_[i] = ~sset->bytes_[i];

    for (i = 0; i < 8 * result_sset->number_of_bytes_ - result_sset->number_of_elements_; i++)
        BITCLEAR(result_sset->bytes_, sset->number_of_elements_ + i);

    return result_sset;
}

int8_t static_set_is_subset(const StaticSet *const left_sset, const StaticSet *const right_sset) {
    assert(left_sset != NULL && right_sset != NULL);

    same_elements(left_sset, right_sset);

    size_t i;

    StaticSet *union_sset = static_set_union(left_sset, right_sset);

    for (i = 0; i < union_sset->number_of_bytes_ && union_sset->bytes_[i] == right_sset->bytes_[i]; i++);

    return i != union_sset->number_of_bytes_ ? 0 : 1;
}

int8_t static_set_is_equal(const StaticSet *const left_sset, const StaticSet *const right_sset) {
    assert(left_sset != NULL && right_sset != NULL);

    same_elements(left_sset, right_sset);

    size_t i;

    for (i = 0; i < left_sset->number_of_bytes_ && left_sset->bytes_[i] == right_sset->bytes_[i]; i++);

    return i != left_sset->number_of_bytes_ ? 0 : 1;
}

int8_t static_set_is_in(const StaticSet *const sset, const char *const element) {
    assert(sset != NULL && element != NULL);

    size_t i;

    for (i = 0; i < sset->number_of_elements_ && strcmp(element, sset->elements[i]) != 0; i++);

    return BITTEST(sset->bytes_, i);
}

size_t static_set_get_size(const StaticSet *const sset) {
    assert(sset != NULL);

    size_t i, size = 0;

    for (i = 0; i < sset->number_of_bytes_; i++) {
        byte_t byte = sset->bytes_[i];

        while (byte) {
            size  += byte & 1;
            byte >>= 1;
        }
    }

    return size;
}

void static_set_free(StaticSet *sset) {
    assert(sset != NULL);

    free(sset->bytes_);
    free(sset);
}
