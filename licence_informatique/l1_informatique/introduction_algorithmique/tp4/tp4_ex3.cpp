#include <iostream>
using namespace std;

void elementTableaux(int &nbe, int tableau[]) {
  int i;
  std::cout << "donner le nb d'élément du tableau" << '\n';
  std::cin >> nbe;

  for ( i = 0; i <= nbe-1; i++) {
    std::cout << "donner un nb" << '\n';
    std::cin >> tableau [i];
  }
}

void afficherElement(int &nbe,int tableau[]) {
  int i;
  std::cout <<i;
    for ( i = 0; i <=nbe-1; i++) {
      std::cout <<(i+1)<< " : "<< tableau[i]<<endl;
    }

}

void inverserOrdre(int tableau[],int nbe) {
  int sauvegarde,i,moitie;
  nbe--;
  if ((nbe)%2==0) {
    moitie=nbe/2;
  }
  else {
    moitie=(moitie+1)/2
  }

  for ( i = 0; i <=moitie; i++) {
    sauvegarde=tableau[i];
    tableau[i]=tableau[nbe-1];
    tableau[nbe-1]=sauvegarde;
  }
}

void suppEltTableaux(int tableau[], int &nbe) {
  int x,i;
  cout << "donner x";
  cin>> x;
  for ( i = 0; i <nbe; i++) {
    if (tableau[i]>x) {
      tableau [i]=tableau [nbe-1];
      nbe=nbe-1
    }
  }
}

int main() {
  int i;
  int tableau [50];
  int nbe;
  int menu;

  do {
    cout<<endl<<" ----------------------- MENU -----------------------"<<endl<<endl;
    cout<<"1. remplir tableaux"<<endl;
    cout<<"2. afficher elt"<<endl;
    cout<<"3. inverser ordre "<<endl;
    cout<<"4. supp elt tableaux"<<endl;
    cout << " 0 pour sortir"<<endl;
    cout << " donner votre choix"<<endl;
    cin>>menu;

    switch(menu) {

        case 1 : elementTableaux(nbe,tableau);
      break;

        case 2 : afficherElement(nbe,tableau);
      break;

        case 3 : inverserOrdre(tableau,nbe);
      break;

        case 4 : suppEltTableaux(nbe);
      break;
    }
  } while (menu!=0);
}
