#include "DeadState.h"

// DeadState return toujours false car la cellule est morte
bool DeadState::isAlive() const {
	return false;
}

/*
On fait notre copie profonde :
*this représente notre l'objet DeadState actuel
DeadState(*this) appelle le constructeur par copie: créer un nouvel objet identique à celui-ci
std::make_unique créer un std::unique_ptr<DeadState> qui possède cet objet
On utilise ici le polymorphisme ca permet de dupliquer un objet sans connaître son objet concret
*/
std::unique_ptr<CellState> DeadState::clone() const {
	return std::make_unique<DeadState>(*this);
}
