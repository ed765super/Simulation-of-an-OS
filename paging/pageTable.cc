#include "pageTable.h"
using namespace std;
//PRE:
//POST: creates a default pageEntry
pageEntry::pageEntry();

//PRE: The parameters must satisfy the CI
//POST: Creates a page table entry
pageEntry::pageEntry(bool pProgOrStack, int pVPN,
		     bool pDirty, bool pMemOrSwap){
  progOrStack = pProgOrStack;
  VPN = pVPN;
  dirty = pDirty;
  memOrSwap = pMemOrSwap;
}

//COPY CONSTRUCTOR
//PRE: anEntry must be a valid pageEntry
//POST: This object is defined and is a deep copy of anEntry
pageEntry::pageEntry(const pageEntry & anEntry){
  this->setProgOrStack(anEntry.getProgOrStack());
  this->setVPN(anEntry.getVPN());
  this->setDirty(anEntry.getDirty());
  this->setMemOrSwap(anEntry.getMemOrSwap());
}

//DESTRUCTOR
//PRE: this object is defined
//POST: Deletes this object
pageEntry::~pageEntry(){
  delete this;
}

//~~~~~~~
//GETTERS|
//~~~~~~~
//PRE: this object must be defined
//POST: returns the object named after this get
bool pageEntry::getProgOrStack() const{
  return progOrStack;
}
    
//PRE: this object must be defined
//POST: returns the object named after this get
int pageEntry::getVPN() const{
  return VPN;
}

//PRE: this object must be defined
//POST: returns the object named after this get
int pageEntry::getPPN() const{
  return PPN;
}

//PRE: this object must be defined
//POST: returns the object named after this get
bool pageEntry::getDirty() const{
  return dirty;
}

//PRE: this object must be defined
//POST: returns the object named after this get
bool pageEntry::getMemOrSwap() const{
  return memOrSwap;
}

//~~~~~~~
//SETTERS|
//~~~~~~~
//PRE: this object must be defined
//POST: modifies the member data object named after this set
//function s.t. it is equal to the parameter
void pageEntry::setProgOrStack(bool pProgOrStack){
  progOrStack = pProgOrStack;
}

//PRE: this object must be defined
//POST: modifies the member data object named after this set
//function s.t. it is equal to the parameter
void pageEntry::setVPN(int pVPN){
  VPN = pVPN;
}

//PRE: this object must be defined
//POST: modifies the member data object named after this set
//function s.t. it is equal to the parameter
void pageEntry::setPPN(int pPPN){
  PPN = pPPN;
}

//PRE: this object must be defined
//POST: modifies the member data object named after this set
//function s.t. it is equal to the parameter
void pageEntry::setDirty(bool pDirty){
  dirty = pDirty;
}

//PRE: this object must be defined
//POST: modifies the member data object named after this set
//function s.t. it is equal to the parameter
void pageEntry::setMemOrSwap(bool pMemOrSwap){
  memOrSwap = pMemOrSwap;
}

//~~~~~~~~~~~~~~~~~
//OVERLOADED OUTPUT|
//~~~~~~~~~~~~~~~~~
//PRE: the implicit object is declared & defined.
//POST: OS contains all the member data objects of this object.
ostream & operator << (ostream & stream, const pageEntry & thisEntry){
  cout << "Prog or Stack: " << thisEntry.getProgOrStack() << endl;
  cout << "VPN: " << thisEntry.getVPN() << endl;
  cout << "PPN: " << thisEntry.getPPN() << endl;
  cout << "Dirty? " << thisEntry.getDirty() << endl;
  cout << "In Memory or Swap: " << thisEntry.getMemOrSwap() << endl;
}
