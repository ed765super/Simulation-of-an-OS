#include "freeNode.h"
using namespace std;
//CONSTRUCTOR
//PRE:
//POST: creates a this object
freeNode::freeNode(unsigned int pData[NODESIZE]){
  for (int index = 0; index < NODESIZE; index++){
    data[index] = pData[index];
  }
}
//GETTER
//PRE: this object is defined
//POST: RV =  the member data object associated with this function.
unsigned int freeNode::getPrev() const{
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
//POST: RV =  the member data object associated with this function.
unsigned int freeNode::getNext() const{
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
//PRE: this object is defined & parameter is an unsigned int that
//would represent the member data object associated with this function.
//POST: modifies the member data object associated with this function. s.t.
//it is equal to the parameter
void freeNode::setPrev(unsigned int pPrev){
  int dataByte0 = 0; //represents the byte number 0 of some word of
		     //data
  int dataByte1 = 1; //represents the byte number 1 of some word of
		     //data
  int siblingWord = 7; //will hold the word where the sibling
		       //addresses are
  unsigned int byte0 = getByte(pPrev, dataByte0);
  unsigned int byte1 = getByte(pPrev, dataByte1);
  setByte(data[siblingWord], dataByte0, byte0, dataByte0);
  setByte(data[siblingWord], dataByte1, byte1, dataByte1);
}

//PRE: this object is defined & parameter is an unsigned int that
//would represent the member data object associated with this function.
//POST: modifies the member data object associated with this function. s.t.
//it is equal to the parameter
void freeNode::setNext(unsigned int pNext){
  int dataByte2 = 2; //represents the byte number 2 of some word of
		     //data
  int dataByte3 = 3; //represents the byte number 3 of some word of
		     //data
  int siblingWord = 7; //will hold the word where the sibling
		       //addresses are
  unsigned int byte2 = getByte(pNext, dataByte2);
  unsigned int byte3 = getByte(pNext, dataByte3);
  setByte(data[siblingWord], dataByte2, byte2, dataByte2);
  setByte(data[siblingWord], dataByte3, byte3, dataByte3);
}

//OUTPUT
//PRE:
//POST: outputs the data of this node to the terminal
ostream & operator << (ostream & stream, const freeNode & thisNode){
  const unsigned int* thisData = thisNode.getData();
  for (int index = 0; index < NODESIZE; index++){
    cout << hex << thisData[index] << endl;
  }
  return (stream);
}
