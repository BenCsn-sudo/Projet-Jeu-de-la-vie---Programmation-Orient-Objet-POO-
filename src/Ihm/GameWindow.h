#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "../Components/Grid/Grid.h"
#include "../Components/Rules/Rules.h"
#include "../Components/Updaters/GridUpdater.h"


class GameWindow {
public:
    GameWindow(Grid& grid, const Rules& rule, std::unique_ptr<GridUpdater> updater, int windowSize = 800, int delay = 1000);

    void run();

private:
    void update();          // applique la règle pour passer à la génération suivante
    void drawGrid();        // dessine cellules + quadrillage
    void drawInfo();        // affiche l’itération + infos contrôle

    // motifs pré-programmés pour le placement de constructions
    enum class PatternType {
        None,
        Glider,
        Blinker,
        Block
    };

    // motif actuellement sélectionné (par défaut aucun)
    PatternType currentPattern = PatternType::None;

    // place un motif pré-programmé autour de la cellule (row, col)
    void placePattern(PatternType pattern, int row, int col);

private:
    Grid& grid;
    const Rules& rule;
    std::unique_ptr<GridUpdater> updater;
    int windowSize;      // d'abord windowSize
    int iterationDelay;  // ensuite iterationDelay
    bool isPaused() const { return iterationDelay == 1000000; }	// petit helper pour savoir si on est en pause
    float cellSize;
    int iterationCount = 0;
    // Oliv : Dragclick fonctionnel on initialise à false pour pas avoir de problemes mdrr c logique
    bool isDragging = false;

    sf::RenderWindow window;
    sf::RectangleShape cellShape;
    sf::Font font;
    sf::Text text;

    sf::Clock clock;
};

#endif
