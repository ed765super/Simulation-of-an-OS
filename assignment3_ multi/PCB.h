#ifndef INCLUDED_PCB
#define INCLUDED_PCB
#include "MyString.h"
#include "block.h"
#include "LinkedList.h"
#include "Register.h"
#include <iostream>
using namespace std;
class PCB{
  //CI: This object is defined when the following is achieved:
  //    actualPC is an integer x where 0 <= x < number of allocatted space
  //    relativePC is an integer x where 0 <= x < number of allocatted space
  //    progname is a valid program .lcb file
  //    startingAddressProg a valid integer representing the starting
  //    memory location of the program. A valid integer is x where
  //    0 <= x < memory - stackSize (memory is located in the config file
  //    endingAddressProg a valid integer representing ending memory
  //    location of the program. a valid integer is x where
  //    startingAddressProg < x < startingAddressStack
  //    stackPointer a valid integer that represents the first byte
  //    address that is free. This value must be initialized to the
  //    endingAddressStack.
  //    processID is an unique integer that distinguishes this PCB
  //    object from other PCB objects. While there is no max number
  //    this integer may take, each if the IDs of these PCB objects
  //    must be contiguous with each other. 
  //    startingAddressStack is the address where this object's stack
  //    memory starts. Starts at the final byte of free memory which
  //    is located at the byte right after the ending address of the
  //    program. valid integers are x where
  //    endingAddressprog < x < memory - stackSize
  //    endingAddressStack is the address of this program's
  //    stack. Ending in the sence that it is located at the place in
  //    memory 'stackSpace' (found in config file) away from the
  //    startingAddressStack. valid integers are x where
  //    startingAddressStack < x < startingAddressStack+size spacified
  //    in the config.
  //    This object can be NULL. This object is considered NULL if all
  //    member data objects are equal to -1 (excluding progName which
  //    equals ['\0'])
  //    currRegisters hold the state of the program associated with this
  //    PCB at this point
 private:
  int actualPC; //an integer that represents next instruction to be executed
                //(byte address)
  int relativePC; //an integer that represents next instruction to be executed
                  //(byte address)
  MyString progName; //Holds the name of the program associated with this
                     //PCB object
  int startingAddressProg; //starting memory location of the program
  int endingAddressProg; //ending memory location of the program
  LinkedList<Register> currRegisters; //what the registers look like at this
                                      //current momenent
  int processID; //ID of this PCB
  int startingAddressStack; //starting memory location of the stack
  int endingAddressStack; //ending memory location of the stack

 public:
  //CONSTRUCTOR
  //PRE:
  //POST: Defaultly constructs this PCB object
  PCB();
  
  //PRE: the parameters must satisfy the restrictions that have described
  //for their respective member data objects in the CI respectively.
  //prog & stack block must be defined blocks
  //POST: creates a PCB object
  PCB(int rPC, MyString pProgName,
      Block progBlock, Block stackBlock,
      int pProcessID, LinkedList<Register> pRegisters);
  
  //ACCESSOR

  //PRE:
  //POST: returns the relative PC
  int getRelativePC() const;

  //PRE:
  //POST: returns the name of the current program associated with
  //this process control block
  MyString getProgName() const;
  
  //PRE:
  //POST: returns the starting address for the program
  int getStartingAddressProg() const;

  //PRE:
  //POST: returns the ending address for the program
  int getEndingAddressProg() const;

  //PRE:
  //POST: RV = currRegisters
  LinkedList<Register> getRegisters() const;
  
  //PRE:
  //POST: returns the process ID
  int getProcessID() const;

  //PRE:
  //POST: returns the starting address for the stack
  int getStartingAddressStack() const;

  //PRE:
  //POST: returns the ending address for the stack
  int getEndingAddressStack() const;

  //MODIFIERS

  //PRE: this object must be defined. pPC must be an integer that
  //would be a valid PC.
  //POST: sets the relative PC to pPC
  void setRelativePC(int pPC);

  //PRE: this object must be defined. pProgName must be an integer that
  //would be a valid program name
  //POST: modifies the name of the current program associated with
  //this process control block
  void setProgName(MyString pProgName);
  
  //PRE: this object must be defined. pStartingAddressProg must be a valid
  //starting address of a program associated with this process control
  //block 
  //POST: modifies the starting address for the program
  void setStartingAddressProg(int pStartingAddressProg);

  //PRE: this object must be defined. pEndingAddressProg must be a
  //valid ending address of a program associated with this PCB object
  //POST: modifies the ending address for the program
  void setEndingAddressProg(int pEndingAddressProg);

  //PRE: This object mus tbe defined
  //POST: Modifies currRegisters s.t. it more accurately represents the
  //      state of the program by setting it equal to the implicitState
  void setRegisters(LinkedList<Register> implicitState);
  
  //PRE: this object must be defined
  //POST: modifies the process ID
  void setProcessID(int pProcessID);

  //PRE:
  //POST: modifies the starting address for the stack
  void setStartingAddressStack(int pStartingAddressStack);

  //PRE: this object must be defined
  //POST: modifies the ending address for the stack
  void setEndingAddressStack(int pEndingAddressStack);

  //PRE: this object and the implicit objec must be defined
  //POST: sets all the values of the implicit object to this object
  PCB operator =(PCB & implicitPCB);
  
  //OUTPUT
  //PRE: curr_PCB must be defined
  //POST: OS (output stream) contains the member data objects of curr_PCB.
  friend ostream & operator << (ostream & stream, PCB & curr_PCB);
};
#endif
