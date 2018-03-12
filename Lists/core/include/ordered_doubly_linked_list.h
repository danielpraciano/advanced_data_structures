#pragma once

typedef struct list OrderedDoublyLinkedList;


OrderedDoublyLinkedList *ordered_doubly_create();

OrderedDoublyLinkedList *ordered_doubly_insert(OrderedDoublyLinkedList *sll, int data);

void ordered_doubly_iterative_print(const OrderedDoublyLinkedList *const sll);

void ordered_doubly_recursive_print(const OrderedDoublyLinkedList *const sll);

void ordered_doubly_reverse_print(const OrderedDoublyLinkedList *const sll);

int ordered_doubly_is_empty(const OrderedDoublyLinkedList *const sll);

OrderedDoublyLinkedList *ordered_doubly_search(const OrderedDoublyLinkedList *const sll, int data);

OrderedDoublyLinkedList *ordered_doubly_iterative_remove(OrderedDoublyLinkedList *sll, int data);

OrderedDoublyLinkedList *ordered_doubly_recursive_remove(OrderedDoublyLinkedList *sll, int data);

void ordered_doubly_free(OrderedDoublyLinkedList *sll);

int ordered_doubly_are_equals(const OrderedDoublyLinkedList *const sll_left, const OrderedDoublyLinkedList *const sll_right);
