#ifndef STANDARDRULE_H
#define STANDARDRULE_H

#include "Rules.h"

/*
Implémentation des règles classiques du Jeu de la vie de Conway.
Cette classe décide si une cellule sera vivante à la prochaine
génération selon son état actuel et le nombre de voisine vivante.
*/
class StandardRule : public Rules {
public:
	/*
	Implémentation des règles:
		- Une cellule morte devient vivante si elle a exactement
		  3 voisines vivantes.
		- Une cellule vivante reste vivante si elle a 2 ou 3 voisine
		  vivantes.
	*/
	bool willBeAlive(bool isAlive, int neighbours) const override;
};

#endif
