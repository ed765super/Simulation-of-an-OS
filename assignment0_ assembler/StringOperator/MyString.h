#ifndef INCLUDED_MYSTRING
#define INCLUDED_MYSTRING
#include <iostream>
#include "MyStringHelpers.h"
using namespace std;

class MyString{
  //CI: MyString is an array of characters. This object  that contains
  //3 private member functions: StringPtr, numElements, and
  //arraysize. This object can be empty (this object is considered
  //empty if MyString only contains the end of string character. This
  //object can contain any character except for the new line
  //character. StringPtr is a reference to an array. numElements is an
  //integer representing:
  //the number of elements in the array StringPtr is pointing
  //to. arraysize is an integer that represents:
  //the amount of allocated space of the array StringPtr is pointing to.
 private:
  char *StringPtr;
  //ASSERT: StringPtr is a pointer to an array of characters
  int numElements;
  //ASSERT: numElements is the size of the string StringPtr is pointing to
  //up to but not including the end of string character, and it is the index
  //at which the end of string character is at.
  int arraySize;
  //ASSERT: arraySize is the size of the actual array including
  //garbage values and the end of string character. It also represents
  //the indecie at which the end of string character needs to be at in
  //arder for array doubling to take place

 public:
  //PRE:
  //POST: This object is ['\0'] (CI is satisfied)
  MyString();

  //PRE: aChar must be a character of fixed length size
  //POST: this object becomes the mystring object
  MyString(char const * aString);
  
  //COPY CONSTRUCTOR
  //PRE:
  //POST: This object is [a], where a is the contents of string[]
  MyString(const MyString & aString);

  //PRE:
  //POST: deletes the pointer to a MyString object
  ~MyString();
  
  //ACCESSOR
  
  //PRE: this object satisfies the CI
  //POST: RV= the length number of characters in the object.
  int length()const;

  //PRE: this object satisfies the CI
  //POST: RV =  stringPtr
  char* getstring()const;
  
  //MODIFIERS
  //PRE: ch must be a single character
  //POST: adds a character to the object
  void addchar(char ch);

  //PRE: this object satisfies the CI
  //POST: changes all characters in the object to it's uppercase equivalent
  void toUpperCase();

  //PRE: this object satisfies the CI
  //POST: Removes the first pNum values in the object
  void removeFirst(int pNum);
  
  //OPERATORS
  // PRE: string1 and string2 are defined and have the end of string
  // character  at the end.
  // POST: RV is true iff numElements is less than string1.numElements
  bool operator < (const MyString & string1);
  
  // PRE: string1 and string2 are defined and have the end of string
  // character  at the end.
  // POST: RV is true iff string1 has the same characters as MyString.
  bool operator == (const MyString & string1);

  //PRE:string1 and string2 are defined and have the end of string
  // character  at the end.
  //POST: RV is a string that contains an array (string3) where string3 =
  // string1string2.
  MyString operator + (const MyString & string1);

  //PRE: char to add is a character
  //POST: Modifies this object s.t. this objcect becomes this object with
  //      char to add tacked onto the end.
  MyString operator +(const char chartoadd);
  
  // PRE: string1 is defined and has the end of string
  //        character  at the end. MyString has adequate space allocated
  //        to it accomodate string1.
  // POST: for all 0 <= i <= length of MyString, MyString[i] = string1[i].
  MyString operator = (const MyString & string1);
  
  //IO OPERATORS
  //PRE: aString is defined as an array of characters with the end of line
  // character after s
  //POST: stream contains the contents of the IS and transfers it into aString
  friend istream & operator >> (istream & stream, MyString & aString);

  //PRE: aString is defined as an array of characters with the end of line
  // character after s
  //POST: stream contains the contents of the IS and transfers it into aString
  friend ostream & operator << (ostream & stream, const MyString & aString);
};
#endif
