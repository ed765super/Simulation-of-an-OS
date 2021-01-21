//Author: Nicholas Ogbonna
#include "start_shell.h"
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

//PRE: tokenList must be non NULL. sizeofmemory should be the size of the memory
//POST: RV = true iff there are no errors within the tokenList
bool checkToken(LinkedList<MyString> tokenList, int sizeofmemory){
  bool validToken = false;
  MyString* command = tokenList.getHead();
  char* commandString = command->getstring();
  if (isEqualString(commandString, LOAD)){
    if (tokenList.getSize() == 2){
      //there's a name snagged along with this command
      validToken = true;
    }
  }
  else if (isEqualString(commandString, MEM)){
    //ASSERT: user wants to see the memory
    validToken = true;
    if (tokenList.getSize() == 2){
      //There is a parameter
      MyString* startMEM = tokenList.getNth(1);
      char* startMEMstring = startMEM->getstring();
      //ASSERT: startMEM is the representation address where the user
      //wants to start printing
      int startSize = startMEM->length();//Holds how many digits are in
      //startSize
      int curr_digit = 0;
      bool startIsDigit;//Will turn true iff the first operand of MEM is a
      //digit
      while (curr_digit < startSize){
	startIsDigit = isDigit(startMEMstring[curr_digit]);
	curr_digit++;
      }
      if (startIsDigit){
	if ((*startMEMstring >= CHAR0) &&
	    (*startMEMstring < sizeofmemory)){
	  //ASSERT: the start is valid
	  validToken = true;
	}
	else{
	  validToken = false;
	}
      }
      if (tokenList.getSize() == 3){
	//ASSERT: there is a 2nd parameter
	MyString* finishMEM = tokenList.getNth(2);
	char* finishMEMstring = finishMEM->getstring();
	//ASSERT: finishMEM is the representation of address where the
	//user wants to stop printing
    
	int endSize = finishMEM->length(); //Holds how many digits are in
	//finishMEM
    
	curr_digit = 0;
	bool endIsDigit;//Will turn true iff the 2nd operand of MEM is a
	//digit
	while (curr_digit < startSize){
	  endIsDigit = isDigit(finishMEMstring[curr_digit]);
	  curr_digit++;
	}
	if (endIsDigit){
	  if ((*finishMEMstring <= (char)sizeofmemory) &&
	      (*finishMEMstring > *startMEMstring)){
	    //ASSERT: the end is valid
	    validToken = true;
	  }
	  else{
	    validToken = false;
	  }
	}
      }
    }
  }
  else if(isEqualString(commandString, CPU)){
    //ASSERT: user wants to see the status of the CPU
    /*nothing additional to check*/
    validToken = true;
  }
  else if(isEqualString(commandString, STEP)){
    //ASSERT: user wishes to step
    if (tokenList.getSize() == 2){
      MyString* numofSteps = tokenList.getNth(1);
      int numDigitsofStep = numofSteps->length();
      char* numStepString = numofSteps->getstring();
      int cdigit = 0;
      bool pStepIsDigit;//Will turn true iff the first operand of MEM is a
      //digit
      while (cdigit < numDigitsofStep){
      pStepIsDigit = isDigit(numStepString[cdigit]);
      cdigit++;
      }
      if (pStepIsDigit){
	//ASSERT: The parameter the user gave is some number
	if (*numStepString > CHAR0){
	  //ASSERT: The parameter the user gave is a non-negative number
	  validToken = true;
	}
      }
    }
  }
  else if(isEqualString(commandString, RUN)){
    //ASSERT: user wishes to run
    /*nothing more to check*/
    validToken = true;
  }
  else if(isEqualString(commandString, EXIT)){
    //ASSERT: user wishes to stop the simulation
    /*nothing more to check*/
    validToken = true;
  }
  else if(isEqualString(commandString, FREEMEM)){
    validToken = true;
  }
  else if(isEqualString(commandString, JOBS)){
    validToken = true;
  }
  else if(isEqualString(commandString, KILL)){
    MyString* killID = tokenList.getNth(1);
    int lengthOfID = killID->length();
    char* killIDString = killID->getstring();
    int cdigit = 0;
    bool idIsDigit;//Will turn true iff the first operand of KILL is a
		      //digit
    while (cdigit < lengthOfID){
      idIsDigit = isDigit(killIDString[cdigit]);
      cdigit++;
    }
    if (idIsDigit){
      //ASSERT: The parameter the user gave is some number
      if (*killIDString > CHAR0){
	//ASSERT: The parameter the user gave is a non-negative number
	validToken = true;
      }
    }
  }
  else{
    //ASSERT: the command the user typed is not one of the valid
    //strings
    if (!validToken){
    cout << "ERROR: invalid command" << endl;
    }
  }
  //ASSERT: we have checked the user's input
  return (validToken);
}

//PRE:
//POST: puts the user's command into userCommand
void createCommand(char curr_ch, MyString & userCommand){
  cout << ">";
  curr_ch = cin.get();
  while(curr_ch != newLine){
    userCommand.addchar(curr_ch);
    curr_ch = cin.get();
  }
}
  
//PRE:
//POST: Prompts the user for a cmd and if it is a valid comand, passes
//it to evaluate for interpretation, and does one of the following
//depending on what linkedlist evaluate spits back:
//if evaluate returns load: do nothing
//if evaluate returns mem: OS will contain the contents of memory from
//the linkedlist[1] to linkedlist[2].
//if evaluate returns cpu: OS will contain the contents of PC on one
//line then the contents of all the following registers 4 on a line.

void start_shell(Simulator & MySimulator, OS & myOS) {
  char curr_ch;
  MyString userCommand;
  bool done = false; //represents when the main while loop is done
  createCommand(curr_ch, userCommand);
  //ASSERT: curr_ch == '\n' => we have read everything that the user typed
  //        into the terminal
  while (!done){
    char* curr_command = userCommand.getstring();
    //ASSERT: user has not typed in the exit cmd into the terminal
    LinkedList<MyString> tokenList = tokenize(curr_command);
    //ASSERT: tokenList is a linked list of MyString characters that
    //represent the user's command
    int sizeOfMemory = MySimulator.memSize();
    bool validToken = checkToken(tokenList, sizeOfMemory);
    //check whether the entirety of the token is valid
    if (validToken){
      //ASERT: the cmd the user typed in (curr_command) was valid
      //along with the possible 
      //operands that could accomany those cmds.
      if(isEqualString(curr_command, EXIT)){
	//ASSERT: the user wants to be finished
	done = true;
      }
      else{
	//ASSERT: the user is not finished with his/her/it's
	//simulation
	evaluate_command(tokenList, MySimulator, myOS);
      }
      //ASSERT: We've done SOMETHING regarding the current command the
      //user typed
    }
    else{
      //ASSERT: user typed in something nonvalid
      cout << "ERROR: non-valid entry" << endl;
    }
    if (!done){
      //ASSERT: the user has not typed in exit
      MyString nextCMD;
      createCommand(curr_ch, nextCMD);
      userCommand = nextCMD;
    }
  }
  //ASSERT: we are finished with our simulation
}
