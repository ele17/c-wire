# Nom de l'exécutable
TARGET = c-wire

# Fichiers sources
SRC = c-wire.c AVL.c

# Fichiers objets (générés automatiquement)
OBJ = $(SRC:.c=.o)

# Commande de compilation et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Règle principale : générer l'exécutable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Règle pour générer les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJ) $(TARGET)