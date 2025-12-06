#include "GameRunner.h"

#include <iostream>
#include <string>

using namespace std;

#include "../Components/Grid/Grid.h"
#include "../Components/Game.h"
#include "../Components/Rules/StandardRule.h"
#include "../Components/Updaters/SingleThreadUpdater.h"
#include "../Components/Updaters/MultiThreadUpdater.h"


void GameRunner::run() {

	// Selection du fichier d'entrée
	std::string input = askInput();

	// Lecture du fichier
	FileReader reader;
	Grid grid = reader.read(input);

	// Demande de la méthode de calcul
	int strat = askStrat();
	std::unique_ptr<GridUpdater> myUpdater;
	std::string modeName;
	if (strat == 2) {
		myUpdater = make_unique<MultiThreadUpdater>();
	} else {
		myUpdater = make_unique<SingleThreadUpdater>();
	}

	// Demande du nombre d'itérations
	int iterations = askIterations();

	// Préparation du dossier de sortie
	std::string folder = FileName::getOutputFolder(input);
	FolderManager::createFolder(folder);

	StandardRule rule;

	// Création du Game (injection de la stratégie)
	Game game(grid, rule, iterations, std::move(myUpdater), modeName);

	// NOUS DÉLÉGUONS L'EXÉCUTION ET LA MESURE À LA NOUVELLE MÉTHODE
	benchmarkRun(game, folder, iterations);
}

// Demande du chemin de l'input
string GameRunner::askInput() const {
	string input;
	cout << "Chemin du fichier d'entrée : " << endl;
	cin >> input;
	return input;
}

// Demande du nombre d'iteration
int GameRunner::askIterations() const {
	int iterations;
	cout << "Nombre d'iterations : " << endl;
	cin >> iterations;
	return iterations;
}

// Demande de la stratégie
int GameRunner::askStrat() const {
	int strat;
	cout << "Mode de calcul : Mono-thread (1) / Multi-thread (2)" << endl;
	cin >> strat;
	return strat;
}

// Construit le chemin d'un fichier d'iteration : folder/iteration.txt
string GameRunner::iterationFilePath(const string& folder, int iteration) const {
	return folder + "/" + std::to_string(iteration) + ".txt";
}


// AJOUTÉ : Chronomètre la simulation et sauvegarde
void GameRunner::benchmarkRun(Game& game, const std::string& folder, int iterations) {
	FileWriter writer;

	// 1. Démarrer le chronomètre
	auto start = std::chrono::high_resolution_clock::now();

	// Boucle de jeu (le cœur de la logique)
	for (int i = 1; i <= iterations; ++i) {

	        game.nextStep(); // L'appel à la stratégie (Mono ou Multi)

	        // Sauvegarde (nécessaire, mais ne doit pas biaiser la mesure du calcul)
	        std::string outFile = iterationFilePath(folder, i);
	        writer.write(game.getGrid(), outFile);

	        std::cout << "Etat ecrit dans : " << outFile << "\n" << std::endl;
	}

	// 2. Arrêter le chronomètre
	auto end = std::chrono::high_resolution_clock::now();

	// 3. Calculer la durée totale
	std::chrono::duration<double, std::milli> elapsed_ms = end - start;

	// --- AFFICHAGE BENCHMARK ---
	std::cout << "========================================================" << std::endl;
	std::cout << "SIMULATION TERMINEE (" << iterations << " iterations)" << std::endl;
	std::cout << "MODE UTILISÉ: " << (game.getUpdaterName() == "MultiThread" ? "MULTI-THREAD" : "MONO-THREAD") << std::endl;
	std::cout << "DURÉE TOTALE: " << elapsed_ms.count() << " ms" << std::endl;
	std::cout << "MOYENNE PAR ITERATION: " << elapsed_ms.count() / iterations << " ms" << std::endl;
	std::cout << "========================================================" << std::endl;

	// Ecriture de la derniere grille
	std::string finalFile = folder + "final_grid.txt";
	writer.write(game.getGrid(), finalFile);
	std::cout << "Grille finale ecrite dans : " << finalFile << "\n";
}
