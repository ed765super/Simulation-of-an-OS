//Author: Nicholas Ogbonna
#include "evaluate.h"
#include <iostream>
using namespace std;
//PRE: Entirety of tokenList must be valid.  must be initialized
//to false
//POST: Interprets what the tokenList wants to do, calls the member
//function in simulator that corresponds to the tokenList
void evaluate_command(LinkedList<MyString> tokenList, Simulator & sim){
  MyString* command = tokenList.getHead(); 
  if (isEqualString(command->getstring(), LOAD)) {
    MyString* progName = tokenList.getNth(1);
    char* progString = progName->getstring();
    bool RTerror = sim.handleLoad(progString);
    if (RTerror){
      cout << "ERROR: INVALID FILE" << endl;
    }
  }
  else if (isEqualString(command->getstring(), MEM)) {
    MyString* start = tokenList.getNth(1);
    MyString* end = tokenList.getNth(2);
    
    char* startString = start->getstring();
    char* endString = end->getstring();

    int startINT = strToInt(startString);
    int endINT = strToInt(endString);
    sim.handleMem(startINT, endINT);
  }
  else if (isEqualString(command->getstring(), CPU)) {
    sim.handleCpu();
  }
  else if (isEqualString(command->getstring(), STEP)) {
    MyString* numSteps = tokenList.getNth(1);
    char* numString = numSteps->getstring();
    int numStepsInt = strToInt(numString);
    bool error = sim.handleStep(numStepsInt);
    if(error){
      //ASSERT: There is a runtime error
      cout << "ERROR: Runtime Error" << endl;
    }
  }
  else if (isEqualString(command->getstring(), RUN)) {
    bool error = sim.handleRun();
    if(error){
      //ASSERT: There is a runtime error
      cout << "ERROR: Runtime Error" << endl;
    }
  }
}
