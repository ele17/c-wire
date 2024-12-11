#define AVL_H
#define AVL_H 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Station{
int id;
char type [10];
double capacité;
double charge;
}Station;

typedef struct StationAVL {
Station *donnee;
struct StationAVL *droit;
struct StationAVL *gauche;
int hauteur;
int equilibre=0;
}StationAVL;

typedef struct StationListe{
Station *station;
struct StationListe *suivant;
}StationListe;

AVLNoeud* creerNoeud(int elmt, int capacité) {
    AVLNoeud *noeud = malloc(sizeof(AVLNoeud));
    noeud->id = id;
    noeud->capacité= capacité;
    noeud->consommation = 0;
    noeud->hauteur = 1;
    noeud->gauche = noeud->right = NULL;
    return noeud;
}

AVL* insertionAVL(AVL* a, int e, int *h)
{
    if (a == NULL)
    {           
        *h = 1; 
        return creerAVL(e);
    }
    else if (e < a->value)
    { /
        a->fg = insertionAVL(a->fg, e, h);
        *h = -*h; 
    }
    else if (e > a->value)
    { 
        a->fd = insertionAVL(a->fd, e, h);
    }
    else
    { // Élément déjà présent
        *h = 0;
        return a;
    }

    if (*h != 0)
    {
        a->eq += *h;
        a = equilibrerAVL(a);
        *h = (a->eq == 0) ? 0 : 1; // Mise à jour de la hauteur
    }
    return a;
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

AVL* equilibrerAVL(AVL* a)
{
    if (a->eq >= 2) {
        if (a->fd->eq >= 0)
        {
            return rotationGauche(a); 
        }
        else
        {
            return doubleRotationGauche(a);
    }
    else if (a->eq <= -2)
    { 
        if (a->fg->eq <= 0)
        {
            return rotationDroite(a); 
        }
        else
        {
            return doubleRotationDroite(a); 
        }
    }
    return a; 
}

    AVL* rotationGauche(AVL* a) {
    AVL* pivot = a->fd; 
    int eq_a = a->eq, eq_p = pivot->eq;

    a->fd = pivot->fg; 
    pivot->fg = a;    
        
    a->eq = eq_a - max(eq_p, 0) - 1;
    pivot->eq = min3(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);

    return pivot; 
}

AVL* rotationDroite(AVL* a)
{
    AVL* pivot = a->fg; 
    int eq_a = a->eq, eq_p = pivot->eq;

    a->fg = pivot->fd; 
    pivot->fd = a;    

    a->eq = eq_a - min(eq_p, 0) + 1;
    pivot->eq = max3(eq_a + 2, eq_a + eq_p + 2, eq_p + 1);

    return pivot; 
}


StationAVL* creerNoeud (Station *data);
StationAVL* insererAVL(StationAVL *racine, Station *data);
StationAVL* equilibreArbre(StationAVL *noeud);
StationAVL* rotationGauche(StationAVL *noeud);
StationAVL* rotationDroit(StationAVL *noeud);
void freeAVL(StationAVL *racine);

StationListe* insererStationListe(StationList *liste, Station *station);
void freeStationListz(StationListe *liste);

void exportToCSV(StationAVL *racine, const char *filename);
void analyseStations(StationAVL *racine);

