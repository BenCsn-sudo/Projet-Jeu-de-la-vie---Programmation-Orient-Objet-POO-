#include "FileReader.h"
#include <fstream>
#include <iostream>

using namespace std;

/*
Implémentation du lecteur de grille: on lit la taille puis on reconstruit 
celle par cellule en utilisant Grid.
*/
Grid FileReader::read(const string& path) const {

	ifstream file(path);

	// On verifie si le fichier existe
	if (!file) {
		cerr << "Erreur : impossible d'ouvrir " << path << endl;

		// Retourne une grille vide en cas d'erreur
		return Grid(0, 0);
	}

	int height, width;

	/*
	On recupere la largeur et la longueur de la matrice (dans cet ordre)
	On utilise '>>' car prend valeur apres valeur en s'arretant a chaque
	espace (donc la matrice doit etre separee par espace et pas compact)
	*/
	file >> height >> width;

	// Construit une grille morte de dimensions récoltés
	Grid grid(width, height);

	// Lecture cellule par cellule du fichier
	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {
			int val;
			file >> val;
//Modif coco, nouvelle possibilité : si c'est un 2 cest un obstacle
			if (val==2){
				grid.setObstacle(h,w);
			// 1 = Cellule vivante
			}else if (val == 1) {
				grid.setAlive(h, w);

			// 0 = Cellule morte
			} else {
				grid.setDead(h, w);
			}
		}
	}
	return grid;
}
