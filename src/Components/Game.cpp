#include "Game.h"

#include <iostream>

// Copie la grille recue, stocke la règle et le nombre d'itération
Game::Game(const Grid& g, const Rules& r, int iter, std::unique_ptr<GridUpdater> u, std::string name)
    : grid(g), rule(r), iterations(iter), updater(std::move(u)), updaterName(name) {}

// Applique une génération du Jeu de la vie
void Game::nextStep() {
	print();
	updater->update(grid, rule);
}

// Affiche la grille actuelle
void Game::print() const {
	grid.print();
}
