#include "avl.h"

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

