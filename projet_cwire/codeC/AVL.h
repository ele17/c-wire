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

int equilibreArbre (Arbre *a, int elmt){
}
int rotationDroite (Arbre *a, int elmt){
}
int rotationGauche (Arbre *a, int elmt){
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

