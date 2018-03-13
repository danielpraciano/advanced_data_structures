#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <circular_singly_linked_list.h>


struct list {
    int data;
    CircularSinglyLinkedList *next;
};


CircularSinglyLinkedList *circular_singly_create() {
    return NULL;
}

CircularSinglyLinkedList *circular_singly_insert(CircularSinglyLinkedList *csll, int data) {
    CircularSinglyLinkedList *csll_it = csll;
    CircularSinglyLinkedList *new_element = (CircularSinglyLinkedList*) malloc(sizeof(CircularSinglyLinkedList));

    assert(new_element != NULL);

    new_element->data = data;

    if (csll_it == NULL) {
        new_element->next = new_element;
        csll = new_element;
    } else {
        while (csll_it->next != csll)
            csll_it = csll_it->next;

        csll_it->next     = new_element;
        new_element->next = csll;
    }

    return csll;
}

void circular_singly_iterative_print(const CircularSinglyLinkedList *const csll) {
    const CircularSinglyLinkedList *csll_to_print;

    if (csll == NULL)
        return;

    printf("Data: %d\n", csll->data);

    for (csll_to_print = (const CircularSinglyLinkedList*) csll->next; csll_to_print != csll; csll_to_print = csll_to_print->next)
        printf("Data: %d\n", csll_to_print->data);

}

void circular_singly_recursive_print(const CircularSinglyLinkedList *const csll_head, const CircularSinglyLinkedList *const csll_current) {
    if (csll_head == NULL)
        return;

    if (csll_head->next == csll_head) {
        printf("Data: %d\n", csll_head->data);
        return;
    }

    if (csll_current->next == csll_head) {
        printf("Data: %d\n", csll_current->data);
        return;
    }

    printf("Data: %d\n", csll_current->data);
    circular_singly_recursive_print(csll_head, csll_current->next);
}

int circular_singly_is_empty(const CircularSinglyLinkedList *const csll) {
    return csll == NULL;
}

CircularSinglyLinkedList *circular_singly_search(const CircularSinglyLinkedList *const csll, int data) {
    const CircularSinglyLinkedList *csll_to_search = (const CircularSinglyLinkedList*) csll;

    while (csll_to_search->next != csll && csll_to_search->data != data)
        csll_to_search = csll_to_search->next;

    if (csll_to_search->data != data)
        csll_to_search = NULL;

    return (CircularSinglyLinkedList*) csll_to_search;
}

CircularSinglyLinkedList *circular_singly_iterative_remove(CircularSinglyLinkedList *csll, int data) {
    CircularSinglyLinkedList *csll_to_remove = csll, *csll_to_remove_before = NULL;

    while (csll_to_remove->next != csll && csll_to_remove->data != data) {
        csll_to_remove_before = csll_to_remove;
        csll_to_remove = csll_to_remove->next;
    }

    if (csll_to_remove->data == data) {
        if (csll_to_remove_before == NULL) {

            if (csll->next == csll) {
                csll = NULL;
            } else {
                csll_to_remove_before = csll->next;

                while (csll_to_remove_before->next != csll)
                    csll_to_remove_before = csll_to_remove_before->next;

                csll_to_remove_before->next = csll->next;
                csll_to_remove = csll;
                csll = csll->next;
            }

        } else {
            csll_to_remove_before->next = csll_to_remove->next;
        }

        free(csll_to_remove);
    }

    return csll;
}

CircularSinglyLinkedList *circular_singly_recursive_remove(CircularSinglyLinkedList *csll_head, CircularSinglyLinkedList *csll_current, int data) {
    if (csll_head == NULL)
        return NULL;

    if (csll_current->next == csll_head)
        return csll_current;

    if (csll_current->data == data) {
        CircularSinglyLinkedList *csll_to_remove = csll_current;

        csll_current = csll_current->next;
        free(csll_to_remove);
    } else {
        csll_current->next = circular_singly_recursive_remove(csll_head, csll_current->next, data);
    }

    return csll_current;
}

void circular_singly_free(CircularSinglyLinkedList *csll) {
    CircularSinglyLinkedList *csll_to_free = csll;

    while (csll_to_free != csll) {
        csll = csll_to_free->next;

        free(csll_to_free);
        csll_to_free = csll;
    }
}
