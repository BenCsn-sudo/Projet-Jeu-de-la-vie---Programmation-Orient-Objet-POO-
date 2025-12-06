#include "GameWindow.h"
#include <iostream>
#include <vector>
#include <string>
// Oliv : pour std::min (calcul de la taille de cellule)
#include <algorithm>

using namespace std;

GameWindow::GameWindow(Grid& g, const Rules& r, std::unique_ptr<GridUpdater> u, int winSize, int delay)
    : grid(g), rule(r), updater(std::move(u)), windowSize(winSize), iterationDelay(delay),
      window(sf::VideoMode(winSize, winSize), "Jeu de la Vie - SFML")
{
    // Calcul automatique de la taille d'une cellule
    int rows = grid.getHeight();
    int cols = grid.getWidth();

    float cellW = static_cast<float>(windowSize) / cols;
    float cellH = static_cast<float>(windowSize) / rows;
    cellSize = std::min(cellW, cellH); // NEW: usage explicite de std::min

    cellShape.setSize(sf::Vector2f(cellSize, cellSize));

    // Chargement police multi-plateforme (essai de plusieurs chemins)
    bool fontLoaded = false;

    // Liste de polices a essayer (monospace pour style "code/matrice")
    vector<string> fontPaths = {
        // Windows - Polices monospace (style retro/tech)
        "C:/Windows/Fonts/consola.ttf",      // Consolas (monospace, style moderne)
        "C:/Windows/Fonts/cour.ttf",         // Courier New
        "C:/Windows/Fonts/lucon.ttf",        // Lucida Console
        // Linux
        "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationMono-Regular.ttf",
        "/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf",
        // MacOS
        "/System/Library/Fonts/Courier.dfont",
        "/Library/Fonts/Courier New.ttf"
    };

    for (const auto& path : fontPaths) {
        if (font.loadFromFile(path)) {
            fontLoaded = true;
            std::cout << "Police chargee : " << path << std::endl;
            break;
        }
    }

    if (!fontLoaded) {
        cerr << "AVERTISSEMENT : Aucune police trouvee. Le texte ne s'affichera pas correctement.\n";
    }

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Green);  // Vert style "Matrix" pour theme retro
    text.setPosition(10, 10);
}

void GameWindow::run() {
    while (window.isOpen()) {

        // Gestion evenements clavier/fenetre
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // NEW: gestion des touches clavier (flèches, espace, et lettres G/B/L/N/C)
            if (event.type == sf::Event::KeyPressed) {
                sf::Keyboard::Key key = event.key.code;

                // accélérer
                if (key == sf::Keyboard::Up && iterationDelay > 20)
                    iterationDelay -= 20;

                // ralentir
                if (key == sf::Keyboard::Down)
                    iterationDelay += 20;

                // pause / reprise
                if (key == sf::Keyboard::Space)
                    iterationDelay = (iterationDelay == 1000000) ? 200 : 1000000;

                // oliv : motifs pré-programmés avec des lettres (plus fiables que 0/1/2/3 sur AZERTY)

                // oliv: G -> Glider
                if (key == sf::Keyboard::G) {
                    currentPattern = PatternType::Glider;
                    std::cout << "Motif selectionne : Glider (G)" << std::endl;
                }
                // oliv: B -> Blinker
                else if (key == sf::Keyboard::B) {
                    currentPattern = PatternType::Blinker;
                    std::cout << "Motif selectionne : Blinker (B)" << std::endl;
                }
                // oliv: L -> Block
                else if (key == sf::Keyboard::L) {
                    currentPattern = PatternType::Block;
                    std::cout << "Motif selectionne : Block (L)" << std::endl;
                }
                // oliv: N -> aucun motif
                else if (key == sf::Keyboard::N) {
                    currentPattern = PatternType::None;
                    std::cout << "Motif selectionne : aucun (N)" << std::endl;
                }

                // oliv: C -> poser le motif sélectionné au centre de la grille
                if (key == sf::Keyboard::C && currentPattern != PatternType::None && isPaused()) {
                    int centerRow = grid.getHeight() / 2;
                    int centerCol = grid.getWidth() / 2;
                    placePattern(currentPattern, centerRow, centerCol);
                    std::cout << "Motif place au centre" << std::endl;
                }
            }

            // oliv : gestion des clics souris pour éditer la grille, et gérer l'évènement pause
            if (event.type == sf::Event::MouseButtonPressed && isPaused()) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                int rows = grid.getHeight();
                int cols = grid.getWidth();

                // oliv: on vérifie que le clic se situe dans la zone de la grille
                if (mouseX >= 0 && mouseX < static_cast<int>(cols * cellSize) &&
                    mouseY >= 0 && mouseY < static_cast<int>(rows * cellSize)) {

                    int col = static_cast<int>(mouseX / cellSize);
                    int row = static_cast<int>(mouseY / cellSize);

                    if (event.mouseButton.button == sf::Mouse::Left) {
                        // oliv: clic gauche -> on bascule l'état alive -> dead ou dead-> alive de la cellule
                        grid.toggleCell(row, col);
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right) {
                        // oliv: clic droit -> on pose le motif sélectionné centré sur la cellule
                        placePattern(currentPattern, row, col);
                    }
                }
            }
        }

        // Avance d'une generation toutes les X ms
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
    updater->update(grid, rule);
    iterationCount++;
}

// oliv : affichage d'infos supplémentaires (motif courant + rappels des touches)
void GameWindow::drawInfo() {
    std::string patternName = "None";
    switch (currentPattern) {
        case PatternType::Glider:  patternName = "Glider = (G)";  break;
        case PatternType::Blinker: patternName = "Blinker = (B)"; break;
        case PatternType::Block:   patternName = "Block =  (L)";   break;
        case PatternType::None:    patternName = "None = (N)";    break;
    }

    text.setString(
        "Iteration : " + to_string(iterationCount) +
        "\nDelay : " + to_string(iterationDelay) + " ms" +
        "\nPattern : " + patternName +
        "\nL-Click: toggle cell" +
        "\nR-Click: place pattern" +
        "\nG/B/L/N: select pattern" +
        "\nC: place pattern center"
    );

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
                cellShape.setFillColor(sf::Color(30, 30, 30)); // gris fonce

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

// oliv: placement des motifs pré-programmés autour (row, col) d'une cellule  après click sur cette cellule
void GameWindow::placePattern(PatternType pattern, int row, int col) {
    if (pattern == PatternType::None) {
        return;
    }

    // oliv: lambda utilitaire pour ne pas sortir de la grille
    auto setIfInside = [this](int r, int c) {
        if (r >= 0 && r < grid.getHeight() &&
            c >= 0 && c < grid.getWidth()) {
            grid.setAlive(r, c);
        }
    };
//oliv : Switch pour pattern preco corentin
    switch (pattern) {
        case PatternType::Glider:
            // oliv: Glider orienté vers le bas-droite, ancré sur (row, col)
            setIfInside(row,     col + 2);
            setIfInside(row + 1, col + 2);
            setIfInside(row + 1, col);
            setIfInside(row + 2, col + 1);
            setIfInside(row + 2, col + 2);
            break;

        case PatternType::Blinker:
            // oliv: Blinker horizontal centré sur (row, col)
            setIfInside(row, col - 1);
            setIfInside(row, col);
            setIfInside(row, col + 1);
            break;

        case PatternType::Block:
            // oliv: Bloc 2x2 dont (row, col) est le coin supérieur gauche
            setIfInside(row,     col);
            setIfInside(row,     col + 1);
            setIfInside(row + 1, col);
            setIfInside(row + 1, col + 1);
            break;

        default:
            break;
    }
}
