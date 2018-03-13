#include <stdio.h>
#include <stdlib.h>

#include <circular_singly_linked_list.h>


int main(int argc, char *argv[]) {

    const char *const list_type = "CircularSinglyLinkedList";

    printf("Creating %s...\n", list_type);

    CircularSinglyLinkedList *list = circular_singly_create();

    printf("%s created...\n", list_type);

    printf("Inserting data 1 into %s...\n", list_type);

    list = circular_singly_insert(list, 1);

    printf("Data 1 was inserted into %s...\n", list_type);

    printf("Inserting data 2 into %s...\n", list_type);

    list = circular_singly_insert(list, 2);

    printf("Data 2 was inserted into %s...\n", list_type);

    printf("Inserting data 3 into %s...\n", list_type);

    list = circular_singly_insert(list, 3);

    printf("Data 3 was inserted into %s...\n", list_type);

    printf("Inserting data 4 into %s...\n", list_type);

    list = circular_singly_insert(list, 4);

    printf("Data 4 was inserted into %s...\n", list_type);

    printf("Inserting data 5 into %s...\n", list_type);

    list = circular_singly_insert(list, 5);

    printf("Data 5 was inserted into %s...\n", list_type);

    printf("Printing %s iteratively...\n", list_type);

    circular_singly_iterative_print(list);

    printf("%s was printed iteratively...\n", list_type);

    printf("Printing %s recursively...\n", list_type);

    circular_singly_recursive_print(list, list);

    printf("%s was printed recursively...\n", list_type);

    printf("Verifying if %s is empty...\n", list_type);

    if (circular_singly_is_empty(list)) {
        printf("%s IS empty!\n", list_type);
    } else {
        printf("%s ISN'T empty!\n", list_type);
    }

    printf("Searching data 6 in %s...\n", list_type);

    if (circular_singly_search(list, 6) != NULL) {
        printf("Data 6 was found in %s...\n", list_type);
    } else {
        printf("Data 6 wasn't found in %s...\n", list_type);
    }

    printf("Searching data 3 in %s...\n", list_type);

    if (circular_singly_search(list, 3) != NULL) {
        printf("Data 3 was found in %s...\n", list_type);
    } else {
        printf("Data 3 wasn't found in %s...\n", list_type);
    }

    printf("Removing (iteratively) data 1 in %s...\n", list_type);

    list = circular_singly_iterative_remove(list, 1);

    printf("Data 1 was removed iteratively...\n", list_type);

    printf("Printing %s iteratively...\n", list_type);

    circular_singly_iterative_print(list);

    printf("%s was printed iteratively...\n", list_type);

    printf("Removing (recursively) data 3 in %s...\n", list_type);

    list = circular_singly_recursive_remove(list, list, 3);

    printf("Data 3 was removed recursively...\n", list_type);

    printf("Printing %s recursively...\n", list_type);

    circular_singly_recursive_print(list, list);

    printf("%s was printed recursively...\n", list_type);

    printf("Finally, freeing %s...\n", list_type);

    circular_singly_free(list);

    printf("%s was freed...\n", list_type);

    return EXIT_SUCCESS;
}
