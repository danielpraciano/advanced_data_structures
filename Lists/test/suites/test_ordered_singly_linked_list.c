#include <stdio.h>
#include <stdlib.h>
#include <ordered_singly_linked_list.h>


int main(int argc, char *argv[]) {

    const char *const list_type = "OrderedSinglyLinkedList";

    printf("Creating %s...\n", list_type);

    OrderedSinglyLinkedList *list = ordered_singly_create();

    printf("%s created...\n", list_type);

    printf("Inserting data 1 into %s...\n", list_type);

    list = ordered_singly_insert(list, 1);

    printf("Data 1 was inserted into %s...\n", list_type);

    printf("Inserting data 2 into %s...\n", list_type);

    list = ordered_singly_insert(list, 2);

    printf("Data 2 was inserted into %s...\n", list_type);

    printf("Inserting data 3 into %s...\n", list_type);

    list = ordered_singly_insert(list, 3);

    printf("Data 3 was inserted into %s...\n", list_type);

    printf("Inserting data 4 into %s...\n", list_type);

    list = ordered_singly_insert(list, 4);

    printf("Data 4 was inserted into %s...\n", list_type);

    printf("Inserting data 5 into %s...\n", list_type);

    list = ordered_singly_insert(list, 5);

    printf("Data 5 was inserted into %s...\n", list_type);

    printf("Printing %s iteratively...\n", list_type);

    ordered_singly_iterative_print(list);

    printf("%s was printed iteratively...\n", list_type);

    printf("Printing %s recursively...\n", list_type);

    ordered_singly_recursive_print(list);

    printf("%s was printed recursively...\n", list_type);

    printf("Printing %s in reverse order...\n", list_type);

    ordered_singly_reverse_print(list);

    printf("%s was printed in reverse order...\n", list_type);

    printf("Verifying if %s is empty...\n", list_type);

    if (ordered_singly_is_empty(list)) {
        printf("%s IS empty!\n", list_type);
    } else {
        printf("%s ISN'T empty!\n", list_type);
    }

    printf("Searching data 6 in %s...\n", list_type);

    if (ordered_singly_search(list, 6) != NULL) {
        printf("Data 6 was found in %s...\n", list_type);
    } else {
        printf("Data 6 wasn't found in %s...\n", list_type);
    }

    printf("Searching data 3 in %s...\n", list_type);

    if (ordered_singly_search(list, 3) != NULL) {
        printf("Data 3 was found in %s...\n", list_type);
    } else {
        printf("Data 3 wasn't found in %s...\n", list_type);
    }

    printf("Removing (iteratively) data 1 in %s...\n", list_type);

    list = ordered_singly_iterative_remove(list, 1);

    printf("Data 1 was removed iteratively...\n");

    printf("Printing %s iteratively...\n", list_type);

    ordered_singly_iterative_print(list);

    printf("%s was printed iteratively...\n", list_type);

    printf("Removing (recursively) data 3 in %s...\n", list_type);

    list = ordered_singly_recursive_remove(list, 3);

    printf("Data 3 was removed recursively...\n");

    printf("Printing %s recursively...\n", list_type);

    ordered_singly_recursive_print(list);

    printf("%s was printed recursively...\n", list_type);

    printf("Finally, freeing %s...\n", list_type);

    ordered_singly_free(list);

    printf("%s was freed...\n", list_type);

    printf("Verifying whether two %s are equals or not using the same %s...\n", list_type, list_type);

    if (ordered_singly_are_equals(list, list)) {
        printf("%ss are equals...\n", list_type);
    } else {
        printf("%ss aren't equals...\n", list_type);
    }

    return EXIT_SUCCESS;
}
