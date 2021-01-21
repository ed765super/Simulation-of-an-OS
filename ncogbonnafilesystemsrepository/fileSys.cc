#include "fileSys.h"
#include <iostream>
#include <stdio.h>
using namespace std;
//Constructor
//PRE:
//POST: creates a fileSystem object
fileSys::fileSys(int diskSize){
  fileSysSize = diskSize;
  
  ofstream outputFile("disk");
  //ASSERT: disk has been created
  outputFile.close();
  fstream* pDiskPtr = new fstream;
  pDiskPtr->open("disk", ios::in | ios::out);
  //ASSERT: diskFile now points to outputFile
  diskFile = pDiskPtr;
  
  unsigned int superBlockData[NODESIZE];
  superBlock newSuperBlock(superBlockData);
  //ASSERT: superBlock node has been created
  newSuperBlock.setInodeAddress(0);
  //ASSERT: sets the iNode address of the superBlock
  unsigned int firstFreeNode = 0x00000002;
  newSuperBlock.setFirstFreeNode(firstFreeNode);
  //ASSERT: first free node is the left child of root
  unsigned int totalFreeNodes = diskSize - 1;
  totalFreeNodes = totalFreeNodes << (NIBBLE * 4);
  //shifts totalFreeNodes 4 nibbles (2 bytes)
  newSuperBlock.setNumFreeNodes(totalFreeNodes);
  //ASSERT: freeNodes have been set
  newSuperBlock.setTotalNodes(diskSize);
  //ASSERT: total nodes have been set.
  //Collorary: newSuperBlock is ready to be put on the disk
  modifyInode(newSuperBlock);
  //ASSERT:disk contains the superBlock

  unsigned int rootData[NODESIZE];
  directoryNode root(rootData);
  //ASSERT: root node has been created
  root.setInodeAddress(1);
  //ASSERT: sets the iNode address of root
  unsigned int rootName = '/';
  rootName = rootName << (NIBBLE * 4); //shifts typeAndName 4 nibbles
  unsigned int pName[5];
  pName[0] = rootName;
  root.setName(pName);
  //ASSERT: name has been set
  unsigned int rootType = 0x0;
  root.setType(rootType);
  //ASSERT: type has been set
  unsigned int rootChildren = 0x0;
  root.setNumChildren(rootChildren);
  //ASSERT: number of children have been set
  unsigned int rootParent = 0x0;
  root.setParent(rootParent);
  //ASSERT: the parent of root has been set
  root.setChild(firstFreeNode);
  //ASSERT: the leftmost child has been set
  unsigned int rootLeftSibling = 0x0;
  root.setPrevSibling(rootLeftSibling);
  //ASSERT: the previous sibling of root has been set
  unsigned int rootRightSibling = 0x0;
  root.setNextSibling(rootRightSibling);
  //ASSERT: the next sibling of root has been set
  //Collorary: root is ready to be put on the disk
  modifyInode(root);
  //ASSERT:disk contains the root directory

  unsigned int freeData[NODESIZE];
  freeNode free0(freeData);
  //ASSERT: free0 node has been created
  free0.setInodeAddress(2);
  //ASSERT: sets the iNode address of the first freeNode
  unsigned int freeType = 0x03000000;
  free0.setType(freeType);
  //ASSERT: free's type has been set
  unsigned int free0Prev = 0x0;
  free0.setPrev(free0Prev);
  //ASSERT: free's previous has been set
  unsigned int free0Next = 0x00000003;
  free0.setNext(free0Next);
  //ASSERT: free's next has been set
  //Collorary: free0 is ready to be put on disk
  modifyInode(free0);
  //ASSERT: the first freeNode has been set
  
  int index = 3; //index starts at the first place afterwhere the first
		 //freeNode is located
  while (index < (diskSize - 1)){
    freeNode free(freeData);
    //ASSERT: free node has been created
    free.setInodeAddress(index);
    //ASSERT: sets the iNode address of the freeNode
    free.setType(freeType);
    //ASSERT: free's type has been set
    unsigned int freePrev = index - 1;
    free.setPrev(freePrev);
    //ASSERT: free's previous has been set
    unsigned int freeNext = index + 1;
    free.setNext(freeNext);
    //ASSERT: free's next has been set
    //Collorary: free is ready to be put on disk
    modifyInode(free);
    //ASSERT: the freeNode has been set
    index++;
  }
  
  freeNode freeFinal(freeData);
  //ASSERT: freeFinal node has been created
  freeFinal.setInodeAddress(totalFreeNodes);
  //ASSERT: sets the iNode address of the superBlock
  freeFinal.setType(freeType);
  //ASSERT: freeFinal's type has been set
  unsigned int freeFinalPrev = index - 1;
  freeFinal.setPrev(freeFinalPrev);
  //ASSERT: freeFinal's previous has been set
  unsigned int freeFinalNext = 0x0;
  freeFinal.setNext(freeFinalNext);
  //ASSERT: freeFinal's next has been set
  //Collorary: freeFinal is ready to be put on disk
  modifyInode(freeFinal);
  //ASSERT: the freeFinalNode has been set
  currentWorkingDirectory = 1;
  //ASSERT: the current directory is root
}

//destructor
//PRE:
//POST: destoys this object
fileSys::~fileSys(){
  delete diskFile;
}

//copy constructor
//PRE:
//POST: Makes a deep copy of pFileSys to this object
fileSys::fileSys(const fileSys & pFileSys){
  diskFile = pFileSys.getDiskFile();
  currentWorkingDirectory = pFileSys.getCurrDirectory();
  fileSysSize = pFileSys.getDiskSize();
}

//GETTERS
//PRE: this object is defined
//POST: RV =  the member data object associated with this function.
fstream* fileSys::getDiskFile() const{
  return diskFile;
}

//PRE: this object is defined
//POST: RV = iNode ID representing the current working directory
int fileSys::getCurrDirectory() const{
  return currentWorkingDirectory;
}

//PRE: this object is defined
//POST: RV =  the member data object associated with this function.
int fileSys::getDiskSize() const{
  return fileSysSize;
}
  
//SETTERS
//PRE: this object is defined & parameter is an unsigned int that
//would represent the member data object associated with this function.
//POST: modifies the member data object associated with this function. s.t.
//it is equal to the parameter
void fileSys::setDiskFile(fstream* pDiskFile){
  diskFile = pDiskFile;
}

//PRE: this object is defined & parameter is an unsigned int that
//would represent the member data object associated with this function.
//POST: modifies the member data object associated with this function. s.t.
//it is equal to the parameter
void fileSys::setCurrDirectory(int pDirectory){
  currentWorkingDirectory = pDirectory;
}
  
//PRE: this object is defined & parameter is an unsigned int that
//would represent the member data object associated with this function.
//POST: modifies the member data object associated with this function. s.t.
//it is equal to the parameter.
void fileSys::setDiskSize(int pDiskSize){
  fileSysSize = pDiskSize;
}
  
//Translate modifications
//PRE: iNodeID has to represent the ID of the node you want to seekp to
//POST: sets the cursor to the first word of the ID
void fileSys::findInode(int iNodeID){
  int offSet = iNodeID * (NODESIZE * NODESIZE);
  diskFile->seekp(offSet, ios::beg);
}

//PRE: newNode should be some form of Inode that you want to modify
//the node that the cursor is currently at to.
//POST: modifies the node in diskFile that the cursor is currently at
//s.t. it is now equal to newNode
void fileSys::modifyInode(iNode newNode){
  int index = 0;
  while (index < NODESIZE){
    int wordPlusNewLinePlusEOS = 10;
    char newWord[wordPlusNewLinePlusEOS];
    const unsigned int* newNodeData = newNode.getData();
    unsigned int currWord = newNodeData[index];
    //ASSERT: currWord is the word that we currently wanna add to the
    //disk
    sprintf(newWord, "%08x\n", currWord);
    //ASSERT: currWord has been converted to a string of characters
    //and put into newWord
    for (int outputIndex = 0; outputIndex < NODESIZE + 1; outputIndex++){
      diskFile->put(newWord[outputIndex]);
      //ASSSERT: overwritten a character in diskfile with
      //newWord[outputIndex]
    }
    //ASSERT: a word has been overwritten in the disk
    index++;
  }
  //ASSERT: A node has been overwritten in the disk
}
    
  
//HANDLES
//Note: all handles have the prerequisite: this object must be
//declared & defined.
//Note: all parameters must have followed The prerequisites
//defined in the README.
  
//PRE:
//POST: disk has been formatted. Formatted: he file system will now
//have the root directory with no children. Thus, all inodes
//numbered 2 and above will be free/unused inodes.
void fileSys::handleFormat(){
  unsigned int superBlockData[NODESIZE];
  superBlock newSuperBlock(superBlockData);
  //ASSERT: superBlock node has been created
  newSuperBlock.setInodeAddress(0);
  //ASSERT: sets the iNode address of the superBlock
  unsigned int firstFreeNode = 0x00000002;
  newSuperBlock.setFirstFreeNode(firstFreeNode);
  //ASSERT: first free node is the left child of root
  unsigned int totalFreeNodes = fileSysSize - 1;
  totalFreeNodes = totalFreeNodes << (NIBBLE * 4);
  //shifts totalFreeNodes 4 nibbles (2 bytes)
  newSuperBlock.setNumFreeNodes(totalFreeNodes);
  //ASSERT: freeNodes have been set
  newSuperBlock.setTotalNodes(fileSysSize);
  //ASSERT: total nodes have been set.
  //Collorary: newSuperBlock is ready to be put on the disk
  modifyInode(newSuperBlock);
  //ASSERT:disk contains the superBlock

  unsigned int rootData[NODESIZE];
  directoryNode root(rootData);
  //ASSERT: root node has been created
  root.setInodeAddress(1);
  //ASSERT: sets the iNode address of root
  unsigned int rootName = '/';
  rootName = rootName << (NIBBLE * 4); //shifts typeAndName 4 nibbles
  unsigned int pName[5];
  pName[0] = rootName;
  root.setName(pName);
  //ASSERT: name has been set
  unsigned int rootType = 0x0;
  root.setType(rootType);
  //ASSERT: type has been set
  unsigned int rootChildren = 0x0;
  root.setNumChildren(rootChildren);
  //ASSERT: number of children have been set
  unsigned int rootParent = 0x0;
  root.setParent(rootParent);
  //ASSERT: the parent of root has been set
  root.setChild(firstFreeNode);
  //ASSERT: the leftmost child has been set
  unsigned int rootLeftSibling = 0x0;
  root.setPrevSibling(rootLeftSibling);
  //ASSERT: the previous sibling of root has been set
  unsigned int rootRightSibling = 0x0;
  root.setNextSibling(rootRightSibling);
  //ASSERT: the next sibling of root has been set
  //Collorary: root is ready to be put on the disk
  modifyInode(root);
  //ASSERT:disk contains the root directory

  unsigned int freeData[NODESIZE];
  freeNode free0(freeData);
  //ASSERT: free0 node has been created
  free0.setInodeAddress(2);
  //ASSERT: sets the iNode address of the first freeNode
  unsigned int freeType = 0x03000000;
  free0.setType(freeType);
  //ASSERT: free's type has been set
  unsigned int free0Prev = 0x0;
  free0.setPrev(free0Prev);
  //ASSERT: free's previous has been set
  unsigned int free0Next = 0x00000003;
  free0.setNext(free0Next);
  //ASSERT: free's next has been set
  //Collorary: free0 is ready to be put on disk
  modifyInode(free0);
  //ASSERT: the first freeNode has been set
  
  int index = 3; //index starts at the first place afterwhere the first
  		 //freeNode is located
  while (index < (fileSysSize - 1)){
    freeNode free(freeData);
    //ASSERT: free node has been created
    free.setInodeAddress(index);
    //ASSERT: sets the iNode address of the freeNode
    free.setType(freeType);
    //ASSERT: free's type has been set
    unsigned int freePrev = index - 1;
    free.setPrev(freePrev);
    //ASSERT: free's previous has been set
    unsigned int freeNext = index + 1;
    free.setNext(freeNext);
    //ASSERT: free's next has been set
    //Collorary: free is ready to be put on disk
    modifyInode(free);
    //ASSERT: the freeNode has been set
    index++;
  }
  
  freeNode freeFinal(freeData);
  //ASSERT: freeFinal node has been created
  freeFinal.setInodeAddress(totalFreeNodes);
  //ASSERT: sets the iNode address of the superBlock
  freeFinal.setType(freeType);
  //ASSERT: freeFinal's type has been set
  unsigned int freeFinalPrev = index - 1;
  freeFinal.setPrev(freeFinalPrev);
  //ASSERT: freeFinal's previous has been set
  unsigned int freeFinalNext = 0x0;
  freeFinal.setNext(freeFinalNext);
  //ASSERT: freeFinal's next has been set
  //Collorary: freeFinal is ready to be put on disk
  modifyInode(freeFinal);
  //ASSERT: the freeFinalNode has been set
  currentWorkingDirectory = 1;
  //ASSERT: the current directory is root
}

//PRE:
//POST: disk has been defragmented. Defragmented: All the used
//inodes are moved towards the top of the file system so that all
//the unused inodes are contiguous and at the end of the file
//system. Thus, there will be some inode x so that all inodes y
//where y >= x are unused inodes, and all inodes y where y < x are
//used inodes. 
void fileSys::handleDefrag(){
}

//PRE:
//POST: the absolute path of the present working directory has
//been displayed on the terminal
void fileSys::handlePWD(){
}

//PRE: 
//POST: the contents of the present working directory have
//been put on the terminal ("There is nothing" is coutted if
//there are no other directories than root)
void fileSys::handleLS(){
  findInode(1);
  //ASSERT: cursor has been moved to root
  int numChildrenWord = 5;
  int offSet = numChildrenWord * (NODESIZE);
  diskFile->seekp(offSet, ios::cur);
  //ASSERT: seekp has been moved to the line where num children of root is
  char childrenLine[NODESIZE+1];
  char ch;
  for (int index = 0; index < NODESIZE; index++){
    ch = diskFile->get();
    childrenLine[index] = ch;
  }
  childrenLine[NODESIZE+1] = EOS;
  cerr << childrenLine << endl;
  if (childrenLine == zerostring){
    cout << "There is nothing to ls" << endl;
  }
  else{
    //there is something to ls
  } 
}

//PRE: userPathString must be in the format of a "path".
//POST: The contents of the directory specified by the path in
//the parameter are listed in alphabetical order, with
//four names per line of output to the terminal if path is
//valid. A suitable error msg is coutted otherwise
void fileSys::handleLSarg(char* userPathString){
}

//PRE:
//POST: changed the present working directory to the root
//directory.
void fileSys::handleCD(){
}

//PRE: userPathString must be in the format of a "path".
//POST: the present working directory is modified to be the
//directory specified by the path in the parameter if path is
//valid. Else A suitable error msg is coutted.
void fileSys::handleCDarg(char* userPathString){
}

//PRE: userPathString must be in the format of a "path".
//POST: if All intermediate directories in the specified path
//already exists a new directory specified by the path in the
//parameter. else A suitable error msg is coutted.
void fileSys::handleMKDIR(char* userPathString){
}

//PRE: userPathString must be in the format of a "path".
//POST: if All intermediate directories in the specified path
//to the existing file already exists the file specified by the
//path in the parameter is removed. also if a star is located at
//the end of the valid path, all files in the directory are
//removed. if there is any invalidity with the path A suitable
//error msg is coutted.
void fileSys::handleRM(char* userPathString){
}

//PRE: userPathString must be in the format of a "path".
//POST: if All intermediate directories in the specified path
//to the existing directory already exists the directory specified by the
//path in the parameter is removed. if the directory has 1 or more children
//or an intermediary directory doesnt exist, A suitable
//error msg is coutted.
void fileSys::handleRMDIR(char* userPathString){
}

//PRE: both parameters must be in the format of a "path".
//POST: if the path is valid, The file specified (as an
//absolute or relative path) 
//by the first parameter (source) has been copied as the file
//specified (as an absolute or relative path) in the second
//parameter (destination). In this particular instance,
//the source is treated as a path in the Linux file
//system, and the destination is treated as a path in the simulated file
//system. if path is valid. A suitable error msg is coutted else.
void fileSys::handleCPlessThan(char* userPathFromString,
			       char* userPathToString){
}

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
void fileSys::handleCPgreaterThan(char* userPathFromString,
				  char* userPathToString){
}

//PRE: both parameters must be in the format of a "path".
//POST: if the path is valid, The file specified (as an
//absolute or relative path) 
//by the first parameter (source) has been copied as the file
//specified (as an absolute or relative path) in the second
//parameter (destination). both source
//and destination are to be treated as paths in the simulated file
//system. if path is valid. A suitable error msg is coutted else.
void fileSys::handleCP(char* userPathFromString, char* userPathToString){
}

//PRE: hFlag must represent a boolean that is true iff the user
//typed in the 'h' flag or not. userPathString must be in the format
//of a "path".
//POST: the contents of the file the user's path specified has been
//displayed as characters or hexidecimals (dependant on whether
//hFlag is false/true respectively) iff the path was valid and the file
//existed. A suitable error msg is coutted else.
void fileSys::handleCAT(char* userPathString, bool hFlag){
}

//PRE:
//POST: all the contents of inodes numbered are
//displayed on the terminal s.t. each inode was displayed on
//three lines, one line for the inode number and two lines for
//the contents of the inode
void fileSys::handleDisplayInode(){
  findInode(0);
  int fullNodeSize = (NODESIZE * NODESIZE);
  char ch;
  int index = 0;
  while(index < fileSysSize){
    cout << "iNode No. " << index << endl;
    for (int readIndex = 0; readIndex <= (fullNodeSize/2); readIndex++){
      ch = diskFile->get();
      if (ch != newLine){
	cout << ch;
      }
      else{
	//ASSERT: ch is a newLine
	cout << aSpace;
      }
      readIndex++;
    }
    ch = diskFile->get();
    //ASSERT: 4 words of the iNode have been read
    cout << endl;
    for (int readIndex = 0; readIndex < (fullNodeSize/2); readIndex++){
      ch = diskFile->get();
      if (ch != newLine){
	cout << ch;
      }
      else{
	//ASSERT: ch is a newLine
	cout << aSpace;
      }
      readIndex++;
    }
    //ASSERT: 4 words of the iNode have been read
    cout << endl;
    index++;
  }
}

//PRE: n & m must satisfy the assumptions made in the readMe.
//POST: the contents of inodes numbered n through m are
//displayed on the terminal s.t. each inode was displayed on
//three lines, one line for the inode number and two lines for
//the contents of the inode. if n or m are out of bounds, an eror
//is coutted respectively (respectively in the sense that
//the error will let the user know which parameter was out of
//bounds.
void fileSys::handleDisplayInodeArg(int n, int m){
  findInode(n);
  int mMinusn = m - n;
  int fullNodeSize = (NODESIZE * NODESIZE);
  findInode(n);
  //ASSERT: the cursor is set to the beginning of iNode n
  char ch;
  int index = 0;
  while(index < mMinusn){
    cout << "iNode No. " << n << endl;
    for (int readIndex = 0; readIndex < (fullNodeSize/2); readIndex++){
      ch = diskFile->get();
      if (ch != newLine){
	cout << ch;
      }
      else{
	//ASSERT: ch is a newLine
	cout << aSpace;
      }
    }
    //ASSERT: 4 words of the iNode have been read
    cout << endl;
    for (int readIndex = 0; readIndex < (fullNodeSize/2); readIndex++){
      ch = diskFile->get();
      if (ch != newLine){
	cout << ch;
      }
      else{
	//ASSERT: ch is a newLine
	cout << aSpace;
      }
    }
    //ASSERT: 4 words of the iNode have been read
    cout << endl;
    //ASSERT: 1 iNode has been sent to the terminal
    n++;
  }
}

//PRE:
//POST: The size of the present working directory has been
//printed to the terminal. 
void fileSys::handleDU(){
  
}

//PRE: userPathString must be in the format of a "path".
//POST: The size, in bytes, of the directory specified by the
//path in the parameter is printed out. iff path is
//valid. A suitable error msg is coutted elsewise.
void fileSys::handleDUarg(char* userPathString){
}
