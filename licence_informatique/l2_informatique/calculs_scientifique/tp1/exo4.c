#include <stdio.h>
#include <math.h>
#include "interpolation.h"

double M(double x){
  return (pow(x,3)+2*pow(x,2)-5*x-6);
}

int main(){
double val, zk;
int i, j;
FILE *fichier;
fichier = fopen("exo4.dat","r");
fscanf(fichier,"%d",&j);
double y[j],x[j];
double N[100]={0};

  for (i=0; i<j; i++){
      fscanf(fichier, "%le %le \n", &x[i], &y[i]);
      printf("%lf %lf \n", x[i],y[i]);
  }

fclose(fichier);
differences_divisees(N,x,y,j-1);

  for (i=0; i<j; i++){
      val = eval_p_dd(x[i],N,x,j-1);
      printf("\n Année : %.0f, Production : %f",x[i], val);
  }

printf("\n P(2018) = %lf \n", eval_p_dd(2018,N,x,j-1) );
return 0;
}
