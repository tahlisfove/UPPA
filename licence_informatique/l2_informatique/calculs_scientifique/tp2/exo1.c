#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integration.h"

double f(double x){
  return sin(x);
}

int main(){
  double milieu, trapeze, simpson;
  int N=1, a=0, b=M_PI;
  while(N<8192){
    milieu = fabs(2-integrationPtMilieuComposite(&f,a,b,N));
    trapeze = fabs(2-integrationTrapezeComposite(&f,a,b,N));
    simpson = fabs(2-integrationSimpson(&f,a,b,N));
    printf("%d        %g        %g        %g \n", N, milieu, trapeze, simpson);
    N = N*2;
  }
  return 0;
}

/* Du coup j'ai essayé de trouver d’où venait l'erreur de calcul en reprenant les fonctions composites
du cours mais je n'ai pas d'idée peut-être une parenthèse ou quelque chose comme ça mais vu que je n'ai
pas de compilateur je n'ai pas trop voulu toucher au code pour éviter d'ajouter des erreurs en plus,
déjà que je ne peux pas utiliser le programme gnuplot pour avoir le rendu des courbes, merci de votre
compréhension.              CHRISTOPH Samuel */

/* Question 5: On obtient donc un ordre numérique pour chacune des méthodes :
La formule point milieu est d'ordre 1, celle des Trapezes Composites d'ordre 1 et pour finir celle de
Simpson Composite est d'odre 3. Donc la formule de Simpson Composites est la méthode la plus efficace
car elle a une meilleure précision par rapport aux valeurs d'erreur obtenues. */
