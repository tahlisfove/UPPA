#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define FAUX 0
#define VRAI 1

typedef int boolean;

/* Proposer un type concret pour implémenter le type abstrait des polynomes */
typedef struct un_compte{
  char* titulaireDuCompte;
  float SoldeDuCompte;
  boolean IndicateurCloture;
}compte;

/* Définition du type des comptes : un type pointeur vers un objet de type compte */
typedef struct un_compte * COMPTE ;

/* Créer un compte avec un solde nul et non clôturé */
COMPTE creer();

/* Crédite un compte */
COMPTE crediter(COMPTE c, float s);

/* Débite un compte */
COMPTE debiter(COMPTE c, float s);

/* Clôture un compte si son solde est nul */
COMPTE cloturer(COMPTE c);

/* Permet de savoir le nom du titulaire du compte */
char* titulaire(COMPTE c);

/* Teste si un compte est clôturé */
boolean cloture(COMPTE c);

/* Permet de savoir le solde d'un compte */
float solde(COMPTE c);
