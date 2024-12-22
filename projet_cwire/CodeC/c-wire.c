#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Station *creerStation(int centrale, int lvStation, int entreprise, int individuel, double capacite, double charge) {
    Station *station = malloc(sizeof(Station));
    if (station == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    station->centrale = centrale;
    station->lvStation = lvStation;
    station->entreprise = entreprise;
    station->individuel = individuel;
    station->capacite = capacite;
    station->charge = charge;
    station->suivant = NULL;
    return station;
}

StationAVL *lireFichierCSV(const char *nomFichier, StationAVL *racine) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char ligne[256];
    fgets(ligne, sizeof(ligne), fichier); // Ignorer l'en-tête.

    while (fgets(ligne, sizeof(ligne), fichier)) {
        int centrale = 0, lvStation = 0, entreprise = 0, individuel = 0;
        double capacite = 0.0, charge = 0.0;

        char capaciteStr[50], chargeStr[50], entrepriseStr[50], individuelStr[50];
        sscanf(ligne, "%d;%d;%49[^;];%49[^;];%49[^;];%49[^;\n]",
               &centrale, &lvStation, entrepriseStr, individuelStr, capaciteStr, chargeStr);

        // Gérer les champs manquants (`-`).
        entreprise = (strcmp(entrepriseStr, "-") == 0) ? 0 : atoi(entrepriseStr);
        individuel = (strcmp(individuelStr, "-") == 0) ? 0 : atoi(individuelStr);
        capacite = (strcmp(capaciteStr, "-") == 0) ? 0.0 : atof(capaciteStr);
        charge = (strcmp(chargeStr, "-") == 0) ? 0.0 : atof(chargeStr);

        // Créer une station et l'insérer dans l'arbre AVL.
        Station *nouvelleStation = creerStation(centrale, lvStation, entreprise, individuel, capacite, charge);
        racine = insererAVL(racine, nouvelleStation, charge, capacite);
    }

    fclose(fichier);
    return racine;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier_entree.csv> <fichier_sortie.csv>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *fichierEntree = argv[1];
    const char *fichierSortie = argv[2];

    StationAVL *racine = NULL;
    racine = lireFichierCSV(fichierEntree, racine);

    printf("Exportation des données vers %s...\n", fichierSortie);
    exportToCSV(racine, fichierSortie);

    printf("Exportation terminée. Libération de la mémoire...\n");
    freeAVL(racine);
    printf("Mémoire libérée. Programme terminé.\n");

    return EXIT_SUCCESS;
}

	
