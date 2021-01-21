/* Author: Schuyler van Tine */
/* Simulator Class           */

#ifndef INCLUDED_SIMULATOR
#define INCLUDED_SIMULATOR

#include "MyString.h"
#include "Register.h"
#include "LinkedList.h"
#include "constants.h"
#include "utility.h"

// CI: PC > 0 
//     numWords equal to number of unsigned ints held by memory
//     numWords > 0
//     Nodes in sim_registers = MAX_REGISTERS
//     programSize + DEFAULT_STACK <= numWords

class Simulator {
 private:
  int PC; // points to next instruction to be executed (byte address)
  unsigned int* memory; // this array functions as the sim's RAM
  int numWords; // number of unsigned ints in memory
  LinkedList<Register> sim_registers;
  bool programLoaded; // true if a program has successfully loaded
  bool halt; // true iff loaded program has reached halt instruction
  int programSize; // if a program has been loaded
                   //   equal to number of lines in loaded program
                   // else equal to 0 
  
 public:
  //==================================================================
  // Constructors
  //==================================================================

  // PRE:
  // POST: No args given, need memory size to comply with CI,
  //         so do nothing
  Simulator(){};

  // PRE: requestedMemory > 0 
  // POST: PC = 0, numWords = requestedMemory, sim_registers holds number
  //         of registers equal to MAX_REGISTERS, memory holds number
  //         of unsigned ints equal to requestedMemory, halt = false
  //         programSize = 0
  Simulator(int requestedMemory);

  // copy constructor
  // PRE: S is defined.
  // POST: This object is defined and is a deep copy of S.
  Simulator(const Simulator & S);

  //assignment operator
  // PRE: S is defined.
  // POST: This object is defined and is a deep copy of S.
  Simulator & operator= (const Simulator & S);

  // ======================================== 
  // destructor
  // ======================================== 
  
  // PRE: This object is defined.
  // POST: Heap space allocated to this program freed
  ~Simulator();

  //==================================================================
  // Accessors
  //==================================================================
  
  // PRE:
  // POST: returns value of PC
  int getPC() const;

  // PRE:
  // POST: returns numWords
  int memSize() const;

  // PRE:
  // POST: returns memory 
  unsigned int* getMemory() const;

  // PRE: 
  // POST: returns unsigned int located at
  //       index in memory
  unsigned int getWord(int index) const; 

  // PRE:
  // POST: returns sim_registers
  LinkedList<Register> getRegisters() const;

  // PRE:
  // POST: returns pointer to Register object at location
  //       index in sim_registers
  Register* getRegister(int index) const;

  // PRE:
  // POST: returns halt
  bool haltStatus() const;

  // PRE:
  // POST: return programLoaded
  bool loadStatus() const;

  // PRE: programLoaded = true 
  // POST: return programSize
  int getProgramSize() const;
  

  //==================================================================
  // Modifiers
  //==================================================================

  // PRE:
  // POST: sets PC equal to newPC
  void updatePC(int newPC);

  // PRE:
  // POST: sets PC equal to PC + 4
  void incrementPC();

  // PRE: program has been successfully loaded into memory
  //      halt = false
  // POST: current word, say W = memory[PC/4]
  //       determines operand located in W[0]
  //       PC = PC + 4
  //       calls corresponding helper function
  bool executeNext(); 

  //==================================================================
  // Shell Commands
  //==================================================================

  // PRE: fileName is the name of a valid machine code file, say f
  //      f is a sequence of binary bytes encoded in ascii chars 
  // POST: f has number of lines equal to n
  //       if n + DEFAULT_STACK <= numWords, 
  //         then decode ascii chars into bytes,
  //         each set of 8 bytes placed into an unsigned int
  //         all unsigned ints placed into memory
  //         return true
  //       else return false
  bool handleLoad(char* fileName);


  // PRE: start, end are non-negative integers
  //      start and end are byte addresses
  // POST: returns unsigned int* block 
  //         first word in block is located at memory[start/4]
  //         last word in block is located at memory[end/4]
  //         all words between these words in memory appear in the same
  //           order in block
  //  char* handleMem(int start, int end);
  void handleMem(int start, int end); 

  // PRE: 
  // POST: return char* holding register data
  //char* handleCpu();
  void handleCpu();

  // PRE: numSteps > 0
  //      load has successfully loaded a file into memory
  //      halt = false
  // POST: executes number of lines of code in memory
  //         <= numSteps (if halt is reached no more before numSteps
  //         lines executed then no more executions will occur)
  //       if no runtime error occured return true
  //       else return false 
  bool handleStep(int numSteps);

  // PRE: load has successfully loaded a file into memory
  //      halt = false
  // POST: executes code in memory until halt is reached
  //       if no runtime error occured return true
  //       else return false 
  bool handleRun();

  //==================================================================
  // Assembly Instructions
  //==================================================================

  // ASSEMBLY INSTRUCTION DOCUMENTATION NOTES: 
  //   Bytes are reffered to in words in the format Word[index] 
  //   Byte indices in this documentation are big-endian
  
  // PRE: load has successfully loaded a file into memory
  //      halt = false
  // POST: Current word = memory[(PC-4)/4], say W
  //       RegisterX = W[1], RegisterY = W[2], RegisterZ = W[7]
  //       find sum of RegisterY.value + RegisterZ.value to get S
  //       store S in RegisterX.value
  void executeAdd(unsigned int & currentWord);

  // PRE: load has successfully loaded a file into memory
  //      halt = false
  // POST: Current word = memory[(PC-4)/4], say W
  //       RegisterX = W[1], RegisterY = W[2], RegisterZ = W[7]
  //       perform and bitwise operation on RegisterY.value
  //         and RegisterZ.value, to get A
  //       perform not bitwise operation on A
  //       store A in RegisterX.value
  void executeNand(unsigned int & currentWord);

  // PRE: load has successfully loaded a file into memory
  //      halt = false
  // POST: Current word = memory[(PC-4)/4], say W
  //       RegisterX = W[1], RegisterY = W[2], Offset = W[3 - 7]
  //       find sum of RegisterY.value and immediate to get V
  //       store V in RegisterX.value
  void executeAddi(unsigned int & currentWord);

  // PRE: load has successfully loaded a file into memory
  //      halt = false
  // POST: Current word = memory[(PC-4)/4], say W
  //       RegisterX = W[1], RegisterY = W[2], Offset = W[3 - 7]       
  //       find word, say L, in memory at index
  //         index = RegisterY.value + offset
  //       if L is within memory given to program
  //         store value, say V, of L in RegisterX such that
  //           RegisterX.value = V
  //         return success
  //       else return false
  bool executeLw(unsigned int & currentWord);
  
  // PRE: load has successfully loaded a file into memory
  //      halt = false
  // POST: Current word = memory[(PC-4)/4], say W
  //       RegisterX = W[1], RegisterY = W[2], Offset = W[3 - 7]       
  //       find word, say L, in memory at index
  //         index = RegisterY.value + offset
  //       if L is within memory given to program
  //         store value, say V, of RegisterX in L such that
  //           L = RegisterX.value
  //         return success
  //       else return false
  bool executeSw(unsigned int & currentWord);

  // PRE: load has successfully loaded a file into memory
  //      halt = false
  // POST: Current word = memory[(PC-4)/4], say W
  //       RegisterX = W[1], RegisterY = W[2], Offset = W[3 - 7]
  //       if RegisterX.value = RegisterY.value, PC = PC + Offset
  void executeBeq(unsigned int & currentWord);

  // PRE: load has successfully loaded a file into memory
  //      halt = false
  // POST: Current word = memory[(PC-4)/4], say W
  //       RegisterX = W[1], RegisterY = W[2]
  //       RegisterY.value = PC, PC = RegisterX.value
  void executeJalr(unsigned int & currentWord);

  // PRE: load has successfully loaded a file into memory
  // POST: programHalted = true
  void executeHalt(unsigned int & currentWord);

  // PRE: load has successfully loaded a file into memory
  //      halt = false
  // POST: Current word = memory[(PC-4)/4], say W
  //       RegisterX = W[1]
  //       Ask user for input, store this in RegisterX.value
  void executeIn(unsigned int & currentWord);

  // PRE: load has successfully loaded a file into memory
  //      halt = false
  // POST: Current word = memory[(PC-4)/4], say W
  //       RegisterX = W[1]
  //       Send RegisterX.value to output stream
  void executeOut(unsigned int & currentWord);

  // PRE: load has successfully loaded a file into memory
  //      halt = false
  // POST: Current word = memory[(PC-4)/4], say W
  //       RegisterX = W[1], Offset = W[3-7]
  void executeLa(unsigned int & currentWord);

  // PRE: load has successfully loaded a file into memory
  //      halt = false
  // POST: Current word = memory[(PC-4)/4], say W
  //       RegisterX = W[1], RegisterY = W[2], Offset = W[3 - 7]
  //       if RegisterX.value > RegisterY.value, PC = PC + Offset
  void executeBgt(unsigned int & currentWord);

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
  void handleLoadHelper(char* fileName);

  // PRE:
  // POST: returns value of word[3-7]
  int getOffset(unsigned int word);

  // PRE: index > 0
  //      program loaded into simulator
  //      halt = false
  // POST: if index/BYTE <= programSize OR
  //        index/BYTE in range (memorySize - DEFAULT_STACK, memorySize)
  //        return true
  //       else return false 
  bool checkAllocation(int index);
  
}; 

#endif
