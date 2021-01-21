//Author: Nicholas Ogbonna
#ifndef INCLUDED_EVALUATE
#define INCLUDED_EVALUATE
#include "stringFunctions.h"
#include "LinkedList.h"
#include "Register.h"
#include "Simulator.h"
#include "MyString.h"
#include "constants.h"

//PRE: Entirety of tokenList must be valid. RTerror must be initialized
//to false
//POST: Interprets what the tokenList wants to do, calls the member
//function in simulator that corresponds to the tokenList, and
//prints the result of the member function if it has a return
void evaluate_command(LinkedList<MyString> tokenList, Simulator & sim);
#endif
