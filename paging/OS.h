#ifndef INCLUDED_OS_CLASS
#define INCLUDED_OS_CLASS
#include "LinkedList.h"
#include "PCB.h"
#include "block.h"
#include "Exception.h"
#include "frameTable.h"
#include <iostream>

class OS{
  //CI: recent_PCBID is the most recent ID given to a PCB object. It is
  //initalized to 0. PCB_list is a list of PCB objects that represents
  //which process is most ready i.e. the PCB at the 0th object is considered
  //the current PCB. mySim is a simulator object that simulates the CPU and
  //memory.
  //freeBlocks reprent the free blocks of RAM.
  //timeSlice is the timeSlice that the user defined in the config file
  //memFrameTable is the main frame table for memory. memFTsize is the
  //number of entries in this table
  //swapFrameTable is the main frame table for swap. swapFTsize is the
  //number of entries in this table
  //recentlyUsedPages is a linkedlist representing the recently used pages
  //where the last thing in the list is the most recently referenced page
  //recentlyAddedPages is a linkedlist representing the order in which
  //the entries have been added to the memFrameTable where the last frame
  //Entry is the most recently added page.
  //paging is the type of page eviction stratagy where 0 is FIFO and 1 is LRU.
  //pagesize represents the size of any 1 page.
  //memoryPages is the number of pages for memory that the user requested
  //swapPages is the number of pages in swap that the user requested
 private:
  int recent_PCBID;
  LinkedList<PCB> PCB_list;
  LinkedList<Block> freeBlocks;
  int timeSlice;
  frameEntry* memFrameTable;
  frameEntry* swapFrameTable;
  int memFTSize;
  int swapFTSize;
  LinkedList<frameEntry> recentlyUsedPages;
  LinkedList<frameEntry> recentlyAddedPages;
  int paging;
  int pagesize;
  int memoryPages;
  int swapPages;

 public:
  //CONSTRUCTOR
  //PRE:
  //POST: creates an OS class
  OS(Block max_free, int ptimeSlice, int pPaging, int pPagesize,
       int numPagesMemory, int numPagesSwap);

  //ACCESSORS
  //PRE: this object must be defined
  //POST: RV =  the most recent ID given to a PCB object
  int getRecentPCBID() const;

  //PRE:
  //POST: RV = the timeslice the user defined in the config file
  int getTimeSlice() const;

  //PRE: this object must be defined
  //POST: RV = the integer representing the type of eviction stratagy
  int getPaging() const;

  //PRE: this object must be defined
  //POST: RV = the size of a single given page
  int getPageSize() const;

  //PRE: this object must be defined
  //POST: RV = the amount of frame entries in memory
  int getMemFTsize() const;

  //PRE: this object must be defined
  //POST: RV = the amount of frame entries in memory
  int getSwapFTsize() const;
    
  //PRE: this object must be defined
  //POST: RV = the current list of PCB objects
  LinkedList<PCB> getPCB_list() const;

  //PRE: this object must be defined
  //POST: RV = the list of free blocks
  LinkedList<Block> getFreeBlocks() const;
  
  //PRE:
  //POST: RV =  the frame table for memory
  frameEntry* getMemFrameTable() const;

  //PRE:
  //POST: RV =  the frame table for swapSpace
  frameEntry* getSwapFrameTable() const;

  //PRE:
  //POST: returns the list of recently used pages
  LinkedList<int> getRecentlyUsedPages() const;

  //PRE: 
  //POST: RV = the current PCB.
  PCB* getCurrPCB() const;
  
  //MODIFIERS
  //PRE: newFreeBlock must be a valid linked list of freeBlock
  //objects. This object must be defined
  //POST: modifies the list of free blocks s.t. this object's
  //free blocks are equal to newFreeBlock
  void setFreeBlocks(LinkedList<Block> newFreeBlock);

  //PRE: this object must be defined
  //POST: modifies the integer representing the type of eviction stratagy
  //s.t. it is equal to the type of eviction stratagy
  void setPaging(int pPaging);

  //PRE: this object must be defined
  //POST: modifies the set pagesize s.t. it equals pPageSize
  void setPageSize(int pPageSize);
  
  //PRE: This object must be defined
  //POST: pops the current process off the PCB list
  void popOffQueue();

  //PRE: this object must be defined
  //POST: pops the current process off the running queue and appends it to
  //the back of the running queue
  void roundRobin();

  //PRE: This object must be defined
  //POST: Modifies the timeSlice data object s.t. it is equal to pTimeSlice
  void setTimeSlice(int pTimeSlice);

  //PRE: This object must be defined
  //POST: RV =  a ptr to a frame table entry from FrameTable
  frameEntry* getFrameEntry(int PPN) const;

  //PRE: this object must be defined
  //POST: modifies the memFTsize s.t. it is equal to pMemTableSize
  void setMemFTsize(int pMemTableSize);

  //PRE: this object must be defined
  //POST: modifies the swapFTsize s.t. it is equal to pSwapTableSize
  void setSwapFTsize(int pSwapTableSize);
  
  //PRE: This object must be defined
  //POST: makes the frame table for memory equal to the frame table for
  //      pMemTable
  void setMemFrameTable(frameEntry* pMemTable);

  //PRE: This object must be defined
  //POST: makes the frame table for swapSpace equal to the frame table for
  //      pSwapTable
  void setSwapFrameTable(frameEntry* pSwapTable);

  //PRE:
  //POST: returns the list of recently used pages
  void setRecentlyUsedPages(LinkedList<int> pRecentlyUsedPages);
  
  //PRE: This object must be defined
  //POST: RV =  the VPN from the current PCB
  int getPPN(int VPN) const;

  //PRE: anEntry should be the frameEntry object found in either FIFO or LRU
  //     that is considered the victim page. incomingEntry should be the
  //     incoming page in the form of a frameEntry that is attempting to
  //     be put in memory.
  //POST: the page was either added to swap or an error has
  //        been printed to the OS
  void checkSwap(frameEntry anEntry, frameEntry incomingEntry);
  
  //PRE: canEvict must be initialized to false
  //POST: Evicts a page from the frame table of memory using the paging
  //      algorithm FIFO iff at least one of the pages is not dirty. OS
  //      contains an ERROR otherwise.
  void FIFO(bool & canEvict);
  
  //PRE: canEvict must be initialized to false
  //POST: Evicts a page from the frame table of memory using the paging
  //      algorithm LRU iff at least one of the pages is not dirty. OS
  //      contains an ERROR otherwise.
  void LRU(bool & canEvict);
  
  //PRE: memory must be full
  //POST: if all pages are not dirty and memory/swap are full evicts a page
  //      using the eviction stratagy represented by paging and returns a
  //      boolean that represents whether or not a page could be evicted or
  //      not.
  bool evictPage();
  
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

  //PRE: block should be the block you're adding/removing into/from memory.
  //when this is called with the intent to allocate space, the block must have,
  //gone through findSpace and be able to successfully be allocated.
  //locationBlock should be a block located in freemem that you are going
  //to modify
  //POST: modifies freeBlocks and Blocks to reflect the addition
  //of a block in memory
  Block handleChange(Block block, Block locationBlock);

  //PRE: block should be the block you're adding/removing into/from memory.
  //when this is called with the intent to allocate space, the block must have,
  //gone through findSpace and be able to successfully be allocated.
  //POST: Modifies the freeBlocks s.t. it reflects the addition of space back
  //to the system
  void dealocateContiguously(Block block);
  
  //PRE: 
  //POST: adds the PCB object into the running queue
  void addToQueue(PCB incomingPCB);

  //HANDLES
  //PRE: this object should be defined.
  //POST: RV contains a pointer to the PCBList that will make the OS contain
  //all the current jobs in the running queue
  //there are PCBs in the queue. If there is nothing in the queue
  LinkedList<PCB>* handleJobs();
  
  //PRE: PCB_ID should be the ID of the PCB object the user is trying
  //     to kill
  //POST: kills the current process if the PCB_ID is a valid
  //     ID and returns false. Otherwise, RV = false;
  bool handleKill(int PCB_ID);

  //PRE:
  //POST: OS contains the frame tables for memory and swap.
  void handlePages();

  //PRE: PID must be an integer
  //POST: OS contains the page table for the PID given if the PID is valid.
  //      error otherwise.
  void handlePages(int PID);
};
#endif
