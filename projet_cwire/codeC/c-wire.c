#include <stdio.h>
#include "avl.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    AVLNoeud *racine = NULL;
    int id, capacite, consommation;

    while (fscanf(file, "%d;%d;%d", &id, &capacite, &consommation) == 3) {
        racine = inserer(racine, id, capacite, consommation);
    }

    fclose(file);
    freeAVL(racine);

    return 0;
}
