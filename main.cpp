#include <iostream>
#include "Services/FileName.h"
#include "Services/FolderManager.h"
#include "Services/FileReader.h"
#include "Services/FileWriter.h"
#include "Game.h"
#include "StandardLifeRule.h"

int main() {
    std::string input = "input.txt";

    // Lecture de la grille initiale
    FileReader reader;
    Grid g = reader.read(input);

    // Demande du nombre d'itérations
    int iterations;
    std::cout << "Combien d'iterations ? ";
    std::cin >> iterations;

    StandardLifeRule rule;
    
    std::string folder = FileName::getOutputFolder(input);
    FolderManager::createFolder(folder);
    FileWriter writer;
    std::string finalFile = folder + "/final_grid.txt";

    // Lancement du jeu
    Game game(g, rule, iterations);
    game.run();

    // Écrire le résultat final dans un fichier txt
    writer.write(game.getGrid(), finalFile);

    //fin prog
    return 0;
}
