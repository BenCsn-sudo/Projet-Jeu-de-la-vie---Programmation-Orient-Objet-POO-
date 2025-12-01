# Jeu de la Vie de Conway - Projet POO
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/C++-20-blue.svg)](https://isocpp.org/)
[![SFML](https://img.shields.io/badge/SFML-2.6-green.svg)](https://www.sfml-dev.org/)

## Description

Implementation complete du **Jeu de la Vie de John Conway** en C++ avec une architecture orientee objet rigoureuse. Le projet respecte les principes SOLID et propose deux modes d'execution : console (sauvegarde dans fichiers) et graphique (visualisation temps reel avec SFML).

### Caracteristiques principales

- ✅ Architecture POO complete (State Pattern, Strategy Pattern)
- ✅ Mode Console : sauvegarde des iterations dans des fichiers
- ✅ Mode Graphique : visualisation temps reel avec SFML
- ✅ Tests unitaires complets (8 tests)
- ✅ Multi-plateforme (Windows, Linux, macOS)
- ✅ Code conforme C++20 avec STL

---

## Table des matieres

1. [Regles du Jeu](#regles-du-jeu)
2. [Installation](#installation)
3. [Compilation](#compilation)
4. [Utilisation](#utilisation)
5. [Architecture](#architecture)
6. [Tests](#tests)
7. [Exemples](#exemples)
8. [Structure du Projet](#structure-du-projet)

---

## Regles du Jeu

Le Jeu de la Vie est un automate cellulaire base sur une grille 2D ou chaque cellule peut etre **vivante** (1) ou **morte** (0).

### Regles d'evolution (iteration t → t+1)

1. **Naissance** : Une cellule morte avec exactement **3 voisins vivants** devient vivante
2. **Survie** : Une cellule vivante avec **2 ou 3 voisins vivants** reste vivante
3. **Mort** : Dans tous les autres cas, la cellule meurt (isolement ou surpopulation)

### Voisinage

Chaque cellule a **8 voisins** (horizontal, vertical, diagonal) :
```
┌─┬─┬─┐
│█│█│█│
├─┼─┼─┤
│█│X│█│  X = cellule centrale
├─┼─┼─┤
│█│█│█│
└─┴─┴─┘
```

---

## Installation

### Prerequis

- **Compilateur C++20** : g++ 10+ ou MSVC 2019+
- **SFML 2.5+** : Bibliotheque graphique (uniquement pour le mode graphique)
- **Systeme d'exploitation** : Windows, Linux ou macOS

### Installation SFML

#### Windows (MSYS2/MinGW)
```bash
# Dans le terminal MSYS2 MINGW64
pacman -S mingw-w64-x86_64-sfml
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install libsfml-dev
```

#### macOS (Homebrew)
```bash
brew install sfml
```

---

## Compilation

### Methode 1 : Commande manuelle (tous OS)

#### Windows (PowerShell)
```powershell
g++ -std=c++20 -Wall -Wextra -o jeu_de_la_vie.exe `
    main.cpp Components/Game.cpp Components/Grid/Grid.cpp `
    Components/Cell/AliveState.cpp Components/Cell/DeadState.cpp `
    Components/Rules/StandardRule.cpp Services/GameRunner.cpp `
    Services/IO/FileReader.cpp Services/IO/FileWriter.cpp `
    Services/IO/FolderManager.cpp Services/IO/FileName.cpp `
    Ihm/GameWindow.cpp `
    -lsfml-graphics -lsfml-window -lsfml-system
```

#### Linux / macOS
```bash
g++ -std=c++20 -Wall -Wextra -o jeu_de_la_vie \
    main.cpp Components/Game.cpp Components/Grid/Grid.cpp \
    Components/Cell/AliveState.cpp Components/Cell/DeadState.cpp \
    Components/Rules/StandardRule.cpp Services/GameRunner.cpp \
    Services/IO/FileReader.cpp Services/IO/FileWriter.cpp \
    Services/IO/FolderManager.cpp Services/IO/FileName.cpp \
    Ihm/GameWindow.cpp \
    -lsfml-graphics -lsfml-window -lsfml-system
```

### Methode 2 : Makefile (Linux/macOS uniquement)
```bash
make clean
make
```

---

## Utilisation

### Lancement du programme

#### Windows
```powershell
.\jeu_de_la_vie.exe
```

#### Linux / macOS
```bash
./jeu_de_la_vie
```

### Menu principal

```
=== Jeu de la Vie - Conway ===
Choisissez le mode d'execution :
  1. Mode Console (sauvegarde iterations dans fichiers)
  2. Mode Graphique (visualisation SFML)
Votre choix (1 ou 2) :
```

---

## Mode 1 : Console

### Description
Execute la simulation et sauvegarde chaque iteration dans un fichier texte.

### Utilisation

1. Choisir option **1**
2. Entrer le chemin du fichier d'entree (ex: `input.txt`)
3. Entrer le nombre d'iterations (ex: `10`)

### Exemple
```
Votre choix (1 ou 2) : 1
Chemin du fichier d'entree : input.txt
Nombre d'iterations : 5
```

### Resultat
Creation d'un dossier `input_out/` contenant :
```
input_out/
├── 1.txt         <- Etat apres iteration 1
├── 2.txt         <- Etat apres iteration 2
├── 3.txt         <- Etat apres iteration 3
├── 4.txt         <- Etat apres iteration 4
├── 5.txt         <- Etat apres iteration 5
└── final_grid.txt <- Copie de l'etat final
```

### Format des fichiers

**Entree (`input.txt`)** :
```
5 5
0 0 1 0 0
0 0 0 1 0
0 1 1 1 0
0 0 0 0 0
0 0 0 0 0
```

**Sortie (`input_out/1.txt`)** :
```
5 5
0 0 0 0 0
0 1 0 1 0
0 0 1 1 0
0 0 1 0 0
0 0 0 0 0
```

---

## Mode 2 : Graphique

### Description
Affiche la grille en temps reel avec une interface graphique SFML.

### Utilisation

1. Choisir option **2**
2. La simulation demarre automatiquement avec `input.txt`

### Controles clavier

| Touche | Action |
|--------|--------|
| `↑` (Fleche Haut) | Accelerer la simulation (-20ms) |
| `↓` (Fleche Bas) | Ralentir la simulation (+20ms) |
| `Espace` | Pause / Reprendre |
| `Fermer fenetre` | Quitter |

### Interface

- **Cellules vivantes** : Vert
- **Cellules mortes** : Gris fonce
- **Texte** : Affiche iteration actuelle et delai
- **Grille** : Bordures blanches

---

## Architecture

### Principes de conception

Le projet applique les principes **SOLID** :

- **S** (Single Responsibility) : Chaque classe a une responsabilite unique
- **O** (Open/Closed) : Extensible via heritage (Rules, CellState)
- **L** (Liskov Substitution) : Polymorphisme respecte
- **I** (Interface Segregation) : Interfaces minimales et cohesives
- **D** (Dependency Inversion) : Depend d'abstractions (Rules, CellState)

### Patterns utilises

1. **State Pattern** : `CellState`, `AliveState`, `DeadState`
2. **Strategy Pattern** : `Rules`, `StandardRule`
3. **Separation MVC** : Logique (Components) / Vue (Ihm) / Services (IO)

### Diagrammes UML

Le dossier `Diagrammes_UML/` contient tous les diagrammes au format PlantUML :

**Diagramme de classes** : Structure complete du projet
- Classes, attributs, methodes
- Relations (heritage, composition, association)
- Hierarchies (CellState, Rules)

**Diagrammes d'activite** (2 diagrammes) :
- Vue globale : flux complet du programme (menu, modes)
- Calcul generation : detail application regles Conway

**Diagrammes de sequence** (3 diagrammes) :
- Mode console : interactions avec fichiers
- Mode graphique : boucle SFML et affichage
- Application regles : detail technique cellule par cellule

📖 **Documentation** : Voir `Diagrammes_UML/README_DIAGRAMMES.md` pour visualiser

### Diagramme de classes (simplifie)

```
┌──────────┐         ┌──────────┐
│   Game   │─────────│   Grid   │
└──────────┘         └──────────┘
     │                    │
     │                    │ contains
     ▼                    ▼
┌──────────┐         ┌──────────┐
│  Rules   │         │   Cell   │
└──────────┘         └──────────┘
     △                    │
     │                    │ has-a
┌────────────┐            ▼
│StandardRule│       ┌──────────┐
└────────────┘       │CellState │
                     └──────────┘
                          △
                   ┌──────┴──────┐
              ┌────────┐    ┌────────┐
              │AliveState│    │DeadState│
              └────────┘    └────────┘
```

### Hierarchie des fichiers

```
Components/              # Logique metier
├── Game.cpp/h          # Orchestre jeu
├── Cell/               # Gestion cellules
│   ├── Cell.h
│   ├── CellState.h     (interface)
│   ├── AliveState.cpp/h
│   └── DeadState.cpp/h
├── Grid/               # Grille 2D
│   └── Grid.cpp/h
└── Rules/              # Regles d'evolution
    ├── Rules.h         (interface)
    └── StandardRule.cpp/h

Services/               # Services annexes
├── GameRunner.cpp/h    # Mode console
└── IO/                 # Lecture/ecriture
    ├── FileReader.cpp/h
    ├── FileWriter.cpp/h
    ├── FolderManager.cpp/h
    └── FileName.cpp/h

Ihm/                    # Interface graphique
└── GameWindow.cpp/h    # Fenetre SFML

tests/                  # Tests unitaires
└── test_grid.cpp
```

---

## Tests

### Compilation des tests

```bash
# Windows
g++ -std=c++20 -Wall -Wextra -o test_grid.exe tests/test_grid.cpp Components/Game.cpp Components/Grid/Grid.cpp Components/Cell/AliveState.cpp Components/Cell/DeadState.cpp Components/Rules/StandardRule.cpp Services/IO/FileReader.cpp Services/IO/FileWriter.cpp Services/IO/FolderManager.cpp Services/IO/FileName.cpp

# Linux/macOS
g++ -std=c++20 -Wall -Wextra -o test_grid tests/test_grid.cpp Components/Game.cpp Components/Grid/Grid.cpp Components/Cell/AliveState.cpp Components/Cell/DeadState.cpp Components/Rules/StandardRule.cpp Services/IO/FileReader.cpp Services/IO/FileWriter.cpp Services/IO/FolderManager.cpp Services/IO/FileName.cpp
```

### Execution

```bash
# Windows
.\test_grid.exe

# Linux/macOS
./test_grid
```

### Tests couverts

1. ✅ Grille vide reste vide
2. ✅ Regle de naissance (3 voisins)
3. ✅ Mort par isolement (< 2 voisins)
4. ✅ Survie (2-3 voisins)
5. ✅ Mort par surpopulation (> 3 voisins)
6. ✅ Motif stable "Block"
7. ✅ Comptage de voisins
8. ✅ Lecture de fichier

### Resultat attendu

```
========================================
  Tests Unitaires - Jeu de la Vie
========================================

[OK] Grille vide reste vide
[OK] Regle de naissance (3 voisins)
[OK] Mort par isolement (0 voisin)
[OK] Survie avec 2 voisins
[OK] Mort par surpopulation (4 voisins)
[OK] Motif stable 'Block'
[OK] Comptage 8 voisins
[OK] Lecture fichier input.txt

========================================
  Resultats : 8/8 tests passes
========================================
```

---

## Exemples

### Motifs classiques

#### 1. Glider (planeur)
```
5 5
0 0 1 0 0
0 0 0 1 0
0 1 1 1 0
0 0 0 0 0
0 0 0 0 0
```
Motif qui se deplace en diagonale.

#### 2. Blinker (oscillateur periode 2)
```
5 5
0 0 0 0 0
0 0 1 0 0
0 0 1 0 0
0 0 1 0 0
0 0 0 0 0
```
Oscille entre horizontal et vertical.

#### 3. Block (stable)
```
4 4
0 0 0 0
0 1 1 0
0 1 1 0
0 0 0 0
```
Ne change jamais.

#### 4. Toad (oscillateur periode 2)
```
6 6
0 0 0 0 0 0
0 0 0 0 0 0
0 0 1 1 1 0
0 1 1 1 0 0
0 0 0 0 0 0
0 0 0 0 0 0
```

---

## Structure du Projet

```
Projet-Jeu-de-la-vie--POO/
├── README.md                    # Ce fichier
├── MODE_CONSOLE_EXPLICATION.md  # Documentation detaillee mode console
├── main.cpp                     # Point d'entree
├── Makefile                     # Compilation Linux/macOS
├── input.txt                    # Fichier exemple
├── .gitignore                   # Fichiers ignores par git
├── Components/                  # Logique metier
├── Services/                    # Services (IO, GameRunner)
├── Ihm/                         # Interface graphique
├── tests/                       # Tests unitaires
└── Diagrammes_UML/             # Diagrammes de conception

Generes apres execution :
├── jeu_de_la_vie.exe           # Executable Windows
├── jeu_de_la_vie               # Executable Linux/macOS
├── test_grid.exe               # Tests Windows
├── test_grid                   # Tests Linux/macOS
└── *_out/                      # Dossiers de sortie (mode console)
```

---

## Auteurs

- Projet realise dans le cadre du cours de **Programmation Orientee Objet (POO)**
- Annee universitaire 2024-2025

---

## Licence

Ce projet est sous licence MIT. Voir le fichier LICENSE pour plus de details.
