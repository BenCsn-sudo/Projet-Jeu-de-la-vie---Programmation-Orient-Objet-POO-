CXX = g++

# Dossiers d'include
INC_DIRS = -IComponents -IServices -IIhm -I"$(SFML_DIR)/include"

CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -O2 $(INC_DIRS)

# Dossiers de libs
LIB_DIRS = -L"$(SFML_DIR)/lib"

# Libs SFML à l’édition de liens
LDFLAGS = $(LIB_DIRS) -lsfml-graphics -lsfml-window -lsfml-system

# Tous les fichiers sources
SRC := $(wildcard main.cpp) \
       $(wildcard Components/*.cpp) \
       $(wildcard Components/*/*.cpp) \
       $(wildcard Services/*.cpp) \
       $(wildcard Services/*/*.cpp) \
       $(wildcard Ihm/*.cpp) \
       $(wildcard Ihm/*/*.cpp)

# Transformation en .o
OBJ = $(SRC:.cpp=.o)

# Nom de l'exécutable
BIN = jeu_de_la_vie

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $(BIN) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)
	rm -rf *_out
	rm -f input.txt_outfinal_grid.txt


.PHONY: all clean
