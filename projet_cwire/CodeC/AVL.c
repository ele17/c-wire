#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>

int hauteur(StationAVL *noeud) {
    return noeud ? noeud->hauteur : 0;
}

void mettreAJourHauteur(StationAVL *noeud) {
    if (noeud) {
        int hauteurGauche = hauteur(noeud->gauche);
        int hauteurDroit = hauteur(noeud->droit);
        noeud->hauteur = 1 + (hauteurGauche > hauteurDroit ? hauteurGauche : hauteurDroit);
        noeud->equilibre = hauteurDroit - hauteurGauche;
    }
}

StationAVL *creerNoeud(Station *data) {
    StationAVL *noeud = (StationAVL *)malloc(sizeof(StationAVL));
    if (noeud == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    noeud->donnee = data;
    noeud->gauche = NULL;
    noeud->droit = NULL;
    noeud->hauteur = 1;
    noeud->equilibre = 0;
    return noeud;
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
    }
    if (noeud->equilibre < -1) {
        if (noeud->gauche && noeud->gauche->equilibre > 0) {
            noeud->gauche = rotationGauche(noeud->gauche);
        }
        return rotationDroite(noeud);
    }

    return noeud;
}

StationAVL *insererAVL(StationAVL *racine, Station *nouvelleStation, double consommation, double capacite) {
    if (racine == NULL) {
        return creerNoeud(nouvelleStation);
    }

    if (nouvelleStation->lvStation < racine->donnee->lvStation) {
        racine->gauche = insererAVL(racine->gauche, nouvelleStation, consommation, capacite);
    } else if (nouvelleStation->lvStation > racine->donnee->lvStation) {
        racine->droit = insererAVL(racine->droit, nouvelleStation, consommation, capacite);
    } else {
        racine->donnee->capacite += capacite;
        racine->donnee->charge += consommation;
        return racine;
    }

    mettreAJourHauteur(racine);
    return equilibrerAVL(racine);
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
    if (racine != NULL) {
        parcoursInfixe(racine->gauche);
        printf("centrale: %d, lvStation: %d, entreprise: %d, individuel: %d, capacite: %.2f, charge: %.2f\n",
               racine->donnee->centrale, racine->donnee->lvStation, racine->donnee->entreprise,
               racine->donnee->individuel, racine->donnee->capacite, racine->donnee->charge);
        parcoursInfixe(racine->droit);
    }
}

void ecrireCSV(StationAVL *racine, FILE *fichier) {
    if (racine != NULL) {
        ecrireCSV(racine->gauche, fichier);
        fprintf(fichier, "%d;%d;%d;%d;%.2f;%.2f\n",
                racine->donnee->centrale, racine->donnee->lvStation, racine->donnee->entreprise,
                racine->donnee->individuel, racine->donnee->capacite, racine->donnee->charge);
        ecrireCSV(racine->droit, fichier);
    }
}

void exportToCSV(StationAVL *racine, const char *filename) {
    FILE *fichier = fopen(filename, "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    fprintf(fichier, "centrale;LVStation;entreprise;Individuel;Capacite;charge\n");
    ecrireCSV(racine, fichier);
    fclose(fichier);
}

	
