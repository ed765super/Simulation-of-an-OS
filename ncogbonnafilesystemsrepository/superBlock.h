#ifndef INCLUDED_SUPERBLOCK
#define INCLUDED_SUPERBLOCK
#include "iNode.h"

class superBlock:public iNode{
  //CI:
  /*Superblock inode:
  Word No.	Contents
     0	        Bytes 2 and 3 (as a 16 bit value): inode addr. of
                first free inode. (Use the value 0x0000 to denote a
                NULL addr.)  Bytes 0 and 1 are unused.
     1	        Bytes 0 and 1: number of free inodes. Bytes 2 and 3:
                total  number of inodes.
     2-7	Unused*/
 public:
  //CONSTRUCTOR
  //PRE:
  //POST: creates a this object
  superBlock(unsigned int pData[NODESIZE]);
  
  //GETTER
  //PRE: this object is defined
  //POST: RV =  this object's type
  unsigned int getFirstFreeNode() const;

  //PRE: this object is defined
  //POST: RV =  this object's next
  unsigned int getNumFreeNodes() const;

  //PRE: this object is defined
  //POST: RV =  this object's prev
  unsigned int getTotalNodes() const;
  
  //SETTER
  //PRE: this object is defined & parameter is an unsigned int that
  //would represent 'type'
  //POST: modifies this object's type s.t. it is equal to pType
  void setFirstFreeNode(unsigned int pFirstFreeNode);

  //PRE: this object is defined & parameter is an unsigned int that
  //would represent 'next'
  //POST: modifies this object's next s.t. it is equal to pNext
  void setNumFreeNodes(unsigned int pNumFreeNodes);

  //PRE: this object is defined & parameter is an unsigned int that
  //would represent 'prev'
  //POST: modifies this object's prev s.t. it is equal to pPrev
  void setTotalNodes(unsigned int pTotalNodes);

  //OUTPUT
  //PRE:
  //POST: outputs the data of this node to the terminal
  friend ostream & operator << (ostream & stream, const superBlock & thisNode);
};
#endif
