#ifndef CELLRULE_H
#define CELLRULE_H

// Interface des règles d'évolution d'une cellule.
// Une règle décide si la cellule sera vivante à t+1
// en fonction de son état actuel et du nombre de voisines vivantes.
class CellRule {
public:
    //destructeur virtuel
    virtual ~CellRule() = default;
    // Décide l'état futur (vivant ? true / mort ? false) d'une cellule.
    // - isAlive : état actuel de la cellule (true si vivante)
    // - livingNeighbours : nombre de voisines vivantes (0..8)
    // Retourne true si la cellule doit être vivante à la prochaine génération.
    virtual bool willBeAlive(bool isAlive, int livingNeighbours) const = 0;
};

#endif // CELLRULE_H