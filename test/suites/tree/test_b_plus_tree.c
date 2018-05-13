#include <stdio.h>
#include <stdlib.h>

#include <tree/b_plus_tree.h>

int main(int argc, char *argv[]) {

    const char *const tree_type = "BPlusTree";
    void *datum = malloc(sizeof(int));
    void **values;

    printf("Creating %s...\n", tree_type);

    BPlusTree *tree = bp_create(2ul);

    printf("%s created...\n", tree_type);

//    int keys[] = { 25, 5, 10, 15, 20, 30, 50, 55, 75, 80, 65, 60, 85, 90, 28, 75, 75 };

//    int i, amount = 17;

//    for (i = 0; i < amount; i++) {
//        (*(int*) datum) = keys[i];

//        bp_insert(tree, *(int*)datum, datum, sizeof(int));
//    }

//    bp_remove(tree, 75);

//    void **vals;
//    size_t n = bp_search(tree, 75, &vals);

//    printf("n = %d\n", n);

//    int **int_vals = (int**) vals;

//    for (i = 0; i < n; i++)
//        printf("v %d = %d\n", i, *int_vals[i]);

    printf("Inserting data 5 into %s...\n", tree_type);

    (*(int*) datum) = 5;

    bp_insert(tree, *(int*)datum, datum, sizeof(int));

    printf("Data 5 was inserted into %s...\n", tree_type);

    printf("Inserting data 4 into %s...\n", tree_type);

    (*(int*) datum) = 4;

    bp_insert(tree, *(int*)datum, datum, sizeof(int));

    printf("Data 4 was inserted into %s...\n", tree_type);

    printf("Inserting data 3 into %s...\n", tree_type);

    (*(int*) datum) = 3;

    bp_insert(tree, *(int*)datum, datum, sizeof(int));

    printf("Data 3 was inserted into %s...\n", tree_type);

    printf("Inserting data 2 into %s...\n", tree_type);

    (*(int*) datum) = 2;

    bp_insert(tree, *(int*)datum, datum, sizeof(int));

    printf("Data 2 was inserted into %s...\n", tree_type);

    printf("Inserting data 1 into %s...\n", tree_type);

    (*(int*) datum) = 1;

    bp_insert(tree, *(int*)datum, datum, sizeof(int));

    printf("Data 1 was inserted into %s...\n", tree_type);

    printf("Searching data 6 in %s...\n", tree_type);

    if (bp_search(tree, 6, datum))
        printf("Data 6 was found in %s...\n", tree_type);
    else
        printf("Data 6 wasn't found in %s...\n", tree_type);

    printf("Searching data 2 in %s...\n", tree_type);

    if (bp_search(tree, 2, datum))
        printf("Data 2 was found in %s...\n", tree_type);
    else
        printf("Data 2 wasn't found in %s...\n", tree_type);

    printf("Removing data 2 in %s...\n", tree_type);

    bp_remove(tree, 2);

    printf("Data 2 was removed of %s...\n", tree_type);

    printf("Searching data 2 in %s...\n", tree_type);

    if (bp_search(tree, 2, &values))
        printf("Data 2 was found in %s...\n", tree_type);
    else
        printf("Data 2 wasn't found in %s...\n", tree_type);

    printf("Searching data 1 in %s...\n", tree_type);

    if (bp_search(tree, 1, &values))
        printf("Data 1 was found in %s...\n", tree_type);
    else
        printf("Data 1 wasn't found in %s...\n", tree_type);

    printf("Removing data 4 in %s...\n", tree_type);

    bp_remove(tree, 4);

    printf("Data 4 was removed of %s...\n", tree_type);

    printf("Searching data 4 in %s...\n", tree_type);

    if (bp_search(tree, 4, &values))
        printf("Data 4 was found in %s...\n", tree_type);
    else
        printf("Data 4 wasn't found in %s...\n", tree_type);

    printf("Searching data 1 in %s...\n", tree_type);

    if (bp_search(tree, 1, &values))
        printf("Data 1 was found in %s...\n", tree_type);
    else
        printf("Data 1 wasn't found in %s...\n", tree_type);

    printf("Searching data 5 in %s...\n", tree_type);

    if (bp_search(tree, 5, &values))
        printf("Data 5 was found in %s...\n", tree_type);
    else
        printf("Data 5 wasn't found in %s...\n", tree_type);

    return EXIT_SUCCESS;
}
