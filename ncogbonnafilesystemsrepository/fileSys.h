#ifndef INCLUDED_FILE_SYSTEM
#define INCLUDED_FILE_SYSTEM
#include "iNode.h"
#include "superBlock.h"
#include "directoryNode.h"
#include "fileNode.h"
#include "contentNode.h"
#include "freeNode.h"
#include "constants.h"
#include <fstream>
using namespace std;
class fileSys{
  //CI: The iNodes of the fileSystem start @ 0.The file system is
  //byte-addressable i.e the address of word number 0 of inode 0 will
  //be 0, the address of word number 1 of inode 0 will be 4,
  //etc. Inode 0 will always be a superblock inode, and no other inode
  //will be a superblock inode. Inode 1 will be the inode for the root
  //directory.
  
 private:
  fstream* diskFile; //will hold a pointer to the disk
  int currentWorkingDirectory; //ID of the iNode representing the current
			       //working directory
  int fileSysSize; //will hold the number of inodes the user asked for
  
 public:
  //Constructor
  //PRE:
  //POST: creates a fileSystem object
  fileSys(int diskSize);

  //destructor
  //PRE:
  //POST: destoys this object
  ~fileSys();

  //copy constructor
  //PRE:
  //POST: Makes a deep copy of pFileSys to this object
  fileSys(const fileSys & pFileSys);
  
  //GETTERS
  //PRE: this object is defined
  //POST: RV =  the member data object associated with this function.
  fstream* getDiskFile() const;

  //PRE: this object is defined
  //POST: RV = iNode ID representing the current working directory
  int getCurrDirectory() const;

  //PRE: this object is defined
  //POST: RV =  the member data object associated with this function.
  int getDiskSize() const;
  
  //SETTERS
  //PRE: this object is defined & parameter is an unsigned int that
  //would represent the member data object associated with this function.
  //POST: modifies the member data object associated with this function. s.t.
  //it is equal to the parameter
  void setDiskFile(fstream* pDiskFile);

  //PRE: this object is defined & parameter is an unsigned int that
  //would represent the member data object associated with this function.
  //POST: modifies the member data object associated with this function. s.t.
  //it is equal to the parameter
  void setCurrDirectory(int pDirectory);
  
  //PRE: this object is defined & parameter is an unsigned int that
  //would represent the member data object associated with this function.
  //POST: modifies the member data object associated with this function. s.t.
  //it is equal to the parameter.
  void setDiskSize(int pDiskSize);
  
  //Translate modifications
  //PRE: iNodeID has to represent the ID of the node you want to seekp to
  //POST: sets the cursor to the first word of the ID
  void findInode(int iNodeID);

  //PRE: newNode should be some form of Inode that you want to modify
  //the node that the cursor is currently at to.
  //POST: modifies the node in diskfile that the cursor is currently at
  //s.t. it is now equal to newNode
  void modifyInode(iNode newNode);
  
  //HANDLES
  //Note: all handles have the prerequisite: this object must be
  //declared & defined.
  //Note: all parameters must have followed The prerequisites
  //defined in the README.
  
  //PRE:
  //POST: disk has been formatted. Formatted: he file system will now
  //have the root directory with no children. Thus, all inodes
  //numbered 2 and above will be free/unused inodes.
  void handleFormat();

  //PRE:
  //POST: disk has been defragmented. Defragmented: All the used
  //inodes are moved towards the top of the file system so that all
  //the unused inodes are contiguous and at the end of the file
  //system. Thus, there will be some inode x so that all inodes y
  //where y >= x are unused inodes, and all inodes y where y < x are
  //used inodes. 
  void handleDefrag();

  //PRE:
  //POST: the absolute path of the present working directory has
  //been displayed on the terminal
  void handlePWD();

  //PRE: 
  //POST: the contents of the present working directory have
  //been put on the terminal ("There is nothing" is coutted if
  //there are no other directories than root)
  void handleLS();

  //PRE: userPathString must be in the format of a "path".
  //POST: The contents of the directory specified by the path in
  //the parameter are listed in alphabetical order, with
  //four names per line of output to the terminal if path is
  //valid. A suitable error msg is coutted otherwise
  void handleLSarg(char* userPathString);

  //PRE:
  //POST: changed the present working directory to the root
  //directory.
  void handleCD();

  //PRE: userPathString must be in the format of a "path".
  //POST: the present working directory is modified to be the
  //directory specified by the path in the parameter if path is
  //valid. Else A suitable error msg is coutted.
  void handleCDarg(char* userPathString);

  //PRE: userPathString must be in the format of a "path".
  //POST: if All intermediate directories in the specified path
  //already exists a new directory specified by the path in the
  //parameter. else A suitable error msg is coutted.
  void handleMKDIR(char* userPathString);

  //PRE: userPathString must be in the format of a "path".
  //POST: if All intermediate directories in the specified path
  //to the existing file already exists the file specified by the
  //path in the parameter is removed. also if a star is located at
  //the end of the valid path, all files in the directory are
  //removed. if there is any invalidity with the path A suitable
  //error msg is coutted.
  void handleRM(char* userPathString);

  //PRE: userPathString must be in the format of a "path".
  //POST: if All intermediate directories in the specified path
  //to the existing directory already exists the directory specified by the
  //path in the parameter is removed. if the directory has 1 or more children
  //or an intermediary directory doesnt exist, A suitable
  //error msg is coutted.
  void handleRMDIR(char* userPathString);

  //PRE: both parameters must be in the format of a "path".
  //POST: if the path is valid, The file specified (as an
  //absolute or relative path) 
  //by the first parameter (source) has been copied as the file
  //specified (as an absolute or relative path) in the second
  //parameter (destination). In this particular instance,
  //the source is treated as a path in the Linux file
  //system, and the destination is treated as a path in the simulated file
  //system. if path is valid. A suitable error msg is coutted else.
  void handleCPlessThan(char* userPathFromString, char* userPathToString);

  //PRE: both parameters must be in the format of a "path".
  //POST: if the path is valid, The file specified (as an
  //absolute or relative path) 
  //by the first parameter (source) has been copied as the file
  //specified (as an absolute or relative path) in the second
  //parameter (destination). in this particular instance the source is
  //treated as a path in the simulated file 
  //system, and the destination is treated as a path in the Linux file
  //system. if path is valid. A suitable msg is coutted
  //otherwise.
  void handleCPgreaterThan(char* userPathFromString, char* userPathToString);

  //PRE: both parameters must be in the format of a "path".
  //POST: if the path is valid, The file specified (as an
  //absolute or relative path) 
  //by the first parameter (source) has been copied as the file
  //specified (as an absolute or relative path) in the second
  //parameter (destination). both source
  //and destination are to be treated as paths in the simulated file
  //system. if path is valid. A suitable error msg is coutted else.
  void handleCP(char* userPathFromString, char* userPathToString);

  //PRE: hFlag must represent a boolean that is true iff the user
  //typed in the 'h' flag or not. userPathString must be in the format
  //of a "path".
  //POST: the contents of the file the user's path specified has been
  //displayed as characters or hexidecimals (dependant on whether
  //hFlag is false/true respectively) iff the path was valid and the file
  //existed. A suitable error msg is coutted else.
  void handleCAT(char* userPathString, bool hFlag);

  //PRE:
  //POST: all the contents of inodes numbered are
  //displayed on the terminal s.t. each inode was displayed on
  //three lines, one line for the inode number and two lines for
  //the contents of the inode
  void handleDisplayInode();

  //PRE: n & m must satisfy the assumptions made in the readMe.
  //POST: the contents of inodes numbered n through m are
  //displayed on the terminal s.t. each inode was displayed on
  //three lines, one line for the inode number and two lines for
  //the contents of the inode. if n or m are out of bounds, an eror
  //is coutted respectively (respectively in the sense that
  //the error will let the user know which parameter was out of
  //bounds.
  void handleDisplayInodeArg(int n, int m);

  //PRE:
  //POST: The size of the present working directory has been
  //printed to the terminal. 
  void handleDU();

  //PRE: userPathString must be in the format of a "path".
  //POST: The size, in bytes, of the directory specified by the
  //path in the parameter is printed out. iff path is
  //valid. A suitable error msg is coutted elsewise.
  void handleDUarg(char* userPathString);
};
#endif
