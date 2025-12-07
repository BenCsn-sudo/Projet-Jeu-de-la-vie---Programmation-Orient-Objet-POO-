#ifndef CELLSTATE_H
#define CELLSTATE_H

#include <memory> 	// pour std::unique_ptr

/*
Classe abstraite représentant l'état d'une cellule, elle sert
d'interface commune pour toutes les variantes d'état.
*/
class CellState {
public:
	// Destructeur
	virtual ~CellState() = default;

	/*
	Indique si l'état représente une cellule vivante ou morte.
	= 0 pour forcer l'implémentation dans les sous classes
	*/
	virtual bool isAlive() const = 0;

	/*
	On fait une copie profonde; l'objet copié possède ses propres
	données indépendantes et pas seulement des pointeurs vers les mêmes
	données que l'original. Pour que chaque cellule possède son propre
	état et qu'ils ne soient jamais partagé
	*/
	virtual std::unique_ptr<CellState> clone() const = 0;

//Modif Coco, on fait comme is Alive mais pour les obstacles
	virtual bool isObstacle() const {return false;}

};

#endif
