#include "Game.h"

#include <iostream>

// Copie la grille recue, stocke la règle et le nombre d'itération
Game::Game(const Grid& g, const Rules& r, int iter) : grid(g), rule(r), iterations(iter) {}

// Execute la simulation complète
void Game::run() {

	std::cout << "Etat initial :\n" << std::endl;
	print();

	for (int i = 1; i <= iterations; ++i) {
		nextStep();
		std::cout << "\nAprès " << i << " itérations:\n" << std::endl;
		print();
	}
}

// Applique une génération du Jeu de la vie
void Game::nextStep() {
	grid.nextGeneration(rule);
}

// Affiche la grille actuelle
void Game::print() const {
	grid.print();
}
