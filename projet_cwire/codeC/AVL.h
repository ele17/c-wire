#define AVL_H
#define AVL_H 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct AVLNoeud{
int id;
int capacité;
int consommation;
int hauteur;
struct AVLNoeud *fg;
struct AVLNoeud *fd;
}AVLNoeud;
