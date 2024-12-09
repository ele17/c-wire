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
int equilibre=0;
struct AVLNoeud *fg;
struct AVLNoeud *fd;
}AVLNoeud;

AVLNoeud* creerNoeud(int elmt, int capacité) {
    AVLNoeud *noeud = malloc(sizeof(AVLNoeud));
    noeud->id = id;
    noeud->capacité= capacité;
    noeud->consommation = 0;
    noeud->hauteur = 1;
    noeud->gauche = noeud->right = NULL;
    return noeud;
}

int recherche(int elmt, int capacité){
if(capacité==NULL){
free (1);
}
if (capacité->elmt == capacité) {
        return a; 
    }
    if (capacité < capacité->elmt {
        return recherche(capacité->fg, e);
    } else {
        return recherche(capacité->fd, e); 
    }
}

void freeAVL(AVLNode *racine) {
    if (racine) {
        freeAVL(racine->gauche);
        freeAVL(racine->droit);
        free(racine);
    }
}
void infixe (Noeud *racine) {
    if (racine != NULL) {
        infixe(racine->gauche);
        printf("Station ID: %s, Consommation: %.2f\n", racine->stationId, racine->consommation); 
        infixe (racine->droit);
    }
}

