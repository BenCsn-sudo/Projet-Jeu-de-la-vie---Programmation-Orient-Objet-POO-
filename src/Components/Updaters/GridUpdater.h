#ifndef IGRIDUPDATER_H
#define IGRIDUPDATER_H

#include "../Grid/Grid.h"
#include "../Rules/Rules.h"

class GridUpdater {
public:
	virtual ~GridUpdater() = default;

	virtual std::string getName() const = 0;

	// Contrat : Je prends une grille et une règle, et je mets à jour la grille.
	virtual void update(Grid& grid, const Rules& rule) = 0;
};

#endif
