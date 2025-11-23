#ifndef GRID_H
#define GRID_H

#include <vector>	// Pour utiliser les vecteurs

#include "DeadState.h"
#include "Cell.h"
#include "CellRule.h"

class Grid {
private:
	int width;
	int height;
	/*
	On fait un vecteur de vecteur pour représenter une matrice dynamique,
	une grille 2D de dimensions (height x width), le premier vector représente
	les lignes et le second les colonnes. Et chaque élément est un Cell .
	C'est la méthode la plus claire et moderne pour représenter un tableau 2D
	par rapport a : std::array (taille fixe) / std::vector<Cell> (index 1D) /
	Cell** (désuet). Alors qu'avec notre méthode on a:
	- taille construite à l'exécution
	- gestion automatique de la mémoire

	*/
	std::vector<std::vector<Cell>> cells;
public:
	// Constructeur : initialise la grille avec des cellules mortes
	// Il va falloir changer cette partie pour initialiser avec les données du .txt
	Grid(int w, int h);

	// Afficher la grille:
	void print() const;

	// Setters des états des cellules
	void setAlive(int row, int col);
	void setDead(int row, int col);

	// Getters largeur et hauteur
	int getWidth() const { return width; }
	int getHeight() const { return height; }

	// Accès en lecture/écriture à une cellule de la grille.
	Cell& getCell(int row, int col) { return cells[row][col]; }

	/*
	Version const de l'accès : utilisée lorsque l'objet Grid
	est lui-même const. Retourne une référence const,
	empêchant toute modification de la cellule.
	Exemple : dans FileWriter, où on ne fait que lire.
	*/
	const Cell& getCell(int row, int col) const { return cells[row][col]; }

	// Compte le nombre de voisins vivants autour de la cellule (row, col)
	int countLivingNeighbours(int row, int col) const;

	// Calcule la prochaine génération de la grille en appliquant les règles
	void nextGeneration(const CellRule& rule);

};
#endif

