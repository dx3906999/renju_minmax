#ifndef NODE_H
#define NODE_H

#include "evaluate.h"
#include "global.h"

#define MAX_CHILD 10

typedef struct Node Node;

struct Node{
    Node* parent;
    Node* children[MAX_CHILD];
    value_t value;
    int child_num;
    action_t action;
};


#endif