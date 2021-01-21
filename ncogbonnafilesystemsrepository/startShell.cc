#include "startShell.h"
#include "evaluate.h"
#include <iostream>
#include <fstream>
using namespace std;
//PRE:
//POST: RV = what the user typed into the terminal in
//LinkeList<MyString> form where every relevant piece of the user's
//input is broken up into nodes
LinkedList<MyString> tokenize(char* userinput){
  LinkedList<MyString> userCMD;//will hold the list of tokens from the
			       //user's input
  int user_index = 0;
  bool done = false;
  while (!done){
    MyString token; //Will hold a word from the user's input
    while ((userinput[user_index] != aSpace) &&
	   (userinput[user_index] != EOS)){
      //we have not read a word
      char ch = userinput[user_index];//will hold a letter from the userinput
      token.addchar(ch);
      user_index++;
    }
    //ASSERT: we have a full word to put in the userCMD
    //Collorary: user index is either a space or a newline
    userCMD.append(token);
    //ASSERT: token has been added to userCMD
    if (userinput[user_index] == EOS){
      //ASSERT: we have read the entire user input
      done = true;
    }
    else{
      //ASSERT: userinput[user_index] is a space
      user_index++;
      //read past space
    }
  }
  //ASSERT: userCMD contains all tokens from the user
  return (userCMD);
}

//PRE: path must be a char* created in the checkToken function. This
//function cannat be used for rm.
//POST: RV = true iff the path is valid according to the assumptions
//made in the README
bool checkPath(char* pathString){
  bool alphaNumeric = true;
  char ch;//will hold a character from pathString
  int index;
  while (ch != EOS){
    ch = pathString[index];
    if(((ch >= CHAR0) && (ch <= CHAR9)) || ((ch >= UPPERA) && (ch <= UPPERZ))
       || ((ch <= LOWERA) && (ch >= LOWERZ)) || (ch == FWDSLASH) ||
       (ch == PERIOD)){
      //ASSERT: ch is alpha numeric or the '/' chartacter OR THE '.'
      //character
    }
    else{
      alphaNumeric = false;
    }
  }
  //ASSERT: If all characters in the string were alpha numeric or the
  //'/' chartacter OR THE '.' character, alphaNumeric is true.
  //otherwise, alphaNumeric is false.
  return alphaNumeric;
}

//PRE: path must be a char* created in the checkToken function. This
//function can ONLY be used for rm.
//POST: RV = true iff the path is valid according to the assumptions
//made in the README
bool checkPathRM(char* pathString){
  bool alphaNumeric = true;
  char ch;//will hold a character from pathString
  int index;
  while (ch != EOS){
    ch = pathString[index];
    if(((ch >= CHAR0) && (ch <= CHAR9)) || ((ch >= UPPERA) && (ch <= UPPERZ))
       || ((ch <= LOWERA) && (ch >= LOWERZ)) || (ch == FWDSLASH) ||
       (ch == PERIOD) || (ch == STAR)){
      //ASSERT: ch is alpha numeric or the '/' chartacter OR THE '.'
      //or the '*' character
    }
    else{
      alphaNumeric = false;
    }
  }
  //ASSERT: If all characters in the string were alpha numeric or the
  //'/' chartacter OR THE '.' or the '*' character, alphaNumeric is true.
  //otherwise, alphaNumeric is false.
  return alphaNumeric;
}
//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateFormat(LinkedList<MyString> tokenList, bool & validToken,
		    char* commandString){
  //ASSERT: user typed in a valid cmd
  if(tokenList.getSize() == 1){
    validToken = true;
  }
  else{
    //user put an invalid number of parameters
    cout << "invalid # of parameters" << endl;
  }
}

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateDefrag(LinkedList<MyString> tokenList, bool & validToken,
		    char* commandString){
  //ASSERT: user typed in a valid cmd
  if(tokenList.getSize() == 1){
    validToken = true;
  }
  else{
    //user put an invalid number of parameters
    cout << "invalid # of parameters" << endl;
  }
}

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validatePWD(LinkedList<MyString> tokenList, bool & validToken,
		 char* commandString){
  //ASSERT: user typed in a valid cmd
    if(tokenList.getSize() == 1){
    validToken = true;
    }
    else{
      //user put an invalid number of parameters
      cout << "invalid # of parameters" << endl;
    }
}

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateLS(LinkedList<MyString> tokenList, bool & validToken,
		char* commandString){
  //ASSERT: user typed in a valid cmd
    if(tokenList.getSize() == 1){
    validToken = true;
    }
    else{
      if (tokenList.getSize() == 2){
	//ASSERT: a path was given with the cmd
	MyString* path = tokenList.getNth(1);
	char* pathString = path->getstring();
	validToken = checkPath(pathString);
	//ASSERT: validToken is true iff the path is valid according to
	//the README
	if(!validToken){
	  cout << "path for LS was invalid" << endl;
	}
      }
      else{
	//ASSERT: user put in more than 2 tokens
	cout << "invalid # of parameters" << endl;
      }
    }
}

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateCD(LinkedList<MyString> tokenList, bool & validToken,
		char* commandString){
  //ASSERT: user typed in a valid cmd
  if(tokenList.getSize() == 1){
    validToken = true;
  }
  else{
    if (tokenList.getSize() == 2){
      //ASSERT: a path was given with the cmd
      MyString* path = tokenList.getNth(1);
      char* pathString = path->getstring();
      validToken = checkPath(pathString);
      //ASSERT: validToken is true iff the path is valid according to
      //the README
      if(!validToken){
	cout << "path for CD was invalid" << endl;
      }
    }
    else{
      //ASSERT: user put in more than 2 tokens
      cout << "invalid # of parameters" << endl;
    }
  }
}

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateMKDIR(LinkedList<MyString> tokenList, bool & validToken,
		   char* commandString){
  //ASSERT: user typed in a valid cmd
  if (tokenList.getSize() == 2){
    MyString* path = tokenList.getNth(1);
    char* pathString = path->getstring();
    validToken = checkPath(pathString);
    //ASSERT: validToken is true iff the path is valid according to
    //the README
    if(!validToken){
      cout << "path for MKDIR was invalid" << endl;
    }
  }
  else{
    //ASSERT: user put in more than 2 tokens
    cout << "invalid # of parameters" << endl;
  }
}

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateRM(LinkedList<MyString> tokenList, bool & validToken,
		char* commandString){
  //ASSERT: a path was given with the cmd
  if (tokenList.getSize() == 2){
    MyString* path = tokenList.getNth(1);
    char* pathString = path->getstring();
    validToken = checkPathRM(pathString);
    //ASSERT: validToken is true iff the path is valid according to
    //the README
    if(!validToken){
      cout << "path for RM was invalid" << endl;
    }
  }
  else{
    //ASSERT: user put in more than 2 tokens
    cout << "invalid # of parameters" << endl;
  }
}

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateRMDIR(LinkedList<MyString> tokenList, bool & validToken,
		   char* commandString){
  //ASSERT: user typed in a valid cmd
  MyString* path = tokenList.getNth(1);
  char* pathString = path->getstring();
  validToken = checkPath(pathString);
  //ASSERT: validToken is true iff the path is valid according to
  //the README
  if(!validToken){
    cout << "path for RMDIR was invalid" << endl;
  }
}

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateCP(LinkedList<MyString> tokenList, bool & validToken,
		char* commandString){
  //ASSERT: user typed in a valid cmd
  if ((tokenList.getSize() != 3) || (tokenList.getSize() != 4)){
    //ASSERT: user typed in too many or too little number of
    //parameters
    cout << "invalid # of parameters" << endl;
  }
  else{
    if (tokenList.getSize() == 3){
      //ASSERT: user gave no optional parameters
      MyString* path1 = tokenList.getNth(1);
      char* path1String = path1->getstring();
      validToken = checkPath(path1String);
      //ASSERT: validToken is true iff the path is valid according to
      //the README
      if(!validToken){
	cout << "path1 for CP was invalid" << endl;
      }
      //ASSERT: source modification parameter is correct
      MyString* path2 = tokenList.getNth(2);
      char* path2String = path2->getstring();
      validToken = checkPath(path2String);
      //ASSERT: validToken is true iff the path is valid according to
      //the README
      if(!validToken){
	cout << "path2 for CP was invalid" << endl;
      }
    }
    else if (tokenList.getSize() == 4){
      //ASSERT: the optional parameter was given
      MyString* sourceModifier = tokenList.getNth(1);
      char* sourceString = sourceModifier->getstring();
      if ((isEqualString(sourceString, lessThanString)) ||
	  (isEqualString(sourceString, greaterThanString))){
	//ASSERT: source modification parameter is correct
	MyString* path1 = tokenList.getNth(2);
	char* path1String = path1->getstring();
	validToken = checkPath(path1String);
	//ASSERT: validToken is true iff the path is valid according to
	//the README
	if(!validToken){
	  cout << "path1 for CP was invalid" << endl;
	}
	//ASSERT: source modification parameter is correct
	MyString* path2 = tokenList.getNth(3);
	char* path2String = path2->getstring();
	validToken = checkPath(path2String);
	//ASSERT: validToken is true iff the path is valid according to
	//the README
	if(!validToken){
	  cout << "path2 for CP was invalid" << endl;
	}
      }
    }
  }
}

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateCAT(LinkedList<MyString> tokenList, bool & validToken,
		 char* commandString){
  //ASSERT: user typed in a valid cmd
  if ((tokenList.getSize() != 2) || (tokenList.getSize() != 3)){
    //ASSERT: user typed in too many or too little number of
    //parameters
    cout << "invalid # of parameters" << endl;
  }
  else{
    if (tokenList.getSize() == 2){
      //ASSERT: only a path was given with the cmd
      MyString* path = tokenList.getNth(1);
      char* pathString = path->getstring();
      validToken = checkPath(pathString);
      //ASSERT: validToken is true iff the path is valid according to
      //the README
      if(!validToken){
	cout << "path for CAT was invalid" << endl;
      }
    }
    else if (tokenList.getSize() == 3){
      //ASSERT: the optional parameter was given
      MyString* Flag = tokenList.getNth(1);
      char* flagString = Flag->getstring();
      if (isEqualString(flagString, LOWERH)){
	//ASSERT: flag parameter is correct
	MyString* path = tokenList.getNth(2);
	char* path1String = path->getstring();
	validToken = checkPath(path1String);
	//ASSERT: validToken is true iff the path is valid according to
	//the README
	if(!validToken){
	  cout << "path for CAT was invalid" << endl;
	}
      }
    }
  }
}

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateDISPLAYINODE(LinkedList<MyString> tokenList, bool & validToken,
			  char* commandString, fileSys & myFileSys){
  //ASSERT: user typed in a valid cmd
  if((tokenList.getSize() != 1) && (tokenList.getSize() != 3)){
    //user put an invalid number of parameters
    cout << "invalid # of parameters" << endl;
  }
  else{
    if(tokenList.getSize() == 1){
      //user wants the default call of this cmd
      validToken = true;
    }
    else{
      //ASSERT: tokenList must be of size 3
      //COLLORARY: the user typed in bounds for their content to be
      //outputted
      MyString* myN = tokenList.getNth(1);
      char* nString = myN->getstring();
      int n = strToInt(nString);
      MyString* myM = tokenList.getNth(2);
      char* mString = myN->getstring();
      int m = strToInt(mString);
      int MAXM = myFileSys.getDiskSize();
      if ((n >= 0) && (m <= MAXM) && (n <= m)){
	validToken = true;
      }
    }
  }
}

//PRE: validToken must be initialized to false. commandString must be
//a representation of the head of the tokenList
//POST: validToken is true iff user typed in all valid parameters for
//the cmd associated with this function (cmd is located after the word
//validate in this fuction's name)
void validateDU(LinkedList<MyString> tokenList, bool & validToken,
		char* commandString){
  //ASSERT: user typed in a valid cmd
  if(tokenList.getSize() == 1){
    validToken = true;
  }
  else{
    if (tokenList.getSize() == 2){
      //ASSERT: a path was given with the cmd
      MyString* path = tokenList.getNth(1);
      char* pathString = path->getstring();
      validToken = checkPath(pathString);
      //ASSERT: validToken is true iff the path is valid according to
      //the README
      if(!validToken){
	cout << "path for DU was invalid" << endl;
      }
    }
    else{
      //ASSERT: user put in more than 2 tokens
      cout << "invalid # of parameters" << endl;
    }
  }
}

//PRE:  tokenList must be non NULL.
//POST: RV = true iff there are no inValidities within the tokenList
bool checkToken(LinkedList<MyString> tokenList, fileSys & myFileSys){
  //Validity check for every cmd to ensure they follow the assumptions
  //made in the readme
  bool validToken = false;
  MyString* command = tokenList.getHead();
  char* commandString = command->getstring();
  if (isEqualString(commandString, FORMAT)){
    validateFormat(tokenList, validToken, commandString);
  }
  else if (isEqualString(commandString, DEFRAG)){
    validateDefrag(tokenList, validToken, commandString);
  }
  else if (isEqualString(commandString, PWD)){
    validatePWD(tokenList, validToken, commandString);
  }
  else if (isEqualString(commandString, LS)){
    validateLS(tokenList, validToken, commandString);
  }
  else if (isEqualString(commandString, CD)){
    validateCD(tokenList, validToken, commandString);
  }
  else if (isEqualString(commandString, MKDIR)){
    validateMKDIR(tokenList, validToken, commandString);
  }
  else if (isEqualString(commandString, RM)){
    validateRM(tokenList, validToken, commandString);
  }
  else if (isEqualString(commandString, RMDIR)){
    validateRMDIR(tokenList, validToken, commandString);
  }
  else if (isEqualString(commandString, CP)){
    validateCP(tokenList, validToken, commandString);
  }
  else if (isEqualString(commandString, CAT)){
    validateCAT(tokenList, validToken, commandString);
  }
  else if (isEqualString(commandString, DISPLAYINODE)){
    validateDISPLAYINODE(tokenList, validToken, commandString, myFileSys);
  }
  else if (isEqualString(commandString, DU)){
    validateDU(tokenList, validToken, commandString);
  }
  else if (isEqualString(commandString, EXIT)){
    validToken == true;
  }
}
//PRE:
//POST: puts the user's command into userCommand
void createCommand(char curr_ch, MyString & userCommand){
  cout << "F>";
  curr_ch = cin.get();
  while(curr_ch != newLine){
    userCommand.addchar(curr_ch);
    curr_ch = cin.get();
  }
}

//PRE:
//POST: Prompts the user for a cmd and if it is a valid comand, passes
//it to evaluate
void startShell(int diskSize){
  char curr_ch;
  MyString userCommand;
  bool done = false; //represents when the main while loop is done
  fileSys myFileSys(diskSize);
  createCommand(curr_ch, userCommand);
  //ASSERT: curr_ch == '\n' => we have read everything that the user typed
  //        into the terminal
  while (!done){
    char* curr_command = userCommand.getstring();
    //ASSERT: user has not typed in the exit cmd into the terminal
    LinkedList<MyString> tokenList = tokenize(curr_command);
    //ASSERT: tokenList is a linked list of MyString characters that
    //represent the user's command
    bool validToken = checkToken(tokenList, myFileSys);
    //assert: validToken true iff the entirety of the token is valid
    if (validToken){
      //ASERT: the cmd the user typed in (curr_command) was valid
      //along with the possible 
      //operands that could accomany those cmds.
      if(isEqualString(curr_command, EXIT)){
	//ASSERT: the user wants to be finished
	done = true;
	fstream* diskFile = myFileSys.getDiskFile();
	diskFile->close();
      }
      else{
	//ASSERT: the user is not finished with his/her/it's
	//simulation
	evaluate_command(tokenList, myFileSys);
      }
      //ASSERT: We've done SOMETHING regarding the current command the
      //user typed
    }
    else{
      //ASSERT: user typed in something nonvalid
      cout << "ERROR: User typed something invalid" << endl;
    }
    if (!done){
      //ASSERT: the user has not typed in exit
      MyString nextCMD;
      createCommand(curr_ch, nextCMD);
      userCommand = nextCMD;
    }
  }
  //ASSERT: we are finished with our simulation of the fileSystem
}
