#include <iostream>
#include "Services/GameRunner.h"
#include "Services/IO/FileReader.h"
#include "Components/Rules/StandardRule.h"
#include "Ihm/GameWindow.h"

#include "tests/test_grid.cpp"
#include "Components/Updaters/GridUpdater.h"
#include "Components/Updaters/SingleThreadUpdater.h"
#include "Components/Updaters/MultiThreadUpdater.h"
#include <memory>


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
        string inputFile = "input.txt";

        FileReader reader;
        Grid grid = reader.read(inputFile);

        StandardRule rule;

 	// Mode de calcul
        cout << "Mode de calcul : Mono-thread (1) / Multi-thread (2)" << endl;
        int strat;
        cin >> strat;

        std::unique_ptr<GridUpdater> windowUpdater;
        if (strat == 2) {
            windowUpdater = make_unique<MultiThreadUpdater>();
        } else {
            windowUpdater = make_unique<SingleThreadUpdater>();
        }

        // NOUVEL APPEL AU CONSTRUCTEUR
        GameWindow window(grid, rule, std::move(windowUpdater), 800, 200);
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
