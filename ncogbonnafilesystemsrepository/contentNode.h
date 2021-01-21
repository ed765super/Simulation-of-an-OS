#ifndef INCLUDED_CONTENTNODE
#define INCLUDED_CONTENTNODE
#include "iNode.h"
#include <iostream>
using namespace std;

class contentNode:public iNode{
  //CI:
  /*Content inode:
  Word No.	Contents
    0	        Byte 0: 0x02 (indicating a content inode). Bytes 1, 2
                and 3: characters 1 - 3 of the file content.
    1-5	        File content
    6	        Bytes 0 and 1: inode address of file inode for this
                file. Bytes 2 and 3 are unused.
    7	        Bytes 0 and 1: inode address of next content inode for
                this file. Bytes 2 and 3: inode address of previous
                content inode for this file.*/
 public:
  //CONSTRUCTOR
  //PRE:
  //POST: creates a this object
  contentNode(unsigned int pData[NODESIZE]);
  
  //GETTER
  //PRE: this object is defined
  //POST: modifies dummyContent s.t. it = this object's content
  void getContent(unsigned int dummyContent[6]);

  //PRE: this object is defined
  //POST: RV =  this object's associated file
  unsigned int getFile() const;

  //PRE: this object is defined
  //POST: RV =  this object's prev
  unsigned int getPrev() const;

  //PRE: this object is defined
  //POST: RV =  this object's next
  unsigned int getNext() const;
  
  //SETTER
  //PRE: this object is defined & parameter is an unsigned int that
  //would represent 'Content'
  //POST: modifies this object's content s.t. it is equal to pContent
  void setContent(unsigned int pContent[6]);

  //PRE: this object is defined & parameter is an unsigned int that
  //would represent 'next'
  //POST: modifies this object's next s.t. it is equal to pNext
  void setFile(unsigned int pFatherFile);

  //PRE: this object is defined & parameter is an unsigned int that
  //would represent 'prev'
  //POST: modifies this object's prev s.t. it is equal to pPrev
  void setPrev(unsigned int pPrev);

  //PRE: this object is defined & parameter is an unsigned int that
  //would represent 'next'
  //POST: modifies this object's next s.t. it is equal to pNext
  void setNext(unsigned int pNext);

  //OUTPUT
  //PRE:
  //POST: outputs the data of this node to the terminal
  friend ostream & operator << (ostream & stream, const contentNode & thisNode);
};
#endif
