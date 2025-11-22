#include "Grid.h"
#include "DeadState.h"
#include "AliveState.h"
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
            if (cells[row][col].isAlive())
                std::cout << "1 ";
            else
                std::cout << "0 ";
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
