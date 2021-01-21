#include "directoryNode.h"
using namespace std;
//CONSTRUCTOR
//PRE:
//POST: creates a this object
directoryNode::directoryNode(unsigned int pData[NODESIZE]){
  for (int index = 0; index < NODESIZE; index++){
    data[index] = pData[index];
  }
}
//GETTER
//PRE: this object is defined
//POST: modifies the parameter to this object's name in hexidecimal
void directoryNode::getName(unsigned int dummyName[5]){
  unsigned int name1 = 0x0;//will hold the first line of the name
  unsigned int name2 = 0x0;//will hold the second line of the name
  unsigned int name3 = 0x0;//will hold the third line of the name
  unsigned int name4 = 0x0;//will hold the fourth line of the name
  unsigned int name5 = 0x0;//will hold the fifth line of the name
  int dataByte0 = 0; //represents the byte number 0 of some word of
		     //data
  int dataByte1 = 1; //represents the byte number 1 of some word of
		     //data
  int dataByte2 = 2; //represents the byte number 2 of some word of
		     //data
  int dataByte3 = 3; //represents the byte number 3 of some word of
		     //data
  unsigned int byte1 = getByte(data[0], dataByte1);
  unsigned int byte2 = getByte(data[0], dataByte2);
  unsigned int byte3 = getByte(data[0], dataByte3);
  setByte(name1, dataByte1, byte1, dataByte1);
  setByte(name1, dataByte2, byte2, dataByte2);
  setByte(name1, dataByte3, byte3, dataByte3);
  //ASSERT: The bytes that represent the first line of the name
  //associated with this directory node has been placed in name1
  name2 = data[1];
  name3 = data[2];
  name4 = data[3];
  name5 = data[4];
  int CHARWORDS = 5;//will hold the number of words in data that will represent
  //the name of this node
  unsigned int nameArray[CHARWORDS];
  nameArray[0] = name1;
  nameArray[1] = name2;
  nameArray[2] = name3;
  nameArray[3] = name4;
  nameArray[4] = name5;
  //ASSERT: nameArray is fully set
  for (int index = 0; index < CHARWORDS; index++){
    dummyName[index] = nameArray[index];
  }
  //ASSERT: the parameter is now the array that represents this object's
  //name
}

//PRE: this object is defined
//POST: RV =  this object's numChildrens
unsigned int directoryNode::getNumChildren() const{
  return data[5];
}

//PRE: this object is defined
//POST: RV =  this object's parent
unsigned int directoryNode::getParent() const{
  unsigned int parent = 0x0;//will hold the inode address of parent
			    //inode.
  int dataByte0 = 0; //represents the byte number 0 of some word of
		     //data
  int dataByte1 = 1; //represents the byte number 1 of some word of
		     //data
  int parChiWord = 6; //will hold the word where the parent &
		       //children addresses are
  unsigned int byte0 = getByte(data[parChiWord], dataByte0);
  unsigned int byte1 = getByte(data[parChiWord], dataByte1);
  setByte(parent, dataByte0, byte0, dataByte0);
  setByte(parent, dataByte1, byte1, dataByte1);
  return parent;
}
  
//PRE: this object is defined
//POST: RV =  this object's child
unsigned int directoryNode::getChild() const{
  unsigned int child = 0x0;//will hold the inode address of parent
			    //inode.
  int dataByte2 = 2; //represents the byte number 2 of some word of
		     //data
  int dataByte3 = 3; //represents the byte number 3 of some word of
		     //data
  int parChiWord = 6; //will hold the word where the parent &
		       //children addresses are
  unsigned int byte2 = getByte(data[parChiWord], dataByte2);
  unsigned int byte3 = getByte(data[parChiWord], dataByte3);
  setByte(child, dataByte2, byte2, dataByte2);
  setByte(child, dataByte3, byte3, dataByte3);
  return child;
}

//PRE: this object is defined
//POST: RV =  this object's previous siblings
unsigned int directoryNode::getPrevSibling() const{
  unsigned int pSib = 0x0;//will hold the inode address of parent
			    //inode.
  int dataByte0 = 0; //represents the byte number 0 of some word of
		     //data
  int dataByte1 = 1; //represents the byte number 1 of some word of
		     //data
  int siblingWord = 7; //will hold the word where the sibling
		       //addresses are
  unsigned int byte0 = getByte(data[siblingWord], dataByte0);
  unsigned int byte1 = getByte(data[siblingWord], dataByte1);
  setByte(pSib, dataByte0, byte0, dataByte0);
  setByte(pSib, dataByte1, byte1, dataByte1);
  return pSib;
}

//PRE: this object is defined
//POST: RV =  this object's previous siblings
unsigned int directoryNode::getNextSibling() const{
  unsigned int nSib = 0x0;//will hold the inode address of parent
			    //inode.
  int dataByte2 = 2; //represents the byte number 2 of some word of
		     //data
  int dataByte3 = 3; //represents the byte number 3 of some word of
		     //data
  int siblingWord = 7; //will hold the word where the sibling
		       //addresses are
  unsigned int byte2 = getByte(data[siblingWord], dataByte2);
  unsigned int byte3 = getByte(data[siblingWord], dataByte3);
  setByte(nSib, dataByte2, byte2, dataByte2);
  setByte(nSib, dataByte3, byte3, dataByte3);
  return nSib;
}
  
//SETTER
  
//PRE: this object is defined & parameter is an array of unsigned ints
//of size 5 that
//would represent the data member object associated with this
//function
//POST: modifies the data member object associated with this
//function s.t. it is equal to the parameter
void directoryNode::setName(unsigned int pName[5]){
  int dataByte0 = 0; //represents the byte number 0 of some word of
		     //data
  int dataByte1 = 1; //represents the byte number 1 of some word of
		     //data
  int dataByte2 = 2; //represents the byte number 2 of some word of
		     //data
  int dataByte3 = 3; //represents the byte number 3 of some word of
		     //data
  unsigned int byte1 = getByte(pName[0], dataByte1);
  unsigned int byte2 = getByte(pName[0], dataByte2);
  unsigned int byte3 = getByte(pName[0], dataByte3);
  setByte(data[0], dataByte1, byte1, dataByte1);
  setByte(data[0], dataByte2, byte2, dataByte2);
  setByte(data[0], dataByte3, byte3, dataByte3);
  //ASSERT: the bytes that represent the name for line 0 have been set
  unsigned int byte0 = getByte(pName[1], dataByte0);
  byte1 = getByte(pName[1], dataByte1);
  byte2 = getByte(pName[1], dataByte2);
  byte3 = getByte(pName[1], dataByte3);
  setByte(data[1], dataByte0, byte0, dataByte0);
  setByte(data[1], dataByte1, byte1, dataByte1);
  setByte(data[1], dataByte2, byte2, dataByte2);
  setByte(data[1], dataByte3, byte3, dataByte3);
  //ASSERT: the bytes that represent the name for line 1 have been set
  byte0 = getByte(pName[2], dataByte0);
  byte1 = getByte(pName[2], dataByte1);
  byte2 = getByte(pName[2], dataByte2);
  byte3 = getByte(pName[2], dataByte3);
  setByte(data[2], dataByte0, byte0, dataByte0);
  setByte(data[2], dataByte1, byte1, dataByte1);
  setByte(data[2], dataByte2, byte2, dataByte2);
  setByte(data[2], dataByte3, byte3, dataByte3);
  //ASSERT: the bytes that represent the name for line 2 have been set
  byte0 = getByte(pName[3], dataByte0);
  byte1 = getByte(pName[3], dataByte1);
  byte2 = getByte(pName[3], dataByte2);
  byte3 = getByte(pName[3], dataByte3);
  setByte(data[3], dataByte0, byte0, dataByte0);
  setByte(data[3], dataByte1, byte1, dataByte1);
  setByte(data[3], dataByte2, byte2, dataByte2);
  setByte(data[3], dataByte3, byte3, dataByte3);
  //ASSERT: the bytes that represent the name for line 3 have been set
  byte0 = getByte(pName[4], dataByte0);
  byte1 = getByte(pName[4], dataByte1);
  byte2 = getByte(pName[4], dataByte2);
  byte3 = getByte(pName[4], dataByte3);
  setByte(data[4], dataByte0, byte0, dataByte0);
  setByte(data[4], dataByte1, byte1, dataByte1);
  setByte(data[4], dataByte2, byte2, dataByte2);
  setByte(data[4], dataByte3, byte3, dataByte3);
  //ASSERT: the bytes that represent the name for line 4 have been set
}

//PRE: this object is defined & parameter is an unsigned int that
//would represent the data member object associated with this
//function
//POST: modifies the data member object associated with this
//function s.t. it is equal to the parameter
void directoryNode::setNumChildren(unsigned int pNumChildren){
  data[5] = pNumChildren;
}

//PRE: this object is defined & parameter is an unsigned int that
//would represent the data member object associated with this
//function
//POST: modifies the data member object associated with this
//function s.t. it is equal to the parameter
void directoryNode::setParent (unsigned int pParent){
  int dataByte0 = 0; //represents the byte number 0 of some word of
		     //data
  int dataByte1 = 1; //represents the byte number 1 of some word of
		     //data
  int parChiWord = 6; //will hold the word where the parent &
		       //children addresses are
  unsigned int byte0 = getByte(pParent, dataByte0);
  unsigned int byte1 = getByte(pParent, dataByte1);
  setByte(data[parChiWord], dataByte0, byte0, dataByte0);
  setByte(data[parChiWord], dataByte1, byte1, dataByte1);
}

//PRE: this object is defined & parameter is an unsigned int that
//would represent the data member object associated with this
//function
//POST: modifies the data member object associated with this
//function s.t. it is equal to the parameter
void directoryNode::setChild(unsigned int pChild){
  int dataByte2 = 2; //represents the byte number 2 of some word of
		     //data
  int dataByte3 = 3; //represents the byte number 3 of some word of
		     //data
  int parChiWord = 6; //will hold the word where the parent &
		       //children addresses are
  unsigned int byte2 = getByte(pChild, dataByte2);
  unsigned int byte3 = getByte(pChild, dataByte3);
  setByte(data[parChiWord], dataByte2, byte2, dataByte2);
  setByte(data[parChiWord], dataByte3, byte3, dataByte3);
}

//PRE: this object is defined & parameter is an unsigned int that
//would represent the data member object associated with this
//function
//POST: modifies the data member object associated with this
//function s.t. it is equal to the parameter
void directoryNode::setPrevSibling(unsigned int pPrevSibling){
  int dataByte0 = 0; //represents the byte number 0 of some word of
		     //data
  int dataByte1 = 1; //represents the byte number 1 of some word of
		     //data
  int siblingWord = 7; //will hold the word where the sibling
		       //addresses are
  unsigned int byte0 = getByte(pPrevSibling, dataByte0);
  unsigned int byte1 = getByte(pPrevSibling, dataByte1);
  setByte(data[siblingWord], dataByte0, byte0, dataByte0);
  setByte(data[siblingWord], dataByte1, byte1, dataByte1);
}

//PRE: this object is defined & parameter is an unsigned int that
//would represent the data member object associated with this
//function
//POST: modifies the data member object associated with this
//function s.t. it is equal to the parameter
void directoryNode::setNextSibling(unsigned int pNextSibling){
  int dataByte2 = 2; //represents the byte number 2 of some word of
		     //data
  int dataByte3 = 3; //represents the byte number 3 of some word of
		     //data
  int siblingWord = 7; //will hold the word where the sibling
		       //addresses are
  unsigned int byte2 = getByte(pNextSibling, dataByte2);
  unsigned int byte3 = getByte(pNextSibling, dataByte3);
  setByte(data[siblingWord], dataByte2, byte2, dataByte2);
  setByte(data[siblingWord], dataByte3, byte3, dataByte3);
}

//OUTPUT
//PRE:
//POST: outputs the data of this node to the terminal
ostream & operator << (ostream & stream, const directoryNode & thisNode){
  const unsigned int* thisData = thisNode.getData();
  for (int index = 0; index < NODESIZE; index++){
    cout << hex << thisData[index] << endl;
  }
  return (stream);
}
