/**
 * @file arbre.h
 * @author Yannick LE CAM
 * @brief Modelisation et génération d'un arbre genéalogique.
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __ARBRE_H
#define __ARBRE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LG_MAX 64

/***************STRUCTURES***************/
typedef unsigned int ident;

typedef unsigned int Nat;

typedef enum { false, true } bool;

typedef struct s_date { 
    unsigned short int jour;
    unsigned short int  mois;
    unsigned short int  annee; 
} date;

typedef struct s_individu {
    char nom[LG_MAX];
    date naissance, deces;
    ident pere, mere, cadet, faine;
} Individu;

typedef struct s_genealogie {
    Individu *tab; // tableau alloué dynamiquement
    Nat id_cur; // identifiant actuel
    Nat taille_max_tab; // taille max du tableau
} Genealogie;

/***************CONSTRUCTION*******************/
/**
 * @brief Initialisation d'un arbre g
 * 
 * @param g 
 */
void genealogieInit(Genealogie *g);

/**
 * @brief Liberation de la memoire pour le tab 
 * 
 * @param g 
 */
void genealogieFree(Genealogie *g);

/**
 * @brief Ajout un Individu dans l'arbre g avec les elements données si impossible de d'ajouter le nouvel individu alors la fonction renvoie 0 sinon renvoie l'id de l'individu récemment ajouté
 * @pre NON TRAITEE il faut que g soit initialisé ! 
 * @pre s!="" sinon renvoie 0
 * @pre si le nouvel individue a le meme nom et la meme date de naissance alors elle renvoie 0
 * @param g 
 * @param s 
 * @param p 
 * @param m 
 * @param n 
 * @param d 
 * @return ident 
 */
ident adj(Genealogie *g, char *s, ident p, ident m, date n, date d);


/**
 * @brief Renvoie un pointeur sur un Individu venant de l'id x et dans l'arbre g
 * @pre x!=0
 * @pre x<g->id_cur
 * @param g 
 * @param x 
 * @return Individu* 
 */
Individu *get(Genealogie *g, ident x);

/***************LIEN DE PARENTE***************/
/**
 * @brief Renvoie true si x et y sont frere et soeurs entre eux sinon false
 * 
 * @param g 
 * @param x 
 * @param y 
 * @return true 
 * @return false 
 */
bool freres_soeurs(Genealogie *g, ident x, ident y);

/**
 * @brief Renvoie true si x est le cousin de y sinon false
 * 
 * @param g 
 * @param x 
 * @param y 
 * @return true 
 * @return false 
 */
bool cousins(Genealogie *g, ident x, ident y);

/***************AFFICHAGES***************/

/**
 * @brief Affichage de tout les individues de l'arbre g en y affichant toute les informations (surtout pour verifier que tout c'est bien incrémenté) 
 * 
 * @param g 
 */
void affichage_current(Genealogie *g);

/**
 * @brief Affichage de tout les freres et soeurs de l'id x dans l'arbre g
 * 
 * @param g 
 * @param x 
 */
void affiche_freres_soeurs(Genealogie *g, ident x);

/**
 * @brief Affichage de tout les enfants de l'id x dans l'arbre g
 * 
 * @param g 
 * @param x 
 */
void affiche_enfants(Genealogie *g, ident x);

/**
 * @brief Affichage de tout les cousin de l'id x dans l'arbre g
 * 
 * @param g 
 * @param x 
 */
void affiche_cousins(Genealogie *g, ident x);

/**
 * @brief Affichage de tout les oncles/tantes de l'id x dans l'arbre g
 * 
 * @param g 
 * @param x 
 */
void affiche_oncles(Genealogie *g, ident x);

/***************PARCOURS DE L'ARBRE***************/
/**
 * @brief Renvoie true si X est l'ancetre de Y dans l'arbre g sinon false
 * 
 * @param g 
 * @param x 
 * @param y 
 * @return true 
 * @return false 
 */
bool ancetre(Genealogie *g, ident x, ident y);

/**
 * @brief Revoie true si x et y ont un ancetre Commun connue dans l'arbre g sinon false
 * 
 * @param g 
 * @param x 
 * @param y 
 * @return true 
 * @return false 
 */
bool ancetreCommun(Genealogie *g, ident x, ident y);

/**
 * @brief 
 * 
 * @param g 
 * @param x 
 * @return ident 
 */
ident plus_ancien(Genealogie *g, ident x);

/**
 * @brief Affichage de toute les ancetre de x dans l'arbre g
 * 
 * @param g 
 * @param x 
 * @return ident 
 */
ident affiche_parente(Genealogie *g, ident x);

/**
 * @brief Affichage de toute la descendance a partir de x dans l'arbre g
 * 
 * @param g 
 * @param x 
 * @return ident 
 */
ident affiche_descendance(Genealogie *g, ident x);

/***************FUSION***************/
/**
 * @brief Fusion entre deux arbre dans un 3 eme qui doit etre init ATTENTION celle-cie modifie les valeur des dates de naissances des arbres precédents 
 * 
 * @param gres 
 * @param a1 
 * @param a2 
 */
void genealogieFusion(Genealogie *gres, Genealogie *a1, Genealogie *a2);

/***************ANNEXE***************/

/**
 * @brief Copie un string dans un tableau de string
 * 
 * @param out 
 * @param in 
 */
void copieStr(char*out,char*in);

/**
 * @brief Creer une date vide (c'est a dire tout est a 0)
 * 
 * @return date 
 */
date creationDateVide();

/**
 * @brief Creer une date avec les arguments données
 * 
 * @param jour 
 * @param mois 
 * @param annee 
 * @return date 
 */
date creationDate(unsigned short jour, unsigned short mois, unsigned short annee);

/**
 * @brief La fonction donne true si id_A est plus vieux ou si id_B est plus alors return false
 * @pre id_A exist dans ga et id_B exist dans gb
 * @param ga 
 * @param id_A 
 * @param gb 
 * @param id_B 
 * @return true 
 * @return false 
 */
bool plusVieux(Genealogie* ga, ident id_A,Genealogie* gb, ident id_B);
/**
 * @brief Parcour de l'arbre g donné a partir de x et remonte tout les parents de x jusqu'a hauteur=0(de facon recursif)
 * 
 * @param g 
 * @param x 
 * @param hauteur 
 * @return ident 
 */
ident affiche_ind_hauteur(Genealogie* g,ident x,int hauteur);
/**
 * @brief Renvoie l'id du plus vieux de l'arbre g envoyé
 * @pre Ne pas avoir dans g de base un Individu avec une date de naissance vide car il ne serrait pas prit en compte 
 * @param g 
 * @return ident 
 */
ident plus_vieux_fusion(Genealogie* g);
/**
 * @brief Parcours tout l'arbre g pour savoir si il y a deja une personne qui porte le meme nom et la meme date de naissance(ce qui est considéré comme une personne identique)
 * 
 * @param g
 * @param s
 * @param n
 * @return bool
 */
bool est_deja_dedans(Genealogie* g,char* s,date n);
#endif
