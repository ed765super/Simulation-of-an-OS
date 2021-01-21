#include <iostream>
#include <fstream>
#include "start_shell.h"
#include "stringFunctions.h"
#include "Simulator.h"
#include "Exception.h"
#include "OS.h"
using namespace std;

void getConfig(int & requestedMemory, int & stackMemory, int & fitType){
  ifstream inFile (".lc_config");
  char curr_ch = inFile.get();
  while (!inFile.eof()){
    MyString curr_word;
    while(curr_ch != aSpace){
      curr_word.addchar(curr_ch);
      curr_ch = inFile.get();
    }
    //ASSERT: curr_ch = aSpace.
    //curr_word = a word from the inFile
    char* wordString = curr_word.getstring();
    if (isEqualString(wordString, MEMORY)){
      curr_ch = inFile.get(); //ch is now the first integer
      MyString wordInt; //will hold the integer that's next to memory
      while(isDigit(curr_ch)){
	wordInt.addchar(curr_ch);
	curr_ch = inFile.get();
      }
      //ASSERT: curr_ch is no longer an integer
      char* wordIntString = wordInt.getstring();
      requestedMemory = strToInt(wordIntString);
      //memory is now the integer after the word memory in the inFile
    }
    else if (isEqualString(wordString, STACKMEMORY)){
      curr_ch = inFile.get(); //ch is now the first integer
      MyString wordInt; //will hold the integer that's next to memory
      while(isDigit(curr_ch)){
	wordInt.addchar(curr_ch);
	curr_ch = inFile.get();
      }
      //ASSERT: curr_ch is no longer an integer
      char* wordIntString = wordInt.getstring();
      stackMemory = strToInt(wordIntString);
      //stackMemory is now the integer after the word stackMemory in
      //the inFile
    }
    else if (isEqualString(wordString, FITTYPE)){
      curr_ch = inFile.get();//Reads past space
      MyString wordInt; //will hold the integer that's next to memory
      while(isDigit(curr_ch)){
	wordInt.addchar(curr_ch);
	curr_ch = inFile.get();
      }
      //ASSERT: curr_ch is no longer an integer
      char* wordIntString = wordInt.getstring();
      fitType = strToInt(wordIntString);
      //fitType is now the integer after the word stackMemory in
      //the inFile
    }
    curr_ch = inFile.get();
  }
}

int main() {
  int requestedMemory;
  int stackSize;
  int fitType;
  getConfig(requestedMemory, stackSize, fitType);
  //ASSERT: Config file has been loaded
  Simulator sim = Simulator(requestedMemory, stackSize, fitType);
  Block totalFree;
  totalFree.setStart(0);
  totalFree.setEnd(requestedMemory);
  OS myOS(totalFree); //creates the OS class
  start_shell(sim, myOS);
  return (0);
}
