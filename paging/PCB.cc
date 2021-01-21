#include "PCB.h"
using namespace std;
//CONSTRUCTOR
//PRE:
//POST: Defaultly constructs this PCB object
PCB::PCB(){
  relativePC = -1;
  processID = -1;
  processStatus = false;
  numPageFaults = 0;
  numTimeSlices = 0;
}
//PRE:
//POST: creates a PCB object
PCB::PCB(int rPC, MyString pProgName,
	 Block progBlock, Block stackBlock,
	 int pProcessID, LinkedList<Register> pRegisters,
	 LinkedList<pageEntry> pPageTable, bool pProcessStatus,
	 ifstream* pExacutablePtr){
  progName = pProgName;
  relativePC = rPC;
  processID = pProcessID;
  currRegisters = pRegisters;
  pageTable = pPageTable;
  numPageFaults = 0;
  numTimeSlices = 0;
  exacutablePtr = pExacutablePtr;
}

//ACCESSOR

//PRE: This object must be defined and satisfy the CI
//POST: returns the relative PC
int PCB::getRelativePC() const{
  return relativePC;
}

//PRE: This object must be defined and satisfy the CI
//POST: returns the name of the current program associated with
//this process control block
MyString PCB::getProgName() const{
  return progName;
}

//PRE: This object must be defined and satisfy the CI
//POST: RV = currRegisters
LinkedList<Register> PCB::getRegisters() const{
  return currRegisters;
}

//PRE: This object must be defined and satisfy the CI
//POST: returns the process ID
int PCB::getProcessID() const{
  return processID;
}

//PRE: This object must be defined and satisfy the CI
//POST: RV = the pageTable associated with this object
LinkedList<pageEntry> PCB::getPageTable() const{
  return pageTable;
}

//PRE: This object must be defined and satisfy the CI
//POST: returns the running status of this object
bool PCB::getProcessStatus() const{
  return processStatus;
}

//PRE: This object must be defined and satisfy the CI
//POST: returns the number of pagefaults procured by this program
int PCB::getNumPageFaults() const{
  return numPageFaults;
}

//PRE: This object must be defined and satisfy the CI
//POST: returns the number of pagefaults procured by this program
int PCB::getNumTimeSlices() const{
  return numTimeSlices;
}

//PRE: This object must be defined and satisfy the CI
//POST: RV =  the pointer to the ifsteam object associated with this object.
ifstream* PCB::getExacutablePtr() const{
  return exacutablePtr;
}

//PRE: VPN must be an integer. This object must be defined
//POST: RV = the PPN of this program iff the VPN has a
//valid PPN associated with it
int PCB::getPPN(int VPN){
  int index = 1;//index is one because PCB unique IDs start at 1
  bool foundID = false;
  int PPN; //will hold the PPN of this program iff the VPN has a
           //valid PPN associated with it
  while ((index <= PCB_list.getSize()) && (!foundID)){
    PCB* currentPCB = PCB_list.getNth(index-1);
    int currentPCBID = currentPCB->getProcessID();
    if (currentPCBID == VPN){
      foundID = true;
      PPN = pageTable.getPPN();
    }
  }
  if (!foundID){
    cout << "VPN not found" << endl;
  }
  return PPN;
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

//PRE: this object must be defined and the implicit object in the
  //parameter must be a valid object that wouldn't change the
  //satisfaction of the CI
//POST: modifies this object s.t. it is equal to pPageTable
void PCB::setPageTable(LinkedList<pageEntry> pPageTable){
  pageTable = pPageTable;
}

//PRE: this object must be defined and the implicit object in the
  //parameter must be a valid object that wouldn't change the
  //satisfaction of the CI
//POST: modifies the data object associated with this object by the
//same name after set s.t. it's equal to the object given in the
//parameter
void PCB::setProcessStatus(bool pProcessStatus){
  processStatus = pProcessStatus;
}

//PRE: this object must be defined and the implicit object in the
  //parameter must be a valid object that wouldn't change the
  //satisfaction of the CI
//POST: modifies the data object associated with this object by the
//same name after set s.t. it's equal to the object given in the
//parameter
void PCB::setNumTimeSlices(int pNumTimeSlices){
  numTimeSlices = pNumTimeSlices;
}

//PRE: this object must be defined and the implicit object in the
  //parameter must be a valid object that wouldn't change the
  //satisfaction of the CI
//POST: modifies the data object associated with this object by the
//same name after set s.t. it's equal to the object given in the
//parameter
void PCB::setNumPageFaults(int pNumPageFaults){
  numPageFaults = pNumPageFaults;
}

//PRE: This object must be defined and satisfy the CI and the
//implicit object in the parameter must be a valid object that wouldn't
//change the satisfaction of the CI
//POST: modifies the data object associated with this object by the
//same name after set s.t. it's equal to the object given in the
//parameter
void PCB::setExacutablePtr(ifstream* pExactublePtr){
  exacutablePtr = pExactublePtr;
}

//PRE: this object and the implicit objec must be defined
//POST: sets all the values of the implicit object to this object
PCB PCB::operator =(PCB & implicitPCB){
  setRelativePC(implicitPCB.getRelativePC());
  setProgName(implicitPCB.getProgName());
  setProcessID(implicitPCB.getProcessID());
  setRegisters(implicitPCB.getRegisters());
  setPageTable(implicitPCB.getPageTable());
  setProcessStatus(implicitPCB.getProcessStatus());
  setNumPageFaults(implicitPCB.getNumPageFaults());
  setNumTimeSlices(implicitPCB.getNumTimeslices());
  setExacutablePtr(implicitPCB.getExacutablePtr());
  return (*this);
}

//OUTPUT
//PRE: curr_PCB must be defined
//POST: OS (output stream) contains the member data objects of curr_PCB.
ostream & operator << (ostream & stream, PCB & curr_PCB){
  stream << "ID: " << curr_PCB.getProcessID() << endl;
  stream << "Program Name: " << curr_PCB.getProgName() << endl;
  stream << "Status (0 = waiting, 1 = running): "
	 << curr_PCB.getProcessStatus() << endl;
  stream << "Number of Timeslices used: " << curr_PCB.getNumTimeslices()
	 << endl;
  stream << "Number of page faults: " << curr_PCB.getNumPageFaults() << endl;
  return stream;
}
