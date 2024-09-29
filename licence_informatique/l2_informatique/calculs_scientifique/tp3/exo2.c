#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrice.c"

int main()
{
  /*
  initialisation de N et des matrices */
  int N=3;
  double L[9]={1,0,0,1,1,0,0.5,0.5,1};
  double b[3]={2,4,6};
  
  double U[9]={4,2,0,0,2,2,0,0,2};
  double y[3]={2,2,4};

  double o[3], p[3], q[3];
 
  /*
  calcul de la partie 1 et 2 en descente */
  descente(L, b, o, N);
  printf("On obtient:");
  afficheVec(o, N);
  prodMatVec(L, o, p, N);

  printf("\nb =");
  afficheVec(b, N);

  printf("\nb = L.y est vérifiée:");
  afficheVec(p, N);
  printf("\n\n");

  /*
  calcul de la partie 3 et 4 en remontée */
  remontee(U, y, q, N);
  printf("On obtient:");
  afficheVec(q, N);
  prodMatVec(U, q, p, N);

  printf("\ny =");
  afficheVec(y, N);

  printf("\ny = U.x est vérifiée:");
  afficheVec(p, N);
  printf("\n");

  return 0;
}