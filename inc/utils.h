#ifndef UTILS_H
#define UTILS_H

#include "evaluate.h"
#include <stdio.h>

typedef uint64_t hash_t;


typedef struct {
    value_t value;
    action_t index;
} HeapNode;



void swap_heap_node(HeapNode *a, HeapNode *b);
void heapify(HeapNode heap[], int size, int root);
void insert_heap(HeapNode heap[], int *size, value_t value, action_t index, int max_heap_size);
int compare_heap_node(const void *a, const void *b);
void restore_history_from_file(FILE* fp, State* state);
void store_history_to_file(action_t action, FILE* fp);
void print_action(action_t action);
#endif