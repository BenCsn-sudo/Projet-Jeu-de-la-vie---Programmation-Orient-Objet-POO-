#include "StandardLifeRule.h"

bool StandardLifeRule::willBeAlive(bool isAlive, int neighbours) const {
    // Si la cellule est morte : elle naît seulement si elle a exactement 3 voisins vivants.
    if (!isAlive) {
        return (neighbours == 3);
    }

    // Si la cellule est vivante :
    // elle survit seulement si elle a 2 ou 3 voisins vivants.
    if (neighbours == 2 || neighbours == 3) {
        return true;
    }

    // Sinon elle meurt.
    return false;
}
