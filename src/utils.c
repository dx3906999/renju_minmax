#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

void swap_heap_node(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(HeapNode heap[], int size, int root) {
    int smallest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && heap[left].value < heap[smallest].value)
        smallest = left;
    if (right < size && heap[right].value < heap[smallest].value)
        smallest = right;

    if (smallest != root) {
        swap_heap_node(&heap[root], &heap[smallest]);
        heapify(heap, size, smallest);
    }
}

void insert_heap(HeapNode heap[], int *size, value_t value, action_t index, int max_heap_size) {
    if (*size < max_heap_size) {
        heap[*size].value = value;
        heap[*size].index = index;
        (*size)++;

        for (int i = (*size - 1) / 2; i >= 0; i--)
        {
            heapify(heap, *size, i);
        }

    } else if (value > heap[0].value) {
        heap[0].value = value;
        heap[0].index = index;
        heapify(heap, *size, 0);
    }

}



