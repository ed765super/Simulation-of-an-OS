#ifndef INCLUDED_DIRNODE
#define INCLUDED_DIRNODE
#include "iNode.h"

class directoryNode : public iNode{
  //CI:
  /*Directory inode:
    Word No.	Contents
    0	        Byte 0: 0x00 (indicating a directory inode). Bytes 1,
                2 and 3:  characters 1 - 3 of the name of the directory.
    1	        Characters 4 - 7 of the name of directory
    2	        Characters 8 - 11 of the name of directory
    3	        Characters 12 - 15 of the name of directory
    4	        Characters 16 - 19 of the name of directory
    5	        Number of children
    6	        Bytes 0 and 1: inode address of parent inode. Bytes 2
                and 3:  inode address of first (leftmost) child inode.
    7	        Bytes 0 and 1: inode address of next sibling
    inode. Bytes 2 and  3: inode address of previous
    sibling inode.*/
 public:
  //CONSTRUCTOR
  //PRE:
  //POST: creates a this object
  directoryNode(unsigned int pData[NODESIZE]);
  
  //GETTER
  //PRE: this object is defined
  //POST: modifies the parameter to this object's name in hexidecimal
  void getName(unsigned int dummyName[5]);

  //PRE: this object is defined
  //POST: RV =  this object's numChildrens
  unsigned int getNumChildren() const;

  //PRE: this object is defined
  //POST: RV =  this object's parent
  unsigned int getParent() const;

  //PRE: this object is defined
  //POST: RV =  this object's child
  unsigned int getChild() const;
  
  //PRE: this object is defined
  //POST: RV =  this object's previous siblings
  unsigned int getPrevSibling() const;

  //PRE: this object is defined
  //POST: RV =  this object's previous siblings
  unsigned int getNextSibling() const;
  
  //SETTER
  //Note: all parameters must be in their correct placemarks
  //PRE: this object is defined & parameter is an array of unsigned int of
  //size 5 that
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
  void setNumChildren(unsigned int pNumChildren);

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
  void setChild(unsigned int pChild);

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
  friend ostream & operator << (ostream & stream,
				const directoryNode & thisNode);
};
#endif
