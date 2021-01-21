#ifndef INCLUDED_PAGETABLE
#define INCLUDED_PAGETABLE
#include <iostream>
using namespace std;

class pageEntry{
  //CI: pageEntry is an object that represents an entry in a
  //pageTable.
  //object cannot be NULL.
  //progOrStack is a boolean that is 1 iff this entry represents the stack.
  //VPN is an integer that represents the virtual page number that is
  //assosiated with this object
  //dirty is a boolean that represents whether this entry represents a
  //dirty page or not. Of course true iff this object does represent a
  //dirty page
  //memOrSwap is a bool representing whether this entry represents a
  //page that is on the mem or swap where true indicates it's on swap
 private:
  bool progOrStack;
  int VPN;
  bool dirty;
  bool memOrSwap;
 public:
  //PRE:
  //POST: creates a default pageEntry
  pageEntry();
  
  //PRE: The parameters must satisfy the CI
  //POST: Creates a page table entry
  pageEntry(bool pProgOrStack, int pVPN,
	    bool pDirty, bool pMemOrSwap);
  
  //COPY CONSTRUCTOR
  //PRE: anEntry must be a valid frameEntry
  //POST: This object is defined and is a deep copy of anEntry
  pageEntry(const pageEntry & anEntry);

  //DESTRUCTOR
  //PRE: this object is defined
  //POST: Deletes this object
  ~pageEntry();
 
  //~~~~~~~
  //GETTERS|
  //~~~~~~~
  //PRE: this object must be defined
  //POST: returns the object named after this get
  bool getProgOrStack() const;

  //PRE: this object must be defined
  //POST: returns the object named after this get
  int getVPN() const;

  //PRE: this object must be defined
  //POST: returns the object named after this get
  int getPPN() const;

  //PRE: this object must be defined
  //POST: returns the object named after this get
  bool getDirty() const;

  //PRE: this object must be defined
  //POST: returns the object named after this get
  bool getMemOrSwap() const;

  //~~~~~~~
  //SETTERS|
  //~~~~~~~
  //PRE: this object must be defined
  //POST: modifies the member data object named after this set
  //function s.t. it is equal to the parameter
  void setProgOrStack(bool pProgOrStack);

  //PRE: this object must be defined
  //POST: modifies the member data object named after this set
  //function s.t. it is equal to the parameter
  void setVPN(int pVPN);

  //PRE: this object must be defined
  //POST: modifies the member data object named after this set
  //function s.t. it is equal to the parameter
  void setPPN(int pPPN);

  //PRE: this object must be defined
  //POST: modifies the member data object named after this set
  //function s.t. it is equal to the parameter
  void setDirty(bool pDirty);

  //PRE: this object must be defined
  //POST: modifies the member data object named after this set
  //function s.t. it is equal to the parameter
  void setMemOrSwap(bool pMemOrSwap);

  //~~~~~~~~~~~~~~~~~
  //OVERLOADED OUTPUT|
  //~~~~~~~~~~~~~~~~~
  //PRE: the implicit object is declared & defined.
  //POST: OS contains all the member data objects of this object.
  friend ostream & operator << (ostream & stream, const pageEntry & thisEntry);
  
};
#endif
