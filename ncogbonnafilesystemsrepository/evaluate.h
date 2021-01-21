//Author: Nicholas Ogbonna
#ifndef INCLUDED_EVALUATE
#define INCLUDED_EVALUATE
#include "stringFunctions.h"
#include "fileSys.h"
#include "LinkedList.h"
#include "MyString.h"
#include "constants.h"

//PRE: Entirety of tokenList must be valid.
//POST: Interprets what the tokenList wants to do, calls the member
//function in fileSys that corresponds to the tokenList, and
//prints the result of the member function if it has a return
void evaluate_command(LinkedList<MyString> tokenList, fileSys & myFileSys);
#endif
