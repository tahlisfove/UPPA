#include <iostream>
using namespace std;

int main()
{
  int a;
  int b;
  int c;

  cout<<"donner un nombre ";
  cin>> a;

  cout<<"donner un 2eme nombre ";
  cin>> b;

  cout<<"donner un 3eme nombre ";
  cin>> c;

  if ((a<b) && (b<c)) {
    cout<< "ordre  croissant";
  }
  else {
    cout<<"ordre non croisant";
  }
}
