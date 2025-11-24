#ifndef DEADSTATE_H
#define DEADSTATE_H

#include <memory>	// Pour utiliser make_unique
#include "CellState.h"

class DeadState : public CellState {
public:
	// Constructeur
	DeadState() = default;

	bool isAlive() const override;

	// Retourne une nouvelle DeadState
	std::unique_ptr<CellState> clone() const override;
};

#endif
