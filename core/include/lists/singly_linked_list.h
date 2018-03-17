#pragma once

typedef struct list SinglyLinkedList;


SinglyLinkedList *singly_create();

SinglyLinkedList *singly_insert(SinglyLinkedList *sll, void *datum);

void singly_apply_foreach(SinglyLinkedList *sll, void (*func)(void*));

int singly_is_empty(const SinglyLinkedList *const sll);

//typedef enum {LESS_THAN = -1, EQUALS = 0, GREATER_THAN = 1} CompareValue;
//typedef CompareValue (*compare_function)();

//SinglyLinkedList *singly_search(const SinglyLinkedList *const sll, void *datum);

//SinglyLinkedList *singly_iterative_remove(SinglyLinkedList *sll, void *datum);

//SinglyLinkedList *singly_recursive_remove(SinglyLinkedList *sll, void *datum);

//void singly_free(SinglyLinkedList *sll);
