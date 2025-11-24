CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -O2 -IComponents -IServices -IIhm
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

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

.PHONY: all clean
