#pragma once

#include <stddef.h>
#include <stdint.h>


typedef enum heap_type {MIN_HEAP = 0, MAX_HEAP = 1} HeapType;
typedef struct heap_entry Entry;
typedef struct heap_t Heap;

//mudar compare_funciton colocando _ptr
Heap* heap_create(HeapType type, size_t max_size);

void heap_push(Heap *const heap, int64_t priority, const void *const value, size_t num_bytes);

void heap_update_priority(Heap *const heap, int64_t current_priority, int64_t new_priority);

void heap_update_value(Heap *const heap, int64_t priority, const void *const new_value, size_t num_bytes);

const void *const heap_peek(const Heap *const heap);

void* heap_pop(Heap *const heap);

void heap_free(Heap *heap);
