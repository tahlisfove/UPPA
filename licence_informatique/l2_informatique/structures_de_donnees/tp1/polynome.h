#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MaxSize 10
#define FAUX   0
#define VRAI   1

typedef int BOOLEEN;

typedef struct un_polynome 
    {
     int sonDegre;
     float  sonCoefficient[MaxSize];
    }  polynome;

typedef  struct un_polynome *  POLYNOME;  

POLYNOME Nul();
POLYNOME Construire(POLYNOME p1, float a0);
int Degre(POLYNOME p);
float Coefficient(POLYNOME p, int i) ;
BOOLEEN estNul(POLYNOME  p);