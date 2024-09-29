#include <iostream>
using namespace std;

int main()
{
  int i,j,calc;
  for(i=1;i<=10;i++) {
    cout<<"table de"<<i<<endl;
     for(j=1;j<=9;j++) {
      calc = i*j;
      cout << i <<"*"<< j << "=" << calc <<endl;
    }
  }
}
