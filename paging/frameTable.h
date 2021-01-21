#ifndef INCLUDED_FRAMETABLE
#define INCLUDED_FRAMETABLE
#include <iostream>
using namespace std;
class frameEntry{
  //CI:
  //PID is an integer that represents the PID of the process associated with
  //this object
  //VPN is an integer that represents the virtual page number associated with
  //this object.
  //dirty is a boolean that represents whether this entry is dirty or not
  
 private:
  int PID;
  int VPN;
  bool dirty;
 public:
  //PRE:
  //POST: defaultly creates a frame entry object
  frameEntry();

  //PRE:
  //POST: creates a frame table entry
  frameEntry(int pPID, int pVPN);
  
  //COPY CONSTRUCTOR
  //PRE: anEntry must be a valid frameEntry
  //POST: This object is defined and is a deep copy of anEntry
  frameEntry(const frameEntry & anEntry);

  //DESTRUCTOR
  //PRE: this object is defined
  //POST: Deletes this object
  ~frameEntry();
 
  //~~~~~~~
  //GETTERS|
  //~~~~~~~
  
  //PRE: this object must be defined
  //POST: returns the object named after this get
  int getPID() const;

  //PRE: this object must be defined
  //POST: returns the object named after this get
  int getVPN() const;

  //PRE: this object must be defined
  //POST: returns the object named after this get
  bool getDirty() const;
  
  //~~~~~~~
  //SETTERS|
  //~~~~~~~
  
  //PRE: this object must be defined
  //POST: modifies the member data object named after this set
  //function s.t. it is equal to the parameter
  void getPID(int pPID);

  //PRE: this object must be defined
  //POST: modifies the member data object named after this set
  //function s.t. it is equal to the parameter
  void getVPN(int pVPN);

  //PRE: this object must be defined
  //POST: modifies the member data object named after this set
  //function s.t. it is equal to the parameter
  void setDirty(bool pDirty);

  //~~~~~~~~~~~~~~~~~~~~
  //OVERLOADED OPERATORS|
  //~~~~~~~~~~~~~~~~~~~~
  //PRE:
  //POST: makes a deep copy from anEntry to this object and returns this object
  frameEntry operator = (const frameEntry & anEntry);
  
  //PRE:
  //POST: RV = true iff this is equal to anEntry
  frameEntry operator == (const frameEntry & anEntry);
  
  //~~~~~~~~~~~~~~~~~
  //OVERLOADED OUTPUT|
  //~~~~~~~~~~~~~~~~~
  //PRE: the implicit object is declared & defined.
  //POST: OS contains all the member data objects of this object.
  friend ostream & operator << (ostream & stream, const frameEntry & thisEntry);
};
#endif
