#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <string>
#include "../Components/Grid.h"

/*
Classe pour sauvegarder une grille dans un fichier texte.
On lit une grille de type Grid et on la convertit en texte
puis on l'écrit.
*/
class FileWriter {
public:

	/*
	Méthode pour ecrire la grille dans un fichier .txt au format:
		- hauteur largeur
		- matrice de 0/1 correspondant a notre Grid
	*/
	void write(const Grid& grid, const std::string& path) const;
};

#endif
