#include "Grid.h"
#include "DeadState.h"
#include "AliveState.h"
#include "CellRule.h"

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

// Compte le nombre de voisins vivants autour de la cellule (row, col)
//list des cellules voisines : (row-1,col-1) (row -1, col) ( row -1, col +1) (row, col+1) (row, col-1) (row+1,col -1) (row+1, col)(row+1, col+1)
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
        if (newRow >= 0 && newRow < height &&
            newCol >= 0 && newCol < width) {

            if (cells[newRow][newCol].isAlive()) {
                count++;
            }
        }
    }

    return count;
}
// Calcule la prochaine génération de la grille en appliquant les règles
void Grid::nextGeneration(const CellRule& rule) {
    // Grille tampon : même taille, toutes mortes au départ
    Grid next(width, height);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {

            bool aliveNow = cells[row][col].isAlive();
            int neighbours = countLivingNeighbours(row, col);

            // La règle décide si la cellule sera vivante à t+1
            bool aliveNext = rule.willBeAlive(aliveNow, neighbours);

            if (aliveNext)
                next.setAlive(row, col);
            else
                next.setDead(row, col);
        }
    }

    // Remplacer l'ancienne grille par la nouvelle
    *this = next;
}
