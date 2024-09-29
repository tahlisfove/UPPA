#include <iostream>
using namespace std;
#define N 50

void elementTableaux(int &nbe, int tableau[]) {
  int i;
  std::cout << "donner le nb d'élément du tableau";
  std::cin >> nbe;

  for( i=0; i<nbe; i++) {
    std::cout << "donner un nb";
    std::cin >> tableau [i];
  }
}

void afficherElement(int nbe, int tableau[]) {
  int i;
  for(i=0; i<nbe; i++) {
    cout << tableau[i] << " ;";
  }
}

int main() {
  int nbe;
  int tableau [N];

  elementTableaux(nbe,tableau);
  afficherElement(nbe,tableau);
}
