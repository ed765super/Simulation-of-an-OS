#ifndef INCLUDED_FREENODE
#define INCLUDED_FREENODE
#include "iNode.h"
#include <iostream>
using namespace std;

class freeNode:public iNode{
  //CI:
   /*Free inode:
    Word No.	Contents
    0	        Byte 0: 0x03 (indicating a free inode). Bytes 1, 2 and
                3 are unused.
    1-6	        Unused
    7	        Bytes 0 and 1: inode address of next free inode. Bytes
                2 and 3: inode address of previous free inode.*/
 public:
  //CONSTRUCTOR
  //PRE:
  //POST: creates a this object
  freeNode(unsigned int pData[NODESIZE]);
  
  //GETTER
  //PRE: this object is defined
  //POST: RV =  the member data object associated with this function.
  unsigned int getPrev() const;

  //PRE: this object is defined
  //POST: RV =  the member data object associated with this function.
  unsigned int getNext() const;

  //SETTER

  //PRE: this object is defined & parameter is an unsigned int that
  //would represent the member data object associated with this function.
  //POST: modifies the member data object associated with this function. s.t.
  //it is equal to the parameter
  void setPrev(unsigned int pPrev);

  //PRE: this object is defined & parameter is an unsigned int that
  //would represent the member data object associated with this function.
  //POST: modifies the member data object associated with this function. s.t.
  //it is equal to the parameter
  void setNext(unsigned int pNext);

  //OUTPUT
  //PRE:
  //POST: outputs the data of this node to the terminal
  friend ostream & operator << (ostream & stream, const freeNode & thisNode);
};
#endif
