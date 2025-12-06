#ifndef SINGLETHREADUPDATER_H
#define SINGLETHREADUPDATER_H

#include "GridUpdater.h"

/*
Classe concrète qui implémente la stratégie de mise à jour
de la grille en mode Mono-thread (séquentiel).
 */
class SingleThreadUpdater : public GridUpdater {
public:

	std::string getName() const override { return "Mono-thread"; }

	void update(Grid& grid, const Rules& rule) override {

	/*
	Double Buffering : Création d'une grille tampon ('next').
	C'est crucial : on ne doit jamais écrire le résultat dans la grille
	que l'on est en train de lire (la grille 'grid' actuelle), sinon le calcul
	de la cellule suivante serait basé sur des données déjà mises à jour (erreur logique).
	*/
	Grid next(grid.getWidth(), grid.getHeight());

	// Les deux boucles imbriquées parcourent chaque cellule de la grille de manière ordonnée.
	for (int y = 0; y < grid.getHeight(); ++y) {
		for (int x = 0; x < grid.getWidth(); ++x) {

			// Logique standard : on lit l'état actuel de la cellule et de ses voisins.
			bool aliveNow = grid.getCell(y, x).isAlive();
			int neighbours = grid.countLivingNeighbours(y, x);

			// 3. Application des Règles : La classe Rule décide du prochain état.
			if (rule.willBeAlive(aliveNow, neighbours)) {
				// Si la règle dit de vivre, on met à jour la grille tampon (next), pas la grille source (grid).
				next.setAlive(y, x);
			} else {
				next.setDead(y, x);
			}
		}
        }

        // Validation : Remplacement de l'ancienne grille par la nouvelle.
        // 'swap' est la méthode la plus rapide pour échanger les données (les vecteurs 'cells')
        // entre la grille source et la grille tampon sans faire de copie coûteuse en mémoire.
        grid.swap(next);
    }
};

#endif
