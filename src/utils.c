#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

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

int compare_heap_node(const void *a, const void *b){
    return ((HeapNode*)b)->value - ((HeapNode*)a)->value;
}


hash_t (*init_hash_board())[CHESSBOARD_LEN][2]{
    hash_t (*hash_board)[CHESSBOARD_LEN][2] = malloc(sizeof(hash_t)*CHESSBOARD_LEN*CHESSBOARD_LEN*2);
    srand(time(NULL));
    if (hash_board) 
    {
        for (size_t i = 0; i < CHESSBOARD_LEN; i++)
        {
            for (size_t j = 0; j < CHESSBOARD_LEN; j++)
            {
                for (size_t k = 0; k < 2; k++)
                {
                    hash_board[i][j][k]=(hash_t)((((hash_t)rand())<<(sizeof(int)*8))|rand());
                }

            }

        }
    }

    return hash_board;
    
    
}


hash_t update_hash(hash_t hash_current, hash_t hash_board[CHESSBOARD_LEN][CHESSBOARD_LEN][2], action_t action, player_t player){
    return hash_current ^ hash_board[action/CHESSBOARD_LEN][action%CHESSBOARD_LEN][player==WHITE?1:0];
}



