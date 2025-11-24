/*#include "Services/GameRunner.h"

int main() {
    GameRunner runner;
    runner.run();
    return 0;
}
*/

#include <iostream>
#include "Services/IO/FileReader.h"
#include "Services/IO/FileName.h"
#include "Services/IO/FolderManager.h"
#include "Services/IO/FileWriter.h"
#include "Components/Rules/StandardRule.h"
#include "Ihm/GameWindow.h"

int main() {
    std::string inputFile = "input.txt";

    // Lecture de la grille initiale
    FileReader reader;
    Grid grid = reader.read(inputFile);

    // Utilisation de la règle standard de Conway
    StandardRule rule;

    // Création et lancement de la fenêtre graphique
    GameWindow window(grid, rule, 800, 1000);
    window.run();

    return 0;
}
