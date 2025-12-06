#ifndef MULTITHREADUPDATER_H
#define MULTITHREADUPDATER_H


#include "GridUpdater.h"

// Inclusion du service de gestion des threads (dépendance technique)
#include "../../Services/WorkerPool/WorkerPool.h"

#include <memory>
#include <iostream>

/*
Classe concrète qui implémente la stratégie de mise à jour de la grille
en mode Multi-thread, en utilisant un Thread Pool (WorkerPool).
Responsabilités : Découper la grille en tranches, assigner ces tranches
au pool, et synchroniser l'attente de la fin du travail.
*/
class MultiThreadUpdater : public GridUpdater {
private:
	// Le Thread Pool : gère la vie des threads (Dependency Inversion Principe)
	std::unique_ptr<WorkerPool> pool;

	// Pointeur temporaire utilisé pour partager l'adresse de la grille tampon
	// (celle où les threads écrivent) avec les lambdas des threads ouvriers.
	Grid* tempGrid = nullptr;

public:
	// Constructeur : initialise et prépare le pool de threads
	MultiThreadUpdater();

	std::string getName() const override { return "Multi-thread"; }

	// Mise à jour de la grille pour la prochaine génération.
	void update(Grid& grid, const Rules& rule) override;
};

#endif
