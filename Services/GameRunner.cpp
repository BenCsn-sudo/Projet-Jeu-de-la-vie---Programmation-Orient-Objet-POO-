#include "GameRunner.h"

#include <iostream>
#include <string>

#include "../Components/Grid/Grid.h"
#include "../Components/Game.h"
#include "../Components/Rules/StandardRule.h"


void GameRunner::run() {

	// Selection du fichier d'entrée
	std::string input = askInput();

	// Lecture du fichier
	FileReader reader;
	Grid grid = reader.read(input);

	// Demande du nombre d'itérations
	int iterations = askIterations();

	// Préparation du dossier de sortie
	std::string folder = FileName::getOutputFolder(input);
	FolderManager::createFolder(folder);

	FileWriter writer;
	StandardRule rule;

	// Création du Game
	Game game(grid, rule, iterations);

	// Pour chaque itération : avancer + sauvegarder dans un fichier texte
	for (int i = 1; i <= iterations; ++i) {

		game.nextStep();

		std::string outFile = iterationFilePath(folder, i);
		writer.write(game.getGrid(), outFile);

		std::cout << "Etat écrit dans : " << outFile << "\n" << std::endl;
	}

	// Ecriture de la dernière grille (+ de visibilité)
	std::string finalFile = folder + "final_grid.txt";
	writer.write(game.getGrid(), finalFile);
	std::cout << "Grille finale écrite dans : " << finalFile << "\n";
}

// Demande du chemin de l'input
std::string GameRunner::askInput() const {
	std::string input;
	std::cout << "Chemin du fichier d'entrée : " << std::endl;
	std::cin >> input;
	return input;
}

// Demande du nombre d'itération
int GameRunner::askIterations() const {
	int iterations;
	std::cout << "Nombre d'iterations : " << std::endl;
	std::cin >> iterations;
	return iterations;
}

// Construit le chemin d'un fichier d'itération : folder/iteration.txt
std::string GameRunner::iterationFilePath(const std::string& folder, int iteration) const {
	return folder + "/" + std::to_string(iteration) + ".txt";
}
