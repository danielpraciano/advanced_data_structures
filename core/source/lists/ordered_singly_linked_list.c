#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <lists/ordered_singly_linked_list.h>


struct list {
    int data;
    OrderedSinglyLinkedList *next;
};


OrderedSinglyLinkedList *ordered_singly_create() {
    return NULL;
}

OrderedSinglyLinkedList *ordered_singly_insert(OrderedSinglyLinkedList *osll, int data) {
    OrderedSinglyLinkedList *new_element = (OrderedSinglyLinkedList*) malloc(sizeof(OrderedSinglyLinkedList));

    assert(new_element != NULL);

    new_element->data = data;

    if (osll == NULL || osll->data >= data) {
        new_element->next = osll;
        osll              = new_element;
    } else {
        OrderedSinglyLinkedList *osll_current = osll->next, *osll_previous = osll;

        while (osll_current != NULL && data > osll_current->data) {
            osll_previous = osll_current;
            osll_current = osll_current->next;
        }

        osll_previous->next = new_element;
        new_element->next   = osll_current;
    }

    return osll;
}

void ordered_singly_iterative_print(const OrderedSinglyLinkedList *const osll) {
    const OrderedSinglyLinkedList *osll_to_print;

    for (osll_to_print = (const OrderedSinglyLinkedList*) osll; osll_to_print != NULL; osll_to_print = osll_to_print->next)
        printf("Data: %d\n", osll_to_print->data);

}

void ordered_singly_recursive_print(const OrderedSinglyLinkedList *const osll) {
    if (osll == NULL)
        return;

    printf("Data: %d\n", osll->data);
    ordered_singly_recursive_print(osll->next);
}

void ordered_singly_reverse_print(const OrderedSinglyLinkedList *const osll) {
    if (osll == NULL)
        return;

    ordered_singly_reverse_print(osll->next);
    printf("Data: %d\n", osll->data);
}

int ordered_singly_is_empty(const OrderedSinglyLinkedList *const osll) {
    return osll == NULL;
}

OrderedSinglyLinkedList *ordered_singly_search(const OrderedSinglyLinkedList *const osll, int data) {
    const OrderedSinglyLinkedList *osll_to_search = (const OrderedSinglyLinkedList*) osll;

    while (osll_to_search != NULL && osll_to_search->data != data)
        osll_to_search = osll_to_search->next;

    return (OrderedSinglyLinkedList*) osll_to_search;
}

OrderedSinglyLinkedList *ordered_singly_iterative_remove(OrderedSinglyLinkedList *osll, int data) {
    OrderedSinglyLinkedList *osll_to_remove = osll, *osll_to_remove_before = NULL;

    while (osll_to_remove != NULL && osll_to_remove->data != data) {
        osll_to_remove_before = osll_to_remove;
        osll_to_remove = osll_to_remove->next;
    }

    if (osll_to_remove != NULL) {
        if (osll_to_remove_before == NULL) {
            osll = osll_to_remove->next;
        } else {
            osll_to_remove_before->next = osll_to_remove->next;
        }

        free(osll_to_remove);
    }

    return osll;
}

OrderedSinglyLinkedList *ordered_singly_recursive_remove(OrderedSinglyLinkedList *osll, int data) {
    if (osll == NULL)
        return NULL;

    if (osll->data == data) {
        OrderedSinglyLinkedList *osll_to_remove = osll;

        osll = osll->next;
        free(osll_to_remove);
    } else {
        osll->next = ordered_singly_recursive_remove(osll->next, data);
    }

    return osll;
}

void ordered_singly_free(OrderedSinglyLinkedList *osll) {
    OrderedSinglyLinkedList *osll_to_free = osll;

    while (osll_to_free != NULL) {
        osll = osll_to_free->next;

        free(osll_to_free);
        osll_to_free = osll;
    }
}

int ordered_singly_are_equals(const OrderedSinglyLinkedList *const osll_left, const OrderedSinglyLinkedList *const osll_right) {
    const OrderedSinglyLinkedList *osll_left_it, *osll_right_it;

    for (osll_left_it  = (const OrderedSinglyLinkedList*) osll_left,
         osll_right_it = (const OrderedSinglyLinkedList*) osll_right;
         osll_left_it != NULL && osll_right_it != NULL;
         osll_left_it  = osll_left_it->next,
         osll_right_it = osll_right_it->next) {

        if (osll_left_it->data != osll_right_it->data)
            return 0;
    }

    return osll_left_it == osll_right_it;
}
