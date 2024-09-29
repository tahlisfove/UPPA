#include <math.h>
#include <stdio.h>

int main()
{
  int n;
  float m;
  float q=0.987;
  float u0=1;
  float u=u0;
  printf( " Saisir la valeur de n : ");
  scanf("%d", &n);
  for (int i=0;i<n;i++)
    {
      u = u * q;
      m = u0 * pow(q,n)
    }
  printf(" u_%d=%f\n",n,u);
  printf(" u_%d=%f\n",n,m);
}
