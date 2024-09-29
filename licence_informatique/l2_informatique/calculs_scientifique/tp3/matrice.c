#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrice.h"

void afficheVec(double *x, int n)
{
  for(int i=0; i<n; i++)
  {
    printf("%3g\n", x[i]);
  }
}

void afficheMat(double *A, int n)
{
  for(int i=0; i<=n-1; i++)
  {
    for(int j=0; j<=n-1; j++)
    {
      printf("%3g", A[i*n+j]);
    }
    printf("\n");
  }
}

void prodMatVec(double *A, double *x, double *y, int n)
{
  for(int i=0; i<n; i++)
  {
    y[i] = 0;    
    for(int j=0; j<n; j++)
    {
      y[i] += (A[i*n+j])*(x[j]);
    }
  }
}

void prodMatMat(double *A, double *B, double *C, int n)
{
  for(int i=0; i<n; i++)
  {
    for(int j=0; j<n; j++)
    {
      C[i*n+j] = 0;
      for(int k=0; k<n; k++)
      {
        C[i*n+j] += A[i*n+k]*B[k*n+j];
      }
    }
  }
}

void descente(double *L, double *b, double *y, int n)
{
  for(int i=0; i<=n-1; i++)
  {
    y[i] = b[i];
    for(int j=0; j<=i-1; j++)
    {
      y[i] -= L[i*n+j]*y[j];
    }
  }
}

void remontee(double *U, double *y, double *x, int n)
{
  for(int i=n-1; i>=0; i--)
  {
    x[i] = y[i];
    for(int j=i+1; j<=n-1; j++)
    {
      x[i] -= U[i*n+j]*x[j];
    }
    x[i] /= U[i*n+i];
  }
}

void decompositionLU(double *A, double *L, double *U, int n)
{
  for (int i=0; i<n*n; i++)
  {
    U[i] = A[i];
  }
  for(int j=0; j<n; j++)
  {
    L[j*n+j] = 1;
    for (int i=0; i<j; i++)
    {
      L[i*n+j] = 0;
    }
    for(int i=j+1; i<n; i++)
    {
      L[i*n+j] = U[i*n+j]/U[j*n+j];
      for(int k=j+1; k<n; k++)
      {
        U[i*n+k] -= L[i*n+j]*U[j*n+k];
      }
      U[i*n+j] = 0;
    }
  }
}

void resolutionSystLin(double *A, double *b, double *x, int n)
{
  double *L, *U, *y;
  L = calloc(n*n, sizeof(*L));
  U = calloc(n*n, sizeof(*U));
  y = calloc(n*n, sizeof(*y));
  decompositionLU(A, L, U, n);
  descente(L, b, y, n);
  remontee(U, y, x, n);
}

void inverse(double *A, double *B, int n)
{
  double *a = calloc(n*n, sizeof(*a));
  double *b = calloc(n*n, sizeof(*b));
  for(int i=0; i<n; i++)
  {
    for(int j=0; j<n; j++)
    {
      if(j == i)
      {
        a[j] = 1;
      }
      else
      {
        a[j] = 0;
      }
    }
    resolutionSystLin(A, a, b, n);
    for(int i=0; i<n; i++)
    {
      B[i*n+i] = b[i];
    }
  }
}

void inverse_opt(double *A, double *B, int n)
{
  double *L=calloc(n*n, sizeof(*L));
  double *U=calloc(n*n, sizeof(*U));
  double *y=calloc(n*n, sizeof(*y));
  double *a=calloc(n*n, sizeof(*a));
  double *b=calloc(n*n, sizeof(*b));

  decompositionLU(A, L, U, n);

  for(int j=0; j<n; j++)
  {
    for(int i=0; i<n; i++)
    {
      if(i == j)
      {
        a[i] = 1;
      }
      else
      {
        a[i] = 0;
      }
    }

    descente(L, a, y, n);
    remontee(U, y, b, n);

    for(int i=0; i<n; i++)
    {
      B[i*n+j] = b[i];
    }
  }
}