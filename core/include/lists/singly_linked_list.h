#pragma once

typedef struct list SinglyLinkedList;


SinglyLinkedList *singly_create();

SinglyLinkedList *singly_insert(SinglyLinkedList *sll, void *datum);

void singly_iterative_print(const SinglyLinkedList *const sll);

void singly_recursive_print(const SinglyLinkedList *const sll);

void singly_reverse_print(const SinglyLinkedList *const sll);

int singly_is_empty(const SinglyLinkedList *const sll);

SinglyLinkedList *singly_search(const SinglyLinkedList *const sll, void *datum);

SinglyLinkedList *singly_iterative_remove(SinglyLinkedList *sll, void *datum);

SinglyLinkedList *singly_recursive_remove(SinglyLinkedList *sll, void *datum);

void singly_free(SinglyLinkedList *sll);
