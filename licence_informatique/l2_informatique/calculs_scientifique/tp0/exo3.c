#include <math.h>
#include <stdio.h>

int fact(float n)
{
  int fact = 1;
  int i;
  for(i=1;i<=n;i++)
    fact = 2*n+1;
  return fact;
}

double sin_approx (double x, int n)
{
  double r, i;
  for(i=0;i<=n;i++)
  {
    r = pow(-1,n) * pow(x,(2*n+1))/fact(n);
  }
  return r;
}

int main()
{
  float r,n;
  double x;
  printf( " Saisir la valeur de n : ");
  scanf("%f", &n);
  printf( " Saisir la valeur de x : ");
  scanf("%lf", &x);
  x = M_PI/6;
  sin_approx(x,n);
  r = sin_approx(x,n);
  printf("Le résultat est : %lf\n",r);
  return (0);
}
