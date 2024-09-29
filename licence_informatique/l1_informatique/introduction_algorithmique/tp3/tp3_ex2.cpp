#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


int nombreAlea(int maxi) {
  srand(time(NULL));
  return(rand()%maxi);
}

int main() {
  int myst,tentatives,n,i,nbe,verif;
  int tab[10];

  i=0;
  myst = nombreAlea(10);
  tentatives=1;
  cout << "deviner un chiffre entre  0 et 9"<<endl;
  cin >> n;
  tab[0]=n;
  nbe=1;
  while(n!= myst) {
    tentatives=tentatives+1;
    if (n<myst) {
      cout <<"plus grand"<<endl;
    }
    else {
      cout <<"plut petit"<<endl;
    }
    cin >> n;

    while(i!=nbe) {
      if (tab[i]==n) {
        cout << "deja fait,bouffon"<<endl;
        cin>>n;
        tentatives++;
        i=0;  
      }
      else {
        i++;
      }
    }
    i=0;
    tab[nbe]=n;
    nbe++;
  }
  cout << "bg , seulement"<<tentatives<<"tentatives";
}
