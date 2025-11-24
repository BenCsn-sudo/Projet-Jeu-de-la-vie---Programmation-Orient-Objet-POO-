#include "AliveState.h"

// AliveState return toujours true car la cellule est vivante
bool AliveState::isAlive() const {
	return true;
}

/*
On fait notre copie profonde :
*this représente notre l'objet AliveState actuel
AliveState(*this) appelle le constructeur par copie: créer un nouvel objet identique à celui-ci
std::make_unique créer un std::unique_ptr<AliveState> qui possède cet objet
On utilise ici le polymorphisme ca permet de dupliquer un objet sans connaître son objet concret
*/
std::unique_ptr<CellState> AliveState::clone() const {
	return std::make_unique<AliveState>(*this);
}
