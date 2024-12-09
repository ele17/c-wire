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

AVLNoeud* creerNoeud(int elmt, int capacité) {
    AVLNoeud *noeud = malloc(sizeof(AVLNoeud));
    noeud->id = id;
    noeud->capacité = capacité;
    noeud->consommation = 0;
    noeud->hauteur = 1;
    noeud->gauche = noeud->right = NULL;
    return noeud;
}

void freeAVL(AVLNode *racine) {
    if (racine) {
        freeAVL(racine->gauche);
        freeAVL(racine->droit);
        free(racine);
    }
}


