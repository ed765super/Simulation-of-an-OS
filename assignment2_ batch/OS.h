#ifndef INCLUDED_OS_CLASS
#define INCLUDED_OS_CLASS
#include "LinkedList.h"
#include "PCB.h"
#include "block.h"
#include "Exception.h"
#include <iostream>

class OS{
  //CI: recent_PCBID is the most recent ID given to a PCB object. It is
  //initalized to 0. PCB_list is a list of PCB objects that represents
  //which process is most ready i.e. the PCB at the 0th object is considered
  //the current PCB. mySim is a simulator object that simulates the CPU and
  //memory.
  //freeBlocks reprent the free blocks of RAM.
 private:
  int recent_PCBID;
  LinkedList<PCB> PCB_list;
  LinkedList<Block> freeBlocks;

 public:
  //CONSTRUCTOR
  //PRE:
  //POST: creates an OS class
  OS(Block max_free);

  //ACCESSORS
  //PRE: this object must be defined
  //POST: RV =  the most recent ID given to a PCB object
  int getRecentPCBID() const;
  
  //PRE: this object must be defined
  //POST: RV = the current list of PCB objects
  LinkedList<PCB> getPCB_list() const;

  //PRE: this object must be defined
  //POST: RV = the list of free blocks
  LinkedList<Block> getFreeBlocks() const;

  //PRE: this object must be defined
  //POST: RV = the current PCB
  PCB* getCurrPCB() const;
  
  //MODIFIERS
  //PRE: newFreeBlock must be a valid linked list of freeBlock
  //objects. This object must be defined
  //POST: modifies the list of free blocks s.t. this object's
  //free blocks are equal to newFreeBlock
  void setFreeBlocks(LinkedList<Block> newFreeBlock);
  
  //PRE: This object must be defined
  //POST: modifies the PCB list
  void popOffQueue();

  //PRE: this object is defined. fitType is a 0 or 1 dependant on whether
  //the memory management is first fit or best fit respectively. program&stack
  //represent the relative program & stack locations.
  //POST: finds space in memory if it cant returns foundSpace as false
  //      if it did, returns found space as true. Also modifies
  //      newProg/newStack s.t. they contain the actual addresses of the
  //      prog/stack they represent
  bool findSpace(int fitType, Block stack,
		 Block program, Block & newProg, Block & newStack);
  
  //PRE: this object is defined. the parameters here follow the pre of the
  //member function "find space" located within this file 
  //POST: Actually tries to fit the block in memory using one of the fit
  //method types. If it cant, throws an error to be handled in find space
  //      tempBlock should be the location in freemem,
  //      that block was allocated (if allocated)
  //      newBlock shuld now be the ACTUAL start & end that the block takes up
  //      in free mem
  void allocateSpace(bool fitType, int progSize, Block & block,
		     Block & newBlock, Block & tempBlock);
  
  //PRE: this object is defined. Location block
  //should be a Block object with the exact start and end of where Block
  //was allocated in memory
  //POST: undos the allocation of the Block just added to freemem
  void deallocateSpace(Block locationBlock);
  
  //PRE: this object is defined. success must be initially false. block should
  //     be a block representing the relative start & end of the object it's
  //     representing.
  //POST: Searches for the first free block in memory.
  //      success = true iff search was successful
  //      search was successful iff a freeblock was found
  //      tempBlock should be the location in freemem,
  //      that block was allocated (if allocated)
  //      newBlock shuld now be the ACTUAL start & end that the block takes up
  //      in free mem
  void firstFit(int size, bool & success, Block & block, Block & newBlock,
		Block & tempBlock);
  
  //PRE: this object is defined. block should
  //     be a block representing the relative start & end of the object it's
  //     representing. success should be initialized to false.
  //POST: Searches for the best free block to put block in
  //memory.
  //      success = true iff search was successful
  //      search was successful iff a freeblock was found
  //      tempBlock should be the location in freemem,
  //      that block was allocated (if allocated)
  //      newBlock shuld now be the ACTUAL start & end that the block takes up
  //      in free mem
  void bestFit(int size, bool & success, Block & block, Block & newBlock,
	       Block & tempBlock);

  //PRE: block should be the block you're adding into memory. AorD
  //should be a character that represents whether you should be allocating
  //or deallocating space
  //locationBlock should be a block located in freemem that you are going
  //to modify
  //POST: modifies freeBlocks to reflect the addition
  //of a block in memory. If allocating, returns a Block representing where
  //in freeblocks the change was made
  Block handleChange(Block block, char AorD, Block locationBlock);
  
  //PRE: this object must be defined
  //POST: adds the PCB object into the running queue
  void addToQueue(PCB incomingPCB);

  //HANDLES
  //PRE: this object must be defined
  //POST: OS (output stream) contains the blocks of freememory
  void handleFreeMem();

  //PRE: this object must be defined
  //POST: OS contains the process information for all the processes
  //in the running queue, starting with the process at the front of
  //the queue.
  void handleJobs();

  //PRE: PCB_ID should be the ID of the PCB object the user is trying
  //     to kill
  //POST: kills the current process if the PCB_ID is a valid
  //     ID and returns false. Otherwise, RV = false;
  bool handleKill(int PCB_ID);
};
#endif
