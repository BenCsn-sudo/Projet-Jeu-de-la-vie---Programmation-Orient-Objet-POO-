#include "Services/FileName.h"
#include "Services/FolderManager.h"
#include "Services/FileReader.h"
#include "Services/FileWriter.h"

int main() {
    std::string input = "input.txt";

    FileReader reader;
    Grid g = reader.read(input);

    // Génération du nom du dossier et création
    std::string folder = FileName::getOutputFolder(input);
    FolderManager::createFolder(folder);

    // Génération d'un nom de fichier pour la première itération
    FileWriter writer;
    std::string outFile = folder + "/grid_1.txt";

    writer.write(g, outFile);

    return 0;
}
