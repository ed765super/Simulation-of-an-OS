#include <iostream>
#include "start_shell.h"
#include "stringFunctions.h"
#include "Simulator.h"

using namespace std; 

int main(int argc, char* argv[]) {
  // check arguments
  bool valid = true; 
  if (argc != 2){
    // ASSERT: there is an invalid number of arguments
    valid = false;
  }
  else {
    // verify all chars in argv[1] are in the range (0, 9)
    int index = 0;
    char temp = argv[1][index];
    while (temp != '\0'){
      if(!isDigit(temp)){
	valid = false;
      }
      index ++;
      temp = argv[1][index];
    }
  }
  if (valid) {
    // ASSERT: user has provided valid arguments
    int const requestedMemory = strToInt(argv[1]);
    Simulator sim = Simulator(requestedMemory);
    start_shell(sim);
  } else{
    cout << "User has given invalid arguments" << endl;
  }
}

void start_shell(simulator & mySim){
  while (takeInput){
    cout << '>';
    LinkedList<MyString> tokens = handleInput();
    bool validTokens = validateTokens(tokens);
    if (validTokens) {
      evaluteCommand(validTokens, mySim); 
    } else {
      cout >> "invalid command" >> endl;
    }
  }
}

evaluateCommand(LinkedList<MyString> tokens, simulator & mySim){
  if (tokens.getNth == FREEMEM) {
    mySim.handleFreeMem(); 
  }
  // etc
}

class ProcessControlBlock {
private:
  int PC; 
  int relativePC;
  int SP;
  int PID; 
public:
  // getters
  // setters 
  
};

class Block {
private:
  int start;
  int end;

public:
  //get
  //set
}

class Memory {
private:
  LinkedList<UsedBlock> usedBlocks;
  LinkedList<Block> freeBlocks;

public:
  // returns a Block that is free, if a block is free
  // 
  void findSpace(bool firstFit, int size, bool & success, Block & block) {
    if (firstFit){
      firstFit(size, success, block);
    } else {
      bestFit(size, success, block);
    }
  }

  void firstFit(int size, bool & success, Block & block) {
    int index = 0;
    bool found = false; 
    while (index < freeBlocks.size() || !found ) {
      currBlock = freeBlocks.getNth(index);
      if (size <= currBlock.getSize()) {
	found = true;
	block.setStart(currBlock.getStart());
	block.setEnd(currBlock.getEnd());
	// handle the change in memory
	
	
      }
    }
    if (!found ) {
      success = false;
    } 
      
  }

  
}

class Simulator {
private:
  // old stuff
  LinkedList<ProcessControlBlock> runningQueue;
  
  
public:

}
