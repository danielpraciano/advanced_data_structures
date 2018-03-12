#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <singly_linked_list.h>


struct list {
    int data;
    SinglyLinkedList *next;
};


SinglyLinkedList *singly_create() {
    return NULL;
}

SinglyLinkedList *singly_insert(SinglyLinkedList *sll, int data) {
    SinglyLinkedList *new_element = (SinglyLinkedList*) malloc(sizeof(SinglyLinkedList));

    assert(new_element != NULL);

    new_element->data = data;
    new_element->next = sll;

    return new_element;
}

void singly_iterative_print(const SinglyLinkedList *const sll) {
    const SinglyLinkedList *sll_to_print;

    for (sll_to_print = (const SinglyLinkedList*) sll; sll_to_print != NULL; sll_to_print = sll_to_print->next)
        printf("Data: %d\n", sll_to_print->data);

}

void singly_recursive_print(const SinglyLinkedList *const sll) {
    if (sll == NULL)
        return;

    printf("Data: %d\n", sll->data);
    singly_recursive_print(sll->next);
}

void singly_reverse_print(const SinglyLinkedList *const sll) {
    if (sll == NULL)
        return;

    singly_reverse_print(sll->next);
    printf("Data: %d\n", sll->data);
}

int singly_is_empty(const SinglyLinkedList *const sll) {
    return sll == NULL;
}

SinglyLinkedList *singly_search(const SinglyLinkedList *const sll, int data) {
    const SinglyLinkedList *sll_to_search = (const SinglyLinkedList*) sll;

    while (sll_to_search != NULL && sll_to_search->data != data)
        sll_to_search = sll_to_search->next;

    return (SinglyLinkedList*) sll_to_search;
}

SinglyLinkedList *singly_iterative_remove(SinglyLinkedList *sll, int data) {
    SinglyLinkedList *sll_to_remove = sll, *sll_to_remove_before = NULL;

    while (sll_to_remove != NULL && sll_to_remove->data != data) {
        sll_to_remove_before = sll_to_remove;
        sll_to_remove = sll_to_remove->next;
    }

    if (sll_to_remove != NULL) {
        if (sll_to_remove_before == NULL) {
            sll = sll_to_remove->next;
        } else {
            sll_to_remove_before->next = sll_to_remove->next;
        }

        free(sll_to_remove);
    }

    return sll;
}

SinglyLinkedList *singly_recursive_remove(SinglyLinkedList *sll, int data) {
    if (sll == NULL)
        return NULL;

    if (sll->data == data) {
        SinglyLinkedList *sll_to_remove = sll;

        sll = sll->next;
        free(sll_to_remove);
    } else {
        sll->next = singly_recursive_remove(sll->next, data);
    }

    return sll;
}

void singly_free(SinglyLinkedList *sll) {
    SinglyLinkedList *sll_to_free = sll;

    while (sll_to_free != NULL) {
        sll = sll_to_free->next;

        free(sll_to_free);
        sll_to_free = sll;
    }
}
