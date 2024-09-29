#include <iostream>
using namespace std;

void tables_mult(int n) {
  int j,calc;
  cout<<"table de"<<n<<endl;
  for(j=1;j<=9;j++){
    calc = n*j;
    cout << n <<"*"<< j << "=" << calc <<endl;
  }
}

int main() {
  int n;
  for(n=1;n<=10;n++){
    tables_mult(n);
  }
}
