#ifndef OBSTACLESTATE_H
#define OBSTACLESTATE_H

#include "CellState.h"

class ObstacleState : public CellState {
public:
    ObstacleState() = default;

    // Un obstacle est considéré comme "non-vivant" pour le voisinage (comme un mur inerte)
    bool isAlive() const override { return false; }

    // C'est ici qu'on se distingue des autres
    bool isObstacle() const override { return true; }

    std::unique_ptr<CellState> clone() const override {
        return std::make_unique<ObstacleState>();
    }
};

#endif
