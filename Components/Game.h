#ifndef GAME_H
#define GAME_H

#include "Grid/Grid.h"
#include "Rules/Rules.h"

/*
Orchestre du jeu de la vie:
Gère:
	- la grille actuelle
	- la règle à utiliser (polymorphisme)
	- le nombre d'itérations
	- le déroulement du jeu (run)
*/
class Game {
private:
	Grid grid;
	const Rules& rule;
	int iterations;
public:
	// Constructeur
	Game(const Grid& g, const Rules& r, int iter);

	// Méthodes interne : applique la prochaine génération
	void nextStep();

	// Affiche l'état actuel de la grille
	void print() const;

	// Getter de la grille
	const Grid& getGrid() const { return grid; }
};

#endif
