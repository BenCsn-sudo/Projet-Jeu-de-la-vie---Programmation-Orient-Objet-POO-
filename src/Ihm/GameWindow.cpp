#include "GameWindow.h"
#include <iostream>
#include <vector>
#include <string>
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

        sf::Event event;
        while (window.pollEvent(event)) {

            // gestion de la fermeture de la fenêtre SFML (croix en haut à droite)
            if (event.type == sf::Event::Closed)
                window.close();

            // ============================
            //  GESTION DU CLAVIER
            // ============================
            if (event.type == sf::Event::KeyPressed) {
                sf::Keyboard::Key key = event.key.code;

                // flèche haut -> on réduit le délai => la simulation va plus vite
                if (key == sf::Keyboard::Up && iterationDelay > 20)
                    iterationDelay -= 20;

                // flèche bas -> on augmente le délai => la simulation va plus lentement
                if (key == sf::Keyboard::Down)
                    iterationDelay += 20;

                // barre espace -> pause / reprise
                //       on considère que delay = 1000000 <=> pause
                if (key == sf::Keyboard::Space)
                    iterationDelay = (iterationDelay == 1000000) ? 1000 : 1000000;

                // motifs pré-programmés avec des lettres (plus fiables que 0/1/2/3 sur AZERTY)

                // G -> motif Glider sélectionné
                if (key == sf::Keyboard::G) {
                    currentPattern = PatternType::Glider;
                    std::cout << "Motif selectionne : Glider (G)" << std::endl;
                }
                // B -> motif Blinker sélectionné
                else if (key == sf::Keyboard::B) {
                    currentPattern = PatternType::Blinker;
                    std::cout << "Motif selectionne : Blinker (B)" << std::endl;
                }
                // L -> motif Block sélectionné
                else if (key == sf::Keyboard::L) {
                    currentPattern = PatternType::Block;
                    std::cout << "Motif selectionne : Block (L)" << std::endl;
                }
                // N -> aucun motif (désactivation)
                else if (key == sf::Keyboard::N) {
                    currentPattern = PatternType::None;
                    std::cout << "Motif selectionne : aucun (N)" << std::endl;
                }

                // C -> placer le motif sélectionné au centre de la grille
                //        uniquement quand le jeu est en pause (édition protégée)
                if (key == sf::Keyboard::C && currentPattern != PatternType::None && isPaused()) {
                    int centerRow = grid.getHeight() / 2;
                    int centerCol = grid.getWidth() / 2;
                    placePattern(currentPattern, centerRow, centerCol);
                    std::cout << "Motif place au centre" << std::endl;
                }

		if (key == sf::Keyboard::D && isPaused()) {
		    clearGrid();
		    std::cout << "Grille effacé" << std::endl;
		}
            }

            // ======================================
            // SOURIS - CLIC (début du drag)
            // ======================================
            // on n'autorise l'édition de la grille à la souris QUE quand le jeu est en pause
            if (event.type == sf::Event::MouseButtonPressed && isPaused()) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                int rows = grid.getHeight();
                int cols = grid.getWidth();

                // on vérifie que le clic est à l'intérieur de la zone de la grille
                if (mouseX >= 0 && mouseX < static_cast<int>(cols * cellSize) &&
                    mouseY >= 0 && mouseY < static_cast<int>(rows * cellSize)) {

                    int col = static_cast<int>(mouseX / cellSize);
                    int row = static_cast<int>(mouseY / cellSize);

                    if (event.mouseButton.button == sf::Mouse::Left) {
                        // clic gauche -> on TOGGLE l'état de la cellule (vivante <-> morte)
                        //       => le clic simple continue de marcher comme avant
                        grid.toggleCell(row, col);

                        // on active le "mode drag"
                        //       tant que le bouton reste enfoncé, on va pouvoir dessiner
                        isDragging = true;
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right) {
                        // clic droit -> on pose le motif pré-sélectionné autour de cette cellule
                        placePattern(currentPattern, row, col);
                    }
                }
            }

            // ======================================
            // SOURIS - RELÂCHEMENT (fin du drag)
            // ======================================
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // on arrête le mode drag dès qu'on relâche le bouton gauche
                    isDragging = false;
                }
            }

            // ======================================
            // SOURIS - MOUVEMENT (drag dessin)
            // ======================================
            // si le bouton gauche est en drag ET que le jeu est en pause,
            //       chaque mouvement de souris "peint" des cellules vivantes
            if (event.type == sf::Event::MouseMoved && isDragging && isPaused()) {
                int mouseX = event.mouseMove.x;
                int mouseY = event.mouseMove.y;

                int rows = grid.getHeight();
                int cols = grid.getWidth();

                // même vérification que pour le clic: on reste dans les bornes de la grille
                if (mouseX >= 0 && mouseX < static_cast<int>(cols * cellSize) &&
                    mouseY >= 0 && mouseY < static_cast<int>(rows * cellSize)) {

                    int col = static_cast<int>(mouseX / cellSize);
                    int row = static_cast<int>(mouseY / cellSize);

                    // "pinceau" -> on force la cellule en vivante
                    //       (drag = dessiner des vivantes sur le chemin)
                    grid.setAlive(row, col);
                }
            }
        }

        // avance d'une génération toutes les X ms
        //       si le delay est énorme (pause), cette condition est rarement vraie
        if (clock.getElapsedTime().asMilliseconds() >= iterationDelay) {
            update();
            clock.restart();
        }

        // phase d'affichage SFML (fond -> grille -> texte)
        window.clear(sf::Color::Black);
        drawGrid();
        drawInfo();
        window.display();
    }
}

// met toutes les cellules de la grille à l'état mort
void GameWindow::clearGrid() {
    int rows = grid.getHeight();
    int cols = grid.getWidth();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid.setDead(r, c);
        }
    }
}

void GameWindow::update() {
    updater->update(grid, rule);
    iterationCount++;
}

// affichage d'infos supplémentaires (motif courant + rappels des touches)
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
	    "\nDel: clear grid"
    );

    window.draw(text);
}

void GameWindow::drawGrid() {
    int rows = grid.getHeight();
    int cols = grid.getWidth();

    // Dessin des cellules
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
	    if (grid.getCell(r,c).isObstacle()){
		cellShape.setFillColor(sf::Color(200,0,0));
            }else if (grid.getCell(r, c).isAlive())
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

// placement des motifs pré-programmés autour (row, col) d'une cellule  après click sur cette cellule
void GameWindow::placePattern(PatternType pattern, int row, int col) {
    if (pattern == PatternType::None) {
        return;
    }

    // lambda utilitaire pour ne pas sortir de la grille
    auto setIfInside = [this](int r, int c) {
        if (r >= 0 && r < grid.getHeight() &&
            c >= 0 && c < grid.getWidth()) {
            grid.setAlive(r, c);
        }
    };
// Switch pour pattern preco
    switch (pattern) {
        case PatternType::Glider:
            // Glider orienté vers le bas-droite, ancré sur (row, col)
            setIfInside(row,     col + 2);
            setIfInside(row + 1, col + 2);
            setIfInside(row + 1, col);
            setIfInside(row + 2, col + 1);
            setIfInside(row + 2, col + 2);
            break;

        case PatternType::Blinker:
            // Blinker horizontal centré sur (row, col)
            setIfInside(row, col - 1);
            setIfInside(row, col);
            setIfInside(row, col + 1);
            break;

        case PatternType::Block:
            // Bloc 2x2 dont (row, col) est le coin supérieur gauche
            setIfInside(row,     col);
            setIfInside(row,     col + 1);
            setIfInside(row + 1, col);
            setIfInside(row + 1, col + 1);
            break;

        default:
            break;
    }
}
