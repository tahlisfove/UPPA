#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "integration.h"

double f1 (double x){
  return pow(x,5);
}

double f2 (double x){
  return pow(x,6);
}

double f3 (double x){
  return pow(x,2);
}

double boole(double (*f)(double), double a, double b, int N){
  double h, xA, xB, xM;
	double r = 0;
	h = (b - a) / N;
	for (int i = 0; i < N; i++) {
		xA = a + i * h;
		xB = a + ( (i+1) * h );
    r += ( (xB-xA) / 90 ) * ( 7 * f(xA) + 32 * f(xA+0.25*h) + 12 * f(xA+0.5*h) + 32 * f(xA+0.75*h) + 7 * f(xB) );
    }
    return r;

int main(){
  double a, b, c1, c2, c3, c4;
  int N = 4;
  int N1 = 10;
  int N2 = 20;
  a = 0;
  b = 1;
  c1 = boole(*f1,a,b,N);
  c2 = boole(*f2,a,b,N);
  c3 = boole(*f3,a,b,N1);
  c4 = boole(*f3,a,b,N2);
  printf("Degré d'exactitude : 5 --> %lg %lg\n",c1,fabs((1.0/6)-c1));
  printf("Degré d'exactitude : 6 --> %lg %lg\n",c2,fabs((1.0/7)-c2));
  printf("Comparaison de l'ordre de convergence pour une même fonction (ici x²) mais avec un N différent : %lg <---> %lg\n",fabs((1.0/3)-c3),fabs((1.0/3)-c4));
  return 0;
}