#include "contentNode.h"
using namespace std;
//CONSTRUCTOR
//PRE:
//POST: creates a this object
contentNode::contentNode(unsigned int pData[NODESIZE]){
  for (int index = 0; index < NODESIZE; index++){
    data[index] = pData[index];
  }
}
//GETTER:
//PRE: this object is defined
//POST: modifies dummyContent s.t. it = this object's content
void contentNode::getContent(unsigned int dummyContent[6]){
  unsigned int content1 = 0x0;//will hold the first line of the content
  unsigned int content2 = 0x0;//will hold the second line of the content
  unsigned int content3 = 0x0;//will hold the third line of the content
  unsigned int content4 = 0x0;//will hold the fourth line of the content
  unsigned int content5 = 0x0;//will hold the fifth line of the content
  unsigned int content6 = 0x0;//will hold the sixth line of the content
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
  setByte(content1, dataByte1, byte1, dataByte1);
  setByte(content1, dataByte2, byte2, dataByte1);
  setByte(content1, dataByte3, byte3, dataByte3);
  //ASSERT: The bytes that represent the first line of the content
  //associated with this file node has been placed in content1
  content2 = data[1];
  content3 = data[2];
  content4 = data[3];
  content5 = data[4];
  content6 = data[5];
  int CONTWORDS = 6; //will hold the number of words in data that will represent
  //the content of this node
  unsigned int contentArray[CONTWORDS];
  contentArray[0] = content1;
  contentArray[1] = content2;
  contentArray[2] = content3;
  contentArray[3] = content4;
  contentArray[4] = content5;
  contentArray[5] = content6;
  //ASSERT: contentArray is fully set
  for (int index = 0; index < CONTWORDS; index++){
    dummyContent[index] = contentArray[index];
  }
  //ASSERT: the parameter is now the array that represents this object's
  //content
}

//PRE: this object is defined
//POST: RV =  this object's associated file
unsigned int contentNode::getFile() const{
  return data[6];
}

//PRE: this object is defined
//POST: RV =  this object's prev
unsigned int contentNode::getPrev() const{
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
//POST: RV =  this object's next
unsigned int contentNode::getNext() const{
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
//would represent 'Content'
//POST: modifies this object's content s.t. it is equal to pContent
void contentNode::setContent(unsigned int pContent[6]){
  int dataByte0 = 0; //represents the byte number 0 of some word of
		     //data
  int dataByte1 = 1; //represents the byte number 1 of some word of
		     //data
  int dataByte2 = 2; //represents the byte number 2 of some word of
		     //data
  int dataByte3 = 3; //represents the byte number 3 of some word of
		     //data
  unsigned int byte1 = getByte(pContent[0], dataByte1);
  unsigned int byte2 = getByte(pContent[0], dataByte2);
  unsigned int byte3 = getByte(pContent[0], dataByte3);
  setByte(data[0], dataByte1, byte1, dataByte1);
  setByte(data[0], dataByte2, byte2, dataByte2);
  setByte(data[0], dataByte3, byte3, dataByte3);
  //ASSERT: the bytes that represent the content for line 0 have been set
  unsigned int byte0 = getByte(pContent[1], dataByte0);
  byte1 = getByte(pContent[1], dataByte1);
  byte2 = getByte(pContent[1], dataByte2);
  byte3 = getByte(pContent[1], dataByte3);
  setByte(data[1], dataByte0, byte0, dataByte0);
  setByte(data[1], dataByte1, byte1, dataByte1);
  setByte(data[1], dataByte2, byte2, dataByte2);
  setByte(data[1], dataByte3, byte3, dataByte3);
  //ASSERT: the bytes that represent the content for line 1 have been set
  byte0 = getByte(pContent[2], dataByte0);
  byte1 = getByte(pContent[2], dataByte1);
  byte2 = getByte(pContent[2], dataByte2);
  byte3 = getByte(pContent[2], dataByte3);
  setByte(data[2], dataByte0, byte0, dataByte0);
  setByte(data[2], dataByte1, byte1, dataByte1);
  setByte(data[2], dataByte2, byte2, dataByte2);
  setByte(data[2], dataByte3, byte3, dataByte3);
  //ASSERT: the bytes that represent the content for line 2 have been set
  byte0 = getByte(pContent[3], dataByte0);
  byte1 = getByte(pContent[3], dataByte1);
  byte2 = getByte(pContent[3], dataByte2);
  byte3 = getByte(pContent[3], dataByte3);
  setByte(data[3], dataByte0, byte0, dataByte0);
  setByte(data[3], dataByte1, byte1, dataByte1);
  setByte(data[3], dataByte2, byte2, dataByte2);
  setByte(data[3], dataByte3, byte3, dataByte3);
  //ASSERT: the bytes that represent the content for line 3 have been set
  byte0 = getByte(pContent[4], dataByte0);
  byte1 = getByte(pContent[4], dataByte1);
  byte2 = getByte(pContent[4], dataByte2);
  byte3 = getByte(pContent[4], dataByte3);
  setByte(data[4], dataByte0, byte0, dataByte0);
  setByte(data[4], dataByte1, byte1, dataByte1);
  setByte(data[4], dataByte2, byte2, dataByte2);
  setByte(data[4], dataByte3, byte3, dataByte3);
  //ASSERT: the bytes that represent the content for line 4 have been set
  byte0 = getByte(pContent[5], dataByte0);
  byte1 = getByte(pContent[5], dataByte1);
  byte2 = getByte(pContent[5], dataByte2);
  byte3 = getByte(pContent[5], dataByte3);
  setByte(data[5], dataByte0, byte0, dataByte0);
  setByte(data[5], dataByte1, byte1, dataByte1);
  setByte(data[5], dataByte2, byte2, dataByte2);
  setByte(data[5], dataByte3, byte3, dataByte3);
  //ASSERT: the bytes that represent the content for line 5 have been set
}
  
//PRE: this object is defined & parameter is an unsigned int that
//would represent 'parent'
//POST: modifies this object's parent file s.t. it is equal to pFatherFile
void contentNode::setFile(unsigned int pFatherFile){
  data[6] = pFatherFile;
}
  
//PRE: this object is defined & parameter is an unsigned int that
//would represent 'prev'
//POST: modifies this object's prev s.t. it is equal to pPrev
void contentNode::setPrev(unsigned int pPrev){
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
//would represent 'next'
//POST: modifies this object's next s.t. it is equal to pNext
void contentNode::setNext(unsigned int pNext){
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
ostream & operator << (ostream & stream, const contentNode & thisNode){
  const unsigned int* thisData = thisNode.getData();
  for (int index = 0; index < NODESIZE; index++){
    cout << hex << thisData[index] << endl;
  }
  return (stream);
}
