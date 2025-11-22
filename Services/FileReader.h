#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include "../Components/Grid.h"

/*
Classe pour la lecture d'une grille depuis un fichier texte.
On reconstruit un objet Grid entièrement initialisé à partir
des données lues.
*/
class FileReader {
public:
	/*
	Lit un fichier situé à 'path' (le chemin renseigné).
	Le fichier doit contenir:
		- hauteur largeur
		- matrice d'entier (0/1)
	On retourne une Grid initialisé avec ces données.
	*/
	Grid read(const std::string& path) const;
};

#endif
