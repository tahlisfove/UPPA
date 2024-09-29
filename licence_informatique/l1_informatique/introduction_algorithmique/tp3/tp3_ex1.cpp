#include <iostream>
using namespace std;

int main() {
int tableau [50];
int nbe;
int som;
int i;
float moy;
int min;
int max;
int x;
int cpt;

std::cout << "donner le nb d'élément du tableau" << '\n';
std::cin >> nbe;

for ( i = 0; i <= nbe-1; i++) {
  std::cout << "donner un nb" << '\n';
  std::cin >> tableau [i];
}

i = 0;
som = 0;
for (i=0; i<=nbe-1; i++) {
  som = som + tableau [i];
}

moy = som/nbe;
std::cout << "la moyenne est " <<moy<< '\n';

min = tableau[0];
max= tableau [0];

for (i=0; i<=nbe-1; i++) {
  if (tableau[i]<=min) {
    min = tableau[i];
    }

  else{
    tableau[i]>=max;
    max = tableau[i];
    }
}
  std::cout << min <<'\n';
  std::cout << max <<'\n';

  std::cout << "donner le nb d'éléments < 10" << '\n';
  std::cin >> x;
  cpt = 0;

  while ((cpt <= x) && (i<=nbe-1)) {
       i=i+1;
     if (tableau [i]<10) {
     cpt=cpt+1;
     }
   }

   std::cout << "le nb d'éléments est au moins " <<cpt<< '\n';
}
