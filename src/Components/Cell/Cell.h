#ifndef CELL_H
#define CELL_H

#include "CellState.h"

/*
La classe Cell représente une cellule du jeu. Elle ne
stocke pas un simple booléen mais un état polymorphe :
   - AliveState <- dérive de CellState
   - DeadStaate <- dérive de CellState
Donc une cellule peut changer détat sans changer de type
de cellule. Le polymorphisme permet également d'ajouter
de nouveaux états dans le futur.
*/
class Cell {
private:
	/*
	On utilise unique_ptr pour que la céllule possède
	son propre état. Cela garantit qu'il n'y jamais
	deux cellules qui partagent le même état propre.
	Parfait pour éviter les fuites mémoires.
	*/
	std::unique_ptr<CellState> state;

public:
	/*
	Constructeur initial: on créer une cellule en lui donnant
	son état initial (prend possession du pointeur).
	explicit : empêche les conversions implicites depuis un
	pointeur CellState*, ce qui évite la création accidentelle
	d'une Cell et force une intention claire.
	*/
	explicit Cell(CellState* state) : state(state) {}

	/*
	Constructeur par copie : copie profonde de l'état d'une
	cellule. On veut copier l'état pas juste copier le pointeur
	donc on appelle notre méthodes clone(). C'est indispensable
	pour que deux cellules ne partagent pas le même état en
	mémoire.
	*/
	Cell(const Cell& other) : state(other.state ? other.state->clone() : nullptr) {}

	/*
	On veut que la cellule courante (this) devienne une copie
	profonde de other. Donc on vérifie si other.state n'est pas
	vide alors on clone l'état sinon on met nullptr.
	L'opérateur renvoies un std::unique_ptr<CellState> qui pointe
	vers un nouveau AliveState ou DeadState.
	*/
	Cell& operator = (const Cell&other) {
		if (this != &other) {
			state = other.state ? other.state->clone():nullptr;
		}
	return *this;
	}
	//Vérifie si la cellule est vivante en déléguant au state
	bool isAlive() const {
        	return state->isAlive();
    }
	//Méthode pour changer l'état de la cellule
	void setState(CellState* newState) {
    		state.reset(newState);
	}
};
#endif
