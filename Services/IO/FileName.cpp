#include "FileName.h"

std::string FileName::getBaseName(const std::string& path) {

	// On trouve la dernière occurence d'un flash (pour supprimer chemin)
	size_t slash = path.find_last_of("/\\");

	// On trouve la dernière occurence d'un point (pour supprimer extension)
	size_t dot = path.find_last_of('.');

	// Nom avec chemin retiré
	std::string name = (slash == std::string::npos) ? path : path.substr(slash + 1);

	// Si le point d'extension est présent après le slash
	if (dot != std::string::npos && dot > slash) {
		name = name.substr(0, dot - (slash == std::string::npos ? 0 : slash + 1));
	}

	return name;
}

std::string FileName::getOutputFolder(const std::string& inputPath) {
	std::string base = getBaseName(inputPath);
	return base + "_out";
}
