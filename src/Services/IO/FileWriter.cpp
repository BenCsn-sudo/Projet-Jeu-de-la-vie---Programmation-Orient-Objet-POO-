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
//Modif Coco, ben j'ai changé ton système ultra compact, j'ai fais comme un switch mais avec des ifs
//Donc ça fait la même mais avec plus que juste isAlive j'ajoute isObstacle

			const Cell& c = grid.getCell(h,w);
			int val =0;
			if (c.isObstacle()){
				val=2;
			}else if(c.isAlive()){
				val=1;
			}else{
				val=0;
			}
			out << val << " ";

		}
		out << "\n";
	}
}
