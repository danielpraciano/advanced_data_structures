#pragma once

typedef struct list OrderedDoublyLinkedList;


OrderedDoublyLinkedList *ordered_doubly_create();

OrderedDoublyLinkedList *ordered_doubly_insert(OrderedDoublyLinkedList *odll, int data);

void ordered_doubly_iterative_print(const OrderedDoublyLinkedList *const odll);

void ordered_doubly_recursive_print(const OrderedDoublyLinkedList *const odll);

void ordered_doubly_reverse_print(const OrderedDoublyLinkedList *const odll);

int ordered_doubly_is_empty(const OrderedDoublyLinkedList *const odll);

OrderedDoublyLinkedList *ordered_doubly_search(const OrderedDoublyLinkedList *const odll, int data);

OrderedDoublyLinkedList *ordered_doubly_iterative_remove(OrderedDoublyLinkedList *odll, int data);

OrderedDoublyLinkedList *ordered_doubly_recursive_remove(OrderedDoublyLinkedList *odll, int data);

void ordered_doubly_free(OrderedDoublyLinkedList *odll);

int ordered_doubly_are_equals(const OrderedDoublyLinkedList *const odll_left, const OrderedDoublyLinkedList *const odll_right);
