#define AVL_H
#define AVL_H 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct AVLNode{
int id;
int capacity;
int consumption;
int height;
struct AVLNode *fg;
struct AVLNode *fd;
}AVLNode;
