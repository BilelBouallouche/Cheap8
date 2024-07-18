# Nom de l'exécutable
EXEC = chip8

# Compilateur
CC = gcc


# Options de compilation
CFLAGS = -Wall -std=c99 -I$(RAYLIB_DIR)/includ

# Options d'édition de liens
LDFLAGS = -L$(RAYLIB_DIR)/lib -lraylib -lgdi32 -lwinmm

# Répertoires des sources et des objets
SRC_DIR = src
OBJ_DIR = obj

# Chercher tous les fichiers source dans SRC_DIR et remplacer l'extension .c par .o pour les objets
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Règle par défaut
all: $(EXEC)

# Règle pour créer l'exécutable
$(EXEC): $(OBJ_FILES)
	$(CC) $^ -o $@ $(LDFLAGS)

# Règle pour créer les fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Créer le répertoire obj si nécessaire
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Règle pour nettoyer les fichiers générés
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

# Règle pour tout nettoyer
distclean: clean
	rm -rf $(OBJ_DIR)

# Ignorer les erreurs de makedepend
.PHONY: clean distclean

# Supprimer les lignes générées par makedepend
# DO NOT DELETE

