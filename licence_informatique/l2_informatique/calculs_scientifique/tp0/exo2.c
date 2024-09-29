#include <math.h>
#include <stdio.h>

int main()
{
  int i, n;
  float a, b, a1, b1, c, d, r;
  printf( " Saisir la valeur de c : ");
  scanf("%f", &c);
  printf( " Saisir la valeur de d : ");
  scanf("%f", &d);
  printf( " Saisir la valeur de n : ");
  scanf("%d", &n);
  for (int i=1;i<=n;i++)
    {
      a1 = pow(a,2) - pow(b,2) + c;
      b1 = 2 * a * b + d;
      a = a1;
      b = b1;
    }
  r = sqrt(pow(a,2) + pow(b,2));
  printf("Le résultat est : %f\n", r);
  return(0);
}
