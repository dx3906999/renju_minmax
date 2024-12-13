#include <stdlib.h>
#include "global.h"
#include "node.h"

Node* new_node(Node* parent, action_t action){
    Node* node=malloc(sizeof(Node));
    if (node)
    {
        node->parent=parent;
        node->child_num=0;
        node->action=action;
        if (parent)
        {
            parent->child_num++;
            parent->children[parent->child_num-1]=node;
        }
        
    }
    
    
}

