#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

AVLNode* createNode(int id, int capacity) {
    AVLNode *node = malloc(sizeof(AVLNode));
    node->id = id;
    node->capacity = capacity;
    node->consumption = 0;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

void freeAVL(AVLNode *root) {
    if (root) {
        freeAVL(root->left);
        freeAVL(root->right);
        free(root);
    }
}

