#include <iostream>

using namespace std ;

int main()
{
  char rep;
  cout<<"\nRépondre à toutes les questions par oui (o) ou par non (n)"<<endl;
  cout<<"\nAvez-vous obtenu une offre d'emploi de classe A1 ?"<<endl;
  cout<<"Oui (o) ou non (n) : ";
  cin>>rep;
  if(rep == 'o')
  {
    cout<<"Vous êtes exclus du processus de classement"<<endl;
  }
  else
  {
    cout<<"Avez-vous accepté une 2eme offre d'emploi ?"<<endl;
    cout<<"Oui (o) ou non (n) : ";
    cin>>rep;
    if(rep == 'o')
    {
      cout<<"1ère offre annulée"<<endl;
      cout<<"Vous êtes exclus du processus de classement"<<endl;
    }
    else
    {
      cout<<"Avez-vous refusé 3 offres différentes pour un 2eme emploi ?"<<endl;
      cout<<"Oui (o) ou non (n) : ";
      cin>>rep;
      if(rep == 'o')
      {
        cout<<"Vous êtes exclus du processus de classement"<<endl;
      }
      else
      {
        cout<<"Avez-vous obtenu un emploi de type B1 ?"<<endl;
        cout<<"Oui (o) ou non (n) : ";
        cin>>rep;
        if(rep == 'o')
        {
          cout<<"Vous ne pouvez viser qu'un emploi B1 pour une deuxième offre"<<endl;
        }
        else
        {
          cout<<"Avez-vous obtenu un stage S1 ?"<<endl;
          cout<<"Oui (o) ou non (n) : ";
          cin>>rep;
          if(rep == 'o')
          {
            cout<<"Vous êtes éligible aux offres de classe A1"<<endl;
          }
          else
          {
            cout<<"Avez-vous obtenu un stage S2 ?"<<endl;
            cout<<"Oui (o) ou non (n) : ";
            cin>>rep;
            if(rep == 'o')
            {
              cout<<"Vous êtes éligible qu'aux offres de classe A2"<<endl;
            }
          }
        }
      }
    }
  }
  cout<<"Processus de placement terminé"<<endl;
  return 0;
}