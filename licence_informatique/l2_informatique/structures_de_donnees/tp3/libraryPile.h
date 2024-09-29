/*
définition du fichier .h */
#ifndef LIBRARYPILE_H
#define LIBRARYPILE_H

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
#define maxsize 100

/*
type entier déf des booléens */
typedef int BOOLEEN;
/*
type entier déf d'un élement */
typedef int ELEMENT;

/*
propose un type CONCRET pour implémenter le type ABSTRAIT des piles */
typedef struct une_place{
  ELEMENT element;
  struct une_place *suivante;
}une_place;

/*
définition du type des places: un type pointeur vers un objet de type pile */
typedef struct une_place*  PILE;

/*
constructeur qui créer une pile vide */
PILE pileVide();
/*
constructeur qui permet d'empiler un élement */
PILE empiler(PILE p,ELEMENT e);
/*
constructeur qui permet de dépiler le dernier élément inséré */
PILE depiler(PILE p);
/*
accesseur qui permet de savoir si une pile est vide */
BOOLEEN estVide(PILE p);
/*
accesseur définissant le sommet de la pile */
ELEMENT sommet(PILE p);

/*
fin de la définition du fichier .h */
#endif
