#include "iNode.h"
using namespace std;
//CONSTRUCTOR
//PRE:
//POST: creates a default iNode
iNode::iNode(){
  iNodeAddress = -1;
}

//PRE:
//POST: creates a general inode object
iNode::iNode(unsigned int pData[NODESIZE]){
  for (int index = 0; index < NODESIZE; index++){
    data[index] = pData[index];
  }
  iNodeAddress = -1;
}
  
//GETTER
//PRE: this object is defined
//POST: RV =  this object's data
const unsigned int* iNode::getData() const{
  return data;
}

//PRE: this object is defined
//POST: RV =  the type of iNode
int iNode::getType() const{
  unsigned int firstWord = data[0];
  //firstWord is the firstWord of the data array
  int type = getNibble(firstWord, PLACEMARK1);
  //ASSERT: since the type is identified as a single digit located at
  //the nibble at placemark 1, type is now equal to the type of iNode
  return type;
}

//PRE: this object is defined
//POST: RV = this iNode's ID
int iNode::getInodeAddress() const{
  return iNodeAddress;
}
  
//SETTER
//PRE: this object is defined & parameter is an unsigned int that
//would represent 'data'
//POST: modifies this object's data s.t. it is equal to pData
void iNode::setData(unsigned int pData[NODESIZE]){
  for (int index = 0; index < NODESIZE; index++){
    data[index] = pData[index];
  }
}

//PRE: this object is defined & parameter is an unsigned int that
//would represent 'type'. pType does not need to be shifted.
//POST: modifies this object's type s.t. it is equal to pType
void iNode::setType(unsigned int pType){
  unsigned int mask = 0x10111111; //create mask that will clear out the
				//placemark where the current type is at.
  setNibble(data[0], pType, mask, PLACEMARK1, 1);
  
}

//PRE: this object is defined & parameter is an unsigned int that
//would represent 'iNode address'
//POST: modifies this object's iNode address s.t. it is equal to pAddress
void iNode::setInodeAddress(int pAddress){
  iNodeAddress = pAddress;
}

//OUTPUT
//PRE:
//POST: outputs the data of this node to the terminal
ostream & operator << (ostream & stream, const iNode & thisNode){
  for (int index = 0; index < NODESIZE; index++){
    cout << thisNode.data[index] << endl;
  }
  return (stream);
}
