#include <iostream>
using namespace std;

int main() {

  float U0;
  int n ;
  int i;
  U0=3;

  cout<< "donner un nombre n ";
  cin>>n;

  for (i=0; i<=n; i++) {
    U0=U0*0.5+2;
    cout<<U0 <<endl;
  }
  
  cout<<U0;
}
