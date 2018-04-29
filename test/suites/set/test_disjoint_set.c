#include <set/disjoint_set.h>

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    size_t n = 5, element;
    const char *const adt_name = "Disjoint Set";

    DisjointSet *set1, *set2, *set3;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Creating %s...\n", adt_name);

    set1 = disjoint_set_create(n);

    printf("%s created...\n", adt_name);

    printf("Applying find in element 1 of set 1...\n");

    element = disjoint_set_find(set1, 1);

    printf("The result of find is %d...\n", element);

    printf("set 2 = Union of elements 2 and 1 of set 1...\n");

    set2 = disjoint_set_union(set1, 2, 1);

    printf("Applying find in element 1 of set 2...\n");

    element = disjoint_set_find(set2, 1);

    printf("The result of find is %d...\n", element);

    printf("Verifying if element 1 and 2 belong to same partition of set2...\n");

    if (disjoint_set_is_equal(set2, 1, 2))
        printf("The element 1 is in the same partition of 2 in set2!\n");
    else
        printf("The element 1 ISN'T in the same partition of 2 in set2!\n");

    printf("Verifying if element 2 and 3 belong to same partition of set2...\n");

    if (disjoint_set_is_equal(set2, 2, 3))
        printf("The element 2 is in the same partition of 3 in set2!\n");
    else
        printf("The element 2 ISN'T in the same partition of 3 in set2!\n");

    printf("set 3 = Union of elements 1 and 3 of set 2...\n");

    set3 = disjoint_set_union(set2, 1, 3);

    printf("Verifying if element 2 and 3 belong to same partition of set3...\n");

    if (disjoint_set_is_equal(set3, 2, 3))
        printf("The element 2 is in the same partition of 3 in set3!\n");
    else
        printf("The element 2 ISN'T in the same partition of 3 in set3!\n");

    printf("Finally, freeing %s...\n", adt_name);

    disjoint_set_free(set1);
    disjoint_set_free(set2);
    disjoint_set_free(set3);

    printf("3 %s were freed...\n", adt_name);

    return EXIT_SUCCESS;
}
