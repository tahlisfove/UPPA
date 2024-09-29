#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integration.h"

double integrationPtMilieu(double(*f)(double),double a,double b){
  double r;
  r=(b-a)*f((a+b)/2);
  return r;
}

double integrationPtMilieuComposite(double(*f)(double),double a,double b, int N){
  double r=0, h=((b-a)/N), xi;
  for(int i=0; i<=N-1; i++){
    xi = a+i*h;
    r += f(xi+(h/2));
  }
  return h*r;
}

double integrationTrapezeComposite(double(*f)(double),double a, double b, int N){
  double r=0, h=((b-a)/N), xi, xi2;
  for(int i=0; i<=N-1; i++){
    xi = a+i*h;
    xi2 = a+(i+1)*h;
    r += f(xi+(xi2));
  }
  return (h/2)*r;
}

double integrationSimpson(double(*f)(double),double a, double b, int N){
  double r=0, h=((b-a)/N), xi, xi2, xi3;
  for (int i=0; i<N; i++){
    xi = a+i*h;
    xi2 = a+(i+1)*h;
    xi3 = (1/2)*(xi+xi2);
   	r = f(xi+(xi2)+(4*(xi3)));
  }
  return (h/6)*r;
}
