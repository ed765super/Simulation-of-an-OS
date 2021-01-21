//Author: Nicholas Ogbonna
#include "evaluate.h"
#include "stringFunctions.h"
#include <iostream>
using namespace std;
//PRE: Entirety of tokenList must be valid.  must be initialized
//to false
//POST: Interprets what the tokenList wants to do, calls the member
//function in fileSys that corresponds to the tokenList
void evaluate_command(LinkedList<MyString> tokenList, fileSys & myFileSys){
  MyString* command = tokenList.getHead();
  if (isEqualString(command->getstring(), FORMAT)) {
    myFileSys.handleFormat();
    //ASSERT: disk has been formatted
  }
  else if (isEqualString(command->getstring(), DEFRAG)) {
    myFileSys.handleDefrag();
    //ASSERT: disk has been defragmented
  }
  else if (isEqualString(command->getstring(), PWD)) {
    myFileSys.handlePWD();
    //ASSERT: the absolute path of the present working directory has
    //been displayed on the terminal
  }
  else if (isEqualString(command->getstring(), LS)) {
    if(tokenList.getSize() == 2){
      MyString* userPath = tokenList.getNth(1);
      char* userPathString = userPath->getstring();
      myFileSys.handleLSarg(userPathString);
      //ASSERT: The contents of the directory specified by the path in
      //the parameter are listed in alphabetical order, with
      //four names per line of output to the terminal if path is
      //valid. A suitable error msg is coutted else
    }
    else{
      //ASSERT: user added no parameters
      myFileSys.handleLS();
      //ASSERT: the contents of the present working directory have
      //been put on the terminal ("There is nothing" is coutted if
      //there are no other directories than root)
    }
  }
  else if (isEqualString(command->getstring(), CD)) {
    if(tokenList.getSize() == 2){
      MyString* userPath = tokenList.getNth(1);
      char* userPathString = userPath->getstring();
      myFileSys.handleCDarg(userPathString);
      //ASSERT: the present working directory is modified to be the
      //directory specified by the path in the parameter if path is
      //valid. A suitable error msg is coutted elsewise.
    }
    else{
      myFileSys.handleCD();
      //ASSERT: changed the present working directory to the root
      //directory.
    }
  }
  else if (isEqualString(command->getstring(), MKDIR)) {
    MyString* userPath = tokenList.getNth(1);
    char* userPathString = userPath->getstring();
    myFileSys.handleMKDIR(userPathString);
    //ASSERT: if All intermediate directories in the specified path
    //already exists a new directory specified by the path in the
    //parameter. else A suitable error msg is coutted.
  }
  else if (isEqualString(command->getstring(), RM)) {
    MyString* userPath = tokenList.getNth(1);
    char* userPathString = userPath->getstring();
    myFileSys.handleRM(userPathString);
    //ASSERT: if All intermediate directories in the specified path
    //to the existing file already exists the file specified by the
    //path in the parameter is removed. also if a star is located at
    //the end of the valid path, all files in the directory are
    //removed. if there is any invalidity with the path A suitable
    //error msg is coutted.
  }
  else if (isEqualString(command->getstring(), RMDIR)) {
    MyString* userPath = tokenList.getNth(1);
    char* userPathString = userPath->getstring();
    myFileSys.handleRMDIR(userPathString);
    //ASSERT: if All intermediate directories in the specified path
    //to the existing directory already exists the directory specified by the
    //path in the parameter is removed. if the directory has 1 or more children
    //or an intermediary directory doesnt exist, A suitable
    //error msg is coutted.
  }
  else if (isEqualString(command->getstring(), CP)) {
    if(tokenList.getSize() == 3){
      //ASSERT: user added the optional parameter
      MyString* optionalParameter = tokenList.getNth(1);
      char* oParameterString = optionalParameter->getstring();
      if (isEqualString(oParameterString, lessThanString)){
	//ASSERT: the optional parameter is the character '<', therefore
	//the source should be treated as a path in the Linux file
	//system, and the destination as a path in the simulated file
	//system. if path is valid. A suitable error msg is coutted else.
	MyString* userPathFrom = tokenList.getNth(2);
	char* userPathFromString = userPathFrom->getstring();
	MyString* userPathTo = tokenList.getNth(3);
	char* userPathToString = userPathTo->getstring();
	myFileSys.handleCPlessThan(userPathFromString, userPathToString);
	//ASSERT: if the path is valid, The file specified (as an
	//absolute or relative path) 
	//by the first parameter (source) has been copied as the file
	//specified (as an absolute or relative path) in the second
	//parameter (destination). A suitable msg is coutted
	//otherwise.
      }
      else{
	//ASSERT: the optional parameter is the character '>', therefore
	//the source should be treated as a path in the simulated file
	//system, and the destination as a path in the Linux file
	//system. if path is valid. A suitable error msg is coutted else.
	MyString* userPathFrom = tokenList.getNth(2);
	char* userPathFromString = userPathFrom->getstring();
	MyString* userPathTo = tokenList.getNth(3);
	char* userPathToString = userPathTo->getstring();
	myFileSys.handleCPgreaterThan(userPathFromString, userPathToString);
	//ASSERT: if the path is valid, The file specified (as an
	//absolute or relative path) 
	//by the first parameter (source) has been copied as the file
	//specified (as an absolute or relative path) in the second
	//parameter (destination). A suitable msg is coutted
	//otherwise.
      }
    }
    else{
      //ASSERT: user did not add a '<' or a '>'. therefore both source
      //and destination are to be treated as paths in the simulated file
      //system. if path is valid. A suitable error msg is coutted else.
      MyString* userPathFrom = tokenList.getNth(1);
      char* userPathFromString = userPathFrom->getstring();
      MyString* userPathTo = tokenList.getNth(2);
      char* userPathToString = userPathTo->getstring();
      myFileSys.handleCP(userPathFromString, userPathToString);
      //ASSERT: if the path is valid, The file specified (as an
      //absolute or relative path) 
      //by the first parameter (source) has been copied as the file
      //specified (as an absolute or relative path) in the second
      //parameter (destination). A suitable msg is coutted
      //otherwise.
    }
  }
  else if (isEqualString(command->getstring(), CAT)) {
    bool hFlag; //will hold whether or not the hFlag was given
    if(tokenList.getSize() == 2){
      //ASSERT: the user did not indicate the 'h' flag
      MyString* userPath = tokenList.getNth(1);
      char* userPathString = userPath->getstring();
      hFlag = false;
      myFileSys.handleCAT(userPathString, hFlag);
      //ASSERT: the contents of the file the user's path specified has been
      //displayed as characters iff the path was valid and the file
      //existed. A suitable error msg is coutted else.
    }
    else{
      //ASSERT: the user did give the hFlag
      MyString* userPath = tokenList.getNth(1);
      char* userPathString = userPath->getstring();
      hFlag = true;
      myFileSys.handleCAT(userPathString, hFlag);
      //ASSERT: the contents of the file in the user's path specified has been
      //displayed as hexidecimals iff the path was valid and the file
      //exists. A suitable error msg is coutted else.
    }
  }
  else if (isEqualString(command->getstring(), DISPLAYINODE)) {
    if(tokenList.getSize() == 1){
      //ASSERT: No parameters have been specified
      myFileSys.handleDisplayInode();
      //ASSERT: all the contents of inodes numbered are
      //displayed on the terminal s.t. each inode was displayed on
      //three lines, one line for the inode number and two lines for
      //the contents of the inode
    }
    else{
      //ASSERT: user gave the optional n & m parameters.
      MyString* n = tokenList.getNth(1);
      char* nString = n->getstring();
      int nInt = strToInt(nString);
      MyString* m = tokenList.getNth(2);
      char* mString = m->getstring();
      int mInt = strToInt(mString);
      myFileSys.handleDisplayInodeArg(nInt, mInt);
      //ASSERT: the contents of inodes numbered n through m are
      //displayed on the terminal s.t. each inode was displayed on
      //three lines, one line for the inode number and two lines for
      //the contents of the inode. if n or m are out of bounds, an eror
      //is coutted respectively (respectively in the sense that
      //the error will let the user know which parameter was out of
      //bounds.
    }
  }
  else if (isEqualString(command->getstring(), DU)) {
    if(tokenList.getSize() == 2){
      //ASSERT: the user added the optional parameter
      MyString* userPath = tokenList.getNth(1);
      char* userPathString = userPath->getstring();
      myFileSys.handleDUarg(userPathString);
      //ASSERT: The size, in bytes, of the directory specified by the
      //path in the parameter is printed out. iff path is
      //valid. A suitable error msg is coutted else
    }
    else{
      //ASSERT: user did not add the optional parameter
      myFileSys.handleDU();
      //ASSERT: The size of the present working directory has been
      //printed to the terminal. 
    }
  } 
}
