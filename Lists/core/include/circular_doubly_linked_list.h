#pragma once

typedef struct list CircularDoublyLinkedList;


CircularDoublyLinkedList *circular_doubly_create();

CircularDoublyLinkedList *circular_doubly_insert(CircularDoublyLinkedList *sll, int data);

void circular_doubly_iterative_print(const CircularDoublyLinkedList *const sll);

void circular_doubly_recursive_print(const CircularDoublyLinkedList *const sll);

int circular_doubly_is_empty(const CircularDoublyLinkedList *const sll);

CircularDoublyLinkedList *circular_doubly_search(const CircularDoublyLinkedList *const sll, int data);

CircularDoublyLinkedList *circular_doubly_iterative_remove(CircularDoublyLinkedList *sll, int data);

CircularDoublyLinkedList *circular_doubly_recursive_remove(CircularDoublyLinkedList *sll, int data);

void circular_doubly_free(CircularDoublyLinkedList *sll);
