#include "WorkerPool.h"
#include <iostream>

/*
CONSTRUCTEUR

Ce que fait la méthode :
Elle initialise le pool en créant le nombre demandé de threads (ouvriers).
Ces threads ne font rien au départ : ils entrent immédiatement dans une boucle infinie
où ils se mettent en "sommeil" en attendant qu'on leur donne du travail.

Comment elle le fait :
- Une boucle 'for' crée 'numThreads' objets std::thread.
- Chaque thread exécute une fonction lambda (fonction anonyme) qui contient une boucle 'while(true)'.
- À l'intérieur, on verrouille le mutex (std::unique_lock) pour protéger les données partagées.
- On utilise 'cv_start.wait' : cela endort le thread et relâche le mutex automatiquement.
	Le thread ne se réveillera que si 'has_work' devient vrai ou si 'stop' (arrêt du programme) devient vrai.
- Une fois réveillé, le thread récupère la tâche, relâche le mutex (pour travailler en parallèle), et exécute la tâche.
- Une fois fini, il reprend le mutex, décrémente le compteur de travailleurs actifs, et si c'est le dernier à finir, il réveille le chef (Main Thread) via 'cv_done'.
*/
WorkerPool::WorkerPool(int numThreads)
    : workers(), currentTask(), mtx(), cv_start(), cv_done(), // Init par défaut des objets complexes
      active_workers(0), total_threads(numThreads), stop(false), current_task_id(0)
{
	// On crée les threads un par un
	for (int i = 0; i < numThreads; ++i) {
		workers.emplace_back([this, i] {

			// VARIABLE LOCALE IMPORTANTE :
			// Chaque thread retient l'ID de la dernière tâche qu'il a effectuée.
			// Elle doit être déclarée ICI (avant le while) pour persister entre les réveils.
			size_t my_last_task_id = 0;

            		while (true) {

				// VERROUILLAGE : On entre dans la zone critique protégée
		                std::unique_lock<std::mutex> lock(mtx);

				/*
				Le mutex est un mécanisme de sécurité pour le multi-threading qui garantit que deux thread ne
				peuvent jamais accéder à la meme ressource en même temps.
				std::mutex mtx = déclare la clé
				std::unique_lock<std::mutex> lock(mtx) = prend la clé
				*/

		                // ARRÊT : Si le destructeur a sonné la fin, on sort de la boucle infinie pour tuer le thread
		                // On passe &my_last_task_id en référence pour que la lambda puisse lire la variable locale
		                cv_start.wait(lock, [this, &my_last_task_id] {
                   			 return stop || (current_task_id > my_last_task_id);
                		});

				if (stop) return;

				// Mise à jour de l'ID local pour dire "C'est bon, je prends cette tâche"
                		my_last_task_id = current_task_id;

		                // PRÉPARATION : On copie la tâche locale pour l'exécuter
		                auto task = currentTask;

		                // PARALLÉLISME : On déverrouille le mutex ICI:
		                // C'est crucial : si on gardait le mutex, les threads s'exécuteraient l'un après l'autre !
		                lock.unlock();

				// EXECUTION : le travail réel se fait ici (i sert d'identifiant pour le découpage)
				try {
		                    if (task) task(i);
		                } catch (const std::exception& e) {
		                    // Si une erreur C++ standard est trouvée, on l'affiche
		                    std::cerr << "ERREUR THREAD " << i << " (std::exception) : " << e.what() << std::endl;
		                } catch (...) {
		                    // Si c'est une erreur inconnue (segmentation fault, etc.)
		                    std::cerr << "ERREUR INCONNUE FATALE dans le THREAD " << i << std::endl;
				}

		                // FIN DE TÂCHE : On reverrouille pour modifier le compteur partagé
		                lock.lock();
		                active_workers--;

		                // SIGNALEMENT : Si je suis le dernier ouvrier à finir, je préviens le patron (Main Thread)
		                if (active_workers == 0) {
		                    cv_done.notify_one();
                		}
            		}
        	});
    	}
}


/*
DESTRUCTEUR

Ce que fait la méthode :
Elle assure un arrêt propre du programme. Elle force tous les threads à sortir de
leur boucle infinie et attend qu'ils soient tous fermés avant de détruire l'objet WorkerPool.

Comment elle le fait :
 - On verrouille le mutex pour modifier la variable 'stop' en toute sécurité.
 - On passe 'stop' à true.
 - On utilise 'cv_start.notify_all()' : cela envoie un signal de réveil à TOUS les threads.
   Comme 'stop' est vrai, ils ne vont pas exécuter de tâche mais sortir du 'while(true)' (return).
 - On fait une boucle 'join()' sur chaque thread : le programme principal attend ici
   que chaque thread ait bien terminé sa fermeture avant de continuer.
*/
WorkerPool::~WorkerPool() {
	{
		// On verrouille pour changer le flag 'stop'
		std::unique_lock<std::mutex> lock(mtx);
		stop = true;
    	}

	// On réveille tout le monde pour qu'ils voient le flag 'stop' et quittent
	cv_start.notify_all();

	// On attend qu'ils aient tous bien fermé leur thread
	for (auto& t : workers) {
		if (t.joinable()) {
			t.join();
        	}
    	}
}


/*
EXECUTE AND WAIT

Ce que fait la méthode :
C'est la méthode appelée par le chef d'orchestre (Main Thread). Elle donne une tâche
à tous les ouvriers, les réveille, et bloque le programme principal jusqu'à ce que
TOUS les ouvriers aient fini. C'est une "barrière de synchronisation".

Comment elle le fait :
 - Verrouille le mutex.
 - Définit la tâche (la fonction lambda reçue en paramètre).
 - Initialise le compteur 'active_workers' au nombre total de threads.
 - Met le flag 'has_work' à true.
 - Appelle 'cv_start.notify_all()' pour réveiller tous les threads endormis dans le constructeur.
 - Appelle 'cv_done.wait(...)' : le Main Thread s'endort ici et attend que la condition
   (active_workers == 0) soit remplie. Cette condition sera remplie par le dernier thread ouvrier.
 - Une fois réveillé (le travail est fini), remet 'has_work' à false pour le prochain tour.
*/
void WorkerPool::executeAndWait(std::function<void(int)> task) {
	std::unique_lock<std::mutex> lock(mtx);

	// On prépare le travail
	currentTask = task;
	active_workers = total_threads;

	// INCREMENTATION DE L'ID :
    	// Cela invalide instantanément la condition d'attente de tous les threads
    	current_task_id++;

	// ON LANCE TOUT LE MONDE
	cv_start.notify_all();

	// Le thread principal (Chef) attend que le compteur retombe à 0
	cv_done.wait(lock, [this] { return active_workers == 0; });
}


int WorkerPool::getThreadCount() const {
	return total_threads;
}
