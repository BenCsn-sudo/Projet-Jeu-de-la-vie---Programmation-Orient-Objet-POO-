#include "Grid.h"
#include "../Cell/DeadState.h"
#include "../Cell/AliveState.h"
#include <iostream>
/*
Description du construceur, il initialise les différentes cellules
indépendemment pour ne pas utiliser les copies et risquer une erreur mémoire
Il va falloir changer cette partie pour initialiser avec les données du .txt
*/
Grid::Grid(int w, int h) : width(w), height(h), cells(h, std::vector<Cell>()) {

	for (int row = 0; row < height; ++row) {
		cells[row].reserve(width);

		for (int col = 0; col < width; ++col) {
    			cells[row].emplace_back(new DeadState());
		}
	}
}

//Méthode pour afficher la grille dans la console
void Grid::print() const {

	for (int row = 0; row < height; ++row) {

        	for (int col = 0; col < width; ++col) {

            		if (cells[row][col].isAlive()) {
                		std::cout << "1 ";
            		} else {
                		std::cout << "0 ";
			}
        	}
        	std::cout << '\n';
    	}
}

//Méthode pour changer l'état d'une cellule en vivante
void Grid::setAlive(int row, int col) {
	cells[row][col].setState(new AliveState());
}

void Grid::setDead(int row, int col) {
	cells[row][col].setState(new DeadState());
}


// Compte le nombre de voisins vivants autour de la cellule (row, col)
int Grid::countLivingNeighbours(int row, int col) const {

	int count = 0;

	// Les 8 directions
	const int directions[8][2] = {
		{-1, -1}, {-1, 0}, {-1, +1},
		{ 0, -1},          { 0, +1},
		{+1, -1}, {+1, 0}, {+1, +1}
	};

	for (const auto& d : directions) {
        	int newRow = row + d[0];
        	int newCol = col + d[1];

        	// Vérification des limites de la grille
        	if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width) {

            		if (cells[newRow][newCol].isAlive()) {
                		count++;
            		}
        	}
    	}

    	return count;
}


void Grid::swap(Grid& other) {
	// Echange efficace des données sans tout recopier
	std::swap(width, other.width);
	std::swap(height, other.height);
	std::swap(cells, other.cells);
}
