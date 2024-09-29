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
pour les en-têtes des constructeurs et accesseurs prédéfinis */
#include "libraryPile.h"

/*
définition de faux à la valeur 0 */
#define FAUX 0
/*
définition de vrai à la valeur 1 */
#define VRAI 1

/*
création d'une pile vide */
PILE pileVide(){
  return NULL;
}

/*
empiler d'un élément dans une pile non-vide */
PILE empiler(PILE laPile,ELEMENT e){
  PILE sommet;
  sommet=malloc(sizeof(struct une_place));
  if(sommet == NULL){
    fprintf(stderr,"Allocation impossible \n");
    exit(EXIT_FAILURE);
  }
  else{
    sommet->element=e;
    sommet->suivante=laPile;
    laPile=sommet;
  }
}

/*
depiler un élément d'un pile non-vide */
PILE depiler(PILE laPile){
  PILE autrePile;
  autrePile=laPile;
  laPile=autrePile->suivante;
  free(autrePile);
  autrePile=NULL;
  return laPile;
}

/*
tester si la pile est vide */
BOOLEEN estVide(PILE laPile){
  return(laPile==NULL);
}

/*
indique quel élément se trouve au sommet de la pile */
ELEMENT sommet(PILE laPile){
  return laPile->element ;
}
