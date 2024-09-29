/*
définition du fichier.h */
#ifndef LIBRARYARBREFORET_H
#define LIBRARYARBREFORET_H

/*
en-tête standard d'entrée/sortie en langage c */
#include <stdio.h>
/*
permet de gérer la mémoire dynamiquement (free, malloc...) */
#include <stdlib.h>
/*
propose un ensemble de fonction de traitement de caractères */
#include <ctype.h>

/*
définition de faux à la valeur 0 */
#define FAUX 0
/*
définition de vrai à la valeur 1 */
#define VRAI 1
/*
taille maximale de 100 éléments à la pile */
#define MAX 100

/*
type entier déf des booléens */
typedef int BOOLEEN;
/*
type entier déf d'un élement */
typedef int ELEMENT;

/*
propose un type CONCRET pour implémenter le type ABSTRAIT des arbres */
/*
un arbre est défini par: sa racine et une forêt composée de ses sous-arbres */
typedef struct NOEUD_{
  ELEMENT etiquette;
  int nb_sous_arbres;
  struct NOEUD_* sous_arbres[MAX];
}*NOEUD;  /* type concret des noeuds */

/*
définition du type des noeuds: un type pointeur vers un objet de type arbre */
typedef NOEUD ARBRE;  /* type concret des arbres */

/*
propose un type CONCRET pour implémenter le type ABSTRAIT des forêt */
/* 
une forêt est une liste dont les élément sont des arbres */
struct tree{
  ARBRE un_arbre;
  struct tree *suivant;
};

/*
définition du type des trees: un type pointeur vers un objet de type forêt */
typedef struct tree *FORET;  /* type concret des forêts */


 /* ------------------------------------ ABRRE --------------------------------------- */

/*
constructeur qui créer une arbre vide */
ARBRE arbreVide();
/* 
constructeur construire qui construit un arbre a à partir d’un noeud o et d’une forêt f */
ARBRE construire(NOEUD o, FORET f);
/* 
accesseur qui teste si un arbre a est vide */
BOOLEEN estArbreVide(ARBRE a);
/*
accesseur qui permet de donner la racine d’un arbre a */
NOEUD racine(ARBRE a) ;


 /* ------------------------------------ FORÊT --------------------------------------- */

/*
constructeur qui créer une forêt vide */
FORET foretVide();
/* 
accesseur qui teste si une forêt f est vide */
BOOLEEN estForetVide(FORET f);
/* 
constructeur qui donne la forêt composée des sous_arbre d’un arbre a */
FORET listeSousArbres(ARBRE a);
/* 
constructeur qui ajoute un arbre a au rang i dans une forêt f */
FORET planter(ARBRE a, int i, FORET f);
/* 
entier qui définit le nombre de sous arbres d’une forêt f */
int nombreArbres(FORET f);
/*
accesseur qui cherche un arbre de rang i dans la forêt f */
ARBRE iemeArbre(FORET f, int i);

/*
fin de la définition du fichier.h */
#endif