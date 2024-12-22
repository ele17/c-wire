#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

// Définition des structures
typedef struct Station {
    int centrale;
    int lvStation;
    int entreprise;
    int individuel;
    double capacite;
    double charge;
    struct Station *suivant;
} Station;

typedef struct StationAVL {
    Station *donnee;
    struct StationAVL *gauche;
    struct StationAVL *droit;
    int hauteur;
    int equilibre;
} StationAVL;

// Prototypes des fonctions
int hauteur(StationAVL *noeud);
void mettreAJourHauteur(StationAVL *noeud);
StationAVL *creerNoeud(Station *data);
StationAVL *insererAVL(StationAVL *racine, Station *nouvelleStation, double consommation, double capacite);
StationAVL *rotationGauche(StationAVL *noeud);
StationAVL *rotationDroite(StationAVL *noeud);
StationAVL *equilibrerAVL(StationAVL *noeud);
void freeAVL(StationAVL *racine);
void parcoursInfixe(StationAVL *racine);
void exportToCSV(StationAVL *racine, const char *filename);

#endif // AVL_H

	

