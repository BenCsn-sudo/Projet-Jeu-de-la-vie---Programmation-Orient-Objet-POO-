#ifndef FILENAME_H
#define FILENAME_H

#include <string>

/*
Class pour manipuler les noms de fichier:
	- extraction du nom de base (sans chemin ni extension)
	- construction du nom de dossier de sortie (nom + _out)
*/
class FileName {
public:
	// Extrait le nom du fichier
	static std::string getBaseName(const std::string& path);

	// Construit le nom du dossier avec le _out
	static std::string getOutputFolder(const std::string& inputPath);
};

#endif
