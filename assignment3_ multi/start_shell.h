//Author: Nicholas Ogbonna
#ifndef INCLUDED_START_SHELL
#define INCLUDED_START_SHELL
#include "MyString.h"
#include "LinkedList.h"
#include "evaluate.h"
#include "constants.h"
#include "Simulator.h"
#include "OS.h"
#include <iostream>
#include <fstream>

//PRE:
//POST: RV = what the user typed into the terminal in
//LinkeList<MyString> form where every relevant piece of the user's
//input is broken up into nodes
LinkedList<MyString> tokenize(char* user_input);

//PRE:  tokenList must be non NULL. sizeOfMemory should be the result
//      from the simulator's memSize functions
//POST: RV = true iff there are no errors within the tokenList
bool checkToken(LinkedList<MyString> tokenList, int sizeOfMemory);

//PRE:
//POST: Prompts the user for a cmd and if it is a valid comand, passes
//it to evaluate
void start_shell(Simulator & MySimulator, OS & myOS);

//PRE:
//POST: puts the user's command into userCommand
void createCommand(char curr_ch, MyString & userCommand);

#endif
