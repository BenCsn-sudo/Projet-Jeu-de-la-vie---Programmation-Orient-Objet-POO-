#include "FolderManager.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void FolderManager::createFolder(const std::string& folderPath) {
	try {
		fs::create_directories(folderPath);
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Erreur : impossible de créer le dossier \"" << folderPath
			  << "\" : " << e.what() << std::endl;
	}
}
