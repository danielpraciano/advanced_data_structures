#pragma once

typedef struct list CircularSinglyLinkedList;


CircularSinglyLinkedList *circular_singly_create();

CircularSinglyLinkedList *circular_singly_insert(CircularSinglyLinkedList *csll, int data);

void circular_singly_iterative_print(const CircularSinglyLinkedList *const csll);

void circular_singly_recursive_print(const CircularSinglyLinkedList *const csll, const CircularSinglyLinkedList * const csll_current);

int circular_singly_is_empty(const CircularSinglyLinkedList *const csll);

CircularSinglyLinkedList *circular_singly_search(const CircularSinglyLinkedList *const csll, int data);

CircularSinglyLinkedList *circular_singly_iterative_remove(CircularSinglyLinkedList *csll, int data);

CircularSinglyLinkedList *circular_singly_recursive_remove(CircularSinglyLinkedList *csll_head, CircularSinglyLinkedList *csll_current, int data);

void circular_singly_free(CircularSinglyLinkedList *csll);
