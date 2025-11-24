#include "Game.h"

#include <iostream>

// Copie la grille recue, stocke la règle et le nombre d'itération
Game::Game(const Grid& g, const Rules& r, int iter) : grid(g), rule(r), iterations(iter) {}

// Applique une génération du Jeu de la vie
void Game::nextStep() {
	print();
	grid.nextGeneration(rule);
}

// Affiche la grille actuelle
void Game::print() const {
	grid.print();
}
