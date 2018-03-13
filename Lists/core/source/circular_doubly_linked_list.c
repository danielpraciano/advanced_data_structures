#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <circular_doubly_linked_list.h>


struct list {
    int data;
    CircularDoublyLinkedList *previous, *next;
};


CircularDoublyLinkedList *circular_doubly_create() {
    return NULL;
}

CircularDoublyLinkedList *circular_doubly_insert(CircularDoublyLinkedList *cdll, int data) {
    CircularDoublyLinkedList *new_element = (CircularDoublyLinkedList*) malloc(sizeof(CircularDoublyLinkedList));

    assert(new_element != NULL);

    new_element->data = data;

    if (cdll == NULL) {
        new_element->previous = new_element;
        new_element->next     = new_element;
        cdll                  = new_element;
    } else {
        new_element->previous = cdll->previous;
        new_element->next     = cdll;
        cdll->previous->next  = new_element;
        cdll->previous        = new_element;
    }

    return cdll;
}

void circular_doubly_iterative_print(const CircularDoublyLinkedList *const cdll) {
    const CircularDoublyLinkedList *cdll_to_print;

    if (cdll == NULL)
        return;

    printf("Data: %d\n", cdll->data);

    for (cdll_to_print = (const CircularDoublyLinkedList*) cdll->next; cdll_to_print != cdll; cdll_to_print = cdll_to_print->next)
        printf("Data: %d\n", cdll_to_print->data);

}

void circular_doubly_recursive_print(const CircularDoublyLinkedList *const cdll_head, const CircularDoublyLinkedList * const cdll_current) {
    if (cdll_head == NULL)
        return;

    if (cdll_head->next == cdll_head) {
        printf("Data: %d\n", cdll_head->data);
        return;
    }

    if (cdll_current->next == cdll_head) {
        printf("Data: %d\n", cdll_current->data);
        return;
    }

    printf("Data: %d\n", cdll_current->data);
    circular_doubly_recursive_print(cdll_head, cdll_current->next);
}

int circular_doubly_is_empty(const CircularDoublyLinkedList *const cdll) {
    return cdll == NULL;
}

CircularDoublyLinkedList *circular_doubly_search(const CircularDoublyLinkedList *const cdll, int data) {
    const CircularDoublyLinkedList *cdll_to_search = (const CircularDoublyLinkedList*) cdll;

    while (cdll_to_search->next != cdll && cdll_to_search->data != data)
        cdll_to_search = cdll_to_search->next;

    if (cdll_to_search->data != data)
        cdll_to_search = NULL;

    return (CircularDoublyLinkedList*) cdll_to_search;
}

CircularDoublyLinkedList *circular_doubly_iterative_remove(CircularDoublyLinkedList *cdll, int data) {
    CircularDoublyLinkedList *cdll_to_remove = cdll;

    while (cdll_to_remove->next != cdll && cdll_to_remove->data != data)
        cdll_to_remove = cdll_to_remove->next;

    if (cdll_to_remove->data == data) {
        if (cdll_to_remove == cdll) {

            if (cdll->next == cdll) {
                cdll = NULL;
            } else {
                cdll_to_remove->previous->next = cdll->next;
                cdll->next->previous           = cdll_to_remove->previous;
                cdll_to_remove = cdll;
                cdll = cdll->next;
            }

        } else {
            cdll_to_remove->previous->next = cdll_to_remove->next;
            cdll_to_remove->next->previous = cdll_to_remove->previous;
        }

        free(cdll_to_remove);
    }

    return cdll;
}

CircularDoublyLinkedList *circular_doubly_recursive_remove(CircularDoublyLinkedList *cdll_head, CircularDoublyLinkedList *cdll_current, int data) {
    if (cdll_head == NULL)
        return NULL;

    if (cdll_current->next == cdll_head)
        return cdll_current;

    if (cdll_current->data == data) {
        CircularDoublyLinkedList *cdll_to_remove = cdll_current;

        cdll_to_remove->previous->next = cdll_current->next;
        cdll_current->next->previous   = cdll_to_remove->previous;
        cdll_current                   = cdll_current->next;

        free(cdll_to_remove);
    } else {
        cdll_current->next = circular_doubly_recursive_remove(cdll_head, cdll_current->next, data);
    }

    return cdll_current;
}

void circular_doubly_free(CircularDoublyLinkedList *cdll) {
    CircularDoublyLinkedList *cdll_to_free = cdll;

    while (cdll_to_free != cdll) {
        cdll = cdll_to_free->next;

        free(cdll_to_free);
        cdll_to_free = cdll;
    }
}
