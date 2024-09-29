#include <iostream>
using namespace std;

int main() {

  int note;

  cout<< "donner une note ";
  cin>> note;
  
  while ((note<0) || (note>20)){
    cout << "donner une note correcte ";
    cin>> note;
  }
  if (note<10) {
    cout<< "ajourné";
  }
  else {
      if (note<12) {
        cout<< "passable";
      }
      else {
        if (note<14) {
        cout<< "mention assez bien";
      }
      else {
        if(note<16) {
          cout<< "mention bien";
        }
        else {
          if(note>=16) {
            cout<<"mention très bien";
          }
  
        }
      }
    }
  }
}
