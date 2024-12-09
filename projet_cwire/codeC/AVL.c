#include "avl.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <fichier_csv>\n", argv[0]);
        return 1;
    }

    Noeud *racine = processCSV(argv[1]);
    if (racine == NULL) {
        return 1;
    }

    printf("Données traitées:\n");
    infixe(racine);
  
    return 0;
}
