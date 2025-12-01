#include <iostream>
#include "Services/GameRunner.h"
#include "Services/IO/FileReader.h"
#include "Components/Rules/StandardRule.h"
#include "Ihm/GameWindow.h"

using namespace std;

int main() {
    cout << "=== Jeu de la Vie - Conway ===\n";
    cout << "Choisissez le mode d'execution :\n";
    cout << "  1. Mode Console (sauvegarde iterations dans fichiers)\n";
    cout << "  2. Mode Graphique (visualisation SFML)\n";
    cout << "Votre choix (1 ou 2) : ";
    
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
    else {
        cerr << "Choix invalide. Veuillez relancer le programme.\n";
        return 1;
    }
    
    return 0;
}
