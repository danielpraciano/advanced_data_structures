#include <stdio.h>
#include <stdlib.h>

#include <lists/singly_linked_list.h>

void print_int(void *datum) {
    printf("Data: %d\n", *((int*) datum));
}

int main(int argc, char *argv[]) {

    const char *const list_type = "SinglyLinkedList";
    void *datum;

    printf("Creating %s...\n", list_type);

    SinglyLinkedList *list = singly_create();

    printf("%s created...\n", list_type);

    printf("Inserting data 1 into %s...\n", list_type);

    datum = malloc(sizeof(int));

    (*(int*) datum) = 1;

    list = singly_insert(list, datum);

    printf("Data 1 was inserted into %s...\n", list_type);

    printf("Inserting data 2 into %s...\n", list_type);

    datum = malloc(sizeof(int));

    (*(int*) datum) = 2;

    list = singly_insert(list, datum);

    printf("Data 2 was inserted into %s...\n", list_type);

    printf("Inserting data 3 into %s...\n", list_type);

    datum = malloc(sizeof(int));

    (*(int*) datum) = 3;

    list = singly_insert(list, datum);

    printf("Data 3 was inserted into %s...\n", list_type);

    printf("Inserting data 4 into %s...\n", list_type);

    datum = malloc(sizeof(int));

    (*(int*) datum) = 4;

    list = singly_insert(list, datum);

    printf("Data 4 was inserted into %s...\n", list_type);

    printf("Inserting data 5 into %s...\n", list_type);

    datum = malloc(sizeof(int));

    (*(int*) datum) = 5;

    list = singly_insert(list, datum);

    printf("Data 5 was inserted into %s...\n", list_type);

    printf("Printing %s iteratively...\n", list_type);

    singly_apply_foreach(list, print_int);

//    singly_iterative_print(list);

//    printf("%s was printed iteratively...\n", list_type);

//    printf("Printing %s recursively...\n", list_type);

//    singly_recursive_print(list);

//    printf("%s was printed recursively...\n", list_type);

//    printf("Printing %s in reverse order...\n", list_type);

//    singly_reverse_print(list);

//    printf("%s was printed in reverse order...\n", list_type);

//    printf("Verifying if %s is empty...\n", list_type);

//    if (singly_is_empty(list)) {
//        printf("%s IS empty!\n", list_type);
//    } else {
//        printf("%s ISN'T empty!\n", list_type);
//    }

//    printf("Searching data 6 in %s...\n", list_type);

//    if (singly_search(list, 6) != NULL) {
//        printf("Data 6 was found in %s...\n", list_type);
//    } else {
//        printf("Data 6 wasn't found in %s...\n", list_type);
//    }

//    printf("Searching data 3 in %s...\n", list_type);

//    if (singly_search(list, 3) != NULL) {
//        printf("Data 3 was found in %s...\n", list_type);
//    } else {
//        printf("Data 3 wasn't found in %s...\n", list_type);
//    }

//    printf("Removing (iteratively) data 1 in %s...\n", list_type);

//    list = singly_iterative_remove(list, 1);

//    printf("Data 1 was removed iteratively...\n", list_type);

//    printf("Printing %s iteratively...\n", list_type);

//    singly_iterative_print(list);

//    printf("%s was printed iteratively...\n", list_type);

//    printf("Removing (recursively) data 3 in %s...\n", list_type);

//    list = singly_recursive_remove(list, 3);

//    printf("Data 3 was removed recursively...\n", list_type);

//    printf("Printing %s recursively...\n", list_type);

//    singly_recursive_print(list);

//    printf("%s was printed recursively...\n", list_type);

//    printf("Finally, freeing %s...\n", list_type);

//    singly_free(list);

//    printf("%s was freed...\n", list_type);

    return EXIT_SUCCESS;
}
