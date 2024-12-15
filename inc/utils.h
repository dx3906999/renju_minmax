#ifndef UTILS_H
#define UTILS_H

#include "evaluate.h"

typedef uint64_t hash_t;


typedef struct {
    value_t value;
    action_t index;
} HeapNode;



void swap_heap_node(HeapNode *a, HeapNode *b);
void heapify(HeapNode heap[], int size, int root);
void insert_heap(HeapNode heap[], int *size, value_t value, action_t index, int max_heap_size);
int compare_heap_node(const void *a, const void *b);

#endif