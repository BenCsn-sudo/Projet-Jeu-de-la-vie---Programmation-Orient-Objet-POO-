#include "FolderManager.h"
#include <filesystem>
#include <iostream>

using namespace std;

namespace fs = filesystem;

void FolderManager::createFolder(const string& folderPath) {
	try {
		fs::create_directories(folderPath);
	}
	catch (const fs::filesystem_error& e) {
		cerr << "Erreur : impossible de creer le dossier \"" << folderPath
			  << "\" : " << e.what() << endl;
	}
}
