#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrice.c"

int main()
{
  int N=4;
  double A[16]={1,2,1,2,-2,-3,0,-5,4,8,6,7,1,-1,0,5};
  double x[4]={1,2,3,4};

  double B[16]={-24,-5,4,-1,6,1,-1,0,1,0.6,0,0.2,6,1.2,-1,0.4};
  double y[4];
  
  double C[16];

  afficheVec(x,N);
  afficheMat(A,N);
  prodMatVec(A, x, y, N);
  afficheVec(y,N);
  prodMatMat(A,B,C,N);
  afficheMat(C,N);
  return 0;
}