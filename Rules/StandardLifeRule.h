#ifndef STANDARDLIFERULE_H
#define STANDARDLIFERULE_H

#include "CellRule.h"

// Implémentation des règles classiques du Jeu de la Vie de Conway.
// Cette classe décide si une cellule sera vivante à la prochaine génération
// en fonction de son état actuel et du nombre de voisines vivantes.
class StandardLifeRule : public CellRule {
public:
    // Implémentation des règles :
    // - Une cellule morte devient vivante si elle a exactement 3 voisines vivantes.
    // - Une cellule vivante reste vivante si elle a 2 ou 3 voisines vivantes.
    bool willBeAlive(bool isAlive, int neighbours) const override;
};

#endif // STANDARDLIFERULE_H
