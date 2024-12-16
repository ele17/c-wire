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
int equilibre;
}StationAVL;

typedef struct StationListe{
Station *station;
struct StationListe *suivant;
}StationListe;

int hauteur(StationAVL *noeud){
return noeud ? noeud->hauteur : 0;

void mettreAJourHauteur(StationAVL *noeud) {
    if (noeud) {
        noeud->hauteur = 1 + (hauteur(noeud->gauche) > hauteur(noeud->droit) ? hauteur(noeud->gauche) : hauteur(noeud->droit));
        noeud->equilibre = hauteur(noeud->droit) - hauteur(noeud->gauche);
    }
}

StationAVL *creerNoeud(Station *data) {
    StationAVL *noeud = (StationAVL *)malloc(sizeof(StationAVL));
    noeud->donnee = data;
    noeud->gauche = NULL;
    noeud->droit = NULL;
    noeud->hauteur = 1;
    noeud->equilibre = 0;
    return noeud;
}

StationAVL *insererAVL(StationAVL *racine, Station *data) {
    if (!racine) {
        return creerNoeud(data);
    }

    if (data->id < racine->donnee->id) {
        racine->gauche = insererAVL(racine->gauche, data);
    } else if (data->id > racine->donnee->id) {
        racine->droit = insererAVL(racine->droit, data);
    } else {

        return racine;
    }

    return equilibrerAVL(racine);
}

StationAVL *rotationGauche(StationAVL *noeud) {
    StationAVL *pivot = noeud->droit;
    noeud->droit = pivot->gauche;
    pivot->gauche = noeud;
    mettreAJourHauteur(noeud);
    mettreAJourHauteur(pivot);
    return pivot;
}

StationAVL *rotationDroite(StationAVL *noeud) {
    StationAVL *pivot = noeud->gauche;
    noeud->gauche = pivot->droit;
    pivot->droit = noeud;
    mettreAJourHauteur(noeud);
    mettreAJourHauteur(pivot);
    return pivot;
}
StationAVL *equilibrerAVL(StationAVL *noeud) {
    mettreAJourHauteur(noeud);

    if (noeud->equilibre > 1) {
        if (noeud->droit && noeud->droit->equilibre < 0) {
            noeud->droit = rotationDroite(noeud->droit);
        }
        return rotationGauche(noeud);
    } else if (noeud->equilibre < -1) {
        if (noeud->gauche && noeud->gauche->equilibre > 0) {
            noeud->gauche = rotationGauche(noeud->gauche);
        }
        return rotationDroite(noeud);
    }

    return noeud;
}

void freeAVL(StationAVL *racine) {
    if (racine) {
        freeAVL(racine->gauche);
        freeAVL(racine->droit);
        free(racine->donnee);
        free(racine);
    }
}

void parcoursInfixe(StationAVL *racine) {
    if (racine) {
        parcoursInfixe(racine->gauche);
        printf("Station ID: %d, Type: %s, Capacité: %.2f, Charge: %.2f\n",
               racine->donnee->id, racine->donnee->type, racine->donnee->capacite, racine->donnee->charge);
        parcoursInfixe(racine->droit);
    }
}

void exportToCSV(StationAVL *racine, const char *filename) {
    FILE *fichier = fopen(filename, "w");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    fprintf(fichier, "ID,Type,Capacite,Charge\n");

    if (racine) {
        exportToCSV(racine->gauche, filename);
        fprintf(fichier, "%d,%s,%.2f,%.2f\n",
                racine->donnee->id, racine->donnee->type, racine->donnee->capacite, racine->donnee->charge);
        exportToCSV(racine->droit, filename);
    }

    fclose(fichier);
}
