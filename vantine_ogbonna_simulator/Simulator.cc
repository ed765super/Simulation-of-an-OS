/* Author: Schuyler van Tine */
/* Simulator Class           */

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "Simulator.h"
#include "MyString.h"
#include "Register.h"
#include "LinkedList.h"
#include "constants.h"
#include "utility.h"

using namespace std; 


//==================================================================
// Constructors
//==================================================================

// PRE: requestedMemory > 0 
// POST: PC = 0, numWords = requestedMemory, sim_registers holds number
//         of registers equal to MAX_REGISTERS, memory holds number
//         of unsigned ints equal to requestedMemory, halt = false
//         programSize = 0
Simulator::Simulator(int requestedMemory){
  PC = 0;
  numWords = requestedMemory;
  memory = new unsigned int[requestedMemory]; 
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
  sim_registers = S.getRegisters(); // get deep copy of registers
  halt = S.haltStatus();
  programLoaded = S.loadStatus();
  programSize = S.getProgramSize(); 
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
  sim_registers = S.getRegisters(); // get deep copy of registers
  halt = S.haltStatus();
  programLoaded = S.loadStatus();
  programSize = S.getProgramSize();   
}

// ======================================== 
// destructor
// ======================================== 
  
// PRE: This object is defined.
// POST: Heap space allocated to this program freed
Simulator::~Simulator() {
  delete [] memory;
}

//==================================================================
// Accessors
//==================================================================
  
// PRE:
// POST: returns value of PC
int Simulator::getPC() const {
  return PC;
}

// PRE:
// POST: returns numWords
int Simulator::memSize() const {
  return numWords;
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
// POST: current word, say W = memory[PC/BYTE]
//       determines operand located in W[0]
//       PC = PC + BYTE
//       calls corresponding helper function
bool Simulator::executeNext(){
  unsigned int currentWord = memory[PC/BYTE];
  int opcode = getByte(currentWord, 0);
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
bool Simulator::handleLoad(char* fileName){
  bool loadError = true; 
  ifstream file(fileName);
  if (file != NULL) {
    int numLines = countBinLines(file);
    file.close();
    if ((numLines + DEFAULT_STACK) <= numWords) {
      // ASSERT: this program will fit into memory
      cerr << "fileName: " << fileName << endl;
      handleLoadHelper(fileName);
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
    }
  }
  return loadError;
}


// PRE: start, end are non-negative integers
//      start and end are byte addresses (divisible by 4)
// POST: returns unsigned int* block 
//         first word in block is located at memory[start/BYTE]
//         last word in block is located at memory[end/BYTE]
//         all words between these words in memory appear in the same
//           order in block
//char* Simulator::handleMem(int start, int end){
void Simulator::handleMem(int start, int end){
  //int numWords = (end / BYTE) - (start / BYTE);
  //char* output = new char[(WORDSIZE + 5) * numWords];
  //int outputIndex = 0;
  //int currWord; 
  // for(int index = start / BYTE; index < end / BYTE; index ++) {
  //   currWord = memory[index]; 
  //   char buffer [WORDSIZE + 5];
  //   snprintf (buffer, WORDSIZE, "%#08x\n\0", currWord);
  //   int bufferIndex = 0; 
  //   char ch = buffer[bufferIndex]; 
  //   while (ch != '\0'){
  //     cout << "ch " << ch << endl ;
  //     output[outputIndex] = ch; 
  //     outputIndex ++;
  //     bufferIndex ++;
  //     ch = buffer[bufferIndex];
  //   }
  // }
  //output[outputIndex] = '\0';
  //  return output;
  int numWords = (end / BYTE) - (start / BYTE);
  while (start < end){
    unsigned int currentWord = memory[start / BYTE];
    printf("%#08x\n", currentWord);
    start = start + BYTE; 
  }
}

// PRE: 
// POST: return char* holding register data
//char* Simulator::handleCpu(){
void Simulator::handleCpu(){
  // Register curr;
  // MyString output;
  // for(int index = 0; index < MAX_REGISTERS; index++) {
  //   curr = *sim_registers.getNth(index);
  //   MyString temp(curr.getStr());
  //   output = output + temp; 
  // }
  //return output.getstring();
  cout << sim_registers << endl; 

}

// PRE: numSteps > 0
//      load has successfully loaded a file into memory
//      halt = false
// POST: executes number of lines of code in memory
//         <= requestedSteps (if halt is reached no more before numSteps
//         lines executed then no more executions will occur)
//       if no runtime error occured return true
//       else return false 
bool Simulator::handleStep(int requestedSteps){
  int steps = 0;
  bool error = false; 
  while (steps < requestedSteps && !halt && !error) {
    error = executeNext();
    steps ++; 
  }
  return error; 
}

// PRE: load has successfully loaded a file into memory
//      halt = false
// POST: executes code in memory until halt is reached
//       if no runtime error occured return true
//       else return false 
bool Simulator::handleRun(){
  bool error = false;
  while (!halt && !error) {
    error = executeNext(); 
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
  int indexRegX = getByte(currentWord, 1);
  if (!indexRegX == 0) {
    // ASSERT: registerX is not $zero
    int indexRegY = getByte(currentWord, 2);
    int indexRegZ = getByte(currentWord, 7); 
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
  int indexRegX = getByte(currentWord, 1);
  if (!indexRegX == 0) {
    // ASSERT: registerX is not $zero
    int indexRegY = getByte(currentWord, 2);
    int indexRegZ = getByte(currentWord, 7); 
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
  int indexRegX = getByte(currentWord, 1);
  if (!indexRegX == 0) {
    // ASSERT: registerX is not $zero
    int indexRegY = getByte(currentWord, 2);
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
  int indexRegX = getByte(currentWord, 1);
  if (!indexRegX == 0) {
    // ASSERT: registerX is not $zero
    int indexRegY = getByte(currentWord, 2);
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
  int indexRegX = getByte(currentWord, 1);
  int indexRegY = getByte(currentWord, 2);
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
  int indexRegX = getByte(currentWord, 1);
  int indexRegY = getByte(currentWord, 2);
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
  int indexRegX = getByte(currentWord, 1);
  int indexRegY = getByte(currentWord, 2);
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
  int indexRegX = getByte(currentWord, 1);
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
  int indexRegX = getByte(currentWord, 1);
  Register registerX = *sim_registers.getNth(indexRegX);
  cout << registerX.getValue(); 
}

// PRE: load has successfully loaded a file into memory
//      halt = false
// POST: Current word = memory[(PC-BYTE)/BYTE], say W
//       RegisterX = W[1], Offset = W[3-7]
//       RegisterX.value = PC + Offset
void Simulator::executeLa(unsigned int & currentWord){
  int indexRegX = getByte(currentWord, 1);
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
  int indexRegX = getByte(currentWord, 1);
  int indexRegY = getByte(currentWord, 2);
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
//      n/BYTE + DEFAULT_STACK <= numWords
///     n % 4 = 0 
// POST: decodes chars into bytes,
//         each set of 8 bytes placed into an unsigned int,
//         all unsigned ints placed into memory
void Simulator::handleLoadHelper(char* fileName) {
  ifstream file(fileName); // this fiel holds the program 
  unsigned int currentWord = 0; // this accumulates a word at a time
  unsigned int mask = 0xff; 
  char ch = '0'; // this holds current char in file
  unsigned int tempInt = 0; // this holds int casted ch 
  int readCount = 0; // how many chars we've read
  int memoryIndex = 0; // hold our place in memory
  
  while (!file.eof()) {
    file.get(ch); // get next char
    tempInt = (int)ch; // tempInt holds two bytes
    currentWord = currentWord << 2*BYTE; // make space 
    tempInt = tempInt & mask; 
    currentWord += tempInt; // add rightmost byte
    readCount ++;
    if (readCount == 4) {
      // store current word in memory 
      memory[memoryIndex] = currentWord;
      memoryIndex ++;
      readCount = 0; 
    }
  }
  file.close();
}

// PRE:
// POST: returns value of word[3-7]
int Simulator::getOffset(unsigned int word){
  // shift 12 (3 bytes) to pad word[0-2] with 0's
  word = word << 12; 
  word = word >> 12;
  int offset = word; 
  return offset; 
}

// PRE: index > 0
//      program loaded into simulator
//      halt = false
// POST: if index/BYTE <= programSize OR
//        index/BYTE in range (numWords - DEFAULT_STACK, numWords)
//        return true
//       else return false 
bool Simulator::checkAllocation(int index) { 
  bool allocated = false;
  if (index / BYTE <= programSize ||
      (index / BYTE >= numWords - DEFAULT_STACK
       && index / BYTE <= numWords)){
    allocated = true; 
  }
  return allocated;
}
