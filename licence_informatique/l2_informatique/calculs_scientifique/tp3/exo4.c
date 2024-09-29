#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrice.c"

int main()
{
  int n;
  double *A, *B;

  printf("\nValeur de n : ");
  scanf("%d", &n);
  A = calloc(n*n, sizeof(*A));
  B = calloc(n*n, sizeof(*B));

  for(int i=0; i<n; i++)
  {
    A[i*n+(i-1)] = -1;
    A[i*n+(i)] = 3;
    A[i*n+(i+1)] = -1;
  }

  printf("\nMatrice A:\n\n");
  afficheMat(A, n);

  printf("\n\nInverse de la matrice A:\n\n");
  inverse(A, B, n);
  afficheMat(B, n);

  printf("\n\nInverse optimisée de la matrice A:\n\n");
  inverse_opt(A, B, n);
  afficheMat(B, n);


  clock_t tstart, tend;
  tstart = clock();
  inverse(A, B, n);
  tend = clock();
  double time_comp = ((double) (tend -tstart)) / CLOCKS_PER_SEC *1000;
  printf("\n\nComputational time inverse: %lf ms\n", time_comp); // en  milisecondes

  tstart = clock();
  inverse_opt(A, B, n);
  tend = clock();
  time_comp = ((double) (tend -tstart)) / CLOCKS_PER_SEC *1000;
  printf("Computational time inverse_opt: %lf ms\n\n", time_comp); // en  milisecondes
}

/*
Question 4: on obtient 2750.000000 ms de temps nécessaire pour inverser la matrice An de taille n=200. */

/*
Question 5: on observe l'obtention d'un résultat plus rapidement avec la seconde méthode,
en effet on passe de 2750.000000 ms pour inverse à 31.250000 ms pour inverse_opt. 
soit un gain de temps de 98,864 % */
