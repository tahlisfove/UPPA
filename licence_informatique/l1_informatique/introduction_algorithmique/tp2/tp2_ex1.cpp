#include <iostream>
using namespace std;

int main()
{
  int j,u,v,k;
  k=0;

  for(j=0;j<=5;j++) {
    if (j %2 ==1) {

      u =j;

      while (u>0) {
         cout <<"while"<<endl;
         k=k+1;
         u=u/2;
      }
    }
    else {
      for(v= (-1 );v<=(j-1);v++) {
        cout <<"for"<<endl;
         k=k+2;
      }
    }
    cout <<"ok"<<endl;
  }
  
  cout<<k<<endl;
}