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
    void drawInfo();        // affiche l’itération

private:
    Grid& grid;
    const Rules& rule;

    int windowSize;      // d'abord windowSize
    int iterationDelay;  // ensuite iterationDelay
    float cellSize;
    int iterationCount = 0;

    sf::RenderWindow window;
    sf::RectangleShape cellShape;
    sf::Font font;
    sf::Text text;

    sf::Clock clock;

};

#endif
