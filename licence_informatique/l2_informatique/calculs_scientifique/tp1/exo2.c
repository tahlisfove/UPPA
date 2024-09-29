#include <stdio.h>
#include <math.h>
#include "interpolation.h"

int main(){
double x[]={25,40,50,60};
double y[]={95,75,63,54};

printf("%lf\n", eval_p_lagrange(30, x, y, 3));
printf("%lf\n", eval_p_lagrange(45, x, y, 3));
printf("%lf\n", eval_p_lagrange(70, x, y, 3));
return 0;
}
