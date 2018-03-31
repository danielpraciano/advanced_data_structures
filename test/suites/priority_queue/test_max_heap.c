#include <priority_queue/heap.h>

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    int n = 5, max_size_initial = 5, i;
    const char *const heap_name = "Max Heap";
    void *priority, *value;

    printf("Enter the param n: ");
    scanf("%d", &n);

    printf("Creating %s...\n", heap_name);

    Heap *heap = heap_create(MAX_HEAP, max_size_initial);

    printf("%s created...\n", heap_name);

    printf("Inserting priority 1 and value 1 into %s...\n", heap_name);

    priority = malloc(sizeof(int));
    value = malloc(sizeof(int));

    (*(int*) priority) = 1;
    (*(int*) value) = 1;

    heap_push(heap, (*(int*) priority), value, 4);

    printf("Priority 1 and value 1 was inserted into %s...\n", heap_name);

    printf("Inserting Priority 2 and value 2 into %s...\n", heap_name);

    priority = malloc(sizeof(int));
    value = malloc(sizeof(int));

    (*(int*) priority) = 2;
    (*(int*) value) = 2;

    heap_push(heap, (*(int*) priority), value, 4);

    printf("Priority 2 and value 2 was inserted into %s...\n", heap_name);

    printf("Inserting Priority 3 and value 3 into %s...\n", heap_name);

    priority = malloc(sizeof(int));
    value = malloc(sizeof(int));

    (*(int*) priority) = 3;
    (*(int*) value) = 3;

    heap_push(heap, (*(int*) priority), value, 4);

    printf("Priority 3 and value 3 was inserted into %s...\n", heap_name);

    printf("Inserting Priority 4 and value 4 into %s...\n", heap_name);

    priority = malloc(sizeof(int));
    value = malloc(sizeof(int));

    (*(int*) priority) = 4;
    (*(int*) value) = 4;

    heap_push(heap, (*(int*) priority), value, 4);

    printf("Priority 4 and value 4 was inserted into %s...\n", heap_name);

    printf("Inserting Priority 5 and value 5 into %s...\n", heap_name);

    priority = malloc(sizeof(int));
    value = malloc(sizeof(int));

    (*(int*) priority) = 5;
    (*(int*) value) = 5;

    heap_push(heap, (*(int*) priority), value, 4);

    printf("Priority 5 and value 5 was inserted into %s...\n", heap_name);

    printf("Inserting Priority 6 and value 6 into %s...\n", heap_name);

    priority = malloc(sizeof(int));
    value = malloc(sizeof(int));

    (*(int*) priority) = 6;
    (*(int*) value) = 6;

    heap_push(heap, (*(int*) priority), value, 4);

    printf("Priority 6 and value 6 was inserted into %s...\n", heap_name);

    printf("Searching the root in %s...\n", heap_name);

    value = (void*) heap_peek(heap);

    if (value != NULL) {
        printf("The root value is %d in %s...\n", (*(int32_t*) value), heap_name);
    } else {
        printf("There's no value in %s...\n", heap_name);
    }

    for (i = 0; i < 6; i++) {

        printf("Removing the root value in %s...\n", heap_name);

        value = (void*) heap_pop(heap);

        if (value != NULL) {
            printf("The value %d was removed of %s...\n", (*(int32_t*) value), heap_name);
        } else {
            printf("There's no value in %s...\n", heap_name);
        }

        printf("Searching the root in %s...\n", heap_name);

        value = (void*) heap_peek(heap);

        if (value != NULL) {
            printf("The root value is %d in %s...\n", (*(int32_t*) value), heap_name);
        } else {
            printf("There's no value in %s...\n", heap_name);
        }

    }

    printf("Inserting Priority 1 and value 1 into %s...\n", heap_name);

    priority = malloc(sizeof(int));
    value = malloc(sizeof(int));

    (*(int*) priority) = 1;
    (*(int*) value) = 1;

    heap_push(heap, (*(int*) priority), value, 4);

    printf("Priority 1 and value 1 was inserted into %s...\n", heap_name);

    printf("Searching the root in %s...\n", heap_name);

    value = (void*) heap_peek(heap);

    if (value != NULL) {
        printf("The root value is %d in %s...\n", (*(int32_t*) value), heap_name);
    } else {
        printf("There's no value in %s...\n", heap_name);
    }

    printf("Changing the value 1 to 5 in %s...\n", heap_name);

    (*(int*) value) = 5;

    heap_update_value(heap, 1, value, 4);

    printf("Searching the root in %s...\n", heap_name);

    void* value2 = (void*) heap_peek(heap);

    if (value2 != NULL) {
        printf("The root value is %d in %s...\n", (*(int32_t*) value2), heap_name);
    } else {
        printf("There's no value in %s...\n", heap_name);
    }

    printf("Finally, freeing %s...\n", heap_name);

    heap_free(heap);

    printf("%s was freed...\n", heap_name);

    return EXIT_SUCCESS;
}
