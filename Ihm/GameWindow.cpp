#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow(Grid& g, const Rules& r, int winSize, int delay)
    : grid(g), rule(r), windowSize(winSize), iterationDelay(delay),
      window(sf::VideoMode(winSize, winSize), "Jeu de la Vie - SFML")
{
    // Calcul automatique de la taille d'une cellule
    int rows = grid.getHeight();
    int cols = grid.getWidth();

    float cellW = static_cast<float>(windowSize) / cols;
    float cellH = static_cast<float>(windowSize) / rows;
    cellSize = std::min(cellW, cellH);

    cellShape.setSize(sf::Vector2f(cellSize, cellSize));

    // Chargement police pour afficher l’itération
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Erreur : impossible de charger la police.\n";
    }
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);
}

void GameWindow::run() {
    while (window.isOpen()) {

        // Gestion événements clavier/fenêtre
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {

                // accélérer
                if (event.key.code == sf::Keyboard::Up && iterationDelay > 20)
                    iterationDelay -= 20;

                // ralentir
                if (event.key.code == sf::Keyboard::Down)
                    iterationDelay += 20;

                // mettre en pause
                if (event.key.code == sf::Keyboard::Space)
                    iterationDelay = (iterationDelay == 1000000) ? 200 : 1000000;
            }
        }

        // Avance d’une génération toutes les X ms
        if (clock.getElapsedTime().asMilliseconds() >= iterationDelay) {
            update();
            clock.restart();
        }

        // Dessin
        window.clear(sf::Color::Black);
        drawGrid();
        drawInfo();
        window.display();
    }
}

void GameWindow::update() {
    grid.nextGeneration(rule);
    iterationCount++;
}

void GameWindow::drawInfo() {
    text.setString("Iteration : " + std::to_string(iterationCount) +
                   "\nDelay : " + std::to_string(iterationDelay) + " ms");

    window.draw(text);
}

void GameWindow::drawGrid() {
    int rows = grid.getHeight();
    int cols = grid.getWidth();

    // Dessin des cellules
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {

            if (grid.getCell(r, c).isAlive())
                cellShape.setFillColor(sf::Color::White);
            else
                cellShape.setFillColor(sf::Color(30, 30, 30)); // gris foncé

            cellShape.setPosition(c * cellSize, r * cellSize);
            window.draw(cellShape);
        }
    }

    // Quadrillage
    sf::RectangleShape line;
    line.setFillColor(sf::Color(80, 80, 80));

    // lignes horizontales
    for (int r = 0; r <= rows; ++r) {
        line.setSize(sf::Vector2f(cols * cellSize, 1));
        line.setPosition(0, r * cellSize);
        window.draw(line);
    }

    // lignes verticales
    for (int c = 0; c <= cols; ++c) {
        line.setSize(sf::Vector2f(1, rows * cellSize));
        line.setPosition(c * cellSize, 0);
        window.draw(line);
    }
}
