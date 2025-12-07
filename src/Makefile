# --- Makefile ---

# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -O2


# --- CHEMINS VERS LA LIBRAIRIE LOCALE (IMPORTANT) ---
# On pointe vers le dossier lib qu'on vient de créer
SFML_PATH = ../lib/linux
INCLUDES = -IComponents -IServices -IIhm -I$(SFML_PATH)/include
LIBS_DIR = -L$(SFML_PATH)/lib

# Options de l'éditeur de liens (Linker)
# -Wl,-rpath... permet à l'exécutable de trouver les .so sans définir LD_LIBRARY_PATH à chaque fois
LDFLAGS = $(LIBS_DIR) -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,'$$ORIGIN/../lib/linux/lib'


# Fichiers sources (Automatique)
SRCS = main.cpp \
       Components/Game.cpp \
       Components/Cell/AliveState.cpp \
       Components/Cell/DeadState.cpp \
       Components/Grid/Grid.cpp \
       Components/Rules/StandardRule.cpp \
       Components/Updaters/MultiThreadUpdater.cpp \
       Services/GameRunner.cpp \
       Services/IO/FileName.cpp \
       Services/IO/FileReader.cpp \
       Services/IO/FileWriter.cpp \
       Services/IO/FolderManager.cpp \
       Services/WorkerPool/WorkerPool.cpp \
       Ihm/GameWindow.cpp

# Fichiers objets
OBJS = $(SRCS:.cpp=.o)

# Nom de l'exécutable
TARGET = jeu_de_la_vie

# Règle par défaut
all: $(TARGET)

# Édition de liens
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compilation des .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf input_obstacles.txt_out
	rm -rf jeu_de_la_vie
	rm -f input_obstacles.txt_outfinal_grid.txt



.PHONY: all clean

