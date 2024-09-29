#include <iostream>
using namespace std;

int calculJours (int mois, int a) {
  int nbJ;
  if (mois==2 && a%4==0 && a%100!=0 || mois==2 && a%400==0) {
    nbJ=29;
  }
  else {
    if (mois==2) {
      nbJ==28;
    }
    else {
      if (mois%2==0 && mois<8 || mois%2!=0 && mois>7) {
        nbJ=30;
      }
      else {
        nbJ=31;
      }
    }
  }
  return (nbJ);
}

void Lendemain (int jours, int mois, int a) {
  int nbJ;
  nbJ=calculsJours (mois,a);

  if (jours==nbJ) {
    jours=1;
    if (mois==12) {
      m=1;
      a=a+1;
    }
    else {
      mois = mois+1;
    }
  }
  else {
    jours=jours+1;
  }
  cout<< "le jour suivant est"<<jours<<"/"<<mois<<"/"a;
}

int main () {
  int jours,mois,a,nbJ;
  cout<<"jours?"<<endl;
  cin >>jours;
  cout<<"mois?"<<endl;
  cin >>mois;
  cout<<"année?"<<endl;
  cin >>a;
  
  Lendemain(jours,mois,a);
}
