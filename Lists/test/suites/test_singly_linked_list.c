#include <stdio.h>
#include <stdlib.h>
#include <singly_linked_list.h>


int main(int argc, char *argv[]) {

    printf("Creating SinglyLinkedList...\n");

    SinglyLinkedList *list = singly_create();

    printf("SinglyLinkedList created...\n");

    printf("Inserting data 1 into SinglyLinkedList...\n");

    list = singly_insert(list, 1);

    printf("Data 1 was inserted into SinglyLinkedList...\n");

    printf("Inserting data 2 into SinglyLinkedList...\n");

    list = singly_insert(list, 2);

    printf("Data 2 was inserted into SinglyLinkedList...\n");

    printf("Inserting data 3 into SinglyLinkedList...\n");

    list = singly_insert(list, 3);

    printf("Data 3 was inserted into SinglyLinkedList...\n");

    printf("Inserting data 4 into SinglyLinkedList...\n");

    list = singly_insert(list, 4);

    printf("Data 4 was inserted into SinglyLinkedList...\n");

    printf("Inserting data 5 into SinglyLinkedList...\n");

    list = singly_insert(list, 5);

    printf("Data 5 was inserted into SinglyLinkedList...\n");

    printf("Printing SinglyLinkedList iteratively...\n");

    singly_iterative_print(list);

    printf("SinglyLinkedList was printed iteratively...\n");

    printf("Printing SinglyLinkedList recursively...\n");

    singly_recursive_print(list);

    printf("SinglyLinkedList was printed recursively...\n");

    printf("Printing SinglyLinkedList in reverse order...\n");

    singly_reverse_print(list);

    printf("SinglyLinkedList was printed in reverse order...\n");

    printf("Verifying if SinglyLinkedList is empty...\n");

    if (singly_is_empty(list)) {
        printf("SinglyLinkedList IS empty!\n");
    } else {
        printf("SinglyLinkedList ISN'T empty!\n");
    }

    printf("Searching data 6 in SinglyLinkedList...\n");

    if (singly_search(list, 6) != NULL) {
        printf("Data 6 was found in SinglyLinkedList...\n");
    } else {
        printf("Data 6 wasn't found in SinglyLinkedList...\n");
    }

    printf("Searching data 3 in SinglyLinkedList...\n");

    if (singly_search(list, 3) != NULL) {
        printf("Data 3 was found in SinglyLinkedList...\n");
    } else {
        printf("Data 3 wasn't found in SinglyLinkedList...\n");
    }

    printf("Removing (iteratively) data 1 in SinglyLinkedList...\n");

    list = singly_iterative_remove(list, 1);

    printf("Data 1 was removed iteratively...\n");

    printf("Printing SinglyLinkedList iteratively...\n");

    singly_iterative_print(list);

    printf("SinglyLinkedList was printed iteratively...\n");

    printf("Removing (recursively) data 3 in SinglyLinkedList...\n");

    list = singly_recursive_remove(list, 3);

    printf("Data 3 was removed recursively...\n");

    printf("Printing SinglyLinkedList recursively...\n");

    singly_recursive_print(list);

    printf("SinglyLinkedList was printed recursively...\n");

    printf("Finally, freeing SinglyLinkedList...\n");

    singly_free(list);

    printf("SinglyLinkedList was freed...\n");

    return EXIT_SUCCESS;
}
