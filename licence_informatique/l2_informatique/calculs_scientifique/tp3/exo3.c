#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrice.c"

void partie1()
{
  double A[9] = {4,2,0,4,4,2,2,2,3};
  double L[9], U[9], B[9];

  printf("\nmatrice A:\n\n");
  afficheMat(A, 3);

  printf("\nrésultat de la décomposition LU:\n\n");
  decompositionLU(A, L, U, 3);
  afficheMat(U, 3);

  printf("\nmatrice A':\n\n");
  prodMatMat(L, U, B, 3);
  afficheMat(B, 3);
}

void partie2()
{
  double A[9] = {4,2,0,4,4,2,2,2,3};
  double b[3] = {2,4,6};
  double y[3], x[3];

  printf("\nvecteur b:\n\n");
  afficheVec(b, 3);

  printf("\nrésultat du système linéaire Ax=b:\n\n");
  resolutionSystLin(A, b, x, 3);
  afficheVec(x, 3);

  printf("\nvecteur y:\n\n");
  prodMatVec(A, x, y, 3);
  afficheVec(y, 3);
}

int main()
{
  printf("\nquestion n°1 et n°2:\n");
  partie1();
  printf("\nLa fonction est bien vérifiée, le produit de L par U donne bien A.\n");

  printf("\n\nquestion n°3 et n°4:\n");
  partie2();
  printf("\nLa fonction est vérifiée grâce au système linéaire Ax=b.\n\n");

  return 0;
}