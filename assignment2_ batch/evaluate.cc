//Author: Nicholas Ogbonna
#include "evaluate.h"
#include <iostream>
using namespace std;
//PRE: Entirety of tokenList must be valid.  must be initialized
//to false
//POST: Interprets what the tokenList wants to do, calls the member
//function in simulator that corresponds to the tokenList
void evaluate_command(LinkedList<MyString> tokenList, Simulator & sim,
		      OS & myOS){
  MyString* command = tokenList.getHead();
  if (isEqualString(command->getstring(), LOAD)) {
    MyString* progName = tokenList.getNth(1);
    char* progString = progName->getstring();
    bool RTerror = sim.handleLoad(progString, myOS);
    if (RTerror){
      cout << "ERROR: INVALID FILE" << endl;
    }
  }
  else if (isEqualString(command->getstring(), MEM)) {
    bool ifLoaded = sim.loadStatus();
    if (ifLoaded){
      if (tokenList.getSize() == 1){
	//User gave no arguements
	sim.handleMem();
      }
      else if (tokenList.getSize() == 2){
	//user gave a start arguement
	MyString* start = tokenList.getNth(1);
	char* startString = start->getstring();
	int startINT = strToInt(startString);
	bool couldDoMem = sim.handleMem1arg(startINT);
	if (!couldDoMem){
	  cout << "ERROR: given arguements were invalid"
	       << endl;
	}
      }
      else if (tokenList.getSize() == 3){
	//user gave a start and end arguement
	MyString* start = tokenList.getNth(1);
	MyString* end = tokenList.getNth(2);
    
	char* startString = start->getstring();
	char* endString = end->getstring();

	int startINT = strToInt(startString);
	int endINT = strToInt(endString);
	bool couldDoMem = sim.handleMem2arg(startINT, endINT);
	if (!couldDoMem){
	  cout << "ERROR: given arguements were invalid"
	       << endl;
	}
      }
    }
    else{
      //ASSERT: nothing loaded
      cout << "ERROR: Cannot find memory if nothing is loaded" << endl;
    }
  }
  else if (isEqualString(command->getstring(), CPU)) {
    bool ifLoaded = sim.loadStatus();
    if (ifLoaded){
      PCB* curr_PCB = myOS.getCurrPCB();
      int currPCB_ID = curr_PCB->getProcessID();
      sim.handleCpu(currPCB_ID);
    }
    else{
      cout << "ERROR: cant find the CPU of a non loaded program" << endl;
    }
  }
  else if (isEqualString(command->getstring(), STEP)) {
    bool ifLoaded = sim.loadStatus();
    if (ifLoaded){
      MyString* numSteps = tokenList.getNth(1);
      char* numString = numSteps->getstring();
      int numStepsInt = strToInt(numString);
      bool error = sim.handleStep(numStepsInt, myOS);
      if(error){
	//ASSERT: There is a runtime error
	cout << "ERROR: Runtime Error" << endl;
      }
    }
    else{
      cout << "ERROR: Cannot step if nothing's loaded" << endl;
    }
  }
  else if (isEqualString(command->getstring(), RUN)) {
    bool ifLoaded = sim.loadStatus();
    if (ifLoaded){
      bool error = sim.handleRun(myOS);
      if(error){
	//ASSERT: There is a runtime error
	cout << "ERROR: Runtime Error" << endl;
      }
    }
    else{
      cout << "ERROR: Can't run what is not loaded" << endl;
    }
  }
  else if (isEqualString(command->getstring(), FREEMEM)) {
    myOS.handleFreeMem();
  }
  else if (isEqualString(command->getstring(), JOBS)) {
    myOS.handleJobs();
  }
  else if (isEqualString(command->getstring(), KILL)) {
    bool ifLoaded = sim.loadStatus();
    if (ifLoaded){
      MyString* userPCB_ID_to_kill = tokenList.getNth(1);
      char* IDstring = userPCB_ID_to_kill->getstring();
      int PCB_ID = strToInt(IDstring);
      bool killConfirmed = myOS.handleKill(PCB_ID);
      if (!killConfirmed){
	cout << "Invalid PID" << endl;
      }
    }
    else{
      //ASSERT: nothing loaded
      cout << "Error: Nothing loaded. Kill needs something to kill" << endl;
    }
  }
}
