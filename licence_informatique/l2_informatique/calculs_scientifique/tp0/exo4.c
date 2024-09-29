#include <math.h>
#include <stdio.h>

int main()
{
  int mois;
  int c = 200000;
  int d = 20;
  float t, interet;
  float r1 = 0;
  float cdu = 200000;
  float ta = 0.0132;
  double m;

  t = (pow((1.0+ta).(1.0/12))-1.0);
  m = ((c*t)*pow((1.0+t).(12*d))) / (pow(1.0+t)).(12*d)-1.0));
  printf("mensualité : %f\n", m);
  printf("\n");

  for (mois=1;mois<=240;mois++)
  {
    interet = t*(c-r1);
    r1 = r1 + (m - interet);
    cdu = cdu - r1;

    if (mois == 1) {
      printf("premiere ligne du taleau");
      printf("mois max est : %d\n", mois);
      printf("interet est de : %f\n", interet);
      printf("capital remboursé est de : %f\n", r1);
      printf("capital du a la fin est de : %f\n" ,cdu);
      printf("\n");
    }

    if (mois == 2) {
      printf("deuxieme ligne du taleau");
      printf("mois max est : %d\n", mois);
      printf("interet est de : %f\n", interet);
      printf("capital remboursé est de : %f\n", r1);
      printf("capital du a la fin est de : %f\n" ,cdu);
      printf("\n");
    }

    if (cdu<0) {
      cdu = 0;
    }
  }

  printf("mois max est : %d\n", mois);
  printf("interet est de : %f\n", interet);
  printf("capital remboursé est de : %f\n", r1);
  printf("capital du a la fin est de : %f\n" ,cdu);

  return(0);

}
