#include <iostream>
#include <fstream>
#include "start_shell.h"
#include "stringFunctions.h"
#include "Simulator.h"
#include "OS.h"
using namespace std;

//PRE:
//POST: Modifies the objects passed for numPagesMemory, stackMemory, fitType,
//      paging, swapspace, pagesize,
//      and timeSlice s.t. they are equal to the integers in the config file
//      associated with them.
void getConfig(int & numPagesMemory, int & stackMemory, int & fitType,
	       int & timeSlice, int & paging, int & swapspace,
	       int & pagesize){
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
      numPagesMemory = strToInt(wordIntString);
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
    else if (isEqualString(wordString, TIMESLICE)){
      curr_ch = inFile.get(); //ch is now the first integer
      MyString wordInt; //will hold the integer that's next to memory
      while(isDigit(curr_ch)){
	wordInt.addchar(curr_ch);
	curr_ch = inFile.get();
      }
      //ASSERT: curr_ch is no longer an integer
      char* wordIntString = wordInt.getstring();
      timeSlice = strToInt(wordIntString);
      //stackMemory is now the integer after the word stackMemory in
      //the inFile
    }
    else if (isEqualString(wordString, PAGING)){
      curr_ch = inFile.get(); //ch is now the first integer
      MyString wordInt; //will hold the integer that's next to memory
      while(isDigit(curr_ch)){
	wordInt.addchar(curr_ch);
	curr_ch = inFile.get();
      }
      //ASSERT: curr_ch is no longer an integer
      char* wordIntString = wordInt.getstring();
      paging = strToInt(wordIntString);
      //stackMemory is now the integer after the word stackMemory in
      //the inFile
    }
    else if (isEqualString(wordString, TIMESLICE)){
      curr_ch = inFile.get(); //ch is now the first integer
      MyString wordInt; //will hold the integer that's next to memory
      while(isDigit(curr_ch)){
	wordInt.addchar(curr_ch);
	curr_ch = inFile.get();
      }
      //ASSERT: curr_ch is no longer an integer
      char* wordIntString = wordInt.getstring();
      timeSlice = strToInt(wordIntString);
      //stackMemory is now the integer after the word stackMemory in
      //the inFile
    }
    else if (isEqualString(wordString, SWAPSPACE)){
      curr_ch = inFile.get();//Reads past space
      MyString wordInt; //will hold the integer that's next to memory
      while(isDigit(curr_ch)){
	wordInt.addchar(curr_ch);
	curr_ch = inFile.get();
      }
      //ASSERT: curr_ch is no longer an integer
      char* wordIntString = wordInt.getstring();
      swapspace = strToInt(wordIntString);
      //fitType is now the integer after the word stackMemory in
      //the inFile
    }
    else if (isEqualString(wordString, PAGESIZE)){
      curr_ch = inFile.get(); //ch is now the first integer
      MyString wordInt; //will hold the integer that's next to memory
      while(isDigit(curr_ch)){
	wordInt.addchar(curr_ch);
	curr_ch = inFile.get();
      }
      //ASSERT: curr_ch is no longer an integer
      char* wordIntString = wordInt.getstring();
      pagesize = strToInt(wordIntString);
      //stackMemory is now the integer after the word stackMemory in
      //the inFile
    }
    curr_ch = inFile.get();
  }
}

int main() {
  int numPagesMemory;
  int numPagesStack;
  int fitType;
  int timeSlice;
  int paging;
  int NumPagesSwap;
  int pagesize;
  getConfig(numPagesMemory, numPagesStack, fitType, timeSlice, paging,
	    numPagesSwap, pagesize);
  //ASSERT: Config file has been loaded
  Simulator sim(numPagesMemory * pagesize, numPagesStack * pagesize,
		numPagesSwap * pagesize, fitType);
  Block totalFree;
  totalFree.setStart(0);
  totalFree.setEnd(numPagesMemory * pagesize);
  OS myOS(totalFree, timeSlice, paging, pagesize,
	  numPagesMemory, numPagesSwap); //creates the OS class
  start_shell(sim, myOS);
  return (0);
}
