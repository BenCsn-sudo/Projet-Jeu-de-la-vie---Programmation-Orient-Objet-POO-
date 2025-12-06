#ifndef FOLDERMANAGER_H
#define FOLDERMANAGER_H

#include <string>

class FolderManager {
public:
	// Créer un dossier s'il n'existe pas déjà
	static void createFolder(const std::string& folderPath);
};

#endif
