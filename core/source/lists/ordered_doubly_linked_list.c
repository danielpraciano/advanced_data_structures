#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <lists/ordered_doubly_linked_list.h>


struct list {
    int data;
    OrderedDoublyLinkedList *previous, *next;
};


OrderedDoublyLinkedList *ordered_doubly_create() {
    return NULL;
}

OrderedDoublyLinkedList *ordered_doubly_insert(OrderedDoublyLinkedList *odll, int data) {
    OrderedDoublyLinkedList *new_element = (OrderedDoublyLinkedList*) malloc(sizeof(OrderedDoublyLinkedList));

    assert(new_element != NULL);

    new_element->data = data;

    if (odll == NULL || odll->data >= data) {
        new_element->previous = NULL;
        new_element->next     = odll;
        odll                  = new_element;
    } else {
        OrderedDoublyLinkedList *odll_current = odll;

        while (odll_current->next != NULL && data > odll_current->data)
            odll_current = odll_current->next;

        if (odll_current->next != NULL)
            odll_current->next->previous = new_element;

        new_element->previous        = odll_current;
        new_element->next            = odll_current->next;
        odll_current->next           = new_element;

    }

    return odll;
}

void ordered_doubly_iterative_print(const OrderedDoublyLinkedList *const odll) {
    const OrderedDoublyLinkedList *odll_to_print;

    for (odll_to_print = (const OrderedDoublyLinkedList*) odll; odll_to_print != NULL; odll_to_print = odll_to_print->next)
        printf("Data: %d\n", odll_to_print->data);
}

void ordered_doubly_recursive_print(const OrderedDoublyLinkedList *const odll) {
    if (odll == NULL)
        return;

    printf("Data: %d\n", odll->data);
    ordered_doubly_recursive_print(odll->next);
}

void ordered_doubly_reverse_print(const OrderedDoublyLinkedList *const odll) {
    if (odll == NULL)
        return;

    ordered_doubly_reverse_print(odll->next);
    printf("Data: %d\n", odll->data);
}

int ordered_doubly_is_empty(const OrderedDoublyLinkedList *const odll) {
    return odll == NULL;
}

OrderedDoublyLinkedList *ordered_doubly_search(const OrderedDoublyLinkedList *const odll, int data) {
    const OrderedDoublyLinkedList *odll_to_search = (const OrderedDoublyLinkedList*) odll;

    while (odll_to_search != NULL && odll_to_search->data != data)
        odll_to_search = odll_to_search->next;

    return (OrderedDoublyLinkedList*) odll_to_search;
}

OrderedDoublyLinkedList *ordered_doubly_iterative_remove(OrderedDoublyLinkedList *odll, int data) {
    OrderedDoublyLinkedList *odll_to_remove = odll;

    while (odll_to_remove != NULL && odll_to_remove->data != data)
        odll_to_remove = odll_to_remove->next;

    if (odll_to_remove != NULL) {
        if (odll_to_remove->previous == NULL) {
            odll = odll_to_remove->next;

            if (odll != NULL)
                odll->previous = NULL;
        } else {
            odll_to_remove->previous->next = odll_to_remove->next;

            if (odll_to_remove->next != NULL)
                odll_to_remove->next->previous = odll_to_remove->previous;
        }

        free(odll_to_remove);
    }

    return odll;
}

OrderedDoublyLinkedList *ordered_doubly_recursive_remove(OrderedDoublyLinkedList *odll, int data) {
    if (odll == NULL || odll->data > data)
        return odll;

    if (odll->data == data) {
        OrderedDoublyLinkedList *odll_to_remove = odll;

        if (odll_to_remove->previous == NULL) {
            odll = odll_to_remove->next;

            if (odll != NULL)
                odll->previous = NULL;
        } else {
            odll_to_remove->previous->next = odll_to_remove->next;

            if (odll_to_remove->next != NULL)
                odll_to_remove->next->previous = odll_to_remove->previous;
        }

        free(odll_to_remove);

    } else {
        ordered_doubly_recursive_remove(odll->next, data);
    }

    return odll;
}

void ordered_doubly_free(OrderedDoublyLinkedList *odll) {
    OrderedDoublyLinkedList *odll_to_free = odll;

    while (odll_to_free != NULL) {
        odll = odll_to_free->next;

        free(odll_to_free);
        odll_to_free = odll;
    }
}

int ordered_doubly_are_equals(const OrderedDoublyLinkedList *const odll_left, const OrderedDoublyLinkedList *const odll_right) {
    const OrderedDoublyLinkedList *odll_left_it, *odll_right_it;

    for (odll_left_it  = (const OrderedDoublyLinkedList*) odll_left,
         odll_right_it = (const OrderedDoublyLinkedList*) odll_right;
         odll_left_it != NULL && odll_right_it != NULL;
         odll_left_it  = odll_left_it->next,
         odll_right_it = odll_right_it->next) {

        if (odll_left_it->data != odll_right_it->data)
            return 0;
    }

    return odll_left_it == odll_right_it;
}
