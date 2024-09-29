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
pour les fonctions constructeurs et accesseurs à vérifier */
#include "libraryArbreForet.c"

/*
fonction principale */
int main()
{
  ARBRE a, a1;
  NOEUD e1;
  FORET F, F1;
  int i, k, success;

  /* 
  allocation mémoire et vérification */
  a=malloc(sizeof(struct NOEUD_));
  a1=malloc(sizeof(struct NOEUD_));
  if(a == NULL || a1 == NULL)
  {
    fprintf(stderr,"Allocation impossible \n");
    exit(EXIT_FAILURE);
  };

  /* 
  allocation mémoire et vérification */
  F=malloc(sizeof(struct tree));
  F1=malloc(sizeof(struct tree));
  if(F == NULL || F1 == NULL)
  {
    fprintf(stderr,"Allocation impossible \n");
    exit(EXIT_FAILURE);
  };


  /* 
  vérification de l'implémentation du constructeur arbreVide */
  a=arbreVide();
  /* 
  initialiser l'indice success */
  success=0;
  /* 
  vérification avec l'accesseur estArbreVide
  vérifier la propriété : estArbreVide(a)=True */
  if(!(estArbreVide(a))) success=success+1;
  /* 
  bilan de la vérification */
  if(success != 0)
  {
    printf("\n Implémentation incorrecte du constructeur arbreVide");
    printf("\n Interruption de la vérification : revoir l'implémentation du type asbtrait\n");
    exit(EXIT_FAILURE);
  };


  /* 
  vérification de l'implémentation du constructeur construire */
  /* 
  ne pas oublier de saisir e1 */
  printf("\n saisir un élément, e1 est le premier argument");
  /*
  ne pas oublier de saisir la foret F1 */
  printf("\n saisir un élément, F1 est le second argument\n");
  a=construire(e1,F1);


  /*
  réinitialiser la variable success */
  success=0;
  /*
  vérification avec l'accesseur arbreVide */
  if(estArbreVide(a)) success=success+1;
  /* 
  bilan de la vérification */
  if(success != 0)
  {
    printf("\n Implémentation incorrecte de estArbreVide(construire)");
    printf("\n Interruption de la vérification: revoir l'implémentation du type abstrait\n");
    exit(EXIT_FAILURE);
  };


  /* 
  réinitialiser la variable success*/
  success=0;
  /*
  vérification avec listeSousArbres */
  if (listeSousArbres(a) == F1) success=success+1;
  /*
  bilan de la vérification */
  if (success != 0)
  {
    printf("\n Implémentation incorrecte de listeSousArbres(construire)");
    printf("\n Interruption de la vérification: revoir l'implémentation du type abstrait\n");
    exit(EXIT_FAILURE);
  };


  /* 
  réinitialiser la variable success */
  success=0 ;
  /*
  vérification avec racine */
  if(racine(a) == e1) success=success+1;
  /* 
  bilan de la vérification */
  if (success != 0)
  {
    printf ("\n Implémentation incorrecte de racine(construire)");
    printf ("\n Interruption de la vérification: revoir l'implémentation du type abstrait\n");
    exit(EXIT_FAILURE);
  };


  /*
  vérification de l'implémentation du constructeur foretVide */
  F=foretVide();
  /*
  initialiser l'indice success */
  success=0;
  /*
  vérification avec l'accesseur estForetVide
  vérifier la propriété : estForetVide(F)=True*/
  if(!(estForetVide(F))) success=success+1;
  /* 
  bilan de la vérification */
  if(success != 0)
  {
    printf("\n Implémentation incorrecte du constructeur estForetVide(foretVide)");
    printf("\n Interruption de la vérification : revoir l'implémentation du type asbtrait\n");
    exit(EXIT_FAILURE);
  }


  /* 
  réinitialiser la variable success */
  success=0 ;
  /* 
  vérification avec nombreArbres */
  if(nombreArbres(F) != 0) success=success+1;
  /* 
  bilan de la vérification */
  if(success != 0)
  {
    printf ("\n Implémentation incorrecte de nombreArbres(foretVide)");
    printf ("\n Interruption de la vérification: revoir l'implémentation du type abstrait\n");
    exit(EXIT_FAILURE);
  };


  /*
  vérification de l'implémentation du constructeur planter */
  /*
  ne pas oublier de saisir l'arbre a1 */
  printf("\n saisir un élément, a1 est le premier argument");
  /*
  ne pas oublier de saisir i */
  printf("\n saisir un élément, i est le second argument");
  /*
  ne pas oublier de saisir la foret F1 */
  printf("\n saisir un élément, F1 est le troisième argument\n");
  F=planter(a1,i,F1);


  /*
  réinitialiser la variable success */
  success=0 ;
  /*
  vérification avec l'accesseur estForetVide */
  if(estForetVide(F)) success=success+1;
  /*
  bilan de la vérification */
  if(success != 0)
  {
    printf ("\n Implémentation incorrecte de estForetVide(planter)");
    printf ("\n Interruption de la vérification: revoir l'implémentation du type abstrait\n");
    exit(EXIT_FAILURE);
  };


  /*
  réinitialiser la variable success */
  success=0 ;
  /*
  vérification avec l'accesseur nombreArbres */
  if(nombreArbres(F) == nombreArbres(F1)+1) success=success+1;
  /* 
  bilan de la vérification */
  if(success != 0)
  {
    printf ("\n Implémentation incorrecte de nombreArbres(planter)");
    printf ("\n Interruption de la vérification: revoir l'implémentation du type abstrait\n");
    exit(EXIT_FAILURE);
  };


  /*
  réinitialiser la variable success */
  success=0 ;
  /*
  vérification avec l'accesseur iemeArbre */
  if(i==k)
  {
    if(iemeArbre(F,k) != a1) success=success+1;
  }
  if((0 < k) && (k < i))
  {
    if(iemeArbre(F,k) != iemeArbre(F1,k)) success=success+1;
  }
  if((i < k) && (k < nombreArbres(F1)+2))
  {
    if(iemeArbre(F,k) != iemeArbre(F1,k-1)) success=success+1;
  }
  /*
  bilan de la vérification */
  if(success != 0)
  {
    printf ("\n Implémentation incorrecte de iemeArbre(planter)");
    printf ("\n Interruption de la vérification: revoir l'implémentation du type abstrait\n");
    exit(EXIT_FAILURE);
  };


  /*
  bilan de l'implémentation du type abstrait */
  printf("\n L'implementation du type abstrait est vérifiée");
  printf("\n Fin normale de la vérification de l'implémentation du type abstrait\n\n");
  return EXIT_SUCCESS;
}