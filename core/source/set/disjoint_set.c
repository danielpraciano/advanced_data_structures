#include <set/disjoint_set.h>

#include <stdlib.h>
#include <assert.h>

#define ROOT_VALUE 0

struct disjoint_set_t {
    size_t number_of_elements_;
    size_t *partitions_;
};


DisjointSet* disjoint_set_create(size_t number_of_elements) {
    assert(number_of_elements > 0);

    DisjointSet* dset = (DisjointSet*) malloc(sizeof(DisjointSet));

    assert(dset != NULL);

    dset->number_of_elements_ = number_of_elements;
    dset->partitions_         = (size_t*) calloc(number_of_elements + 1, sizeof(size_t));

    assert(dset->partitions_ != NULL);

    // NOTE: As partitions are initialized with zeros, then
    // they are already ROOT_VALUE (since ROOT_VALUE is zero).
    // Furthermore, partitions[0] doesn't matter for us!

    return dset;
}

size_t disjoint_set_find(const DisjointSet *const dset, size_t element) {
    assert(dset != NULL && element > 0 && element <= dset->number_of_elements_);

    if (dset->partitions_[element] == ROOT_VALUE)
        return element;

    return disjoint_set_find(dset, dset->partitions_[element]);
}

DisjointSet* disjoint_set_union(const DisjointSet *const dset, size_t lhs, size_t rhs) {
    assert(dset != NULL);
    assert(lhs > 0 && lhs <= dset->number_of_elements_);
    assert(rhs > 0 && rhs <= dset->number_of_elements_);

    size_t i, lhs_rep, rhs_rep;

    DisjointSet *result_dset = disjoint_set_create(dset->number_of_elements_);

    for (i = 1; i <= result_dset->number_of_elements_; i++)
        result_dset->partitions_[i] = dset->partitions_[i];

    lhs_rep = disjoint_set_find(dset, lhs);
    rhs_rep = disjoint_set_find(dset, rhs);

    result_dset->partitions_[rhs_rep] = lhs_rep;

    return result_dset;
}

int8_t disjoint_set_is_equal(const DisjointSet *const dset, size_t lhs, size_t rhs) {
    assert(dset != NULL);
    assert(lhs > 0 && lhs <= dset->number_of_elements_);
    assert(rhs > 0 && rhs <= dset->number_of_elements_);

    size_t i, lhs_rep, rhs_rep;

    lhs_rep = disjoint_set_find(dset, lhs);
    rhs_rep = disjoint_set_find(dset, rhs);

    return lhs_rep != rhs_rep ? 0 : 1;
}

void disjoint_set_free(DisjointSet *dset) {
    assert(dset != NULL);

    free(dset->partitions_);
    free(dset);
}
