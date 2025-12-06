#include <iostream>
#include <fstream>
#include <random>
 
using namespace std;

int main() {
    int width = 10;   // Largeur de la grille
    int height = 10;  // Hauteur de la grille
    int density = 60;   // Pourcentage de cellules vivantes au départ (env. 40%)

    cout << "Creation du fichier input.txt (" << width << "x" << height << ")..." << endl;

    ofstream file("input.txt");
    
    if (!file) {
        cerr << "Erreur : Impossible de creer le fichier." << endl;
        return 1;
    }

    // 1. Écriture de l'en-tête (Hauteur Largeur)
    // Attention : FileReader.cpp lit d'abord Height, puis Width
    file << height << " " << width << "\n";

    // Initialisation du générateur aléatoire
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 100);

    // 2. Remplissage de la grille
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Si le nombre tiré est <= densité, la cellule est vivante (1), sinon morte (0)
            int state = (distrib(gen) <= density) ? 1 : 0;
            file << state << " ";
        }
        file << "\n";
    }

    cout << "Fermeture du fichier..." << endl;
    file.close();

    cout << "Termine ! Tu peux lancer ton Jeu de la Vie." << endl;
    return 0;
}
