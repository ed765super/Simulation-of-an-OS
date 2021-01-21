#ifndef INCLUDED_INODE
#define INCLUDED_INODE
#include <iostream>
#include "constants.h"
#include "utility.h"
using namespace std;

class iNode{
  //CI: this object is defaulted as an array of unsigned int of size 8
  //and iNode address = -1 indicating that there is no address assigned
  //data is essentially logical unit of the file
  //system. this iNode has 8 words (each word is 32 bits, i.e., 4
  //bytes). Each inode is one of the following types: a superblock
  //inode, a directory inode, a file inode, a content inode, or a free
  //inode.
  //The structure of each inode in fileSystem is explained below:
  /*Superblock inode:
  Word No.	Contents
     0	        Bytes 2 and 3 (as a 16 bit value): inode addr. of
                first free inode. (Use the value 0x0000 to denote a
                NULL addr.)  Bytes 0 and 1 are unused.
     1	        Bytes 0 and 1: number of free inodes. Bytes 2 and 3:
                total  number of inodes.
     2-7	Unused*/
  
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

  /*Free inode:
    Word No.	Contents
    0	        Byte 0: 0x03 (indicating a free inode). Bytes 1, 2 and
                3 are unused.
    1-6	        Unused
    7	        Bytes 0 and 1: inode address of next free inode. Bytes
                2 and 3: inode address of previous free inode.*/
 protected:
  unsigned int data[NODESIZE]; //will hold a type associated with this
			       //node
  int iNodeAddress; //will hold the iNode address of this node object
  
 public:
  //CONSTRUCTOR
  //PRE:
  //POST: creates a default iNode
  iNode();
  
  //PRE:
  //POST: creates a general iNode object
  iNode(unsigned int pData[NODESIZE]);
  
  //GETTER
  //PRE: this object is defined
  //POST: RV =  this object's data
  const unsigned int* getData() const;

  //PRE: this object is defined
  //POST: RV =  the type of iNode
  int getType() const;

  //PRE: this object is defined
  //POST: RV = this iNode's ID
  int getInodeAddress() const;
  
  //SETTER
  //PRE: this object is defined & parameter is an unsigned int that
  //would represent 'data'
  //POST: modifies this object's data s.t. it is equal to pData
  void setData(unsigned int pData[NODESIZE]);

  //PRE: this object is defined & parameter is an unsigned int that
  //would represent 'type'
  //POST: modifies this object's type s.t. it is equal to pType
  void setType(unsigned int pType);

  //PRE: this object is defined & parameter is an unsigned int that
  //would represent 'iNode address'
  //POST: modifies this object's iNode address s.t. it is equal to pAddress
  void setInodeAddress(int pAddress);
  
  //OUTPUT
  //PRE:
  //POST: outputs the data of this node to the terminal
  friend ostream & operator << (ostream & stream, const iNode & thisNode);
};
#endif
