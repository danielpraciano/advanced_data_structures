#pragma once

typedef struct list CircularSinglyLinkedList;


CircularSinglyLinkedList *circular_singly_create();

CircularSinglyLinkedList *circular_singly_insert(CircularSinglyLinkedList *sll, int data);

void circular_singly_iterative_print(const CircularSinglyLinkedList *const sll);

void circular_singly_recursive_print(const CircularSinglyLinkedList *const sll);

int circular_singly_is_empty(const CircularSinglyLinkedList *const sll);

CircularSinglyLinkedList *circular_singly_search(const CircularSinglyLinkedList *const sll, int data);

CircularSinglyLinkedList *circular_singly_iterative_remove(CircularSinglyLinkedList *sll, int data);

CircularSinglyLinkedList *circular_singly_recursive_remove(CircularSinglyLinkedList *sll, int data);

void circular_singly_free(CircularSinglyLinkedList *sll);
