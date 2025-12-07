#include <iostream>
#include <cassert>
#include "../Components/Grid/Grid.h"
#include "../Components/Rules/StandardRule.h"
#include "../Components/Cell/AliveState.h"
#include "../Components/Cell/DeadState.h"
#include "../Services/IO/FileReader.h"
#include "../Components/Updaters/SingleThreadUpdater.h"

using namespace std;

// Test 1 : Grille vide reste vide
void test_empty_grid() {
    Grid grid(5, 5);
    StandardRule rule;
    SingleThreadUpdater updater;

    updater.update(grid, rule);

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            assert(!grid.getCell(row, col).isAlive());
        }
    }

    cout << "[OK] Test 1 : Grille vide reste vide" << endl;
}

// Test 2 : Regle de naissance (3 voisins)
void test_birth_rule() {
    Grid grid(3, 3);
    StandardRule rule;
    SingleThreadUpdater updater;

    grid.getCell(0, 0).setState(new AliveState());
    grid.getCell(0, 1).setState(new AliveState());
    grid.getCell(0, 2).setState(new AliveState());

    updater.update(grid, rule);

    assert(grid.getCell(1, 1).isAlive());

    cout << "[OK] Test 2 : Regle de naissance (3 voisins)" << endl;
}

// Test 3 : Mort par sous-population (<2 voisins)
void test_death_by_underpopulation() {
    Grid grid(3, 3);
    StandardRule rule;
    SingleThreadUpdater updater;

    grid.getCell(1, 1).setState(new AliveState());
    grid.getCell(0, 0).setState(new AliveState());

    updater.update(grid, rule);

    assert(!grid.getCell(1, 1).isAlive());

    cout << "[OK] Test 3 : Mort par sous-population (<2 voisins)" << endl;
}

// Test 4 : Survie avec 2 voisins
void test_survival_rule() {
    Grid grid(3, 3);
    StandardRule rule;
    SingleThreadUpdater updater;

    grid.getCell(1, 1).setState(new AliveState());
    grid.getCell(0, 0).setState(new AliveState());
    grid.getCell(0, 1).setState(new AliveState());

    updater.update(grid, rule);

    assert(grid.getCell(1, 1).isAlive());

    cout << "[OK] Test 4 : Survie avec 2 voisins" << endl;
}

// Test 5 : Mort par surpopulation (>3 voisins)
void test_death_by_overpopulation() {
    Grid grid(3, 3);
    StandardRule rule;
    SingleThreadUpdater updater;

    grid.getCell(1, 1).setState(new AliveState());
    grid.getCell(0, 0).setState(new AliveState());
    grid.getCell(0, 1).setState(new AliveState());
    grid.getCell(1, 0).setState(new AliveState());
    grid.getCell(2, 0).setState(new AliveState());

    updater.update(grid, rule);

    assert(!grid.getCell(1, 1).isAlive());

    cout << "[OK] Test 5 : Mort par surpopulation (>3 voisins)" << endl;
}

// Test 6 : Motif stable Block 2x2
void test_stable_block() {
    Grid grid(4, 4);
    StandardRule rule;
    SingleThreadUpdater updater;

    grid.getCell(1, 1).setState(new AliveState());
    grid.getCell(1, 2).setState(new AliveState());
    grid.getCell(2, 1).setState(new AliveState());
    grid.getCell(2, 2).setState(new AliveState());

    updater.update(grid, rule);

    assert(grid.getCell(1, 1).isAlive());
    assert(grid.getCell(1, 2).isAlive());
    assert(grid.getCell(2, 1).isAlive());
    assert(grid.getCell(2, 2).isAlive());

    cout << "[OK] Test 6 : Motif stable 'Block' 2x2" << endl;
}

// Test 7 : Comptage de 8 voisins
void test_neighbour_count() {
    Grid grid(3, 3);

    grid.getCell(0, 0).setState(new AliveState());
    grid.getCell(0, 1).setState(new AliveState());
    grid.getCell(0, 2).setState(new AliveState());
    grid.getCell(1, 0).setState(new AliveState());
    grid.getCell(1, 2).setState(new AliveState());
    grid.getCell(2, 0).setState(new AliveState());
    grid.getCell(2, 1).setState(new AliveState());
    grid.getCell(2, 2).setState(new AliveState());

    int count = grid.countLivingNeighbours(1, 1);
    assert(count == 8);

    cout << "[OK] Test 7 : Comptage correct de 8 voisins" << endl;
}

// Test 8 : Lecture de fichier
void test_file_reading() {
    FileReader reader;

    // Utilisation de input_merci.txt qui est present dans le dossier src
    Grid grid = reader.read("input_merci.txt");

    if (grid.getHeight() > 0 && grid.getWidth() > 0) {
        cout << "[OK] Test 8 : Lecture fichier input_merci.txt" << endl;
    } else {
        throw runtime_error("Fichier input_merci.txt introuvable ou vide");
    }
}

// Test 9 : Grille torique
void test_toroidal_grid() {
    Grid grid(5, 5);

    grid.getCell(0, 0).setState(new AliveState());
    grid.getCell(0, 4).setState(new AliveState());
    grid.getCell(4, 0).setState(new AliveState());
    grid.getCell(4, 4).setState(new AliveState());

    int count_corner = grid.countLivingNeighbours(0, 0);
    assert(count_corner == 3);

    cout << "[OK] Test 9 : Grille torique (wraparound)" << endl;
}

// Test 10 : Oscillateur Blinker
void test_blinker_oscillator() {
    Grid grid(5, 5);
    StandardRule rule;
    SingleThreadUpdater updater;

    grid.getCell(1, 2).setState(new AliveState());
    grid.getCell(2, 2).setState(new AliveState());
    grid.getCell(3, 2).setState(new AliveState());

    updater.update(grid, rule);

    assert(grid.getCell(2, 1).isAlive());
    assert(grid.getCell(2, 2).isAlive());
    assert(grid.getCell(2, 3).isAlive());
    assert(!grid.getCell(1, 2).isAlive());
    assert(!grid.getCell(3, 2).isAlive());

    cout << "[OK] Test 10 : Oscillateur Blinker (periode 2)" << endl;
}

// Fonction principale pour executer tous les tests
int run_all_tests() {
    cout << "\n========================================" << endl;
    cout << "  TESTS UNITAIRES - JEU DE LA VIE" << endl;
    cout << "========================================\n" << endl;

    int tests_passed = 0;
    int tests_total = 10;

    try {
        test_empty_grid();
        tests_passed++;

        test_birth_rule();
        tests_passed++;

        test_death_by_underpopulation();
        tests_passed++;

        test_survival_rule();
        tests_passed++;

        test_death_by_overpopulation();
        tests_passed++;

        test_stable_block();
        tests_passed++;

        test_neighbour_count();
        tests_passed++;

        test_file_reading();
        tests_passed++;

        test_toroidal_grid();
        tests_passed++;

        test_blinker_oscillator();
        tests_passed++;

        cout << "\n========================================" << endl;
        cout << "  RESULTATS : " << tests_passed << "/" << tests_total << " tests passes" << endl;
        cout << "========================================\n" << endl;
    }
    catch (const exception& e) {
        cerr << "\n[ERREUR] Un test a echoue : " << e.what() << endl;
        cout << "\nResultats : " << tests_passed << "/" << tests_total << " tests passes" << endl;
        return 1;
    }
    return 0;
}
