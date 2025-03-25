# Structures de Données et Algorithmes II - Projet

Ce dépôt contient un projet portant sur la création et la manipulation d'un arbre généalogique en C, mettant en œuvre divers concepts avancés en structures de données et algorithmes, notamment l'utilisation de graphes et leurs parcours tels que la recherche en profondeur (DFS) et la recherche en largeur (BFS).

## Contenu du projet

### `Structures principales`
Le projet repose sur les structures suivantes :
- **Genealogie** : Contient un tableau dynamique d'individus et gère la structure globale de l'arbre.
- **Individu** : Représente une personne avec son nom, ses dates de naissance et de décès, ainsi que ses liens de parenté (père, mère, cadet, aîné).
- **Date** : Structure simple contenant jour, mois et année.

### `Fonctions principales`
#### **1. Constructeurs**
- `void genealogieInit(Genealogie *g);` : Initialise une généalogie.
- `ident adj(Genealogie *g, char *s, ident p, ident m, date n, date d);` : Ajoute un individu à l'arbre.

#### **2. Gestion des relations familiales**
- `bool freres_soeurs(Genealogie *g, ident x, ident y);` : Vérifie si deux individus sont frères et sœurs.
- `bool cousins(Genealogie *g, ident x, ident y);` : Vérifie si deux individus sont cousins.

#### **3. Affichages**
- `void affichage_current(Genealogie *g);` : Affiche tous les individus de l'arbre.
- `void affichage_fratrie(Genealogie *g, ident x);` : Affiche les frères et sœurs d'un individu.
- `void affichage_cousins(Genealogie *g, ident x);` : Affiche les cousins d'un individu.
- `void affichage_oncles(Genealogie *g, ident x);` : Affiche les oncles d'un individu.

#### **4. Parcours de l'arbre**
- `bool ancetre(Genealogie *g, ident x, ident y);` : Vérifie si x est un ancêtre de y.
- `bool ancetreCommun(Genealogie *g, ident x, ident y);` : Détermine si x et y ont un ancêtre commun.
- `ident plus_ancien(Genealogie *g, ident x);` : Trouve l'individu le plus ancien d'un sous-arbre.

#### **5. Fusion d'arbres généalogiques**
- `void genealogieFusion(Genealogie *res, Genealogie *a1, Genealogie *a2);` : Fusionne deux arbres généalogiques.
- `void genealogieFusion_aux(Genealogie *res, Genealogie *g, ident a_ajouter);` : Fonction auxiliaire pour ajouter un individu lors de la fusion.

## Prérequis
- Compilateur C compatible (GCC recommandé)
- Environnement Linux/macOS pour exécuter les commandes Makefile

## Installation
Clonez le dépôt et accédez au projet :
```bash
git clone https://github.com/YannickLeCam/SDA.git
cd SDA
```

## Utilisation
Compilation et exécution :
```bash
make
./programme
```

