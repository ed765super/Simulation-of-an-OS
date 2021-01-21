#include "superBlock.h"
using namespace std;
//CONSTRUCTOR
//PRE:
//POST: creates a this object
superBlock::superBlock(unsigned int pData[NODESIZE]){
  for (int index = 0; index < NODESIZE; index++){
    data[index] = pData[index];
  }
}
//GETTER
//PRE: this object is defined
//POST: RV = the unsigned int that represents the iNode address of the
//first freeNode
unsigned int superBlock::getFirstFreeNode() const{
  unsigned int firstFreeNode = 0x0;//will hold the first free node
  int dataByte2 = 2; //represents the byte number 2 of some word of
		     //data
  int dataByte3 = 3; //represents the byte number 3 of some word of
		     //data
  unsigned int byte2 = getByte(data[0], dataByte2);
  unsigned int byte3 = getByte(data[0], dataByte3);
  
  setByte(firstFreeNode, dataByte2, byte2, dataByte2);
  setByte(firstFreeNode, dataByte3, byte3, dataByte3);
  return firstFreeNode;
}

//PRE: this object is defined
//POST: RV =  the remaining number of freeNodes in the disk
unsigned int superBlock::getNumFreeNodes() const{
  unsigned int freeNodes = 0x0;//will hold the totalFreeNodes.
  int dataByte0 = 0; //represents the byte number 0 of some word of
		     //data
  int dataByte1 = 1; //represents the byte number 1 of some word of
		     //data
  unsigned int byte0 = getByte(data[1], dataByte0);
  unsigned int byte1 = getByte(data[1], dataByte1);
  setByte(freeNodes, dataByte0, byte0, dataByte0);
  setByte(freeNodes, dataByte1, byte1, dataByte1);
  return freeNodes;
}

//PRE: this object is defined
//POST: RV = the total nodes in the disk
unsigned int superBlock::getTotalNodes() const{
  unsigned int totalNodes = 0x0;//will hold the totalnodes.
  int dataByte2 = 2; //represents the byte number 2 of some word of
		     //data
  int dataByte3 = 3; //represents the byte number 3 of some word of
		     //data
  unsigned int byte2 = getByte(data[1], dataByte2);
  unsigned int byte3 = getByte(data[1], dataByte3);
  setByte(totalNodes, dataByte2, byte2, dataByte2);
  setByte(totalNodes, dataByte3, byte3, dataByte3);
  return totalNodes;
}
  
//SETTER
//PRE: this object is defined & parameter must represent an unsigned
//int that represents the first freeNode
//POST: modifies this object's firstFreeNode s.t. it is equal to pFirstFreeNode
void superBlock::setFirstFreeNode(unsigned int pFirstFreeNode){
  int dataByte2 = 2; //represents the byte number 2
  int dataByte3 = 3; //represents the byte number 3
  unsigned int byte2 = getByte(pFirstFreeNode, dataByte2);
  unsigned int byte3 = getByte(pFirstFreeNode, dataByte3);
  setByte(data[0], dataByte2, byte2, dataByte2);
  setByte(data[0], dataByte3, byte3, dataByte3);
}

//PRE: this object is defined & parameter is an unsigned int that
//would represent 'numFreeNodes'
//POST: modifies this object's numFreeNodes s.t. it is equal to pNumFreeNodes
void superBlock::setNumFreeNodes(unsigned int pNumFreeNodes){
  int dataByte0 = 0; //represents the byte number 0 of some word of
		     //data
  int dataByte1 = 1; //represents the byte number 1 of some word of
		     //data
  unsigned int byte0 = getByte(pNumFreeNodes, dataByte0);
  unsigned int byte1 = getByte(pNumFreeNodes, dataByte1);
  setByte(data[1], dataByte0, byte0, dataByte0);
  setByte(data[1], dataByte1, byte1, dataByte1);
}

//PRE: this object is defined & parameter is an unsigned int that
//would represent 'totalNodes'
//POST: modifies this object's totalNodes s.t. it is equal to pTotalNodes
void superBlock::setTotalNodes(unsigned int pTotalNodes){
  int dataByte2 = 2; //represents the byte number 2 of some word of
		     //data
  int dataByte3 = 3; //represents the byte number 3 of some word of
		     //data
  unsigned int byte2 = getByte(pTotalNodes, dataByte2);
  unsigned int byte3 = getByte(pTotalNodes, dataByte3);
  setByte(data[1], dataByte2, byte2, dataByte2);
  setByte(data[1], dataByte3, byte3, dataByte3);
}

//OUTPUT
//PRE:
//POST: outputs the data of this node to the terminal
ostream & operator << (ostream & stream, const superBlock & thisNode){
  const unsigned int* thisData = thisNode.getData();
  for (int index = 0; index < NODESIZE; index++){
    cout << hex << thisData[index] << endl;
  }
  return (stream);
}
