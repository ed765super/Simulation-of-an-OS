//Author: Nicholas Ogbonna
#ifndef INCLUDED_START_SHELL
#define INCLUDED_START_SHELL
#include "MyString.h"
#include "LinkedList.h"
#include "constants.h"
#include "fileSys.h"
#include "stringFunctions.h"

//PRE:
//POST: RV = what the user typed into the terminal in
//LinkeList<MyString> form where every relevant piece of the user's
//input is broken up into nodes
LinkedList<MyString> tokenize(char* userinput);

//PRE: path must be a char* created in the checkToken function
//POST: RV = true iff the path is valid according to the assumptions
//made in the README
bool checkPath(char* path);

//PRE: path must be a char* created in the checkToken function. This
//function can ONLY be used for rm.
//POST: RV = true iff the path is valid according to the assumptions
//made in the README
bool checkPathRM(char* pathString);

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateFormat(LinkedList<MyString> tokenList, bool & validToken,
		    char* commandString);

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateDefrag(LinkedList<MyString> tokenList, bool & validToken,
		    char* commandString);

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validatePWD(LinkedList<MyString> tokenList, bool & validToken,
		    char* commandString);

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateLS(LinkedList<MyString> tokenList, bool & validToken,
		    char* commandString);

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateCD(LinkedList<MyString> tokenList, bool & validToken,
		    char* commandString);

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateMKDIR(LinkedList<MyString> tokenList, bool & validToken,
		    char* commandString);

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateRM(LinkedList<MyString> tokenList, bool & validToken,
		    char* commandString);

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateRMDIR(LinkedList<MyString> tokenList, bool & validToken,
		    char* commandString);

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateCP(LinkedList<MyString> tokenList, bool & validToken,
		    char* commandString);

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateCAT(LinkedList<MyString> tokenList, bool & validToken,
		    char* commandString);

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateDISPLAYINODE(LinkedList<MyString> tokenList, bool & validToken,
			  char* commandString, fileSys & myFileSys);

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateDU(LinkedList<MyString> tokenList, bool & validToken,
		    char* commandString);

//PRE:  tokenList must be non NULL.
//POST: RV = true iff there are no errors within the tokenList
bool checkToken(LinkedList<MyString> tokenList, fileSys & myFileSys);

//PRE:
//POST: Prompts the user for a cmd and if it is a valid comand, passes
//it to evaluate
void startShell(int diskSize);

//PRE:
//POST: puts the user's command into userCommand
void createCommand(char curr_ch, MyString & userCommand);

#endif
