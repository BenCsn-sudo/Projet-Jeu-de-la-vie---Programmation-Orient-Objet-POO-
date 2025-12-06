#ifndef ALIVESTATE_H
#define ALIVESTATE_H

#include <memory> 	// Pour std::unique_ptr
#include "CellState.h"

class AliveState : public CellState {
public:
	// Constructeur
	AliveState() = default;

	bool isAlive() const override;

	// Retourne une nouvelle AliveState
	std::unique_ptr<CellState> clone() const override;
};

#endif
