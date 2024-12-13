#ifndef UTILS_H
#define UTILS_H

#include "evaluate.h"

typedef struct {
    value_t value;
    int index;
} HeapNode;

void swap_heap_node(HeapNode *a, HeapNode *b);
void heapify(HeapNode heap[], int size, int root);
void insert_heap(HeapNode heap[], int *size, int value, int index, int max_heap_size);

#endif