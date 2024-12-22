#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Station *creerStation(int centrale, int lvStation, int entreprise, int individuel, double capacite, double charge) {
    Station *station = malloc(sizeof(Station));
    if (station == NULL) {
        perror("Erreur d'allocation memoire");
        exit(EXIT_FAILURE);
    }
    station->centrale = centrale;
    station->lvStation = lvStation;
    station->entreprise = entreprise;
    station->individuel = individuel;
    station->capacite = capacite;
    station->charge = charge;
    station->suivant= NULL;
    return station;
}

Station *ajouterStation(Station *liste, Station *nouvelleStation) {
    if (liste == NULL) {
        return nouvelleStation;
    }
    Station *temp = liste;
    while (temp->suivant != NULL) {
        temp = temp->suivant;
    }
    temp->suivant = nouvelleStation;
    return liste;
}

Station *lireFichierCSV(const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char ligne[256];
    fgets(ligne, sizeof(ligne), fichier); 

    Station *insererAVL = NULL;

    while (fgets(ligne, sizeof(ligne), fichier)) {
        int centrale, lvStation, entreprise = -1, individuel = -1;
        double capacite = 0, charge = 0;
        sscanf(ligne, "%2d;%2d;%2d;%2d;%2le;%2le\n", &centrale, &lvStation, &entreprise, &individuel, &capacite, &charge);

        if (entreprise == -1) entreprise = 0;
        if (individuel == -1) individuel = 0;

        Station *nouvelleStation = creerStation(centrale, lvStation, entreprise, individuel, capacite, charge);
        insererAVL = ajouterStation(insererAVL, nouvelleStation);
    }

    fclose(fichier);
    return insererAVL;
}


void exporterFichierCSV(const char *nomFichier, Station *tete) {
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        perror("Erreur lors de la creation du fichier");
        exit(EXIT_FAILURE);
    }

    fprintf(fichier, "centrale;LVStation;entreprise;Individuel;Capacite;charge\n");

    Station *temp = tete;
    while (temp != NULL) {
        fprintf(fichier, "%2d;%2d;%2d;%2d;%2f;%2f\n", temp->centrale, temp->lvStation, temp->entreprise,temp->individuel, temp->capacite, temp->charge);
        temp = temp->suivant;
    }

    fclose(fichier);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier_entree.csv> <fichier_sortie.csv>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *fichierEntree = argv[1];
    const char *fichierSortie = argv[2];

    Station *listeStations = lireFichierCSV(fichierEntree);

    exporterFichierCSV(fichierSortie, listeStations);

    printf("Les donnees ont ete exportees vers le fichier : %s\n", fichierSortie);

    Station *temp;
    while (listeStations != NULL) {
        temp = listeStations;
        listeStations = listeStations->suivant;
        free(temp);
    }

    return EXIT_SUCCESS;
}
