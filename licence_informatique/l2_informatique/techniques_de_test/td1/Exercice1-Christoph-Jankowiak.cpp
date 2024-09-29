#include <iostream>

using namespace std;

class Triangle
{
  private:
    float a;
    float b;
    float c;

  public:
    Triangle();
    void displayTriangle();
    void typeTriangle();
};

Triangle::Triangle()
{
  cout<<"Donnez une longueur numéro 1 : ";
  cin>>(*this).a;
  cout<<"Donnez une longueur numéro 2 : ";
  cin>>(*this).b;
  cout<<"Donnez une longueur numéro 3 : ";
  cin>>(*this).c;
}

void Triangle::displayTriangle()
{
  cout<<"A: "<<(*this).a<<endl;
  cout<<"B: "<<(*this).b<<endl;
  cout<<"C: "<<(*this).c<<endl;
}

void Triangle::typeTriangle()
{
  if(((a==0)&&(b==0)&&(c==0))||((a<0)||(b<0)||(c<0)))
    cout<<"Cas impossible"<<endl;
  else
  {
    float max;
    char p = 'a';
    bool faux = false;
    max = (*this).a;

    if((*this).b>max)
    {
      max = (*this).b;
      p = 'b';
    }
    if((*this).c>max)
    {
      max = (*this).c;
      p = 'c';
    }
    
    switch(p)
    {
      case 'a':
      {
        if(max>(*this).b + (*this).c)
        {
          cout<<"Non triangle"<<endl;
          faux=true;
        }
        break;
      }
      case 'b':
      {
        if(max>(*this).a + (*this).c)
        {
          cout<<"Non triangle"<<endl;
          faux = true;
        }
        break;
      }
      case 'c':
      {
        if(max>(*this).a + (*this).b)
        {
          cout<<"Non triangle"<<endl;
          faux = true;
        }
        break;
      }
      default:
      {
        break;
      }
    }
    if(!(faux))
    {
      if((*this).a==(*this).b)
      {
        if((*this).b==(*this).c)
        {
          cout<<"Triangle équilatéral"<<endl;
        }
        else
        {
          cout<<"Triangle isocèle"<<endl;
        }
      }
      else if((*this).b==(*this).c)
        cout<<"Triangle isocèle"<<endl;
      else if((*this).a==(*this).c)
        cout<<"Triangle isocèle"<<endl;
      else
        cout<<"Triangle scalène"<<endl;
    }
  }
}

int main()
{
  Triangle Q;
  Q.displayTriangle();
  Q.typeTriangle();
}