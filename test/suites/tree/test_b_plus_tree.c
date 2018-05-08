#include <stdio.h>
#include <stdlib.h>

#include <tree/b_plus_tree.h>

int main(int argc, char *argv[]) {

    const char *const tree_type = "BPlusTree";
    void *datum = malloc(sizeof(int));

    printf("Creating %s...\n", tree_type);

    BPlusTree *tree = bp_create(2ul);

    printf("%s created...\n", tree_type);

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
        printf("Data 6 wasn't found in %s...\n", tree_type);
    else
        printf("Data 6 was found in %s...\n", tree_type);

    printf("Searching data 2 in %s...\n", tree_type);

    if (bp_search(tree, 2, datum))
        printf("Data 2 wasn't found in %s...\n", tree_type);
    else
        printf("Data 2 was found in %s...\n", tree_type);

//    printf("Removing data 2 in %s...\n", tree_type);

//    bst_remove(tree, 2);

//    printf("Data 2 was removed of %s...\n", tree_type);

//    printf("Searching data 2 in %s...\n", tree_type);

//    if (bst_search(tree, 2) == NULL)
//        printf("Data 2 wasn't found in %s...\n", tree_type);
//    else
//        printf("Data 2 was found in %s...\n", tree_type);

//    printf("Searching data 1 in %s...\n", tree_type);

//    if (bst_search(tree, 1) == NULL)
//        printf("Data 1 wasn't found in %s...\n", tree_type);
//    else
//        printf("Data 1 was found in %s...\n", tree_type);


//    printf("Removing data 4 in %s...\n", tree_type);

//    bst_remove(tree, 4);

//    printf("Data 4 was removed of %s...\n", tree_type);

//    printf("Searching data 4 in %s...\n", tree_type);

//    if (bst_search(tree, 4) == NULL)
//        printf("Data 4 wasn't found in %s...\n", tree_type);
//    else
//        printf("Data 4 was found in %s...\n", tree_type);

//    printf("Searching data 1 in %s...\n", tree_type);

//    if (bst_search(tree, 1) == NULL)
//        printf("Data 1 wasn't found in %s...\n", tree_type);
//    else
//        printf("Data 1 was found in %s...\n", tree_type);

//    printf("Searching data 5 in %s...\n", tree_type);

//    if (bst_search(tree, 5) == NULL)
//        printf("Data 5 wasn't found in %s...\n", tree_type);
//    else
//        printf("Data 5 was found in %s...\n", tree_type);

//    int64_t *s1 = bst_successor(tree, 1);
//    int64_t *s3 = bst_successor(tree, 3);
//    int64_t *s5 = bst_successor(tree, 5);

//    if (s1 != NULL)
//        printf("Successor of data 1 in %s: %d\n", tree_type, *s1);
//    else
//        printf("Data 1 hasn't successor in %s...\n", tree_type);

//    if (s3 != NULL)
//        printf("Successor of data 3 in %s: %d\n", tree_type, *s3);
//    else
//        printf("Data 3 hasn't successor in %s...\n", tree_type);

//    if (s5 != NULL)
//        printf("Successor of data 5 in %s: %d\n", tree_type, *s5);
//    else
//        printf("Data 5 hasn't successor in %s...\n", tree_type);

//    printf("Finally, freeing %s...\n", tree_type);

//    bst_free(tree);

//    printf("%s was freed...\n", tree_type);

    return EXIT_SUCCESS;
}
