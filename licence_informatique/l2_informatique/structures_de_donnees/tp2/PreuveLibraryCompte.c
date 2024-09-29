#include <stdio.h>
#include <stdlib.h>
#include "libraryCompte.c"

int main(int argc, char*argv[]){
  COMPTE c,c1;
  int success;
  float s;

  /* Allocation mémoire et vérification */
  c = malloc(sizeof(struct un_compte));
  c1 = malloc(sizeof(struct un_compte));
  if(c == NULL){
    fprintf(stderr,"Allocation impossible \n");
    exit(EXIT_FAILURE);
  }

  /* Vérifier l'implémentation du constructeur creer() */
  c = creer();
  /* Initialiser l'indice success */
  success = 0;
  /* Vérification avec l'accesseur estCloture */
  /* Vérifier la propriété : estCloture(c)= FALSE */
  if (cloture(c)) success=success+1;
  /* Vérification avec l'accesseur solde */
  /* Vérifier la propriété : solde(c) = 0 */
  if (solde(c) != 0)   success=success+1;

  /* Bilan de la vérification */
  if (success != 0){
    printf ("\n Implémentation incorrecte du constructeur creer()");
    printf("Interruption de la vérification: revoir l'implémentation du type abstrait \n");
    exit(EXIT_FAILURE);
  };

  /* Vérifier l'implémentation du constructeur _crediter(c,s) */
  /* Ne pas oublier de saisir le compte c1 */
  printf("\n saisir un compte, c1 est le premier argument");
  /* Ne pas oublier de saisir le réel(s) */
  printf("\n saisir un reel: s est le second argument");

  /* Apres la saisie de c1 et s, appliquer "crediter" pour créditer un compte c */
  c = crediter(c,s);

  /* Réinitialiser la variable success */
  success=0 ;
  /* Vérification avec l’accesseur solde */
  /* Vérifier la propriété :  solde(c) = solde(c1)+s */
  if (solde(c)!=solde(c)+s) succes = succes+1;

  /* Bilan de la vérification */
  if (success != 0){
    printf ("\n Implémentation incorrecte de  crediter(solde)");
    printf("Interruption de la vérification: revoir l'implémentation du type abstrait \n");
    exit(EXIT_FAILURE);
  };


  /* Vérification avec l’accesseur titulaire */
  /* Réinitialiser la variable success */
  succes=0 ;
  /* Vérifier la propriété :  titulaire(c) = titulaire(c) */
  if (titulaire(c)!=titulaire(c1)) success=success+1;

  /* Bilan de la vérification */
  if (success=0){
    printf ("\n Implémentation incorrecte du constructeur crediter(titulaire)");
    printf("Interruption de la vérification: revoir l'implémentation du type abstrait \n");
    exit(EXIT_FAILURE);
  };
  printf("test" );


  /* Vérifier l'implémentation du constructeur debiter(c,s) */
  /* Ne pas oublier de saisir le compte c1 */
  printf("\n saisir un compte, c1 est le premier argument");
  /* Ne pas oublier de saisir le réel(s) */
  printf("\n saisir un reel: s est le second argument");
  /* Apres la saisie de c1 et s, appliquer "debiter" pour débiter un compte c */
  c = debiter(c1,s);
  /* Réinitialiser la variable success */
  success=0 ;
  /* Vérification avec l’accesseur solde */
  if (solde(c)!=solde(c1)-s) success=success+1;

  /* Bilan de la vérification */
  if (success != 0){
    printf ("\n Implémentation incorrecte de debiter(solde)");
    printf("Interruption de la vérification: revoir l'implémentation du type abstrait \n");
    exit(EXIT_FAILURE);
  };

    /* Réinitialiser la variable success */
   success=0 ;
    /* Vérification avec l’accesseur titulaire */
  if (titulaire(c)!=titulaire(c1)) success=success+1;

    /* Bilan de la vérification */
  if (success != 0){
      printf ("\n Implémentation incorrecte de debiter(titulaire)");
      printf("Interruption de la vérification: revoir l'implémentation du type abstrait \n");
      exit(EXIT_FAILURE);
  };


  /* Vérifier l'implémentation du constructeur cloturer(c) */
  /*ne pas oublier de saisir le compte c1*/
  printf("\n saisir un compte, c1 ");
  /* Apres la saisie de c1, appliquer "cloturer" pour cloturer un compte c */

  c = cloturer(c1);
  /* Réinitialiser la variable success */
  success=0 ;
  /* Vérification avec l’accesseur estCloture */
  if (!(cloture(c))) success=success+1;

  /* Bilan de la vérification */
  if (success != 0){
    printf ("\n Implémentation incorrecte de cloturer(estCloture)");
    printf("Interruption de la vérification: revoir l'implémentation du type abstrait \n");
    exit(EXIT_FAILURE);
  };

  /* Réinitialiser la variable solde */
    success=0 ;
  /* Vérification avec l’accesseur solde */
  if (solde(c)!=0) success=success+1;

  /* Bilan de la vérification */
  if (success != 0){
      printf ("\n Implémentation incorrecte de cloturer(solde)");
      printf("Interruption de la vérification: revoir l'implémentation du type abstrait \n");
      exit(EXIT_FAILURE);
  };
  printf("test" );

  /* Réinitialiser la variable solde */
  success=0 ;
  /* Vérification avec l’accesseur titulaire */
  if (titulaire(c)!=titulaire(c1)) success=success+1;

  /* Bilan de la vérification */
  if (success != 0){
        printf ("\n Implémentation incorrecte de cloturer(titulaire)");
        printf("Interruption de la vérification: revoir l'implémentation du type abstrait \n");
        exit(EXIT_FAILURE);
  };
  printf("L'implementation du type abstrait est vérifiée\n");
  printf("Fin normale de la vérification de l'implémentation du type abstrait\n");
  return EXIT_SUCCESS;
}
