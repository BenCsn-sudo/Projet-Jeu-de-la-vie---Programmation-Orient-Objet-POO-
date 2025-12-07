#include "MultiThreadUpdater.h"
#include <thread> // Nécessaire pour std::thread::hardware_concurrency


/*
CONSTRUCTEUR

Ce que fait la méthode :
Prépare le pool de threads à être utilisé.

Comment elle le fait :
 - Détermine le nombre optimal de threads à créer en fonction du nombre de cœurs CPU.
 - Crée le WorkerPool (le pool lance immédiatement les threads ouvriers en mode sommeil).
 - Affiche une information de diagnostic.
*/
MultiThreadUpdater::MultiThreadUpdater() {

	// 1. Détecter le nombre de cœurs logiques disponibles pour le multi-threading.
	int cores = std::thread::hardware_concurrency();

	// Mesure de sécurité si la détection échoue (par exemple, cores serait 0).
	if (cores == 0) cores = 2;

	// 2. Initialiser le pool de threads avec le nombre de cœurs détecté.
	pool = std::make_unique<WorkerPool>(cores);

	// 3. Affichage d'information (optionnel, utile pour le benchmarking)
	std::cout << "[INFO] MultiThreadUpdater initialise avec " << cores << " threads.\n";
}

/*
UPDATE

Ce que fait la méthode :
Découpe le travail de calcul de la prochaine génération et le distribue aux threads
du WorkerPool, puis attend la fin du travail.

Comment elle le fait :
 - Prépare la grille tampon (`next`) où les threads vont écrire (Double Buffering).
 - Calcule la taille des tranches (chunkHeight) pour chaque thread.
 - Définit la fonction de travail (`task`) : cette lambda est ce que chaque thread exécutera.
 - Elle capture les variables nécessaires (comme `grid` et `rule`) et calcule la tranche de lignes qui lui a été assignée.
 - Appelle `pool->executeAndWait(task)` : bloque le thread principal jusqu'à ce que tous les ouvriers aient fini leur tranche de calcul.
 - Une fois terminé, échange la grille actuelle avec la grille tampon (`next`) pour valider les changements.
*/
void MultiThreadUpdater::update(Grid& grid, const Rules& rule) {

	// Création de la grille tampon ('next'). Elle est temporaire, mais essentielle
	// pour que les threads lisent tous l'état T et écrivent tous l'état T+1.
	Grid next(grid.getWidth(), grid.getHeight());
	tempGrid = &next; // On stocke l'adresse pour que la lambda puisse écrire dedans

	int totalThreads = pool->getThreadCount();
	int height = grid.getHeight();

	// La hauteur de la tranche que chaque thread doit traiter
	int chunkHeight = height / totalThreads;

	// Définir la tâche (la fonction lambda) que chaque thread va exécuter.
	// La capture [&] permet d'accéder aux variables de la fonction englobante (grid, rule, etc.).
	auto task = [&](int threadId) {

	        // Détermination des limites de la tranche pour ce thread
	        int startY = threadId * chunkHeight;

	        // Le dernier thread prend le reste pour couvrir les divisions non entières
	        int endY = (threadId == totalThreads - 1) ? height : (threadId + 1) * chunkHeight;

	        // Boucle de calcul sur la tranche attribuée au thread
	        for (int y = startY; y < endY; ++y) {
			for (int x = 0; x < grid.getWidth(); ++x) {
				//Modif coco, gestion des obstacles
				if (grid.getCell(y,x).isObstacle()){
					tempGrid->setObstacle(y,x);
					continue;
				}
				// Lecture de l'état (TOUJOURS sur la grille source 'grid')
				bool aliveNow = grid.getCell(y, x).isAlive();
				int neighbours = grid.countLivingNeighbours(y, x);

				// Écriture du nouvel état (TOUJOURS sur la grille tampon 'tempGrid')
				if (rule.willBeAlive(aliveNow, neighbours)) {
				    tempGrid->setAlive(y, x);
				} else {
				    tempGrid->setDead(y, x);
				}
            		}
        	}
	};

	// Exécuter le travail sur le pool et bloquer jusqu'à ce que tous les threads aient fini.
	pool->executeAndWait(task);

	// Appliquer les changements : la validation des données T+1 est faite.
	grid.swap(next);

	// Nettoyage du pointeur temporaire.
	tempGrid = nullptr;
}
