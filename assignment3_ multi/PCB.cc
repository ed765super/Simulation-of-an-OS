#include "PCB.h"
using namespace std;
//CONSTRUCTOR
//PRE:
//POST: Defaultly constructs this PCB object
PCB::PCB(){
  relativePC = -1;
  startingAddressProg = -1;
  endingAddressProg = -1;
  processID = -1;
  startingAddressStack = -1;
  endingAddressStack = -1;
}
//PRE:
//POST: creates a PCB object
PCB::PCB(int rPC, MyString pProgName,
	 Block progBlock, Block stackBlock,
	 int pProcessID, LinkedList<Register> pRegisters){
  progName = pProgName;
  relativePC = rPC;
  startingAddressProg = progBlock.getStart();
  endingAddressProg = progBlock.getEnd();
  processID = pProcessID;
  startingAddressStack = stackBlock.getStart();
  endingAddressStack = stackBlock.getEnd();
  currRegisters = pRegisters;
}

//ACCESSOR

//PRE:
//POST: returns the relative PC
int PCB::getRelativePC() const{
  return relativePC;
}

//PRE:
//POST: returns the name of the current program associated with
//this process control block
MyString PCB::getProgName() const{
  return progName;
}

//PRE:
//POST: returns the starting address for the program
int PCB::getStartingAddressProg() const{
  return startingAddressProg;
}

//PRE:
//POST: returns the ending address for the program
int PCB::getEndingAddressProg() const{
  return endingAddressProg;
}

//PRE:
//POST: RV = currRegisters
LinkedList<Register> PCB::getRegisters() const{
  return currRegisters;
}

//PRE:
//POST: returns the process ID
int PCB::getProcessID() const{
  return processID;
}

//PRE:
//POST: returns the starting address for the stack
int PCB::getStartingAddressStack() const{
  return startingAddressStack;
}

//PRE:
//POST: returns the ending address for the stack
int PCB::getEndingAddressStack() const{
  return endingAddressStack;
}

//MODIFIERS

//PRE: this object must be defined. pPC must be an integer that
//would be a valid PC.
//POST: sets the relative PC to pPC
void PCB::setRelativePC(int pPC){
  relativePC = pPC;
}

//PRE: this object must be defined. pProgName must be an integer that
  //would be a valid program name
  //POST: modifies the name of the current program associated with
  //this process control block
void PCB::setProgName(MyString pProgName){
  progName = pProgName;
}

//PRE: this object must be defined
//POST: modifies the starting address for the program
void PCB::setStartingAddressProg(int pStartingAddressProg){
  startingAddressProg = pStartingAddressProg;
}

//PRE: this object must be defined
//POST: modifies the ending address for the program
void PCB::setEndingAddressProg(int pEndingAddressProg){
  endingAddressProg = pEndingAddressProg;
}

//PRE: This object mus tbe defined
//POST: Modifies currRegisters s.t. it more accurately represents the
//      state of the program by setting it equal to the implicitState
void PCB::setRegisters(LinkedList<Register> implicitState){
  currRegisters = implicitState;
}

//PRE: this object must be defined
//POST: modifies the process ID
void PCB::setProcessID(int pProcessID){
  processID = pProcessID;
}

//PRE:
//POST: modifies the starting address for the stack
void PCB::setStartingAddressStack(int pStartingAddressStack){
  startingAddressStack = pStartingAddressStack;
}

//PRE: this object must be defined
//POST: modifies the ending address for the stack
void PCB::setEndingAddressStack(int pEndingAddressStack){
  endingAddressStack = pEndingAddressStack;
}

//PRE: this object and the implicit objec must be defined
//POST: sets all the values of the implicit object to this object
PCB PCB::operator =(PCB & implicitPCB){
  setRelativePC(implicitPCB.getRelativePC());
  setProgName(implicitPCB.getProgName());
  setStartingAddressProg(implicitPCB.getStartingAddressProg());
  setEndingAddressProg(implicitPCB.getEndingAddressProg());
  setProcessID(implicitPCB.getProcessID());
  setStartingAddressStack(implicitPCB.getStartingAddressStack());
  setEndingAddressStack(implicitPCB.getEndingAddressStack());
  setRegisters(implicitPCB.getRegisters());
  return (*this);
}

//OUTPUT
//PRE: curr_PCB must be defined
//POST: OS (output stream) contains the member data objects of curr_PCB.
ostream & operator << (ostream & stream, PCB & curr_PCB){
  stream << "ID: " << curr_PCB.getProcessID() << endl;
  stream << "relative PC: " << curr_PCB.getRelativePC() << endl;
  stream << "Program Name: " << curr_PCB.getProgName() << endl;
  stream << "Starting Address of Program: " << curr_PCB.getStartingAddressProg()
	 << endl;
  stream << "Ending Address of Program: " << curr_PCB.getEndingAddressProg()
	 << endl;
  stream << "Starting Address of the Stack: "
	 << curr_PCB.getStartingAddressStack() << endl;
  stream << "Ending Address of the Stack: " << curr_PCB.getEndingAddressStack()
	 << endl;
  return stream;
}
