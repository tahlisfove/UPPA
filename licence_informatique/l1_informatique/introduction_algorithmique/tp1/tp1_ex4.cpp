#include <iostream>
using namespace std;

int main() {
  int a,p;
  p=0;

  do {
     cout << "donner la valeur a (U(o)) strictement positif"<< endl;
     cin >> a;
  }while(a<=0);

  while(a!=1) {
    if (a%2==0) {
      a = a/2;
    }
    else {
      a = (a*3)+1;
    }
    p++;
    cout << "U("<<p<<") =" << a <<endl;
  }
}
