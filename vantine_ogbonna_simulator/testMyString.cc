#include "MyString.h"

int main(){
  char* A = "yay";
  char* B = "derp";
  MyString stringA(A);
  MyString stringB(B);

  cout << "A: " << stringA << endl;
  cout << "B: " << stringB << endl;

  stringA = stringB;

  cout << "A=B results in: " << stringA << endl;
  return(0);
}
