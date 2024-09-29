#include <stdio.h>
#include <math.h>
#include "interpolation.h"


double base_lagrange (double x ,int i ,double * X ,int n){
  float a = 1;
  for(int j=0; j<n+1; j++){
    if(j!=i){
      a = a * (x-X[j])/(X[i]-X[j]);
    }
  }
  return a;
}

double eval_p_lagrange (double x, double * X, double * Y, int n){
  float p = 0;
  for(int i=0; i<n+1; i++){
    p = p + Y[i] * base_lagrange(x,i,X,n);
  }
  return p;
}

void differences_divisees (double * N, double * X, double * Y, int n){
    for (int i=0; i<=n; i++){
        N[i]=Y[i];
    }
    for (int i=1; i<=n; i++){
        for (int j=n; j>=i; j--){
            N[j]=((N[j]-N[j-1])/(X[j]-X[j-i]));
        }
    }

}

double eval_p_dd(int x, double * N, double * X, int n){
  double p,q;
  p = N[0];
  q = 1;
  for (int i = 1  ; i <=n; i++) {
    q = q * (x-X[i-1]);
    p = p + N[i] * q;
  }
  return p;
}
