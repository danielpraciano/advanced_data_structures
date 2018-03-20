#pragma once

#include <util.h>

typedef struct list SinglyLinkedList;


void* singly_get_datum(const SinglyLinkedList *const sll);

SinglyLinkedList *singly_create();

SinglyLinkedList *singly_insert(SinglyLinkedList *sll, void *datum);

void singly_apply_foreach(SinglyLinkedList *sll, void (*func)(void*));

int singly_is_empty(const SinglyLinkedList *const sll);

//typedef enum {LESS_THAN = -1, EQUALS = 0, GREATER_THAN = 1} CompareValue;
//typedef CompareValue (*compare_function)();

SinglyLinkedList *singly_search(const SinglyLinkedList *const sll, compare_function compare, void *datum);

SinglyLinkedList *singly_iterative_remove(SinglyLinkedList *sll, compare_function compare, void *datum);

//SinglyLinkedList *singly_recursive_remove(SinglyLinkedList *sll, void *datum);

void singly_free(SinglyLinkedList *sll);
