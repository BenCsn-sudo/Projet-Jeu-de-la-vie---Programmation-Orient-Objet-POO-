#include "StandardRule.h"

bool StandardRule::willBeAlive(bool isAlive, int neighbours) const {

	// Si la cellule est morte : elle nait seulement si elle a exactement
	// 3 voisines vivantes.
	if (!isAlive) {
		return (neighbours == 3);
	}

	// Si la cellule est vivante : elle survit seulement si elle a 2 ou 3
	// voisines vivantes.
	if (neighbours == 2 || neighbours == 3) {
		return true;
	}

	// Sinon elle meurt
	return false;
}
