#include "OS.h"
using namespace std;
//CONSTRUCTOR
//PRE:
//POST: creates an OS class
OS::OS(Block max_free, int pTimeSlice, int pPaging, int pPagesize,
       int numPagesMemory, int numPagesSwap){
  freeBlocks.append(max_free);
  recent_PCBID = 0;
  timeSlice = pTimeSlice;
  paging = pPaging;
  pagesize = pPagesize;
  memFTSize = 0;
  swapFTSize = 0;
  memFrameTable = new frameTable[numPagesMemory];
  swapFrameTable = new frameTable[numPagesSwap];
  memoryPages = numPagesMemory;
  swapPages = numPagesSwap;
}

//ACCESSORS
//PRE:
//POST: RV =  the most recent ID given to a PCB object
int OS::getRecentPCBID() const{
  return recent_PCBID;
}

//PRE:
//POST: RV = the timeslice the user defined in the config file
int OS::getTimeSlice() const{
  return timeSlice;
}

//PRE: this object must be defined
//POST: RV = the integer representing the type of eviction stratagy
int OS::getPaging() const{
  return paging;
}

//PRE: this object must be defined
//POST: RV = the size of a single given page
int OS::getPageSize() const{
  return pagesize;
}

//PRE:
//POST: RV = the current list of PCB objects
LinkedList<PCB> OS::getPCB_list() const{
  return PCB_list;
}

//PRE:
//POST: RV = the list of free blocks
LinkedList<Block> OS::getFreeBlocks() const{
  return freeBlocks;
}

//PRE:
//POST: RV = the current PCB.
PCB* OS::getCurrPCB() const{
  return PCB_list.getHead();
}
  
//MODIFIERS
//PRE: newFreeBlock must be a valid linked list of freeBlock
//objects. This object must be defined
//POST: modifies the list of free blocks s.t. this object's
//free blocks are equal to newFreeBlock
void OS::setFreeBlocks(LinkedList<Block> newFreeBlock){
  freeBlocks = newFreeBlock;
}

//PRE: This object must be defined
//POST: Modifies the timeSlice data object s.t. it is equal to pTimeSlice
void OS::setTimeSlice(int pTimeSlice){
  timeSlice = pTimeSlice;
}

//PRE: this object must be defined
//POST: modifies the integer representing the type of eviction stratagy
//s.t. it is equal to the type of eviction stratagy
void OS::setPaging(int pPaging){
  paging = pPaging;
}

//PRE: this object must be defined
//POST: modifies the set pagesize s.t. it equals pPageSize
void OS::setPageSize(int pPageSize){
  pagesize = pPageSize;
}

//PRE: 
//POST: RV =  a ptr to a frame table entry from FrameTable
frameEntry* OS::getFrameEntry(int PPN) const{
  int index = 1;//index is one because PCB unique IDs start at 1
  bool foundID = false;
  frameEntry* frameEntryPtr;
  while ((index <= PCB_list.getSize()) && (!foundID)){
    frameEntry* currentFrameEntry = frameTable.getNth(index-1);
    int currentFrameIndex = currentFrameEntry->getIndex();
    if (currentFrameIndex == PPN){
      frameEntryPtr = currentFrameEntry;
    }
    else{
      index++;
    }
  }
  //ASSERT: Either we have found the ID the user is looking for or we have
  //run through the entire queue and that ID did not exist
  if (!foundID){
    cout << "No PCB with that ID." << endl;
  }
  return frameEntryPtr;
}

//PRE:
//POST: RV =  the frame table for memory
frameEntry* OS::getMemFrameTable() const{
  return memFrameTable;
}

//PRE:
//POST: RV =  the frame table for swapSpace
frameEntry* OS::getSwapFrameTable() const{
  return swapFrameTable;
}

//PRE: this object must be defined
//POST: RV = the amount of frame entries in memory
int OS::getMemFTsize() const{
  return memFTsize;
}

//PRE: this object must be defined
//POST: RV = the amount of frame entries in memory
int OS::getSwapFTsize() const{
  return swapFTsize;
}
    
//PRE: 
//POST: RV =  the PPN from the current PCB
int OS::getPPN(int VPN) const{
  PCB* currPCB = PCB_list.getHead();
  int currPPN = currPCB.getPPN(VPN);
  return currPPN;
}

//PRE: This object must be defined
//POST: makes the frame table for memory equal to the frame table for
//      pMemTable
void OS::setMemFrameTable(frameEntry* pMemTable){
  memFrameTable = pMemTable;
}

//PRE: This object must be defined
//POST: makes the frame table for swapSpace equal to the frame table for
//      pSwapTable
void OS::setSwapFrameTable(frameEntry* pSwapTable){
  swapFrameTable = pSwapTable;
}

//PRE: this object must be defined
//POST: modifies the memFTsize s.t. it is equal to pMemTableSize
void OS::setMemFTsize(int pMemTableSize){
  memFTsize = pMemTableSize;
}

//PRE: this object must be defined
//POST: modifies the swapFTsize s.t. it is equal to pSwapTableSize
void OS::setSwapFTsize(int pSwapTableSize){
  swapFTsize = pSwapTableSize;
}

//PRE: anEntry should be the frameEntry object found in either FIFO or LRU
//     that is considered the victim page. incomingEntry should be the
//     incoming page in the form of a frameEntry that is attempting to
//     be put in memory.
//POST: the page was either added to swap or an error has
//        been printed to the OS
void OS::checkSwap(frameEntry anEntry, frameEntry incomingEntry){
  //Since all entries in swap are already dirty, I only need
  //to check whether the incoming page is equal to an entry in
  //swap.
  if (!(swapFTsize == swapPages)){
    //ASSERT: swap is not full
    bool existsOnSwap = false;
    while ((index < swapFTsize) && (!existsOnSwap)){
      if(anEntry == swapFrameTable[index]){
	//ASSERT: this entry exists on swap space already
	existsOnSwap = true;
	frameTable temp = swapFrameTable[index];
	swapFrameTable[index] = anEntry;
	anEntry = temp;
      }
    }
    swapFrameTable[swapFTsize + 1] = anEntry;
  else{
    //ASSERT: swap is full
    
  int index = 0;
  while (index < swapFTsize){
    
  //if(true){
  //swap the places of the 2 entries using the temp method where
  //I create a temporary frame entry, set that equal to one of the
  //entries set the non chosen one equal to the chosen one and set,
  //the non chosen one to temp.
  //if(!true){
  //check if swap is full
  //if(full){
  //cout << "Insufficient memory to load a program" << endl;
  //}
  //if(!full){
  //add to the latest freespace in stack
  //Also swapFTsize++;
  //}
  //}
}
//PRE: canEvict must be initialized to false
//POST: Evicts a page from the frame table of memory using the paging
//      algorithm FIFO iff at least one of the pages is not dirty. OS
//      contains an ERROR otherwise.
void OS::FIFO(bool & canEvict){
  int index = recentlyAddedPages.getSize();
  while ((index > 0) && (!done)){
    frameEntry* currEntry = recentlyAddedPages.getNth(index);
    int memIndex = 0;
    while (memIndex < memoryPages){
      if(*currEntry == memFrameTable[memIndex]){
	//ASSERT: we found the recentlyUsedPage that represents the
	//        entry found in the recentlyUsedPage
	if (currEntry.getDirty() == false){
	  //we found a page hat we can evict
	  canEvict = true;
	  done = true;
	  checkSwap();
	  //ASSERT: the page was either added to swap or an error has
	  //        been printed to the OS
	}
      }
      memIndex++;
    }
    index--;
  }
  //ASSERT: we found a page that wasnt dirty or we went through the array and
  //couldn't find a page that wasn't drty 
  if(!canEvict){
    cout << "Insufficient memory to load a program" << endl;
  }
}

//PRE: canEvict must be initialized to false
//POST: Evicts a page from the frame table of memory using the paging
//      algorithm LRU iff at least one of the pages is not dirty. OS
//      contains an ERROR otherwise.
void OS::LRU(bool & canEvict){
  int index = recentlyUsedPages.getSize();
  while ((index > 0) && (!done)){
    frameEntry* currEntry = recentlyUsedPages.getNth(index);
    int memIndex = 0;
    while (memIndex < memoryPages){
      if(*currEntry == memFrameTable[memIndex]){
	//ASSERT: we found the recentlyUsedPage that represents the
	//        entry found in the recentlyUsedPage
	if (currEntry.getDirty() == false){
	  //we found a page we can evict
	  canEvict = true;
	  done = true;
	  checkSwap();
	  //ASSERT: the page was either added to swap or an error has
	  //        been printed to the OS
	}
      }
      memIndex++;
    }
    index--;
  }
  //ASSERT: we have either checked every recentlyUsedPage or we have found a
  //page that wasn't dirty
}

//PRE: memory must be full
//POST: if all pages are not dirty and memory/swap are full evicts a page
//      using the eviction stratagy represented by paging and returns a
//      boolean that represents whether or not a page could be evicted or
//      not.
bool OS::evictPage(){
  bool canEvict = false; //true iff we can evict a page
  if (paging == 0){
    FIFO(canEvict);
    //ASSERT: A page has been evicted using this paging stratagy or
    //we could not evict a page due to all of the pages being dirty and
    //an error has been outputted to the OS.
  }
  else{
    LRU(canEvict);
    //ASSERT: A page has been evicted using this paging stratagy or
    //we could not evict a page due to all of the pages being dirty and
    //an error has been outputted to the OS.
  }
  
  return canEvict;
}


//PRE: this object is defined. fitType is a 0 or 1 dependant on whether
//the memory management is first fit or best fit respectively. program&stack
//represent the relative program & stack locations.
//POST: finds space in memory if it cant returns foundSpace as false
//      if it did, returns found space as true. Also modifies
//      newProg/newStack s.t. they contain the actual addresses of the
//      prog/stack they represent
bool OS::findSpace(int fitType, Block program,
		   Block stack, Block & newProg, Block & newStack){
  bool foundSpace = true;
  Block progTempBlock; //Will hold where stack block was allocatted
  try{
    allocateSpace(fitType, program.getSize(), program, newProg,
		  progTempBlock);
    //throws exception
  }
  catch (Exception e){
    //ASSERT: we could not find space for the progBlock
    foundSpace = false;
    e.handle();
  }
  if(foundSpace){
    try{
      Block stackTempBlock; //Will hold where stack block was allocatted
      allocateSpace(fitType, stack.getSize(), stack, newStack,
		    stackTempBlock);
      //throws exception
      //ASSERT: if exception is thrown, tempBlock is not modified
    }
    catch (Exception e){
      //ASSERT: we could not find space for the stack block but I could
      //Find space for the prog block
      foundSpace = false;
      deallocateSpace(progTempBlock);
      //deallocated program's space
      e.handle();
    }
  }
  return (foundSpace);
}

//PRE: this object is defined. Location block
//should be a Block object with the exact start and end of where Block
//was allocated in memory
//POST: undos the allocation of the Block just added to freemem
void OS::deallocateSpace(Block locationBlock) {
  Block nonLocationBlock; //a meaningless block here to mearely satisfy
                          //the number of parameters
  dealocateContiguously(locationBlock);
}

  
//PRE: this object is defined. the parameters here follow the pre of the
//member function "find space" located within this file 
//POST: Actually tries to fit the block in memory using one of the fit
//method types. If it cant, throws an error to be handled in find space
//      tempBlock should be the location in freemem,
//      that block was allocated (if allocated)
//      newBlock shuld now be the ACTUAL start & end that the block takes up
//      in free mem
void OS::allocateSpace(bool fitType, int progSize, Block & block,
		       Block & newBlock, Block & tempBlock) {
  bool success = false;
  if (fitType){
    bestFit(progSize, success, block, newBlock, tempBlock);
    if (!success){
      throw(Exception((char*)"ERROR: there is not enough space"));
    }
  }
  else {
    firstFit(progSize, success, block, newBlock, tempBlock);
    if (!success){
      throw(Exception((char*)"ERROR: there is not enough space"));
    }
  }
}

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
void OS::firstFit(int size, bool & success, Block & block, Block & newBlock,
		  Block & tempBlock) {
  int index = 0;
  Block firstFree;
  while ((index < freeBlocks.getSize()) && (!success)) {
    Block* currBlock = freeBlocks.getNth(index);
    //ASSERT: currBlock holds the freeBlock that we are testing to see if
    //block can fit in
    if (size <= currBlock->getSize()) {
      success = true;
      firstFree.setStart(currBlock->getStart());
      firstFree.setEnd(firstFree.getStart() + size);
      newBlock.setStart(firstFree.getStart());
      newBlock.setEnd(firstFree.getEnd());
      tempBlock = handleChange(block, *currBlock);
      //handle the change in memory
    }
    index++;
  }
}

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
void OS::bestFit(int size, bool & success, Block & block, Block & newBlock,
		 Block & tempBlock) {
  int index = 0;
  Block* currBlock = freeBlocks.getNth(index);
  Block best = *currBlock;
  while (index < freeBlocks.getSize()) {
    Block* currBlock = freeBlocks.getNth(index);
    if (size <= currBlock->getSize()) {
      if (size <= best.getsize()){
	best.setStart(currBlock->getStart());
	best.setEnd(best.getStart() + size);
	newBlock.setStart(best.getStart());
	newBlock.setEnd(best.getEnd());
	success = true;
      }
    }
    index++;
  }
  //ASSERT: best is now the best of the best spaces
  tempBlock = handleChange(newBlock, best);
  //handle the change in memory
}

//PRE: block should be the block you're adding/removing into/from memory.
//when this is called with the intent to allocate space, the block must have,
//gone through findSpace and be able to successfully be allocated.
//locationBlock should be a block located in freemem that you are going
 //to modify
//POST: modifies freeBlocks and Blocks to reflect the addition
//of a block in memory
Block OS::handleChange(Block block, Block locationBlock){
  Block tempBlock; //will hold the location in freeBlocks where
  //the block was allocated
  //Allocate space
  int index = 0;
  bool done = false; //will turn true once we've found the location block in
  //freeBlocks
  while(!done){
    Block* freeStatus = freeBlocks.getNth(index);
    if (*freeStatus == locationBlock){
      done = true;
    }
    else{
      index++;
    }
  }
  //ASSERT: index is the index of the block equal to location block
    
  Block* freeLocationBlock = freeBlocks.getNth(index);
  //will hold a block from freeBlocks equal to locationBlock
  int blockSize = block.getSize();
  int freeBlockSize = freeLocationBlock->getSize();
  if (blockSize == freeBlockSize){
    /*ASSERT: the incoming block is using up the entirety of
      freeLocationBlock*/
    freeBlocks.deleteNth(index);
  }
    
  else{
    int freeLocationStart = freeLocationBlock->getStart();
    int blockSize = block.getSize();
    tempBlock.setStart(freeLocationStart);
    freeLocationStart += blockSize + 1;
    freeLocationBlock->setStart(freeLocationStart);
    //ASSERT: freeLocation's new start is freeLocationStart + blockSize;
    tempBlock.setEnd(freeLocationBlock->getEnd() - 1);
    //Allocated freemem's space
    //ASSERT: tempBlock now carries the exact start and end of the
    //block that was added.
  }
    
  return tempBlock;
}

//PRE: block should be the block you're adding/removing into/from memory.
//when this is called with the intent to allocate space, the block must have,
//gone through findSpace and be able to successfully be allocated.
//POST: Modifies the freeBlocks s.t. it reflects the addition of space back
//to the system
void OS::dealocateContiguously(Block block){
  bool done = false;
  int index = 0;
  while(!done){
    Block* currentFreeBlock = freeBlocks.getNth(index);
    if (index == 0){
      //ASSERT: we are at the begining of the list
      //ASSERT: [block][currentFreeBlock]
      if (block.getEnd() < currentFreeBlock->getStart()){
	done = true;
	//We've found the place where block belongs
	if (block.getEnd() == (currentFreeBlock->getStart() - 1)){
	  //ASSERT: [block][currentFreeBlock]
	  //ASSERT: The block we are inserting into freeBlocks is
	  //contiguous with the next block
	  Block contiguousBlock;
	  contiguousBlock.setStart(block.getStart());
	  contiguousBlock.setEnd(currentFreeBlock->getEnd());
	  //ASSERT: the block that represents the contiguous block
	  //of currentFreeBlock and block has been created
	  freeBlocks.insertBefore(*currentFreeBlock, contiguousBlock);
	  //ASSERT: freeBlocks looks like some form of the following
	  //    ...[block][contiguousBlock][currentFreeBlock]...
	  freeBlocks.deleteNth(index+1);
	  //Deletes the currentFreeBlock
	}
	else{
	  //ASSERT not contiguous but in right spot
	  freeBlocks.insertBefore(*currentFreeBlock, block);
	}
      }
      else{
	//block is greater and doesnt belong at the start
      }
    }
    else if (index == freeBlocks.getSize()){
      done = true;
      //we are at the end of the freeBlockList
      //ASSERT: [currentFreeBlock][block]
      if (block.getStart() == (currentFreeBlock->getEnd() + 1)){
	//ASSERT: The block we are inserting into freeBlocks is
	//contiguous
	Block contiguousBlock;
	contiguousBlock.setStart(block.getStart());
	contiguousBlock.setEnd(currentFreeBlock->getEnd());
	//ASSERT: the block that represents the contiguous block
	//of currentFreeBlock and block has been created
	freeBlocks.insertAfter(*currentFreeBlock, contiguousBlock);
	//ASSERT: freeBlocks looks like some form of the following
	//    ...[block][contiguousBlock][currentFreeBlock]...
	freeBlocks.deleteNth(index-1);
	//Deletes the currentFreeBlock
	done = true;
      }
      else{
	//block is greater than everything else in freeBlocks and
	//belongs in the end
	freeBlocks.append(block);
      }
    }
    else {
      //ASSERT: block is neither at the beginning nor end
      //ASSERT: [previousFreeBlock]
      //        <some distance>
      //        [block]
      //        <some distance>
      //        [currentFreeBlock]
      Block* previousFreeBlock = freeBlocks.getNth(index - 1);
      if (block.getEnd() < currentFreeBlock->getStart()){
	//We've found the place where block belongs
	if ((block.getEnd() == (currentFreeBlock->getStart() - 1)) &&
	    (block.getStart() != (previousFreeBlock->getEnd() + 1))){
	  //ASSERT: [previousFreeBlock]...[block][currentFreeBlock]
	  //ASSERT: The block we are inserting into freeBlocks is
	  //contiguous with only the next block
	  Block contiguousBlock;
	  done = true;
	  contiguousBlock.setStart(block.getStart());
	  contiguousBlock.setEnd(currentFreeBlock->getEnd());
	  //ASSERT: the block that represents the contiguous block
	  //of currentFreeBlock and block has been created
	  freeBlocks.insertBefore(*currentFreeBlock, contiguousBlock);
	  //ASSERT: freeBlocks looks like some form of the following
	  //    ...[block][contiguousBlock][currentFreeBlock]...
	  freeBlocks.deleteNth(index+1);
	  //Deletes the currentFreeBlock
	  done = true;
	}
	else if ((block.getStart() == (previousFreeBlock->getEnd() + 1))&&
		 (block.getEnd() != (currentFreeBlock->getStart() - 1))){
	  //ASSERT: The block we are inserting into freeBlocks is
	  //contiguous with only the previous
	  //ASSERT: [previousFreeBlock][block]...[currentFreeBlock]
	  Block contiguousBlock;
	  done = true;
	  contiguousBlock.setStart(previousFreeBlock->getStart());
	  contiguousBlock.setEnd(block.getEnd());
	  //ASSERT: the block that represents the contiguous block
	  //of currentFreeBlock and block has been created
	  freeBlocks.insertAfter(*previousFreeBlock, contiguousBlock);
	  //ASSERT: freeBlocks looks like some form of the following
	  //    ...[currentFreeBlock][contiguousBlock]...
	  freeBlocks.deleteNth(index-1);
	  //Deletes currentFreeBlock
	}
	else if ((block.getStart() == (previousFreeBlock->getEnd() + 1)) &&
		 (block.getEnd() == (currentFreeBlock->getStart() - 1))){
	  //ASSERT: The block we are inserting into freeBlocks is
	  //contiguous with the block next to it and behind it
	  //ASSERT: [previousFreeBlock][block][currentFreeBlock]
	  done = true;
	  Block contiguousBlock;
	  contiguousBlock.setStart(previousFreeBlock->getStart());
	  contiguousBlock.setEnd(currentFreeBlock->getEnd());
	  //ASSERT: the block that represents the contiguous block
	  //of currentFreeBlock and block has been created
	  freeBlocks.insertAfter(*previousFreeBlock, contiguousBlock);
	  //ASSERT: freeBlocks looks like some form of the following
	  //    ...[currentFreeBlock][contiguousBlock][block]...
	  freeBlocks.deleteNth(index+1);
	  //Deletes currentFreeBlock
	  freeBlocks.deleteNth(index-1);
	  //Deletes previousFreeBlock
	  done = true;
	}
	else{
	  //ASSERT: block is not contiguous but it's in the right
	  //place
	  done = true;
	  freeBlocks.insertBefore(*currentFreeBlock, block);
	}
	//ASSERT: we have handeled the block
      }
      else{
	//block must be greater than the next block and doesnt belong
      }
      //handled when it's neither at the beggining nor the end
    }
    //ASSERT: handled whether the block is at the beginning, middle,
    //or end
    index++;
  }
  //Deallocated
}

//PRE: this object must be defined
//POST: adds the PCB object into the running queue
void OS::addToQueue(PCB incomingPCB){
  PCB_list.append(incomingPCB);
  recent_PCBID++;
}
//PRE: This object must be defined
//POST: deletes the first thing off the list
void OS::popOffQueue(){
  PCB* deletedPCB = PCB_list.getHead();
  int deletedPCBsID = deletedPCB->getProcessID();
  handleKill(deletedPCBsID);
}

//PRE: this object must be defined
//POST: pops the current process off the running queue and appends it to
//the back of the running queue
void OS::roundRobin(){
  PCB* tempPCB = PCB_list.getHead();
  PCB_list.append(tempPCB);
}
//HANDLES
//PRE: this object should be defined. 
//POST: RV contains a pointer to the PCBList that will make the OS contain
  //all the current jobs in the running queue
LinkedList<PCB>* OS::handleJobs(){
  LinkedList<PCB>* currPCBList = new LinkedList<PCB>;
  *currPCBList = PCB_list;
  return currPCBList;
}
//PRE: PCB_ID should be the ID of the PCB object the user is trying
//     to kill
//POST: kills the current process if the PCB_ID is a valid
//     ID and returns false. Otherwise, RV = false;
bool OS::handleKill(int PCB_ID){
  int index = 1;//index is one because PCB unique IDs start at 1
  bool foundID = false;
  while ((index <= PCB_list.getSize()) && (!foundID)){
    PCB* currentPCB = PCB_list.getNth(index-1);
    int currentPCBID = currentPCB->getProcessID();
    if (currentPCBID == PCB_ID){
      //ASSERT: we've found the ID the user is looking to kill
      cout << "killing PCB with PCB_ID: " << PCB_ID << endl;
      foundID = true;
      PCB* deletedPCB = PCB_list.getNth(index-1);
      //ASSERT: deletedPCB is the PCB with the ID PCB_ID
      Block deletedProgBlock;
      Block deletedStackBlock;
      deletedProgBlock.setStart(deletedPCB->getStartingAddressProg());
      deletedProgBlock.setEnd(deletedPCB->getEndingAddressProg());
      deletedStackBlock.setStart(deletedPCB->getStartingAddressStack());
      deletedStackBlock.setEnd(deletedPCB->getEndingAddressStack());
      Block nonLocationBlock; //a meaningless block here to mearely satisfy
                              //the number of parameters
      dealocateContiguously(deletedProgBlock);
      dealocateContiguously(deletedStackBlock);
      //ASSERT: deallocated the space this PCB was taking in memory
      PCB_list.deleteNth(index-1);
    }
    else{
      index++;
    }
  }
  //ASSERT: Either we have found the ID the user is looking for or we have
  //run through the entire queue and that ID did not exist
  return foundID;
}

//PRE:
//POST: OS contains the frame tables for memory and swap.
void OS::handlePages(){
  cout << "physical: " << memFrameTable << endl;
  cout << "swap: " << swapFrameTable << endl;
}

//PRE: PID must be an integer
//POST: OS contains the page table for the PID given if the PID is valid.
//      error otherwise.
void OS::handlePages(int PID){
  int index = 1;//index is one because PCB unique IDs start at 1
  bool foundID = false;
  while ((index <= PCB_list.getSize()) && (!foundID)){
    PCB* currentPCB = PCB_list.getNth(index-1);
    int currentPCBID = currentPCB->getProcessID();
    if (currentPCBID == PID){
      LinkedList<pageTable> currPageTable= currentPCB.getPageTable();
      cout << currPageTable << endl;
    }
    else{
      index++;
    }
  }
  //ASSERT: Either we have found the ID the user is looking for or we have
  //run through the entire queue and that ID did not exist
  if (!foundID){
    cout << "No PCB with that ID." << endl;
  }
}
