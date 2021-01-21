#include "frameTable.h"
//PRE:
//POST: defaultly creates a frame entry object
frameEntry::frameEntry();

//PRE:
//POST: creates a frame table entry
frameEntry::frameEntry(int pPID, int pVPN, bool pDirty){
  PID = pPID;
  VPN = pVPN;
  dirty = pDirty;
}

//COPY CONSTRUCTOR
//PRE: anEntry must be a valid frameEntry
//POST: This object is defined and is a deep copy of anEntry
frameEntry::frameEntry(const frameEntry & anEntry){
  frameEntry* newEntry = new frameEntry;
  newEntry.setPID(anEntry.getPID());
  newEntry.setVPN(anEntry.getVPN());
  newEntry.setDirty(anEntry.getDirty());
  this = newEntry;
}

//DESTRUCTOR
//PRE: this object is defined
//POST: Deletes this object
frameEntry::~frameEntry(){
  delete this;
}

//~~~~~~~
//GETTERS|
//~~~~~~~

//PRE: this object must be defined
//POST: returns the object named after this get
int frameEntry::getPID() const{
  return PID;
}

//PRE: this object must be defined
//POST: returns the object named after this get
int frameEntry::getVPN() const{
  return VPN;
}

//PRE: this object must be defined
//POST: returns the object named after this get
bool frameEntry::getDirty() const{
  return dirty;
}

//~~~~~~~
//SETTERS|
//~~~~~~~

//PRE: this object must be defined
//POST: modifies the member data object named after this set
//function s.t. it is equal to the parameter
void frameEntry::setPID(int pPID){
  PID = pPID;
}

//PRE: this object must be defined
//POST: modifies the member data object named after this set
//function s.t. it is equal to the parameter
void frameEntry::setVPN(int pVPN){
  VPN = pVPN;
}

//PRE: this object must be defined
//POST: modifies the member data object named after this set
//function s.t. it is equal to the parameter
void frameEntry::setDirty(bool pDirty){
  dirty = pDirty;
}

//~~~~~~~~~~~~~~~~~~~~
//OVERLOADED OPERATORS|
//~~~~~~~~~~~~~~~~~~~~
//PRE:
//POST: makes a deep copy from anEntry to this object and returns this object
frameEntry frameEntry::operator = (const frameEntry & anEntry){
  this->setPID(anEntry.getPID());
  this->setVPN(anEntry.getVPN());
  this->setDirty(anEntry.getDirty());
  return *this;
}
//PRE:
//POST: RV = true iff this is equal to anEntry
frameEntry frameEntry::operator == (const frameEntry & anEntry){
  bool isEqual = false;
  if((PID == anEntry.getPID()) &&
     (VPN == anEntry.getVPN()) &&
     (dirty == anEntry.getDirty())){
    isEqual = true;
  }
  return isEqual;
}

//~~~~~~~~~~~~~~~~~
//OVERLOADED OUTPUT|
//~~~~~~~~~~~~~~~~~
//PRE: the implicit object is declared & defined.
//POST: OS contains all the member data objects of this object in the form
//      <PID,VPN>
friend ostream & operator << (ostream & stream, const frameEntry & thisEntry){
  cout << '<' << thisEntry.getPID() << ',' << thisEntry.getVPN() << '>' << endl;
}
