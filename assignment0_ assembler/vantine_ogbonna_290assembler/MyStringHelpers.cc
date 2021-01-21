#include "MyStringHelpers.h"
#include <iostream>
using namespace std;
// PRE: ch is defined.
// POST: RV is true iff ch is a lowercase letter ('a'..'z')
bool islowercase (char ch) {
  bool answer = false;
  if ((ch >= LOWERA) && (ch <= LOWERZ)){
    answer = true;
  }
  //ASSERT: if LOWERZ <= ch <= LOWERA, answer will become true
  return (answer);
}

// PRE: Array1 and Array2 must be 2 arrays of characters. Array2 must
// be greater than array1. array1size is an integer that represents array1's
//size
// POST: Every element in array1 is deep copied into Array2
void copyArray (const char* Array1, int array1size,  char* Array2){
  int index = 0;
  bool done = false;
  while (!done){
    if (index < array1size){
      //ASSERT: we are not at the end of Array1
      Array2[index] = Array1[index];
      index++;
    }
    else{
      //ASSERT: We're at the end of array 1
      done = true;
    }
  }
  //ASSERT: we have added everything from array1 to newarray2
}
