#ifndef WORKERPOOL_H
#define WORKERPOOL_H

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class WorkerPool {
private:
	// Les threads
	std::vector<std::thread> workers;

	// La tâche actuelle à effectuer
	std::function<void(int)> currentTask;

	// Outils de synchronisation
	std::mutex mtx;
	std::condition_variable cv_start;
	std::condition_variable cv_done;

	// État du pool
	int active_workers;
	int total_threads;
	bool stop;      	 // Flag pour arrêter définitivement les threads
	size_t current_task_id;  // Flag pour dire qu'il y a du travail

public:
	// Constructeur : Lance les threads qui se mettent en attente
	WorkerPool(int numThreads);

	// Destructeur : Arrête proprement les threads
	~WorkerPool();

	// Méthode principale : Lance une tâche sur tous les threads et attend la fin
	void executeAndWait(std::function<void(int)> task);

	// Getter
	int getThreadCount() const;
};

#endif
