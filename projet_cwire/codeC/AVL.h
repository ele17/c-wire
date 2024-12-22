#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

typedef struct StationListe {
    Station *station;
    struct StationListe *suivant;
} StationListe;

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
