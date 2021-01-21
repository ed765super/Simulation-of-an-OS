/* Author: Schuyler van Tine */
/*   Register Class          */

#ifndef INCLUDED_REGISTER
#define INCLUDED_REGISTER
#include "MyString.h"

// CI: name defined, value defined

class Register {
 private:
  MyString name;
  int value; 
 public:
  //==================================================================
  // Constructors
  //==================================================================

  // PRE:
  // POST: need to define namne and value, so do nothing
  Register(){};

  // PRE:
  // POST: name = pname, value = pValue
  Register(MyString pName, int pValue);

  // PRE:
  // POST: returns deep copy of aRegister:
  Register(const Register & aRegister); 

  //==================================================================
  // Accessors
  //==================================================================
  // PRE:
  // POST: returns name
  MyString getName() const;

  // PRE:
  // POST: returns value
  int getValue() const;

  // PRE:
  // POST: returns char* that holds contents of member data
  char* getStr() const; 

  //==================================================================
  // Modifiers
  //==================================================================

  // PRE:
  // POST: name = pName
  void setName(MyString pName);

  // PRE:
  // POST: value = pValue
  void setValue(int pValue);

  // PRE:
  // POST: name = pName & value = pValue
  void setRegister(MyString pName, int pValue);

  //===================================================================
  // Input/Output
  //===================================================================

  // PRE: R is defined
  // POST: OS contains R's name and value 
  friend ostream & operator<< (ostream & str, const Register & R); 

}; 

#endif
