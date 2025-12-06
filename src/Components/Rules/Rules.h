#ifndef RULES_H
#define RULES_H

/*
Classe abstraite (Interface) des règles d'évolution d'une cellule.
Une règle décide si la cellule sera vivante ou non a t+1 en
fonction de son état actuel et du nombre de voisine vivantes.
*/
class Rules {
public:
	// Destructeur virtuel
	virtual ~Rules() = default;

	/*
	Decide l'état future d'une cellule (true = vivant, false = mort)
		- isAlive : état actuel de la cellule
		- livingNeighbours : nombre de voisine vivante
	return true si la cellule doit être vivante à la prochaine génération
	*/
	virtual bool willBeAlive(bool isAlive, int livingNeighbours) const = 0;
};

#endif
