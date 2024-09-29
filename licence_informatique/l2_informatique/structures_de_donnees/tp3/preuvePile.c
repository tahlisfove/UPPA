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
pour les fonctions des constructeurs et accesseurs prédéfinis */
#include "libraryPile.c"

/*
programme principal qui vérifie les différents test de précondition */
int main(){
  PILE p, p1;
  int success;
  ELEMENT e;

  /*
  allocation mémoire et vérification */
  p=malloc(sizeof(struct une_place));
  p1=malloc(sizeof(struct une_place));
  if(p==NULL || p1==NULL){
    fprintf(stderr,"Allocation impossible \n");
    exit(EXIT_FAILURE);
  }

  /*
  vérification de l'implémentation du constructeur pileVide */
  p=pileVide();
  /*
  initialisation de l'indice success */
  success=0;
  /*
  vérification avec l'accesseur estVide
  vérifier la propriété : estVide(p)= True */
  if(!(estVide(p))) success+=1;
  /*
  bilan de la vérification */
  if(success!= 0)
  {
    printf("\n Implémentation incorrecte du constructeur pileVide");
    printf("\n Interruption de la vérification : revoir l'implémentation du type asbtrait");
    exit(EXIT_FAILURE);
  }

  /*
  vérification de l'implémentation du constructeur empiler */
  printf("\n saisir un élément, p1 est le premier argument");
  printf("\n saisir un élément, e est le second argument \n");
  p=empiler(p1,e);

  /*
  réinitialisation de la variable success */
  success=0 ;

  /*
  vérification avec l'accesseur estVide */
  if(estVide(p)) success+=1;

  /*
  bilan de la vérification */
  if(success!= 0){
    printf ("\n Implémentation incorrecte de estVide(empiler)");
    printf ("\n Interruption de la vérification: revoir l'implémentation du type abstrait");
    exit(EXIT_FAILURE);
  };

  /*
  réinitialisation de la variable success */
  success=0 ;

  /*
  vérification avec sommet */
  if(sommet(p)!= e) success+=1;

  /*
  bilan de la vérification */
  if(success!= 0){
    printf ("\n Implémentation incorrecte de sommet(empiler)");
    printf ("\n Interruption de la vérification : revoir l'implémentation du type abstrait");
    exit(EXIT_FAILURE);
  };

  /*
  réinitialisation de la variable success */
  success=0 ;

  /*
  vérification avec depiler */
  if(depiler(p)!= p1) success+=1;

  /*
  bilan de la vérification */
  if(success!= 0){
    printf ("\n Implémentation incorrecte de depiler(empiler)");
    printf ("\n Interruption de la vérification : revoir l'implémentation du type abstrait ");
    exit(EXIT_FAILURE);
  };

  /*
  bilan des vérifications sur le type abstrait des piles */
  printf("\n L'implementation du type abstrait est vérifiée");
  printf("\n Fin normale de la vérification de l'implémentation du type abstrait \n");
  printf("\n");
  return EXIT_SUCCESS;
}
