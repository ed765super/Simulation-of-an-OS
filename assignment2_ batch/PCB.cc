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
	 int pProcessID, Register pStackPointer){
  progName = pProgName;
  relativePC = rPC;
  startingAddressProg = progBlock.getStart();
  endingAddressProg = progBlock.getEnd();
  processID = pProcessID;
  startingAddressStack = stackBlock.getStart();
  endingAddressStack = stackBlock.getEnd();
  stackPointer.setRegister(pStackPointer.getName(), pStackPointer.getValue());
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
//POST: returns the stack pointer
Register PCB::getStackPointer() const{
  return stackPointer;
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

//PRE: this object must be defined
//POST: modifies the stack pointer
void PCB::setStackPointer(Register pStackPointer){
  stackPointer = pStackPointer;
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
  setStackPointer(implicitPCB.getStackPointer());
  setProcessID(implicitPCB.getProcessID());
  setStartingAddressStack(implicitPCB.getStartingAddressStack());
  setEndingAddressStack(implicitPCB.getEndingAddressStack());
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
  stream << "Stack Pointer is currently at: " << curr_PCB.getStackPointer()
	 << endl;
  stream << "Starting Address of the Stack: "
	 << curr_PCB.getStartingAddressStack() << endl;
  stream << "Ending Address of the Stack: " << curr_PCB.getEndingAddressStack()
	 << endl;
  return stream;
}
