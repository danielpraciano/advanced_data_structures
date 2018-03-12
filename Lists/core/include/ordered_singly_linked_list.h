#pragma once

typedef struct list OrderedSinglyLinkedList;


OrderedSinglyLinkedList *ordered_singly_create();

OrderedSinglyLinkedList *ordered_singly_insert(OrderedSinglyLinkedList *osll, int data);

void ordered_singly_iterative_print(const OrderedSinglyLinkedList *const osll);

void ordered_singly_recursive_print(const OrderedSinglyLinkedList *const osll);

void ordered_singly_reverse_print(const OrderedSinglyLinkedList *const osll);

int ordered_singly_is_empty(const OrderedSinglyLinkedList *const osll);

OrderedSinglyLinkedList *ordered_singly_search(const OrderedSinglyLinkedList *const osll, int data);

OrderedSinglyLinkedList *ordered_singly_iterative_remove(OrderedSinglyLinkedList *osll, int data);

OrderedSinglyLinkedList *ordered_singly_recursive_remove(OrderedSinglyLinkedList *osll, int data);

void ordered_singly_free(OrderedSinglyLinkedList *osll);

int ordered_singly_are_equals(const OrderedSinglyLinkedList *const osll_left, const OrderedSinglyLinkedList *const osll_right);
