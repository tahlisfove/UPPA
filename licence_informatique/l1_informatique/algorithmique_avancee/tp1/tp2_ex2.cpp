#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

void creation(bool vect[], int n) {
  int i;

  for (i=0; i<=n-1; i++) {
    vect[i]=true;
  }
}

void elimination(bool vect[], int n) {
  int i=0;
  int y = 1;

  while (y<=sqrt(n)) {
    if (vect[y]==false) {
      y=y+1;
    }
    else {
      for (i=y+1; i<=n-1; i++) {
        if ((i%y)==0) {
          vect[i]=false;
        }
      }
      y=y+1;
    }
  }
}

void affichage(bool vect[], int n) {
  int i;
  for (i=0; i<=n-1; i++) {
    if (vect[i]==true) {
      cout << i << "|";
    }
  }
}

main() {
  int n;
  bool*vect;

  do {
    cout << "definir un nb max pour le crible d'eratosthene, en dessous de 51" << endl;
    cin >> n;
  }while((n>75)||(n<0));

  vect = (bool*) malloc(sizeof (bool)*n);
  creation(vect,n);
  vect[1]=false;

  elimination(vect,n);
  affichage(vect,n);
}
