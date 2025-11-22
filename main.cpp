#include <iostream>
#include <fstream>

#include "Components/Cell.h"
#include "Components/AliveState.h"
#include "Components/DeadState.h"
#include "Components/Grid.h"

int main() {
    int width, height;
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "Erreur : impossible d'ouvrir input.txt" << std::endl;
        return 1;
    }

    file >> height >> width;

    std::cout << "Dimensions lues : " << height << " (hauteur) x " << width << " (largeur)"<< std::endl;
    Grid g(width, height); //Création de la grille toute morte
    //Assignment des cellules vivantes selon les données du fichir input.txt
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            int val;
            file >> val;

            if (val == 1) {
                g.setAlive(r, c);
            } else {
                g.setDead(r, c);
            }
        }
    }
    g.print();

    return 0;
}
