#include <stdio.h>
#include <math.h>


double M(double x){
  return (pow(x,3)+2*pow(x,2)-5*x-6);
}

int main(){

double zk;

for (int k=0;k<=1000;k++){
 zk=((-5)+(10.0*k/1000.0));
 printf("%lf ", zk);
 printf("%lf\n",M(zk));

}

return 0;
}
