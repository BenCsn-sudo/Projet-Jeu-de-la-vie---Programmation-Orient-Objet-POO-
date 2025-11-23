#include "Game.h"
#include <iostream>

// Constructeur : copie la grille reçue, stocke la règle et le nombre d'itérations.
Game::Game(const Grid& g, const CellRule& r, int iter)
    : grid(g), rule(r), iterations(iter) {}


// Exécute la simulation complète
void Game::run() {
    std::cout << "État initial :\n";
    print();

    for (int i = 1; i <= iterations; ++i) {
        nextStep();
        std::cout << "\nAprès iteration " << i << " :\n";
        print();
    }
}


// Applique une génération du Jeu de la Vie
void Game::nextStep() {
    grid.nextGeneration(rule);
}


// Affiche la grille actuelle
void Game::print() const {
    grid.print();
}