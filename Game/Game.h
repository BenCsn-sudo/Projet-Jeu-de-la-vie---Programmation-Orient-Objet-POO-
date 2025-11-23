#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "CellRule.h"

/*
Classe Game : orchestrateur du Jeu de la Vie.
Elle ne modifie pas les règles, ni la logique interne de la grille.
Elle gère simplement :
- la grille actuelle
- la règle à utiliser (polymorphisme)
- le nombre d'itérations
- le déroulement du jeu (run)
*/
class Game {
private:
    Grid grid;
    const CellRule& rule;
    int iterations;

public:
    // Constructeur principal
    Game(const Grid& g, const CellRule& r, int iter);

    // Lance la simulation : affiche la grille, applique les règles n fois
    void run();

    // Méthode interne : applique la prochaine génération
    void nextStep();

    // Affiche l'état actuel de la grille
    void print() const;

    //Getter de la grille
    const Grid& getGrid() const { return grid; }

};

#endif // GAME_H
