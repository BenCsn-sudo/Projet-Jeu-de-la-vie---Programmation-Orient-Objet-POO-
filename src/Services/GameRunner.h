#ifndef GAMERUNNER_H
#define GAMERUNNER_H

#include <string>
#include "../Components/Game.h"
#include "IO/FileReader.h"
#include "IO/FileWriter.h"
#include "IO/FileName.h"
#include "IO/FolderManager.h"

class GameRunner {
private:
	// Méthode interne : demande à l'utilisateur combien d'itération exécuter
	int askIterations() const;

	// Méthode interne : demande le chemin du fichier input
	std::string askInput() const;

	// Méthode interne : demande la méthode de calcul
	int askStrat() const;

	// Méthode interne : génère le nom du fichier de sortie pour une itération donnée
	std::string iterationFilePath(const std::string& folder, int iteration) const;

	// Méthode interne : Chronomètre la simulation et affiche le résultat
	void benchmarkRun(Game& game, const std::string& folder, int iterations);

public:
	// Constructeur par defaut
	GameRunner() = default;

	// Lance la simulation complète
	void run();
};

#endif
