#include "FileWriter.h"
#include <fstream>
#include <iostream>

using namespace std;

/*
On se contente de convertir notre grid en texte et d'écrire
le tout dans un fichier texte.
*/
void FileWriter::write(const Grid& grid, const string& path) const {

	ofstream out(path);

	// Verifie que le fichier existe
	if (!out) {
		cerr << "Erreur : impossible d'ecrire dans " << path << endl;
		return;
	}

	// Ecrit les dimensions sans oublier l'espacement pour la relecture
	out << grid.getHeight() << " " << grid.getWidth() << "\n";

	// Parcourt et écrit chaque cellule
	for (int h = 0; h < grid.getHeight(); ++h) {
		for (int w = 0; w < grid.getWidth(); ++w) {
			// 1 si vivante et 0 si morte
			out << (grid.getCell(h, w).isAlive() ? 1 : 0) << " ";
		}
		out << "\n";
	}
}
