#ifndef UTILS_H
#define UTILS_H

#include "evaluate.h"

typedef struct {
    value_t value;
    action_t index;
} HeapNode;

void swap_heap_node(HeapNode *a, HeapNode *b);
void heapify(HeapNode heap[], int size, int root);
void insert_heap(HeapNode heap[], int *size, value_t value, action_t index, int max_heap_size);

#endif