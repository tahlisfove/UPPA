#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


int nombreAlea(int maxi) {
  srand(time(NULL));
  return(rand()%maxi);
}

int main()
{
  int myst,tentatives,n;
  myst = nombreAlea(10);
  tentatives=1;

  cout << "deviner un chiffre entre  0 et 9"<<endl;
  cin >> n;
   
  while( n!= myst) {
    tentatives=tentatives+1;
    if (n<myst) {
      cout <<"plus grand"<<endl;
    }
    else {
      cout <<"plut petit"<<endl;
    }
    cout << "deviner un chiffre entre  0 et 9"<<endl;
    cin >> n;

  }
  cout << "bg , seulement"<<tentatives<<"tentatives";

}
