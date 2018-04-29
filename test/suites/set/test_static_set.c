#include <set/static_set.h>

#include <stdio.h>
#include <stdlib.h>

// Procedimento para limpar o buffer do teclado.
void descarregar() {
    char ch;

    ch = getchar();
    while (ch != '\n' && ch != EOF)
        ch = getchar();
}

int main(int argc, char *argv[]) {
    int n = 5, i;
    const char *const adt_name = "Static Set";
    char **elements;
    StaticSet *set1, *set2, *set3;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    elements = (char**) malloc(n * sizeof(char*));

    for (i = 0; i < n; i++) {
        elements[i] = (char*) calloc(255, sizeof(char));

        printf("Enter the element %d: ", i);
        scanf("%s", elements[i]);
        descarregar();
    }

    printf("Creating 3 %s...\n", adt_name);

    set1 = static_set_create(n, elements);
    set2 = static_set_create(n, elements);
    set3 = static_set_create(n, elements);

    printf("3 %s created...\n", adt_name);

    printf("Inserting element 0 into set 1...\n");

    static_set_insert(set1, elements[0]);

    printf("Element 0 was inserted into set 1...\n");

    printf("Inserting element 1 into set 1...\n");

    static_set_insert(set1, elements[1]);

    printf("Element 1 was inserted into set 1...\n");

    printf("Inserting element 0 into set 2...\n");

    static_set_insert(set2, elements[0]);

    printf("Element 0 was inserted into set 2...\n");

    printf("Inserting element 1 into set 2...\n");

    static_set_insert(set2, elements[1]);

    printf("Element 1 was inserted into set 2...\n");

    printf("Inserting element 0 into set 3...\n");

    static_set_insert(set3, elements[0]);

    printf("Element 0 was inserted into set 3...\n");

    printf("Inserting element 1 into set 3...\n");

    static_set_insert(set3, elements[1]);

    printf("Element 1 was inserted into set 3...\n");

    printf("Verifying if the element 1 is in set 2\n");

    if (static_set_is_in(set2, elements[1]))
        printf("The element 1 is in set 2!\n");
    else
        printf("The element 1 ISN'T in set 2!\n");

    printf("Verifying if the element 2 is in set 2\n");

    if (static_set_is_in(set2, elements[2]))
        printf("The element 2 is in set 2!\n");
    else
        printf("The element 2 ISN'T in set 2!\n");

    printf("Verifying if set 1 and 2 are equals\n");

    if (static_set_is_equal(set1, set2))
        printf("Set 1 and 2 are equals!\n");
    else
        printf("Set 1 and 2 AREN'T equals!\n");

    printf("Removing element 0 of set 2\n");

    static_set_remove(set2, elements[0]);

    printf("Element 0 was removed from set 2!\n");

    printf("Verifying if set 1 and 2 are equals\n");

    if (static_set_is_equal(set1, set2))
        printf("Set 1 and 2 are equals!\n");
    else
        printf("Set 1 and 2 AREN'T equals!\n");

    printf("The union of sets 1 and 2 will be equals to set 3\n");

    printf("Verifying if union of the set 1 and 2 is equal to set 3\n");

    if (static_set_is_equal(static_set_union(set1, set2), set3))
        printf("The union of the set 1 and 2 is equal to set 3!\n");
    else
        printf("The union of the set 1 and 2 ISN'T equal to set 3!\n");

    printf("The intersect of sets 1 and 2 will not be equals to set 3\n");

    printf("Verifying if intersect of the set 1 and 2 isn't equal to set 3\n");

    if (static_set_is_equal(static_set_intersect(set1, set2), set3))
        printf("The intersect of the set 1 and 2 is equal to set 3!\n");
    else
        printf("The intersect of the set 1 and 2 ISN'T equal to set 3!\n");

    printf("The difference of sets 1 and 2 will be a subset of set 3\n");

    printf("Verifying if difference of the set 1 and 2 is a subset of set 3\n");

    if (static_set_is_subset(static_set_difference(set1, set2), set3))
        printf("The difference of the set 1 and 2 is a subset of set 3!\n");
    else
        printf("The difference of the set 1 and 2 ISN'T a subset of set 3!\n");

    printf("The set 1 needs to be a subset of the complement of the empty set.\n");

    if (static_set_is_subset(set1, static_set_complement(static_set_create(n, elements))))
        printf("The set 1 is a subset of the complement of the empty set!\n");
    else
        printf("The set 1 ISN'T a subset of the complement of the empty set!\n");

    printf("The number of elements in set 1, 2, 3 and the complement of empty set, respectively, is %d, %d, %d, %d.\n",
           static_set_get_size(set1), static_set_get_size(set2), static_set_get_size(set3),
           static_set_get_size(static_set_complement(static_set_create(n, elements))));

    printf("Finally, freeing %s...\n", adt_name);

    static_set_free(set1);
    static_set_free(set2);
    static_set_free(set3);

    printf("3 %s were freed...\n", adt_name);

    return EXIT_SUCCESS;
}
