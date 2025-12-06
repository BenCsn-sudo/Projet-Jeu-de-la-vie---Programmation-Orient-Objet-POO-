#ifndef GAME_H
#define GAME_H

#include <memory>

#include "Grid/Grid.h"
#include "Rules/Rules.h"
#include "Updaters/GridUpdater.h"


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
	std::unique_ptr<GridUpdater> updater;
	std::string updaterName;

public:
	// Constructeur
	Game(const Grid& g, const Rules& r, int iter, std::unique_ptr<GridUpdater> u, std::string name);

	// Méthodes interne : applique la prochaine génération
	void nextStep();

	// Affiche l'état actuel de la grille
	void print() const;

	// Getter de la grille
	const Grid& getGrid() const { return grid; }

	std::string getUpdaterName() const { return updaterName; }
};

#endif
