#include <priority_queue/heap.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define PARENT(i) ( (i-1) >> 1 )
#define LEFT(i)   (    i << 1 | 1 )
#define RIGHT(i)  ( (i+1) << 1 )

struct heap_entry {
    int64_t priority_;
    void *value_;
};

struct heap_t {
    HeapType type_;
    size_t max_size_, size_;
    Entry **entries_;
};


Heap* heap_create(HeapType type, size_t max_size) {
    Heap *heap = malloc(sizeof(Heap));

    assert(heap != NULL);

    heap->type_     = type;
    heap->max_size_ = max_size;
    heap->size_     = 0;
    heap->entries_  = (Entry**) malloc(max_size * sizeof(Entry*));

    assert(heap->entries_ != NULL);

    return heap;
}

void heap_double(Heap *const heap) {
    assert(heap != NULL);

    size_t new_size = 2 * heap->max_size_;

    heap->entries_ = (Entry**) realloc(heap->entries_, new_size * sizeof(Entry*));

    assert(heap->entries_ != NULL);

    heap->max_size_ = new_size;
}

void heapify_up(Heap *const heap, size_t index) {
    assert(heap != NULL);

    size_t parent = PARENT(index);

    if (parent < heap->size_ && heap->entries_[index]->priority_ > heap->entries_[parent]->priority_) {
        Entry *entry_index            = heap->entries_[index];

        heap->entries_[index]         = heap->entries_[parent];
        heap->entries_[parent] = entry_index;

        heapify_up(heap, parent);
    }
}

void heapify_down(Heap *const heap, size_t index) {
    assert(heap != NULL);

    size_t largest  = index;
    size_t left     = LEFT(index);
    size_t right    = RIGHT(index);

    if (left < heap->size_ && heap->entries_[left]->priority_ > heap->entries_[largest]->priority_)
        largest = left;

    if (right < heap->size_ && heap->entries_[right]->priority_ > heap->entries_[largest]->priority_)
        largest = right;

    if (largest != index) {
        Entry *entry_index      = heap->entries_[index];

        heap->entries_[index]   = heap->entries_[largest];
        heap->entries_[largest] = entry_index;

        heapify_down(heap, largest);
    }
}

void heap_push(Heap *const heap, int64_t priority, const void *const value, size_t num_bytes) {
    assert(heap  != NULL);
    assert(value != NULL);

    size_t new_index;
    Entry *new_entry = (Entry*) malloc(sizeof(Entry));

    assert(new_entry != NULL);

    new_entry->priority_ = priority;
    new_entry->value_    = malloc(sizeof(num_bytes));

    assert(new_entry->value_ != NULL);

    memcpy(new_entry->value_, value, num_bytes);

    if (heap->size_ == heap->max_size_)
        heap_double(heap);

    heap->entries_[heap->size_] = new_entry;

    new_index = heap->size_++;

    heapify_up(heap, new_index);
}

void heap_update_priority(Heap *const heap, int64_t current_priority, int64_t new_priority) {
    size_t index;

    for (index = 0; index < heap->size_ && heap->entries_[index]->priority_ != current_priority; index++);

    if (index < heap->size_) {
        heap->entries_[index]->priority_ = new_priority;

        if (new_priority > current_priority)
            heapify_up(heap, index);
        else
            heapify_down(heap, index);
    }

}

void heap_update_value(Heap *const heap, int64_t priority, const void *const new_value, size_t num_bytes) {
    size_t index;

    for (index = 0; index < heap->size_ && heap->entries_[index]->priority_ != priority; index++);

    if (index < heap->size_)
        memcpy(heap->entries_[index]->value_, new_value, num_bytes);
}

const void *const heap_peek(const Heap *const heap) {
    assert(heap != NULL);

    return heap->size_ == 0 ? NULL : (const void *const) heap->entries_[0]->value_;
}

void* heap_pop(Heap *const heap) {
    void *value = NULL;

    if (heap->size_ > 0) {
        value = heap->entries_[0]->value_;

        free(heap->entries_[0]);

        heap->entries_[0] = heap->entries_[--(heap->size_)];

        heapify_down(heap, 0);
    }

    return value;
}

void heap_free(Heap *heap) {
    size_t it;

    assert (heap != NULL);

    for (it = 0; it < heap->size_; it++) {
        free(heap->entries_[it]->value_);
        free(heap->entries_[it]);
    }

    free(heap->entries_);
    free(heap);
}
