#include <iostream>
#include "Services/GameRunner.h"
#include "Services/IO/FileReader.h"
#include "Components/Rules/StandardRule.h"
#include "Ihm/GameWindow.h"
#include "tests/TestRunner.h"

using namespace std;

int main() {
    cout << "=== Jeu de la Vie - Conway ===\n";
    cout << "Choisissez le mode d'execution :\n";
    cout << "  1. Mode Console\n";
    cout << "  2. Mode Graphique\n";
    cout << "  3. Mode Test Unitaire\n";

    cout << "Votre choix (1, 2 ou 3) : ";
    
    int choix;
    cin >> choix;
    cout << "\n";
    
    if (choix == 1) {
        // Mode console : utilise GameRunner
        GameRunner runner;
        runner.run();
    } 
    else if (choix == 2) {
        // Mode graphique : SFML
        string inputFile = "input.txt";  // Fichier d'entrée par défaut
        
        FileReader reader;
        Grid grid = reader.read(inputFile);
        
        StandardRule rule;
        GameWindow window(grid, rule, 800, 200);
        window.run();
    }

    else if (choix == 3) {
        // Mode test unitaire
        run_all_tests();
    }

    else {
        cerr << "Choix invalide. Veuillez relancer le programme.\n";
        return 1;
    }
    
    return 0;
}
