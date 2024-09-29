#include <iostream>
using namespace std;
#define N 50

void elementTableaux(int &nbe, int tableau[]) {
  int i;
  std::cout << "donner le nb d'élément du tableau";
  std::cin >> nbe;

  for ( i = 0; i < nbe; i++) {
    std::cout << "donner un nb";
    std::cin >> tableau [i];
  }
}

void afficherElement(int nbe, int tableau[]) {
    int i;
    for ( i = 0; i <nbe; i++) {
      cout<< tableau[i] << " ;"  ;
    }
}

void triParInsertion(int nbe, int tableau[]) {
  int i;
  int j;
  int x ;

  for (int i = 1; i <nbe; i++) {
    j = i;
     x = tableau[i];
      while ((j>0) && (tableau [j-1]>x)) {
        tableau [j]=  tableau[j-1];
        j= j-1;
     }
     tableau[j]=x;
   }
 }

int main() {
  int nbe;
  int tableau [N];

  elementTableaux(nbe,tableau);
  triParInsertion(nbe,tableau);
  afficherElement(nbe,tableau);
}
