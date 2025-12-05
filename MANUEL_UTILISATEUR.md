# Manuel d'Utilisation - Jeu de la Vie (Conway)

> **Pour utilisateur debutant** : Ce manuel vous explique comment utiliser le programme pas a pas, meme si vous n'avez jamais programme.

---

## 📖 Table des matieres

1. [C'est quoi le Jeu de la Vie ?](#cest-quoi-le-jeu-de-la-vie)
2. [Installation du logiciel](#installation-du-logiciel)
3. [Lancer le programme](#lancer-le-programme)
4. [Mode Console (fichiers texte)](#mode-console)
5. [Mode Graphique (fenetre animee)](#mode-graphique)
6. [Creer vos propres grilles](#creer-vos-propres-grilles)
7. [Exemples prets a l'emploi](#exemples-prets-a-lemploi)
8. [Problemes frequents](#problemes-frequents)

---

## C'est quoi le Jeu de la Vie ?

Le **Jeu de la Vie de Conway** est une simulation automatique inventee en 1970. Imaginez une grille de cases (comme un damier) :
- Chaque case peut etre **vivante** (noire ■) ou **morte** (blanche □)
- A chaque tour, les cases changent selon leurs voisins

### Regles simples :

| Situation | Ce qui se passe |
|-----------|-----------------|
| Une case morte avec exactement 3 voisins vivants | **Nait** (devient vivante) |
| Une case vivante avec 2 ou 3 voisins vivants | **Survit** (reste vivante) |
| Une case vivante avec moins de 2 voisins | **Meurt** (solitude) |
| Une case vivante avec plus de 3 voisins | **Meurt** (surpopulation) |

### Exemple visuel :

```
Tour 1:          Tour 2:          Tour 3:
□ □ □ □ □        □ □ □ □ □        □ □ □ □ □
□ □ ■ □ □        □ □ □ □ □        □ □ □ □ □
□ □ ■ □ □   →    □ ■ ■ ■ □   →    □ □ ■ □ □
□ □ ■ □ □        □ □ □ □ □        □ □ □ □ □
□ □ □ □ □        □ □ □ □ □        □ □ □ □ □
(Barre)          (Barre penche)   (Barre droite)
```

---

## Installation du logiciel

### Etape 1 : Verifier que vous avez les outils

Vous aurez besoin de :
- **MSYS2** (sur Windows) pour compiler le programme
- **SFML** (bibliotheque graphique)

### Etape 2 : Installer MSYS2 (Windows uniquement)

1. Telechargez MSYS2 : [https://www.msys2.org/](https://www.msys2.org/)
2. Installez-le (suivez l'assistant, cliquez "Suivant" partout)
3. A la fin, une fenetre noire s'ouvre (console MSYS2)

### Etape 3 : Installer SFML

Dans la console MSYS2 qui s'est ouverte, tapez :

```bash
pacman -S mingw-w64-x86_64-sfml
```

- Si on vous demande "Continuer ? [O/n]", tapez `O` puis Entree

### Etape 4 : Compiler le programme

1. Ouvrez **MSYS2 MINGW64** (cherchez-le dans le menu Demarrer)
2. Allez dans le dossier du projet :
   ```bash
   cd "/c/Users/Iemane Haddou/Downloads/Projet-Jeu-de-la-vie--POO--main/Projet-Jeu-de-la-vie--POO--main"
   ```
3. Compilez :
   ```bash
   g++ -std=c++20 -o jeu_de_la_vie.exe main.cpp Components/Game.cpp Components/Grid/Grid.cpp Components/Cell/AliveState.cpp Components/Cell/DeadState.cpp Components/Rules/StandardRule.cpp Services/GameRunner.cpp Services/IO/FileReader.cpp Services/IO/FileWriter.cpp Services/IO/FolderManager.cpp Services/IO/FileName.cpp Ihm/GameWindow.cpp -lsfml-graphics -lsfml-window -lsfml-system
   ```

✅ Si tout se passe bien, vous avez maintenant `jeu_de_la_vie.exe` !

---

## Lancer le programme

### Methode 1 : Double-clic (simple)

1. Trouvez `jeu_de_la_vie.exe` dans votre dossier
2. Double-cliquez dessus
3. Une fenetre noire s'ouvre avec un menu

### Methode 2 : Ligne de commande (PowerShell)

1. Ouvrez PowerShell dans le dossier
2. Tapez :
   ```powershell
   .\jeu_de_la_vie.exe
   ```

### Le menu principal

Vous verrez :

```
=== Jeu de la Vie - Conway ===
Choisissez le mode d'execution :
  1. Mode Console (sauvegarde iterations dans fichiers)
  2. Mode Graphique (visualisation SFML)
Votre choix (1 ou 2) :
```

**Tapez 1 ou 2** selon ce que vous voulez faire.

---

## Mode Console

> **C'est quoi ?** Le programme calcule les generations et les enregistre dans des fichiers texte. Ideal pour analyser evolution par evolution.

### Comment l'utiliser :

1. Lancez le programme
2. Tapez `1` puis Entree
3. Le programme demande :
   ```
   Chemin du fichier d'entree :
   ```
   - Tapez : `input.txt` (ou `exemples/glider.txt`)
4. Le programme demande :
   ```
   Nombre d'iterations :
   ```
   - Tapez : `10` (ou n'importe quel nombre)

### Resultat :

Le programme cree un dossier `input_out/` avec :
- `1.txt` : Etat apres 1 tour
- `2.txt` : Etat apres 2 tours
- `3.txt` : Etat apres 3 tours
- ... jusqu'a 10

### Exemple complet :

```
Votre choix (1 ou 2) : 1
Chemin du fichier d'entree : exemples/glider.txt
Nombre d'iterations : 5

=== Demarrage du mode console ===
[Console] Chargement de la grille...
[Console] Grille chargee avec succes (5 x 5)
[Console] --- Iteration 1/5 ---
[Console] Grille sauvegardee : glider_out/1.txt
[Console] --- Iteration 2/5 ---
[Console] Grille sauvegardee : glider_out/2.txt
...
[Console] Simulation terminee.
```

### Lire les fichiers de sortie :

Ouvrez `glider_out/1.txt` avec Bloc-notes :

```
5 5
0 0 0 0 0
0 0 1 0 0
0 0 0 1 0
0 1 1 1 0
0 0 0 0 0
```

- `5 5` = taille de la grille (largeur x hauteur)
- `1` = cellule vivante (■)
- `0` = cellule morte (□)

---

## Mode Graphique

> **C'est quoi ?** Une fenetre avec animation en temps reel. Vous voyez les cellules evoluer sous vos yeux !

### Comment l'utiliser :

1. Lancez le programme
2. Tapez `2` puis Entree
3. Une fenetre s'ouvre avec votre grille animee

### Controles de la fenetre :

| Touche | Action |
|--------|--------|
| **Espace** | Pause / Reprendre l'animation |
| **Fleche Haut ↑** | Accelerer (animation plus rapide) |
| **Fleche Bas ↓** | Ralentir (animation plus lente) |
| **Fermer (X)** | Quitter le programme |

### Ce que vous voyez :

- **Carres noirs** = cellules vivantes
- **Carres blancs** = cellules mortes
- Les cellules changent automatiquement a chaque tour

### Exemple d'utilisation :

```
Votre choix (1 ou 2) : 2

Police chargee : C:/Windows/Fonts/consola.ttf
```

→ La fenetre s'ouvre et l'animation demarre automatiquement !

**Astuce** : Appuyez sur Espace pour mettre en pause et observer un tour precis.

---

## Creer vos propres grilles

Vous pouvez creer votre propre fichier de depart !

### Format du fichier :

```
[Largeur] [Hauteur]
[Ligne 1 de la grille]
[Ligne 2 de la grille]
...
```

### Exemple : Creer un "clignotant"

1. Ouvrez Bloc-notes (Notepad)
2. Tapez :
   ```
   5 5
   0 0 0 0 0
   0 0 1 0 0
   0 0 1 0 0
   0 0 1 0 0
   0 0 0 0 0
   ```
3. Enregistrez sous `mon_motif.txt` dans le dossier du projet
4. Lancez le programme :
   ```
   Votre choix : 1
   Chemin du fichier d'entree : mon_motif.txt
   Nombre d'iterations : 5
   ```

### Conseils :

- ✅ Utilisez `0` pour les cases mortes
- ✅ Utilisez `1` pour les cases vivantes
- ✅ Gardez le meme nombre de colonnes sur chaque ligne
- ❌ N'oubliez pas la premiere ligne (largeur hauteur)

---

## Exemples prets a l'emploi

Le dossier `exemples/` contient 5 motifs classiques :

### 1. Glider (Planeur) - `exemples/glider.txt`

```
□ □ □ □ □        □ □ □ □ □        □ □ □ □ □
□ □ ■ □ □        □ □ □ □ □        □ □ □ □ □
□ □ □ ■ □   →    □ ■ □ ■ □   →    □ □ □ ■ □
□ ■ ■ ■ □        □ □ ■ ■ □        □ ■ □ ■ □
□ □ □ □ □        □ □ ■ □ □        □ □ ■ ■ □
```

**Particularite** : Se deplace en diagonale indefiniment !

### 2. Blinker (Clignotant) - `exemples/blinker.txt`

```
□ □ □ □ □        □ □ □ □ □        □ □ □ □ □
□ □ ■ □ □        □ □ □ □ □        □ □ ■ □ □
□ □ ■ □ □   ↔    □ ■ ■ ■ □   ↔    □ □ ■ □ □
□ □ ■ □ □        □ □ □ □ □        □ □ ■ □ □
□ □ □ □ □        □ □ □ □ □        □ □ □ □ □
```

**Particularite** : Alterne entre vertical et horizontal (periode 2)

### 3. Block (Bloc) - `exemples/block.txt`

```
□ □ □ □
□ ■ ■ □
□ ■ ■ □  (Ne change jamais !)
□ □ □ □
```

**Particularite** : Totalement stable, ne bouge jamais

### 4. Toad (Crapaud) - `exemples/toad.txt`

Oscille entre 2 formes (periode 2)

### 5. Beacon (Phare) - `exemples/beacon.txt`

Oscille entre 2 formes (periode 2)

### Comment les essayer :

```powershell
# Exemple 1 : Voir le planeur en mode graphique
.\jeu_de_la_vie.exe
2  # Mode graphique

# Exemple 2 : Analyser le clignotant en mode console
.\jeu_de_la_vie.exe
1  # Mode console
exemples/blinker.txt
10  # 10 iterations
```

---

## Problemes frequents

### ❌ "Le programme ne se lance pas"

**Cause** : Le fichier `.exe` n'existe pas encore.

**Solution** :
1. Ouvrez MSYS2 MINGW64
2. Allez dans le dossier du projet
3. Recompilez avec la commande de compilation (voir section Installation)

---

### ❌ "cannot find -lsfml-graphics"

**Cause** : SFML n'est pas installe ou introuvable.

**Solution** :
1. Ouvrez MSYS2 MINGW64 (PAS MSYS2 MSYS ou UCRT64 !)
2. Tapez : `pacman -S mingw-w64-x86_64-sfml`
3. Recompilez le programme

---

### ❌ "Impossible d'ouvrir le fichier"

**Cause** : Le chemin du fichier est incorrect.

**Solution** :
- Verifiez que le fichier existe (utilisez `dir` dans PowerShell)
- Utilisez le bon chemin :
  - ✅ `input.txt` (si dans le meme dossier)
  - ✅ `exemples/glider.txt` (si dans le sous-dossier)
  - ❌ `C:\Users\...\glider.txt` (chemin absolu peut causer problemes)

---

### ❌ "La fenetre graphique est toute noire"

**Cause** : Toutes les cellules sont mortes.

**Solution** :
- Choisissez un fichier avec des cellules vivantes (exemples/)
- Appuyez sur Espace pour verifier que l'animation n'est pas en pause

---

### ❌ "La fenetre graphique ne s'affiche pas"

**Cause** : Police introuvable ou fenetre cachee.

**Solution** :
1. Verifiez le message "Police chargee : ..."
2. Regardez derriere vos autres fenetres (Alt+Tab)
3. Si probleme persiste, verifiez que SFML est bien installe

---

## Raccourcis rapides

| Action | Commande |
|--------|----------|
| Lancer en mode console | `.\jeu_de_la_vie.exe` puis `1` |
| Lancer en mode graphique | `.\jeu_de_la_vie.exe` puis `2` |
| Tester avec exemple | `1` → `exemples/glider.txt` → `10` |
| Recompiler | Voir section "Installation du logiciel" |

---

## Pour aller plus loin

- **README.md** : Documentation technique complete
- **GUIDE_TECHNIQUE.md** : Explications de l'architecture et du code
- **MODE_CONSOLE_EXPLICATION.md** : Details du code du mode console
- **CHECKLIST_LIVRAISON.md** : Verification du projet
- **tests/** : Tests automatises du programme

---

**Bon amusement avec le Jeu de la Vie ! 🎮**
