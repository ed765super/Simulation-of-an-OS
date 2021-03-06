#include "MyString.h"
using namespace std;

//PRE:
//POST: This object is ['\0'] (CI is satisfied)
MyString::MyString(){
  StringPtr = new char[1];
  StringPtr[0] = EOS;
  numElements = 0;
  arraySize = 1;
}

//PRE: aChar must be a character
//POST: this object becomes the MyString object of the fixed character
MyString::MyString(char const * aString){
  StringPtr = new char[1];
  numElements = 0;
  arraySize = 1;
  int index = 0;
  while (aString[index] != aSpace){
    addchar(aString[index]);
    index++;
  }
  //ASSERT: This object's StringPtr is now pointting to an array
  //        equal to aString
  addchar(EOS);
  numElements = index;
}

//PRE:
//POST: deletes the pointer to a MyString object
MyString::~MyString(){
  delete [] StringPtr;
}
 
// COPY CONSTRUCTOR
// PRE:
// POST: This object is [a], where a is the contents of string[]
MyString::MyString(const MyString & aString){
  char* copyStringPtr = new char[aString.arraySize];
  numElements = aString.numElements;
  arraySize = aString.arraySize;
  //ASSERT: StringPtr is a pointer to a string of size: numElements
  for (int index = 0; index < aString.numElements; index++){
    char ch = aString.StringPtr[index];
    copyStringPtr[index] = ch;
  }
  copyStringPtr[aString.numElements] = '\0';
  //ASSERT: copyStringPtr is a deep copy of aString
  //delete [] StringPtr;
  StringPtr = copyStringPtr; 
}

//ACCESSOR
//PRE: this object satisfies the CI
//POST: RV = the length number of characters in the object.
int MyString::length()const{
  return(numElements);
}

//PRE: this object satisfies the CI
//POST: RV = StringPtr.
char* MyString::getstring()const{
  return (StringPtr);
}
//MODIFIERS

//PRE: ch must be a single character
//POST: adds a character to the object
void MyString::addchar(char ch){
  if (numElements == arraySize){
    //ASSERT: There's no more space in MyString
    char * aStringPtr = new char [2 * arraySize];
    arraySize *= 2;
    //ASSERT: aStringPtr is now StringPtr with double the space
    copyArray(StringPtr, numElements, aStringPtr);
    //ASSERT: all values in StringPtr have been copied into aStringPtr
    StringPtr = aStringPtr;
    //delete [] aStringPtr;
  }
  //ASSERT: There is enough space to add a character
  StringPtr[numElements] = ch;
  numElements++;
}

//OPERATORS

//PRE:string1 and string2 are defined and have the end of string
// character  at the end.
//POST: RV is a MyString that contains an array (s3) where s3 =
// string1string2.
MyString MyString::operator +(const MyString & string1){
  MyString string3;//will contain an array where string3 = string1string2.
  int index = 0;
  while (StringPtr[index] != EOS){
    string3.addchar(StringPtr[index]);
    index++;
  }
  //ASSERT: string3 is now equal to StringPtr w/out EOS
  index = 0;
  while (string1.StringPtr[index] != EOS){
    string3.addchar(string1.StringPtr[index]);
    index++;
  }
  //ASSERT: everything from this object and string1 has been added to
  // string3 except for EOS
  string3.addchar(EOS);
  return (string3);
}

//PRE: char to add is a character
//POST: RV = an object equivallent to this object with
//      chartoadd tacked onto the end.
MyString MyString::operator +(const char chartoadd){
  MyString stringwithchar;
  int index = 0;
  while (StringPtr[index] != EOS){
    stringwithchar.addchar(StringPtr[index]);
    index++;
  }
  //ASSERT: string3 is now equal to StringPtr w/out EOS
  stringwithchar.addchar(chartoadd);
  //ASSERT: everything from this object and chartoadd has been added to
  //stringwithchar
  stringwithchar.addchar(EOS);
  return (stringwithchar);
}
// PRE: string1 and string2 are defined and have the end of string
// character  at the end.
// POST: RV is true iff numElements is less than string1.numElements
bool MyString::operator <  (const MyString & string1){
  bool isLess = false; //will hold a boolean value that represents whether or not
                      //the number of elements in string1 is less than the
                      //number of elements in string2
  if (numElements < string1.numElements){
    isLess = true;
  }
  return (isLess);
}
  
// PRE: string1 and string2 are defined and have the end of string
// character  at the end.
// POST: RV is true iff string1 is identical in terms of length and
// characters to this object.
bool MyString::operator == (const MyString & string1){
  bool areEqual = true; // indicate if the strings seen so far are equal.
  if((numElements<string1.length()) || (string1.length()<numElements)){
    //ASSERT: These two objects are not the same size therefore they
    //cannot be equal
    areEqual = false;
  }
  //ASSERT: string1 and this object are the same size.
  int index = 0;
  bool done = false;
  while(!done){
    if(index == numElements){
      //ASSERT: we have reached the end of this object and
      //alternatively string1
      done = true;
    }
    else{
      //ASSERT: we have not reached the end of the 2 stringPtrs
      if(StringPtr[index] != string1.StringPtr[index]){
	areEqual = false;
      }
    }
    index++;
  }
  //Post condition is satisfied
  return (areEqual);
}
  
// PRE: string1 is defined and has the end of string
//        character  at the end. MyString has adequate space allocated
//        to it accomodate string1.
// POST: for all 0 <= i <= length of MyString, MyString[i] = string1[i].
MyString MyString::operator = (const MyString & string1){
  int index = 0;
  if (string1.numElements <= numElements){
    //ASSERT: there is enough space in StringPtr
    while (string1.StringPtr[index] != EOS) {
      StringPtr[index] = string1.StringPtr[index];
      index++;
    }
    //ASSERT: we have reached the end of string1
    if (string1.numElements == numElements){
      addchar(EOS);
    }
    else{
      //ASSERT: string1 MUST be less than this object
      //COLLORARY: there must be at least 1 space in StringPtr
      //after all the items from string1 is put into StringPtr.
      StringPtr[index + 1] = EOS;
    }
  }
  else{
    //ASSERT: once the program reaches the end of StringPtr there's still
    //going to be items that need to be deepcopied to StringPtr
    while (StringPtr[index] != EOS) {
      StringPtr[index] = string1.StringPtr[index];
      index++;
    }
    //assert: we've reached the point in StringPtr where we dont have space
    //to deep copie any more items from string1
    while (string1.StringPtr[index] != EOS) {
      addchar(string1.StringPtr[index]);
      index++;
    }
    //ASSERT: everything has been deepcopied from string1 to this object
  }
  return (*this);
}

//PRE: this object satisfies the CI
//POST: changes all characters in the object to it's uppercase equivalent
void MyString::toUpperCase(){
  int curr_index = 0;
  char ch = StringPtr[curr_index];
  while (ch != EOS){
    if(islowercase(ch)){
      ch -= lowerTOupper;
      StringPtr[curr_index] = ch;
    }
    curr_index++;
    ch = StringPtr[curr_index];
  }
}

//MODIFIERS
//PRE: this object satisfies the CI. pNum is a positive integer.
//POST: Removes the first pNum values in the object
void MyString::removeFirst(int pNum){
  char ch = StringPtr[pNum];
  int index = 0;
  if (pNum > numElements){
    //ASSERT: Trying to remove more than we have
    StringPtr[index] = EOS;
    numElements = 0;
  }
  else{
    //ASSERT: We have more than pNum numElements in StringPtr
    index = pNum;
    int pNumindex = 0;
    while (index <= numElements){
      StringPtr[pNumindex] = ch;
      pNumindex++;
      index++;
      ch = StringPtr[index];
    }
    //ASSERT: rStringPtr = the elements in StringPtr from pNum to numElements
    //delete [] StringPtr;
    addchar(EOS);
    numElements -= (pNum + 1);
  }
}

//IO OPERATORS
//PRE: aString is identified
//POST: stream contains the contents of the IS and transfers it into aString
istream & operator >> (istream & stream, MyString & aString){
  char ch = stream.get();
  while(ch != '\n'){
    aString.addchar(ch);
    ch = stream.get();
  }
  //ASSERT: ch is now the new line chararacter
  return (stream);
}
  
//PRE: aString is defined as an array of characters with the end of line
// character after stream
//POST: stream contains the contents of the IS and transfers it into aString
ostream & operator << (ostream & stream, const MyString & aString){
  stream << aString.StringPtr << endl;
  return(stream);
}

