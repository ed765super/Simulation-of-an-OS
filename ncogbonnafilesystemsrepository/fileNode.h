#ifndef INCLUDED_FILENODE
#define INCLUDED_FILENODE
#include "iNode.h"
#include <iostream>
using namespace std;

class fileNode:public iNode{
  //CI:
  /*File inode:
  Word No.	Contents
     0	        Byte 0: 0x01 (indicating a file inode).. Bytes 1, 2
                and 3: characters 1 - 3 of the name of the file.
     1	        Characters 4 - 7 of the name of file
     2	        Characters 8 - 11 of the name of file
     3	        Characters 12 - 15 of the name of file
     4	        Characters 16 - 19 of the name of file
     5	        Size of file in number of bytes
     6	        Bytes 0 and 1: inode address of parent inode. Bytes 2
                and 3: inode address of the first content inode for this file.
     7   	Bytes 0 and 1: inode address of next sibling
                inode. Bytes 2  and 3: inode address of previous
                sibling inode.*/
 public:
  //CONSTRUCTOR
  //PRE:
  //POST: creates a this object
  fileNode(unsigned int pData[NODESIZE]);

  //GETTER
  //PRE: this object is defined.
  //POST: modifies dummyName s.t. it = this object's name in hexidecimal
  void getName(unsigned int dummyName[5]);

  //PRE: this object is defined
  //POST: RV =  this object's fileSize
  unsigned int getFileSize() const;

  //PRE: this object is defined
  //POST: RV =  this object's parent
  unsigned int getParent() const;

  //PRE: this object is defined
  //POST: RV =  this object's first content iNode address
  unsigned int getFirstContent() const;
  
  //PRE: this object is defined
  //POST: RV =  this object's previous siblings
  unsigned int getPrevSibling() const;

  //PRE: this object is defined
  //POST: RV =  this object's previous siblings
  unsigned int getNextSibling() const;
  
  //SETTER
  
  //PRE: this object is defined & parameter is an unsigned int that
  //would represent the data member object associated with this
  //function
  //POST: modifies the data member object associated with this
  //function s.t. it is equal to the parameter
  void setName(unsigned int pName[5]);

  //PRE: this object is defined & parameter is an unsigned int that
  //would represent the data member object associated with this
  //function
  //POST: modifies the data member object associated with this
  //function s.t. it is equal to the parameter
  void setFileSize(unsigned int pFileSize);

  //PRE: this object is defined & parameter is an unsigned int that
  //would represent the data member object associated with this
  //function
  //POST: modifies the data member object associated with this
  //function s.t. it is equal to the parameter
  void setParent (unsigned int pParent);

  //PRE: this object is defined & parameter is an unsigned int that
  //would represent the data member object associated with this
  //function
  //POST: modifies the data member object associated with this
  //function s.t. it is equal to the parameter
  void setFirstContent(unsigned int pChild);

  //PRE: this object is defined & parameter is an unsigned int that
  //would represent the data member object associated with this
  //function
  //POST: modifies the data member object associated with this
  //function s.t. it is equal to the parameter
  void setPrevSibling(unsigned int pPrevSibling);

  //PRE: this object is defined & parameter is an unsigned int that
  //would represent the data member object associated with this
  //function
  //POST: modifies the data member object associated with this
  //function s.t. it is equal to the parameter
  void setNextSibling(unsigned int pNextSibling);

  //OUTPUT
  //PRE:
  //POST: outputs the data of this node to the terminal
  friend ostream & operator << (ostream & stream, const fileNode & thisNode);
};
#endif
