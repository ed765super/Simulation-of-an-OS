#ifndef INCLUDED_PCB
#define INCLUDED_PCB
#include "MyString.h"
#include "block.h"
#include "LinkedList.h"
#include "Register.h"
#include "pageTable.h"
#include <iostream>
using namespace std;
class PCB{
  //CI: This object is defined when the following is achieved:
  //    actualPC is an integer x where 0 <= x < number of allocatted space
  //    relativePC is an integer x where 0 <= x < number of allocatted space
  //    progname is a valid program .lcb file
  //    processID is an unique integer that distinguishes this PCB
  //    object from other PCB objects. While there is no max number
  //    this integer may take, each if the IDs of these PCB objects
  //    must be contiguous with each other. 
  //    startingAddressStack is the address where this object's stack
  //    memory starts. Starts at the final byte of free memory which
  //    is located at the byte right after the ending address of the
  //    program.
  //    This object can be NULL. This object is considered NULL if all
  //    member data objects are equal to -1 (excluding progName which
  //    equals ['\0'])
  //    currRegisters hold the state of the program associated with this
  //    PCB at this point
  //    pageTable is the list of active pages on this program
  //    processStatus is a boolean representing whether this program
  //    is waiting or running where false means this progress is
  //    waiting (i.e. waiting due to the command in or waiting to
  //    start using it's timeslices. and true means this program is
  //    running (i.e used some timeslices, but hasnt hit an in)
  //    numPageFaults is an integer that represents the number of page
  //    faults this program has procured.
  //    numTimeSlices is an integer that represents the number of
  //    timeslices used by this program
  //    executablePtr is a pointer to the ifstream object. this object this
  //    pointer points to must be manually deleted if this object is deleted
 private:
  int relativePC; //an integer that represents next instruction to be executed
                  //(byte address)
  MyString progName; //Holds the name of the program associated with this
                     //PCB object
  LinkedList<Register> currRegisters; //what the registers look like at this
                                      //current momenent
  int processID; //ID of this PCB
  LinkedList<pageEntry> pageTable; //holds all the pages associated
				   //with this program
  bool processStatus; //holds a boolean representing it's running
		      //status
  int numPageFaults; //holds the number of page faults this program
		     //has procured
  int numTimeSlices; //holds the number of timeslices used by this
		     //program
  ifstream* executablePtr; //holds a pointer to the ifstream object
                           //associated with this program
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
      int pProcessID, LinkedList<Register> pRegisters,
      LinkedList<pageEntry> pPageTable, bool pProcessStatus,
      ifstream* pExacutablePtr);
  
  //ACCESSOR
  
  //PRE: This object must be defined and satisfy the CI
  //POST: returns the relative PC
  int getRelativePC() const;

  //PRE: This object must be defined and satisfy the CI
  //POST: returns the name of the current program associated with
  //this process control block
  MyString getProgName() const;

  //PRE: This object must be defined and satisfy the CI
  //POST: RV = currRegisters
  LinkedList<Register> getRegisters() const;

  //PRE: This object must be defined and satisfy the CI
  //POST: RV = the pageTable associated with this object
  LinkedList<pageEntry> getPageTable() const;
  
  //PRE: This object must be defined and satisfy the CI
  //POST: returns the running status of this object
  bool getProcessStatus() const;

  //PRE: This object must be defined and satisfy the CI
  //POST: returns the number of pagefaults procured by this program
  int getNumPageFaults() const;

  //PRE: This object must be defined and satisfy the CI
  //POST: returns the number of pagefaults procured by this program
  int getNumTimeSlices() const;
  
  //PRE: This object must be defined and satisfy the CI
  //POST: returns the process ID
  int getProcessID() const;

  //PRE: This object must be defined and satisfy the CI
  //POST: RV =  the pointer to the ifsteam object associated with this object.
  ifstream* getExacutablePtr() const;

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

  //PRE: This object mus tbe defined and the implicit object in the
  //parameter must be a valid object that wouldn't change the
  //satisfaction of the CI
  //POST: Modifies currRegisters s.t. it more accurately represents the
  //      state of the program by setting it equal to the implicitState
  void setRegisters(LinkedList<Register> implicitState);
  
  //PRE: this object must be defined and the implicit object in the
  //parameter must be a valid object that wouldn't change the
  //satisfaction of the CI
  //POST: modifies the process ID
  void setProcessID(int pProcessID);

  //PRE: this object must be defined and the implicit object in the
  //parameter must be a valid object that wouldn't change the
  //satisfaction of the CI
  //POST: modifies this object s.t. pagetable is equal to pPageTable
  void setPageTable(LinkedList<pageEntry> pPageTable);

  //PRE: this object must be defined and the implicit object in the
  //parameter must be a valid object that wouldn't change the
  //satisfaction of the CI
  //POST: modifies the data object associated with this object by the
  //same name after set s.t. it's equal to the object given in the
  //parameter
  void setProcessStatus(bool pProcessStatus);

  //PRE: this object must be defined and the implicit object in the
  //parameter must be a valid object that wouldn't change the
  //satisfaction of the CI
  //POST: modifies the data object associated with this object by the
  //same name after set s.t. it's equal to the object given in the
  //parameter
  void setNumPageFaults(int pNumPageFaults);

  //PRE: this object must be defined and the implicit object in the
  //parameter must be a valid object that wouldn't change the
  //satisfaction of the CI
  //POST: modifies the data object associated with this object by the
  //same name after set s.t. it's equal to the object given in the
  //parameter
  void setNumTimeSlices(int pNumTimeSlices);
  
  //PRE: This object must be defined and satisfy the CI and the
  //implicit object in the parameter must be a valid object that wouldn't
  //change the satisfaction of the CI
  //POST: modifies the data object associated with this object by the
  //same name after set s.t. it's equal to the object given in the
  //parameter
  void setExacutablePtr(ifstream* pExactublePtr);
  
  //PRE: VPN must be an integer. This object must be defined
  //POST: RV = the PPN of this program iff the VPN has a
  //valid PPN associated with it
  int getPPN(int VPN);
  
  //PRE: this object and the implicit objec must be defined and
  //satisfy the CI
  //POST: sets all the values of the implicit object to this object
  PCB operator =(PCB & implicitPCB);
  
  //OUTPUT
  //PRE: curr_PCB must be defined
  //POST: OS (output stream) contains the member data objects of curr_PCB.
  friend ostream & operator << (ostream & stream, PCB & curr_PCB);
};
#endif
