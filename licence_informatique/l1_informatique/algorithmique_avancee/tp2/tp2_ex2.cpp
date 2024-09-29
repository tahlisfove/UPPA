#include <iostream>
using namespace std;
#define M 21

void remplissage(int tab[M], int nbe, int long &i) {
  if (i<nbe) {
    tab[i]=i;
    i=i+1;
    remplissage(tab, nbe, i);
  }
}

void InserVec(int tab[M], int long &nbe, int long & i, int val) {
  if (i>=0) {
    if (val < tab[i]) {
      tab[i+1]=tab[i];
      i=i-1;
      InserVec(tab, nbe, i, val);
    }
    else {
      tab[i+1]=val;
      nbe = nbe+1;
    }
  }
}

void affiche(int tab[M], int nbe, int long &i) {
  if(i<nbe){
    cout << " \n ";
    cout << tab[i];
    i=i+1;
    affiche(tab, nbe, i);
  }
}


int main () {
  int val;
  int long nbe;
  int tab[M];
  int long i, j;

  cout << "donner le nb d'élément du tableau";
  cin >> nbe;
  cout << "donner la valeur à insérer";
  cin >> val;

  i = 0;
  remplissage(tab, nbe, i);

  i = nbe;
  InserVec(tab, nbe, i, val);

  i = 0;
  affiche(tab, nbe, i);
}
