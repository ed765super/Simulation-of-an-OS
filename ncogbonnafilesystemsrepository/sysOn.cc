//Author: Nicholas Ogbonna
#include "constants.h"
#include "stringFunctions.h"
#include "startShell.h"
#include "fileSys.h"
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char ** argv){
  if ((argc < 1) || (argc > 2)) {
    cout << "ERROR: You must have at least 1 (but no more than 2) argument(s)"
         << "for the executable" << endl;
  }
  else {
    //ASSERT: user has the correct number of parameters
    if (argc == 1){
      //ASSERT: user didn't type an additional parameter
      int diskSize = 16;//diskSize is the default number of nodes
      startShell(diskSize);
    }
    else{
      //ASSERT: user typed in an additional parameter
      bool isInt = true; //false iff user typed in something invalid
      char* userParameter = argv[1];
      int index = 0;
      char ch = userParameter[index];//will hold a character from userParameter
      while ((ch != EOS) && (isInt)){
	if(!isDigit(ch)){
	  isInt = false;
	}
	index++;
	ch = userParameter[index];
      }
      if(isInt){
	int diskSize = strToInt(userParameter);//diskSize is equal to the
	                                       //integer version of what
	                                       //the user typed
	startShell(diskSize);
      }
      else{
	cout << "ERROR: optional parameter must be a positive integer" << endl;
      }
    }
  }
  return (0);
}
  
