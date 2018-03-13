#pragma once

typedef struct list CircularDoublyLinkedList;


CircularDoublyLinkedList *circular_doubly_create();

CircularDoublyLinkedList *circular_doubly_insert(CircularDoublyLinkedList *cdll, int data);

void circular_doubly_iterative_print(const CircularDoublyLinkedList *const cdll);

void circular_doubly_recursive_print(const CircularDoublyLinkedList *const cdll_head, const CircularDoublyLinkedList *const cdll_current);

int circular_doubly_is_empty(const CircularDoublyLinkedList *const cdll);

CircularDoublyLinkedList *circular_doubly_search(const CircularDoublyLinkedList *const cdll, int data);

CircularDoublyLinkedList *circular_doubly_iterative_remove(CircularDoublyLinkedList *cdll, int data);

CircularDoublyLinkedList *circular_doubly_recursive_remove(CircularDoublyLinkedList *cdll_head, CircularDoublyLinkedList *cdll_current, int data);

void circular_doubly_free(CircularDoublyLinkedList *cdll);
