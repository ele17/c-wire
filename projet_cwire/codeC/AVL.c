#include <stdio.h>
typedef struct AVLNoeud{
    int id;
    int capacite;
    int consommation;
    int hauteur;
    struct AVLNoeud *gauche;
    struct AVLNoeud *droit;
} AVLNoeud;

AVLNoeud* creeNoeud(int id, int capacite);
AVLNoeud* inserer(AVLNoeud *racine, int id, int capacite, int consommation);
void inOrderTraversal(AVLNode *racine, FILE *outputFile);
void freeAVL(AVLNoeud *racine);
