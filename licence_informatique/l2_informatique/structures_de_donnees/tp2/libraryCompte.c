#include <stdio.h>
#include <stdlib.h>
#include "libraryCompte.h"

COMPTE creer (){
 COMPTE c ;
 c = malloc(sizeof(struct un_compte));
 if(c == NULL){
   fprintf(stderr,"Allocation impossible \n");
   exit(EXIT_FAILURE);
 }

 else{
   scanf( "Entrer le nom du titulaire %s",c->titulaireDuCompte) ;
   c -> SoldeDuCompte = 0.;
   c -> IndicateurCloture = FAUX;
 }
 return c;
 }

COMPTE crediter (COMPTE c, float s){
  if(!cloture(c)){
    COMPTE c1;
    c1 = creer();
    c1 -> SoldeDuCompte = c-> SoldeDuCompte + s;
    return c1;
  }
  else{
    exit(EXIT_FAILURE);
  }
}

COMPTE debiter (COMPTE c, float s){
  if(!cloture(c)){
    COMPTE c1;
    c1 = creer();
    c1 -> SoldeDuCompte = c->SoldeDuCompte - s;
    return c1;
  }
  else{
    exit(EXIT_FAILURE);
  }
}

COMPTE cloturer (COMPTE c){
  if(!cloture(c) && solde(c) == 0){
    COMPTE c1;
    c1 = creer();
    c1 -> IndicateurCloture = VRAI;
    return c1;
  }
  else{
    exit(EXIT_FAILURE);
  }
}

char* titulaire (COMPTE c){
  return c -> titulaireDuCompte;
}

boolean cloture (COMPTE c){
  return c -> IndicateurCloture;
}

float solde (COMPTE c){
  return c -> SoldeDuCompte;
}
