#include <iostream>
#include <fstream>
#include "Simulator.h"
#include "LinkedList.h"
#include "Register.h"
#include "constants.h"

int main(int argc, char* argv[]) {
  cout << "******************************************" << endl
       << "The following is an attempt to demonstrate" << endl
       << "that the simulator class is functioning properly" << endl
       << "******************************************" << endl;
  
  // verify Simulator constructor
  cout << "==========================================" << endl
       << "VERIFY CONSTRUCTOR" << endl
       << "==========================================" << endl; 
  int requestedMemory = 100;
  cout << "requestedMemory: " << requestedMemory << endl;
  cout << "function call ->   Simulator sim(requestedMemory);" << endl; 
  Simulator sim(requestedMemory);
  cout << "PC: " << sim.getPC() << endl;
  cout << "numWords: " << sim.memSize() << endl;
  cout << "Registers: " << sim.getRegisters() << endl;
  cout << "memory output:" << endl;
  int memSize = sim.memSize(); 
  for(int index = 0; index < sim.memSize(); index ++) {
    cout << "memory[" << index << "] -> ";
    printf("%#08x\n", sim.getWord(index)); 
  }
  cout << "Load Status: " << sim.loadStatus() << endl; 
  cout << "Halt Status: " << sim.haltStatus() << endl;
  cout << "Program Size: " << sim.getProgramSize() << endl;

  //verify handleLoad function
  cout << "==========================================" << endl
       << "VERIFY handleLoad" << endl
       << "==========================================" << endl;
  ifstream file;
  cout << "hex version of input file : " << endl; 
  file.open("prog0.lce");
  char tempChar;
  file.get(tempChar);
  while(!file.eof()){
    cout << tempChar;
    file.get(tempChar);
  }
  bool loadError = sim.handleLoad("prog0.lcb");
  cout << endl << "function call -> sim.handleLoad(\"prog0.lcb\")" << endl; 
  cout << "load error: " << loadError << endl;
  cout << "PC: " << sim.getPC() << endl;
  cout << "numWords: " << sim.memSize() << endl;
  cout << "memory output:" << endl;
  memSize = sim.memSize(); 
  for(int index = 0; index < sim.memSize(); index ++) {
    cout << "memory[" << index << "] -> ";
    printf("%#08x\n", sim.getWord(index)); 
  }
  cout << "Registers: " << sim.getRegisters() << endl;
  cout << "Load Status: " << sim.loadStatus() << endl; 
  cout << "Halt Status: " << sim.haltStatus() << endl;
  cout << "Program Size: " << sim.getProgramSize() << endl;

  //verify handleMem function
  cout << "==========================================" << endl
       << "VERIFY handleMem" << endl
       << "==========================================" << endl;
  cout << "function call -> sim.handleMem(0, 12);" << endl;
  sim.handleMem(0, 12);
  cout << "function call -> sim.handleMem(4, 16);" << endl; 
  sim.handleMem(4, 16);
  cout << "function call -> sim.handleMem(56, 72);" << endl; 
  sim.handleMem(56, 76);

  //verify handleCpu function
  cout << "==========================================" << endl
       << "VERIFY handleCpu" << endl
       << "==========================================" << endl;
  cout << "function call -> sim.handleCpu();" << endl;
  sim.handleCpu(); 

  //verify handleRun function
  cout << "==========================================" << endl
       << "VERIFY handleRun" << endl
       << "==========================================" << endl;
  sim.handleRun();
  cout << "current program calls \"addi regA regA 1\" on every register" << endl; 
  cout << "function call -> sim.handleRun();" << endl;  
  cout << "Registers: " << sim.getRegisters() << endl;
  cout << "Halt Status: " << sim.haltStatus() << endl; 
   
  //verify handleRun function
  cout << "==========================================" << endl
       << "VERIFY handleStep" << endl
       << "==========================================" << endl;

  
  return 0; 
}
