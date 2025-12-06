#include "GameRunner.h"

#include <iostream>
#include <string>

using namespace std;

#include "../Components/Grid/Grid.h"
#include "../Components/Game.h"
#include "../Components/Rules/StandardRule.h"


void GameRunner::run() {

	// Selection du fichier d'entrée
	string input = askInput();

	// Lecture du fichier
	FileReader reader;
	Grid grid = reader.read(input);

	// Demande du nombre d'itérations
	int iterations = askIterations();

	// Préparation du dossier de sortie
	string folder = FileName::getOutputFolder(input);
	FolderManager::createFolder(folder);

	FileWriter writer;
	StandardRule rule;

	// Création du Game
	Game game(grid, rule, iterations);

	// Pour chaque iteration : avancer + sauvegarder dans un fichier texte
	for (int i = 1; i <= iterations; ++i) {

		game.nextStep();

		string outFile = iterationFilePath(folder, i);
		writer.write(game.getGrid(), outFile);

		cout << "Etat ecrit dans : " << outFile << "\n" << endl;
	}

	// Ecriture de la derniere grille (+ de visibilite)
	std::string finalFile = folder + "final_grid.txt";
	writer.write(game.getGrid(), finalFile);
	std::cout << "Grille finale ecrite dans : " << finalFile << "\n";
}

// Demande du chemin de l'input
string GameRunner::askInput() const {
	string input;
	cout << "Chemin du fichier d'entree : " << endl;
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

// Construit le chemin d'un fichier d'iteration : folder/iteration.txt
string GameRunner::iterationFilePath(const string& folder, int iteration) const {
	return folder + "/" + std::to_string(iteration) + ".txt";
}
