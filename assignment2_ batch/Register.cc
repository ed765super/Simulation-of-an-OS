/* Author: Schuyler van Tine */
/*    Register Class         */

#include "MyString.h"
#include "constants.h"
#include "Register.h"

// CI: name defined, value defined

//==================================================================
// Constructors
//==================================================================

// PRE:
// POST: name = pname, value = pValue
Register::Register(MyString pName, int pValue){
  name = pName;
  value = pValue;
}

// PRE:
// POST: this is a deep copy of aRegister
Register::Register(const Register & aRegister){
  name = aRegister.getName(); 
  value = aRegister.getValue(); 
}

//==================================================================
// Accessors
//==================================================================
// PRE:
// POST: returns name
MyString Register::getName() const {
  return name;
}

// PRE:
// POST: returns value
int Register::getValue() const {
  return value;
}

// PRE:
// POST: returns char* that holds contents of member data
char* Register::getStr() const {
  int val = value;
  int digits = 0;
  // determine number of digits in value
  while (val > 0){
    val = val / 10;
    digits ++;
  }
  char* valChar = new char[digits]; // create array to hold char 
  val = value;
  int temp;
  int index = digits - 1; // index is zero-based, so subtract one
  // store least significant
  while (index >= 0){
    temp = val % 10;
    valChar[index] = (char)temp + '0'; //covnert temp to char and
                                       //store in valChar
    val = val / 10;
    index --; 
  }
  MyString output(name);
  output.addchar(':');
  for(int i = 0; i < digits; i++){
    output.addchar(valChar[i]);
  }
  delete valChar;
  return output.getstring(); 
}

//==================================================================
// Modifiers
//==================================================================

// PRE:
// POST: name = pName
void Register::setName(MyString pName){
  name = pName;
}

// PRE:
// POST: value = pValue
void  Register::setValue(int pValue){
  value = pValue;
}

// PRE:
// POST: name = pName & value = pValue
void  Register::setRegister(MyString pName, int pValue){
  name = pName;
  value = pValue;
}

//==================================================================
//     Input/Output
//==================================================================

// PRE: R is defined
// POST: OS contains R's name and value 
ostream & operator << (ostream & str, const Register & R){
  str << R.getName() << "->" << R.getValue(); 
  return str;
}
