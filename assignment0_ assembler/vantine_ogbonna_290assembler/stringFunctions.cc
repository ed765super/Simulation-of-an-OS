#include "constants.h"
#include "stringFunctions.h"
#include <iostream>
using namespace std;
// PRE: ch is defined.
// POST: RV is true iff ch is a digit ('0'..'9')
bool isHexDigit (char ch) {
  bool answer;
  answer = ((ch >= CHAR0) && (ch <= CHAR9)) ||
    ((ch >= CHARHEXA) && (ch <= CHARHEXF));
  return (answer);
}

// PRE: token is a string of digits end with an end of string character.
// POST: RV is the decimal value of the string.
int strToInt (const char token[]) {
  int answer  = 0;
  int index = 0; // index of the next character in token
  while (token[index] != EOS) {
    answer = (answer * DECIMAL_BASE) + ((int)token[index] - (int)CHAR0);
    index++;
  }
  return (answer);
}
// PRE: string1 and string2 are defined and have the end of string
// character  at the end.
// POST: RV is true iff string1 has the same characters as string2.
bool isEqualString (const char string1[], const char string2[]) {
  bool areEqual = true; // indicate if the strings seen so far are equal.
  int index = 0;        // index of the next characters to be
			// compared.
  while ((areEqual) && (string1[index] != EOS) && (string2[index] != EOS)) {
    // ASSERT: The strings are equal up through index and
    //         there are more characters in the strings
    if (string1[index] != string2[index]) {
    // ASSERT: Strings are not equal at index.
      areEqual = false;
    }
    index++;
  }
  //ASSERT: either they are not equal or we've reached the end of a string
  if (areEqual){
    //ASSERT: we left the while because we've reached the end of a string
    if((string1[index] == EOS) && (string2[index] != EOS)){
      areEqual = false;
    }
    if((string1[index] != EOS) && (string2[index] == EOS)){
      areEqual = false;
    }
  }
  //ASSERT: if isEqual is false then the two strings must be inequal because
  //they are the same size at this point and that is the only reason we'd come
  //out of the while loop
  //        conversely, if isEqual is true then the 2 strings must be equal
  //        for a similar reason.
  //Therefore post condition satisfied.
  return (areEqual);
}
