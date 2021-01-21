/* Simulator Class     Multi      */

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "Simulator.h"
using namespace std; 


//==================================================================
// Constructors
//==================================================================

// PRE: requestedMemory > 0 
// POST: PC = 0, numWords = requestedMemory, sim_registers holds number
//         of registers equal to MAX_REGISTERS, memory holds number
//         of unsigned ints equal to requestedMemory, halt = false
//         programSize = 0
Simulator::Simulator(int requestedMemory, int pStackSize, int pFitType){
  PC = 0;
  numWords = requestedMemory;
  memorySize = 0;
  numStackSize = pStackSize;
  memory = new unsigned int[requestedMemory];
  stackSize = new unsigned int[pStackSize];
  fitType = pFitType;
  // create and append all register objects to sim_registers
  for(int index = 0; index < MAX_REGISTERS; index++) {
    const char* new_name = registers[index];
    MyString new_name_string(new_name);
    Register new_register(new_name_string, 0);
    if (index == 13){
      // ASSERT: this is $sp
      new_register.setValue((numWords * BYTE) - BYTE); 
    } 
    sim_registers.append(new_register);
  }
  halt = false;
  programSize = 0;
  programLoaded = false; 
}

// copy constructor
// PRE: S is defined.
// POST: This object is defined and is a deep copy of S.
Simulator::Simulator(const Simulator & S) {
  PC = S.getPC();
  numWords = S.memSize();
  memory = new unsigned int[numWords];
  // get deep copy of memory
  for (int index = 0; index < numWords; index ++){
    memory[index] = S.getWord(index); 
  }
  
  stackSize = new unsigned int[numWords];
  // get deep copy of stackSize
  for (int index = 0; index < numWords; index ++){
    stackSize[index] = S.getStackWord(index); 
  }
  sim_registers = S.getRegisters(); // get deep copy of registers
  halt = S.haltStatus();
  programLoaded = S.loadStatus();
  programSize = S.getProgramSize();
  fitType = S.getFitType();
  memorySize = S.getMemorySize();
}

//assignment operator
// PRE: S is defined.
// POST: This object is defined and is a deep copy of S.
Simulator & Simulator::operator= (const Simulator & S) {
  PC = S.getPC();
  numWords = S.memSize();
  memory = new unsigned int[numWords];
  // get deep copy of memory
  for (int index = 0; index < numWords; index ++){
    memory[index] = S.getWord(index); 
  }
  stackSize = new unsigned int[numWords];
  // get deep copy of stackSize
  for (int index = 0; index < numWords; index ++){
    stackSize[index] = S.getStackWord(index); 
  }
  sim_registers = S.getRegisters(); // get deep copy of registers
  halt = S.haltStatus();
  programLoaded = S.loadStatus();
  programSize = S.getProgramSize();
  fitType = S.getFitType();
  memorySize = S.getMemorySize();
}

// ======================================== 
// destructor
// ======================================== 
  
// PRE: This object is defined.
// POST: Heap space allocated to this program freed
Simulator::~Simulator() {
  delete [] memory;
  delete [] stackSize;
}

//==================================================================
// Accessors
//==================================================================
  
// PRE:
// POST: returns value of PC
int Simulator::getPC() const {
  return PC;
}

//PRE:
//POST: returns the stackSize
unsigned int* Simulator::getStackSize() const{
  return stackSize;
}

// PRE:
// POST: returns numWords
int Simulator::memSize() const {
  return numWords;
}

// PRE:
// POST: returns memorySize
int Simulator::getMemorySize() const {
  return memorySize;
}

//PRE:
//POST: returns the fitType
int Simulator::getFitType() const {
  return fitType;
}

// PRE:
// POST: returns memory 
unsigned int* Simulator::getMemory() const {
  return memory;
}

// PRE: index < numWords
// POST: returns unsigned int located at
//       index in memory
unsigned int Simulator::getWord(int index) const {
  return memory[index];
}

// PRE: index < numStackWords
// POST: returns unsigned int located at
//       index in stackSize
unsigned int Simulator::getStackWord(int index) const {
  return stackSize[index];
}

// PRE:
// POST: returns sim_registers
LinkedList<Register> Simulator::getRegisters() const {
  return sim_registers; 
}

// PRE: index < MAX_REGISTERS
// POST: returns pointer to Register object at location
//       index in sim_registers
Register* Simulator::getRegister(int index) const {
  return sim_registers.getNth(index);
}

// PRE:
// POST: returns halt
bool Simulator::haltStatus() const {
  return halt;
}

// PRE:
// POST: return programLoaded
bool Simulator::loadStatus() const {
  return programLoaded; 
}

// PRE: programLoaded = true 
// POST: return programSize
int Simulator::getProgramSize() const {
  return programSize;
}

//==================================================================
// Modifiers
//==================================================================

// PRE:
// POST: sets PC equal to newPC
void Simulator::updatePC(int newPC){
  PC = newPC;
}

// PRE:
// POST: sets PC equal to PC + BYTE
void Simulator::incrementPC(){
  PC = PC + BYTE;
}

// PRE: program has been successfully loaded into memory
//      halt = false
// POST: RV = true iff there was an error executing one of the opcodes
//       current word, say W = memory[PC/BYTE]
//       determines operand located in W[0]
//       PC = PC + BYTE
//       calls corresponding helper function
bool Simulator::executeNext(){
  unsigned int currentWord = memory[PC/BYTE];
  int opcode = getNibble(currentWord, 0);
  incrementPC();
  bool error = false; 
  if (opcode == 0){
    // ASSERT: opcode is ADD
    executeAdd(currentWord); 
  }
  else if (opcode == 1){
    // ASSERT: opcode is NAND
    executeNand(currentWord);
  }
  else if (opcode == 2){
    // ASSERT: opcode is ADDI
    executeAddi(currentWord); 
  }
  else if (opcode == 3){
    // ASSERT: opcode is LW
    error = executeLw(currentWord);
  }
  else if (opcode == 4){
    //ASSERT: opcode is SW
    error = executeSw(currentWord);
  }
  else if (opcode == 5){
    // ASSERT: opcode is BEQ
    executeBeq(currentWord);
  }
  else if (opcode == 6){
    // ASSERT: opcode is JALR
    executeJalr(currentWord);
  }
  else if (opcode == 7){
    // ASSERT: opcode is HALT
    halt = true;
  }
  else if (opcode == 9){
    // ASSERT: opcode is IN
    executeIn(currentWord);
  }
  else if (opcode == 10){
    // ASSERT: opcode is OUT
    executeOut(currentWord);
  }
  else if (opcode == 12){
    // ASSERT: opcode is LA
    executeLa(currentWord);
  }
  else if (opcode == 13){
    // ASSERT: opcode is BGT
    executeBgt(currentWord);
  }
  return error; 
}

//==================================================================
// Shell Commands
//==================================================================

// PRE: fileName, say f, is defined
// POST: if f refers to file, file holds n chars and 
//       if n/BYTE + DEFAULT_STACK <= numWords
//         then decode ascii chars into bytes,
//         each set of 8 bytes placed into an unsigned int
//         all unsigned ints placed into memory
//         return true
//       else return false
bool Simulator::handleLoad(char* fileName, OS & myOS){
  bool loadError = true;
  MyString trueFileName(fileName);
  trueFileName.addchar('.');
  trueFileName.addchar('l');
  trueFileName.addchar('c');
  trueFileName.addchar('e');
  char* trueFileNameString = trueFileName.getstring();
  ifstream file(trueFileNameString);
  if (file != NULL) {
    //ASSERT: valid file name
    int numLines = countBinLines(file);
    file.close();
    if ((numLines + numStackSize) <= numWords){
      // ASSERT: this program will fit into memory
      handleLoadHelper(trueFileNameString);
      // ASSERT: load completed
      PC = 0; // set PC back to 0
      halt = false; // set halt to false 
      for(int index = 0; index < MAX_REGISTERS; index ++) {
	// set all registers to 0 
	Register currRegister = *sim_registers.getNth(index);
	currRegister.setValue(0);
	sim_registers.update(index, currRegister); 
      }
      loadError = false;
      programLoaded = true;
      programSize = numLines;
      
      // LinkedList<PCB> runningQueue = myOS.getPCB_list();
      // int runningQueueSize = runningQueue.getSize();
      // if (runningQueueSize == 0){
      Block progBlock;
      progBlock.setStart(0);
      progBlock.setEnd(programSize);
      //The block representing the amount of RAM the program block
      //is taking up has been created
      Block stackBlock;
      stackBlock.setStart(0);
      stackBlock.setEnd(numStackSize);
      //The block representing the amount of RAM the stack block
      //is taking up has been created
      Block findProgBlock = progBlock;
      Block findStackBlock = stackBlock;
      bool foundSpace = myOS.findSpace(fitType, progBlock,
				       stackBlock, findProgBlock,
				       findStackBlock);
      if (foundSpace){
	//ASSERT: There was enough space => we can actually allocate the
	//        blocks without fail
	int curr_ID = myOS.getRecentPCBID();
	curr_ID += 1;//make the current ID unique
	PCB currPCB(0, fileName, findProgBlock, findStackBlock,
		    curr_ID, sim_registers);
	myOS.addToQueue(currPCB);
	//ASSERT: The currPCB object has been added to the run queue
      }
      else{
	//ASSERT: there was not enough space
	//found space couts an error => this else contains nothing
      }
    }
  }

  else{
    programLoaded = false;
    loadError = false;
  }
  return loadError;
}

// PRE:
// POST: returns unsigned int* block 
//         first word in block is located at memory[0]
//         last word in block is located at memory[memSize]
//         all words between these words in memory appear in the same
//           order in block
void Simulator::handleMem(){
    int index = 0;
    while (index < memorySize * BYTE){
      unsigned int currentWord = memory[index / BYTE];
      printf("%#08x\n", currentWord);
      index = index + BYTE;
    }
}

// PRE: start, end are non-negative integers
// POST: returns a boolean that represents whether the given parameters
//are actual memory addresses
//         first word in block is located at memory[start/4]
//         last word in block is located at memory[memSize]
//         all words between these words in memory appear in the same
//           order in block.
bool Simulator::handleMem1arg(int start){
  bool canHanleMem = false;
  if(start % NEXTWORD == 0){
    if (start < memorySize * BYTE){
      canHanleMem = true;
      while (start < memorySize * BYTE){
	unsigned int currentWord = memory[start / BYTE];
	printf("%#08x\n", currentWord);
	start = start + BYTE; 
      }
    }
  }
  return canHanleMem;
}

// PRE: start, end are non-negative integers
//      start and end are byte addresses (divisible by 4)
// POST: returns a boolean that represents whether the given parameters
//       are actual memory addresses
//         first word in block is located at memory[start/BYTE]
//         last word in block is located at memory[end/BYTE]
//         all words between these words in memory appear in the same
//           order in block
bool Simulator::handleMem2arg(int start, int end){
  bool canHanleMem = false;
  if((start % NEXTWORD == 0) && (end % NEXTWORD == 0)){
    if ((start < memorySize * BYTE) && (end <= memorySize * BYTE) &&
	(start >= 0) && (end >= 0)){
      canHanleMem = true;
      while (start <= end){
	unsigned int currentWord = memory[start / BYTE];
	printf("%#08x\n", currentWord);
	start = start + BYTE; 
      }
    }
  }
  return canHanleMem;
}


// PRE: myOS must be defined. conCPU must be initialized to false.
// POST: OS contains the ID of the current PCB and the status of the
//       registers of the current program iff a program is loaded.
LinkedList<Register> Simulator::handleCpu(OS & myOS){
  PCB* curr_PCBptr = myOS.getCurrPCB();
  LinkedList<Register> currPCBRegisters = curr_PCBptr->getRegisters();
  return currPCBRegisters;
}

// PRE: numSteps > 0
//      load has successfully loaded a file into memory
//      halt = false
// POST: executes number of lines of code in memory
//         <= requestedSteps (if halt is reached no more before numSteps
//         lines executed then no more executions will occur)
//       if no runtime error occured return true
//       else return false 
bool Simulator::handleStep(int requestedSteps, OS & myOS){
  int steps = 0;
  int userTimeSlice = myOS.getTimeSlice();
  
  bool error = false;
  
  PCB* curr_PCBptr = myOS.getCurrPCB();
  PC = curr_PCBptr->getRelativePC();
  
  LinkedList<Register> currPCBRegisters = curr_PCBptr->getRegisters();
  sim_registers = currPCBRegisters;
  //ASSERT: sim_registers has been overwritten with the registers stored
  //within the current PCB
  LinkedList<PCB> runningQueue = myOS.getPCB_list();
  int RQsize = runningQueue.getSize();
  if(RQsize > 0){
    //ASSERT: There is still another program to run
    halt = false;
  }
  while ((steps < requestedSteps) && (!halt) && (!error)){
    int currSliceOfTime = 0;
    curr_PCBptr = myOS.getCurrPCB();
    PC = curr_PCBptr->getRelativePC();
  
    currPCBRegisters = curr_PCBptr->getRegisters();
    sim_registers = currPCBRegisters;
  
    //ASSERT: sim_registers has been overwritten with the registers stored
    //within the current PCB
    LinkedList<PCB> runningQueue = myOS.getPCB_list();
    int RQsize = runningQueue.getSize();
    if(RQsize > 0){
      //ASSERT: There is still another program to run
      halt = false;
    }
  
    while ((currSliceOfTime < userTimeSlice) && (!halt) && (!error)) {
      error = executeNext();
      currSliceOfTime++;
    }
    //ASSERT: we have either hit a halt, error, or we simply finished the
    //        time slice
    
    int relativePC = curr_PCBptr->getRelativePC();
    relativePC = PC;
    //ASSERT: relativePC is now the number of bytes that have been stepped
    curr_PCBptr->setRelativePC(relativePC);
    if (halt){
      cout << "program has halted" << endl;
      myOS.popOffQueue();
      if (runningQueue.getSize() > 0){
	//there's another program in the running queue
	PCB* nextProgram = runningQueue.getHead();
	for(int index = 0; index < MAX_REGISTERS; index++) {
	  Register* currRegister = sim_registers.getNth(index);
	  currRegister->setValue(0);
	} 
	//ASSERT: all registers have been reset to zero
	
	PC = nextProgram->getStartingAddressProg();
	//ASSERT: PC of the CPU has been set to the starting address of the new
	//process in memory
      }
    }
    else if((currSliceOfTime >= userTimeSlice) && (runningQueue.getSize() > 0)){
      //ASSERT: The process did not halt, but has reached the end of it's
      //slice of time
      curr_PCBptr->setRegisters(sim_registers);
      //ASSERT: all registers (barring stack pointer) have been reset to zero
      myOS.roundRobin();
      //there's another program in the running queue
      PCB* nextProgram = runningQueue.getHead();
      //ASSERT: Nextprogram is a pointer to the PCB representing the
      //process that is ready to run
      PC = nextProgram->getStartingAddressProg();
      //ASSERT: PC of the CPU has been set to the starting address of the new
      //process in memory
      
      //The program at index 1 of the running queue has been moved to the
      //front of the running queue
    }
    else{
      //ASSERT: Hasn't halted, possibly errored, there is not another item
      //to timeslice
      if(error){
      programLoaded = false;
      }
    }
    //ASSERT: we have finished executing this step
    steps ++;
  }
  return error; 
}
  
//==================================================================
// Assembly Instructions
//==================================================================

// ASSEMBLY INSTRUCTION DOCUMENTATION NOTES: 
//   Bytes are reffered to in words in the format Word[index] 
//   Byte indices in this documentation are big-endian
  
// PRE: load has successfully loaded a file into memory
//      halt = false
// POST: Current word = memory[(PC-BYTE)/BYTE], say W
//       RegisterX = W[1], RegisterY = W[2], RegisterZ = W[7]
//       find sum of RegisterY.value + RegisterZ.value to get S
//       store S in RegisterX.value
void Simulator::executeAdd(unsigned int & currentWord){
  int indexRegX = getNibble(currentWord, 1);
  int operand2 = 2;
  int operand3 = 7;
  if (!indexRegX == 0) {
    // ASSERT: registerX is not $zero
    int indexRegY = getNibble(currentWord, operand2);
    int indexRegZ = getNibble(currentWord, operand3); 
    Register registerX = *sim_registers.getNth(indexRegX);
    Register registerY = *sim_registers.getNth(indexRegY);
    Register registerZ = *sim_registers.getNth(indexRegY);
    registerX.setValue(registerY.getValue() + registerZ.getValue());
    sim_registers.update(indexRegX, registerX);
  }
}

// PRE: load has successfully loaded a file into memory
//      halt = false
// POST: Current word = memory[(PC-BYTE)/BYTE], say W
//       RegisterX = W[1], RegisterY = W[2], RegisterZ = W[7]
//       perform and bitwise operation on RegisterY.value
//         and RegisterZ.value, to get A
//       perform not bitwise operation on A
//       store A in RegisterX.value
void Simulator::executeNand(unsigned int & currentWord){
  int indexRegX = getNibble(currentWord, 1);
  int operand2 = 2;
  int operand3 = 7;
  if (!indexRegX == 0) {
    // ASSERT: registerX is not $zero
    int indexRegY = getNibble(currentWord, operand2);
    int indexRegZ = getNibble(currentWord, operand3); 
    Register registerX = *sim_registers.getNth(indexRegX);
    Register registerY = *sim_registers.getNth(indexRegY);
    Register registerZ = *sim_registers.getNth(indexRegY);
    int newVal = ~(registerY.getValue() & registerZ.getValue()); 
    registerX.setValue(newVal);
    sim_registers.update(indexRegX, registerX);
  }
  
}

// PRE: load has successfully loaded a file into memory
//      halt = false
// POST: Current word = memory[(PC-BYTE)/BYTE], say W
//       RegisterX = W[1], RegisterY = W[2], Offset = W[3 - 7]
//       find sum of RegisterY.value and immediate to get V
//       store V in RegisterX.value
void Simulator::executeAddi(unsigned int & currentWord){
  int operand1 = 1;
  int operand2 = 2;
  int indexRegX = getNibble(currentWord, operand1);
  if (!(indexRegX == 0)) {
    // ASSERT: registerX is not $zero
    int indexRegY = getNibble(currentWord, operand2);
    Register registerX = *sim_registers.getNth(indexRegX);
    Register registerY = *sim_registers.getNth(indexRegY);
    int signedValue = getOffset(currentWord);
    registerX.setValue(registerY.getValue() + signedValue);
    sim_registers.update(indexRegX, registerX);
  }
}

// PRE: load has successfully loaded a file into memory
//      halt = false
// POST: Current word = memory[(PC-BYTE)/BYTE], say W
//       RegisterX = W[1], RegisterY = W[2], Offset = W[3 - 7]       
//       find word, say L, in memory at index
//         index = RegisterY.value + offset + PC
//       if L is within memory given to program
//         store value, say V, of L in RegisterX such that
//           RegisterX.value = V
//         return success
//       else return false
bool Simulator::executeLw(unsigned int & currentWord){
  bool error = true;
  int operand1 = 1;
  int operand2 = 2;
  int indexRegX = getNibble(currentWord, operand1);
  if (!indexRegX == 0) {
    // ASSERT: registerX is not $zero
    int indexRegY = getNibble(currentWord, operand2);
    Register registerX = *sim_registers.getNth(indexRegX);
    Register registerY = *sim_registers.getNth(indexRegY);
    int offset = getOffset(currentWord); 
    int index = registerY.getValue() + offset + PC;
    if (checkAllocation(index)) {
      // ASSERT: this program has been allocated memory[index]
      registerX.setValue(memory[index]);
      sim_registers.update(indexRegX, registerX); 
      error = false; 
    }
  } else {
    // ASSERT: $zero is registerX, so load is complete
    //           without updating any value
    error = false;
  }
  return error; 
}
  
// PRE: load has successfully loaded a file into memory
//      halt = false
// POST: Current word = memory[(PC-BYTE)/BYTE], say W
//       RegisterX = W[1], RegisterY = W[2], Offset = W[3 - 7]       
//       find word, say L, in memory at index
//         index = RegisterY.value + offset + PC
//       if L is within memory given to program
//         store value, say V, of RegisterX in L such that
//           L = RegisterX.value
//         return success
//       else return false
bool Simulator::executeSw(unsigned int & currentWord){
  bool error = true;
  int operand1 = 1;
  int operand2 = 2;
  int indexRegX = getNibble(currentWord, operand1);
  int indexRegY = getNibble(currentWord, operand2);
  Register registerX = *sim_registers.getNth(indexRegX);
  Register registerY = *sim_registers.getNth(indexRegY);
  int offset = getOffset(currentWord); 
  int index = registerY.getValue() + offset + PC;
  if (checkAllocation(index)) {
    // ASSERT: this program has been allocated memory[index]
    memory[index] = registerX.getValue(); 
    error = false; 
  }
  return error; 
}

// PRE: load has successfully loaded a file into memory
//      halt = false
// POST: Current word = memory[(PC-BYTE)/BYTE], say W
//       RegisterX = W[1], RegisterY = W[2], Offset = W[3 - 7]
//       if RegisterX.value = RegisterY.value, PC = PC + Offset
void Simulator::executeBeq(unsigned int & currentWord){
  int operand1 = 1;
  int operand2 = 2;
  int indexRegX = getNibble(currentWord, operand1);
  int indexRegY = getNibble(currentWord, operand2);
  Register registerX = *sim_registers.getNth(indexRegX);
  Register registerY = *sim_registers.getNth(indexRegY);
  int offset = getOffset(currentWord); 
  if(registerX.getValue() == registerY.getValue()) {
    PC = PC + offset; 
  }
}

// PRE: load has successfully loaded a file into memory
//      halt = false
// POST: Current word = memory[(PC-BYTE)/BYTE], say W
//       RegisterX = W[1], RegisterY = W[2]
//       RegisterY.value = PC, PC = RegisterX.value
void Simulator::executeJalr(unsigned int & currentWord){
  int operand1 = 1;
  int operand2 = 2;
  int indexRegX = getNibble(currentWord, operand1);
  int indexRegY = getNibble(currentWord, operand2);
  Register registerX = *sim_registers.getNth(indexRegX);
  Register registerY = *sim_registers.getNth(indexRegY);
  registerY.setValue(PC);
  sim_registers.update(indexRegY, registerY);
  PC = registerX.getValue(); 
}

// PRE: load has successfully loaded a file into memory
//      halt = false
// POST: Current word = memory[(PC-BYTE)/BYTE], say W
//       RegisterX = W[1]
//       Ask user for input, store this in RegisterX.value
void Simulator::executeIn(unsigned int & currentWord){
  cout << "?";
  int tmp; 
  cin >> tmp;
  int operand1 = 1;
  int indexRegX = getNibble(currentWord, operand1);
  Register registerX = *sim_registers.getNth(indexRegX);
  registerX.setValue(tmp);
  sim_registers.update(indexRegX, registerX); 
}

// PRE: load has successfully loaded a file into memory
//      halt = false
// POST: Current word = memory[(PC-BYTE)/BYTE], say W
//       RegisterX = W[1]
//       Send RegisterX.value to output stream
void Simulator::executeOut(unsigned int & currentWord){
  int operand1 = 1;
  int indexRegX = getNibble(currentWord, operand1);
  Register registerX = *sim_registers.getNth(indexRegX);
  cout << registerX.getValue(); 
}

// PRE: load has successfully loaded a file into memory
//      halt = false
// POST: Current word = memory[(PC-BYTE)/BYTE], say W
//       RegisterX = W[1], Offset = W[3-7]
//       RegisterX.value = PC + Offset
void Simulator::executeLa(unsigned int & currentWord){
  int operand1 = 1;
  int indexRegX = getNibble(currentWord, operand1);
  Register registerX = *sim_registers.getNth(indexRegX);
  int offset = getOffset(currentWord); 
  registerX.setValue(PC + offset);
  sim_registers.update(indexRegX, registerX); 
}

// PRE: load has successfully loaded a file into memory
//      halt = false
// POST: Current word = memory[(PC-BYTE)/BYTE], say W
//       RegisterX = W[1], RegisterY = W[2], Offset = W[3 - 7]
//       if RegisterX.value > RegisterY.value, PC = PC + Offset
void Simulator::executeBgt(unsigned int & currentWord){
  int operand1 = 1;
  int operand2 = 2;
  int indexRegX = getNibble(currentWord, operand1);
  int indexRegY = getNibble(currentWord, operand2);
  Register registerX = *sim_registers.getNth(indexRegX);
  Register registerY = *sim_registers.getNth(indexRegY);
  int offset = getOffset(currentWord); 
  if(registerX.getValue() > registerY.getValue()) {
    PC = PC + offset; 
  }
}

//==================================================================
// Helpers
//==================================================================
// PRE: file is not NULL,
//      file holds n chars
//      n/BYTE + numStackSize <= numWords
///     n % 4 = 0 
// POST: Validates the given file name by
//         decoding chars into bytes,
//         each set of 8 bytes placed into an unsigned int,
//         all unsigned ints placed into memory.
void Simulator::handleLoadHelper(char* fileName) {
  ifstream file(fileName); // this fiel holds the program 
  unsigned int currentWord = 0; // this accumulates a word at a time
  unsigned int mask = 0xff;
  char ch; // this holds current char in file
  unsigned int tempInt = 0; // this holds int casted ch 
  int readCount = 0; // how many chars we've read
  int memoryIndex = 0; // hold our place in memory
  while (!file.eof()) {
    ch = file.get(); // get next char
    tempInt = (unsigned int)ch; // tempInt holds a byte
    currentWord = currentWord << 2*BYTE; // make space 
    tempInt = tempInt & mask;
    currentWord += tempInt; // add rightmost byte
    readCount ++;
    if (readCount == 4) {
      // store current word in memoryl;
      memory[memoryIndex] = currentWord;
      memoryIndex ++;
      readCount = 0;
      //ASSERT: The word has been stored in memory.
    }
  }
  memorySize = memoryIndex;
  file.close();
}

// PRE:
// POST: returns value of word[3-7]
int Simulator::getOffset(unsigned int word){
  // shift 12 (3 bytes) to pad word[0-2] with 0's
  word = word << THREEBYTES; 
  word = word >> THREEBYTES;
  int offset = word; 
  return offset; 
}

// PRE: index > 0
//      program loaded into simulator
//      halt = false
// POST: if index/BYTE <= programSize OR
//        index/BYTE in range (numWords - numStackSize, numWords)
//        return true
//       else return false 
bool Simulator::checkAllocation(int index) { 
  bool allocated = false;
  if (index / BYTE <= programSize ||
      (index / BYTE >= numWords - numStackSize
       && index / BYTE <= numWords)){
    allocated = true; 
  }
  return allocated;
}
