#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include "../Components/Grid/Grid.h"
#include "../Components/Rules/Rules.h"

class GameWindow {
public:
    GameWindow(Grid& grid, const Rules& rule, int windowSize = 800, int delay = 1000);

    void run();

private:
    void update();          // applique la règle pour passer à la génération suivante
    void drawGrid();        // dessine cellules + quadrillage
    void drawInfo();        // affiche l’itération + infos contrôle




    // oliv: motifs pré-programmés pour le placement de constructions
    enum class PatternType {
        None,
        Glider,
        Blinker,
        Block
    };

    // oliv: motif actuellement sélectionné (par défaut aucun)
    PatternType currentPattern = PatternType::None;

    // oliv: place un motif pré-programmé autour de la cellule (row, col)
    void placePattern(PatternType pattern, int row, int col);

private:
    Grid& grid;
    const Rules& rule;
    bool isPaused() const { return iterationDelay == 1000000; }// Oliv: petit helper pour savoir si on est en pause
    int windowSize;
    int iterationDelay;
    float cellSize;
    int iterationCount = 0;

    sf::RenderWindow window;
    sf::RectangleShape cellShape;
    sf::Font font;
    sf::Text text;

    sf::Clock clock;
};

#endif
