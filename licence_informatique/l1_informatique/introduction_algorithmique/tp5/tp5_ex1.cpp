#include <iostream>
using namespace std;
#define tailleJeu 3

void initialiserGrille(int grille[][tailleJeu]) {
  int i,y;
  for (i=0;i<=tailleJeu-1;i++) {
    for (y=0;y<=tailleJeu-1;y++) {
      grille[i][y] = 0;
   }
 }
}

void afficherGrille(int grille[][tailleJeu]) {
  int i,y;
  for (i=0;i<=tailleJeu-1;i++) {
    for (y=0;y<=tailleJeu-1;y++) {
      cout<< grille[y][i];
    }
    cout<<endl;
  }
}

void verifvainqueur(int grille[][tailleJeu], int &joueur,int &ver) {
  int i,y,verl;
  cout<<"coucou"<<joueur;

  verl=0;

  for (i=0;i<=tailleJeu-1;i++) {
    if (verl==joueur*tailleJeu) {
      cout << "Le joueur "<<joueur<<" Gagne !";
      ver=1;
    }

    verl = 0;
    
    for (y=0;y<=tailleJeu-1;y++) {
      if (grille[i][y]==joueur) {
        verl = verl + grille[i][y];
      }
    }
  }

  for (i=0;i<=tailleJeu-1;i++) {
    if (verl==joueur*tailleJeu) {
      cout << "Le joueur "<<joueur<<" Gagne !";
      ver=1;
    }

    verl = 0;

    for (y=0;y<=tailleJeu-1;y++) {
      if (grille[y][i]==joueur) {
        verl = verl + grille[y][i];
      }
    }
  }

  verl=0;
  y=0;

  for (i=0;i<=tailleJeu-1;i++) {
    if (grille[i][y]==joueur) {
      verl = verl + grille[i][y];
    }
    y++;
  }

  if (verl==joueur*tailleJeu) {
    cout << "Le joueur "<<joueur<<" Gagne !";
    ver=1;
  }

  verl=0;
  y=0;

  for (i=tailleJeu-1;i>=0;i--) {
    if (grille[i][y]==joueur) {
      verl = verl + grille[i][y];
    }
    y++;
  }

  if (verl==joueur*tailleJeu) {
    cout << "Le joueur "<<joueur<<" Gagne !";
    ver=1;
  }

  if (joueur==1) {
    joueur=2;
  }
  else {
    if(joueur==2) {
      joueur=1;
    }
  }

  if (verl==joueur*tailleJeu) {
    cout << "Le joueur "<<joueur<<" Gagne !";
    ver=1;
  }
}

void choix(int grille[][tailleJeu],int &joueur) {
  int c;
  do {
    cout << "choisir la case a remplir , joueur "<<joueur<<" !(une case vide ou tu perdras ton tour)"<<endl<<"789"<<endl<<"456"<<endl<<"123"<<endl;
    cin >> c;
  }while((c<1) || (c>9));

  switch(c){
      case 7 : if(grille[0][0] == 0){grille[0][0] = joueur;}
    break;
      case 8 : if(grille[1][0] == 0){grille[1][0] = joueur;}
    break;
      case 9 : if(grille[2][0] == 0){grille[2][0] = joueur;}
    break;
      case 4 : if(grille[0][1] == 0){grille[0][1] = joueur;}
    break;
      case 5 : if(grille[1][1]== 0){grille[1][1] = joueur;}
    break;
      case 6 : if(grille[2][1] == 0){grille[2][1] = joueur;}
    break;
      case 1 : if(grille[0][2] == 0){grille[0][2] = joueur;}
    break;
      case 2 : if(grille[1][2] == 0){grille[1][2] = joueur;}
    break;
      case 3 : if(grille[2][2]){grille[2][2] = joueur;}
    break;
  }
}

int main() {
  int grille[tailleJeu][tailleJeu],joueur,ver;
  ver=0;
  joueur=1;
  initialiserGrille(grille);
  afficherGrille(grille);

  do {
    choix(grille,joueur);
    afficherGrille(grille) ;
    verifvainqueur(grille,joueur,ver);
  }while(ver!=1);
}
