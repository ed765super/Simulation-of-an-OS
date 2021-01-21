#include <iostream>
#include <stdio.h>
using namespace std;
//constants:
#define SHIFT_BACK_NUMBER 28

#define CHAR0 '0'
#define CHAR9 '9'
#define UPPERA 'A'
#define UPPERF 'F'
#define UPPERZ 'Z'
#define LOWERA 'a'
#define LOWERH "h"
#define LOWERZ 'z'

//placemarks are the place where the nibble resides in a word.
#define PLACEMARK0 7
#define PLACEMARK1 6
#define PLACEMARK2 5
#define PLACEMARK3 4
#define PLACEMARK4 3
#define PLACEMARK5 2
#define PLACEMARK6 1
#define PLACEMARK7 0

#define DECIMAL_BASE 10
#define NODESIZE 8
#define NIBBLE 4

// PRE: index in range (0, 7) where 7 is the leftmost digit & 0 is the
// rightmost digit
// POST: index is big-endian
//       returns nibble located at index
int getNibble(unsigned int word, int index){
  word = word << NIBBLE * index;//Makes the operand the leftmost bit
  word = word >> SHIFT_BACK_NUMBER;
  //makes the operand the rightmost bit
  return word; 
}

//PRE: word should be an unsigned ints that represent what
//you want to modify.
// pNum must be the number that you want to change the nibble mask has
//a 0 in. it is assumed that the digit that you want is the rightmost
//bit
// pMask should be an 8 digit hexadecimal # where the number 0 is in
//the place of the number you wish to modify and a F everywhere else.
// PLACEMARK should be the placemark of the nibble you wish to modify
//POST: modifies word[index] s.t. pNum is placed at the placemark where
//mask has a hexadecimal 0 at.
void setNibble(unsigned int & word, unsigned int pNum, unsigned int pMask,
	       int PLACEMARK, int nibbleLocation){
  cout << "start set nibble" << endl;
  pNum = getNibble(pNum, nibbleLocation);
  //ASSERT: pNum is now rightmost
  //ASSERT: the digit you want to put in the 
  cout << "word is: ";
  printf("%#010x\n", word);
  cout << "pNum is: ";
  printf("%#010x\n", pNum);
  cout << "mask is: ";
  printf("%#010x\n", pMask);
  cout << "The placeMark is: ";
  printf("%#010x\n", PLACEMARK);
  int temp = word & pMask; //temp = word[0] where the type for word
			     //has been reset to 0
  cout << "word & Mask should be a 0 @ placemark rest ok: ";
  printf("%#010x\n", temp);
  unsigned int shiftedP = pNum << (NIBBLE * PLACEMARK);
                                          //shifts pNum s.t  pType's
					  //# is at the placemark
					  //where the original
					  //placemark was
  cout << "shiftedP should be PLACEMARK # of 0s: ";
  printf("%#010x\n", shiftedP);
  word = temp | shiftedP;//modifies this object's type
                            //s.t. it is equal to pType
  cout << "word is now: ";
  printf("%#010x\n", word);
  cout << "end setNibble" << endl;
}

// PRE: index in range (0, 3) where 3 is the rightmost digit & 0 is the
// leftmost digit. can only do 1 word at a time
// POST: index is big-endian
//       returns byte located at index
unsigned int getByte(unsigned int word, int index){
  unsigned int resultingByte = 0x0;
  if (index == 3){
    unsigned int nibble1 = getNibble(word, PLACEMARK6);
    unsigned int nibble2 = getNibble(word, PLACEMARK7);
    int mask1 = 0xFFFFFF0F;
    int mask2 = 0xFFFFFFF0;
    setNibble(resultingByte, nibble1, mask1, PLACEMARK6, 7);
    setNibble(resultingByte, nibble2, mask2, PLACEMARK7, 7);
  }
  else if(index == 2){
    unsigned int nibble1 = getNibble(word, PLACEMARK4);
    unsigned int nibble2 = getNibble(word, PLACEMARK5);
    int mask1 = 0xFFFF0FFF;
    int mask2 = 0xFFFFF0FF;
    setNibble(resultingByte, nibble1, mask1, PLACEMARK4, 7);
    setNibble(resultingByte, nibble2, mask2, PLACEMARK5, 7);
  }
  else if(index == 1){
    unsigned int nibble1 = getNibble(word, PLACEMARK2);
    unsigned int nibble2 = getNibble(word, PLACEMARK3);
    int mask1 = 0xFF0FFFFF;
    int mask2 = 0xFFF0FFFF;
    setNibble(resultingByte, nibble1, mask1, PLACEMARK2, 7);
    setNibble(resultingByte, nibble2, mask2, PLACEMARK3, 7);
  }
  else if(index == 0){
    unsigned int nibble1 = getNibble(word, PLACEMARK0);
    unsigned int nibble2 = getNibble(word, PLACEMARK1);
    int mask1 = 0x0FFFFFFF;
    int mask2 = 0xF0FFFFFF;
    setNibble(resultingByte, nibble1, mask1, PLACEMARK0, 7);
    setNibble(resultingByte, nibble2, mask2, PLACEMARK1, 7);
  }
  return resultingByte; 
}

//PRE: word should be an  unsigned ints that represent what
//you want to modify.
//byteNumber represents the byte of word you wish to
//modify.
// pByte is what you want to change word@byteNumber to
// pByteNumber is the location of the byte in pByte that you want to
//put in word
//can only do 1 word at a time
//POST: modifies word@ByteNumber s.t. pByte is placed at the byte @
//the indicated byteNumber
void setByte(unsigned int & word, unsigned int byteNumber,
	     unsigned int pByte, unsigned int pByteNumber){
  cout << "setByte" << endl;
  cout << "word: ";
  printf("%#010x\n", word);
  cout << "byteNumber: ";
  printf("%#010x\n", byteNumber);
  cout << "pByte: ";
  printf("%#010x\n", pByte);
  cout << "pByteNumber: ";
  printf("%#010x\n", pByteNumber);
  if (byteNumber == 3){
    //ASSERT: User wants to replace the third byte
    if (pByteNumber == 3){
      //ASSERT: the byte with the nibbles user wants to but in Byte number
      //is in pByte's 3rd byte
      unsigned int nibble1 = getNibble(pByte, PLACEMARK6);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK7);
      int mask1 = 0xFFFFFF0F;
      int mask2 = 0xFFFFFFF0;
      setNibble(word, nibble1, mask1, PLACEMARK6, 7);
      setNibble(word, nibble2, mask2, PLACEMARK7, 7);
    }
    else if (pByteNumber == 2){
      //ASSERT: the byte with the nibbles user wants to but in Byte number
      //is in pByte's 3rd byte
      unsigned int nibble1 = getNibble(pByte, PLACEMARK4);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK5);
      int mask1 = 0xFFFF0FFF;
      int mask2 = 0xFFFFF0FF;
      setNibble(word, nibble1, mask1, PLACEMARK4, 7);
      setNibble(word, nibble2, mask2, PLACEMARK5, 7);
    }
    else if (pByteNumber == 1){
      //ASSERT: the byte with the nibbles user wants to but in Byte number
      //is in pByte's 3rd byte
      unsigned int nibble1 = getNibble(pByte, PLACEMARK2);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK3);
      int mask1 = 0xFF0FFFFF;
      int mask2 = 0xFFF0FFFF;
      setNibble(word, nibble1, mask1, PLACEMARK2, 7);
      setNibble(word, nibble2, mask2, PLACEMARK3, 7);
    }
    else if (pByteNumber == 0){
      unsigned int nibble1 = getNibble(pByte, PLACEMARK0);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK1);
      int mask1 = 0x0FFFFFFF;
      int mask2 = 0xF0FFFFFF;
      setNibble(word, nibble1, mask1, PLACEMARK0, 7);
      setNibble(word, nibble2, mask2, PLACEMARK1, 7);
    }
  }
  else if(byteNumber == 2){
   //ASSERT: User wants to replace the second byte
    if (pByteNumber == 3){
      //ASSERT: the byte with the nibbles user wants to but in Byte number
      //is in pByte's 3rd byte
      unsigned int nibble1 = getNibble(pByte, PLACEMARK6);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK7);
      int mask1 = 0xFFFFFF0F;
      int mask2 = 0xFFFFFFF0;
      setNibble(word, nibble1, mask1, PLACEMARK6, 7);
      setNibble(word, nibble2, mask2, PLACEMARK7, 7);
    }
    else if (pByteNumber == 2){
      //ASSERT: the byte with the nibbles user wants to but in Byte number
      //is in pByte's 3rd byte
      unsigned int nibble1 = getNibble(pByte, PLACEMARK4);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK5);
      int mask1 = 0xFFFF0FFF;
      int mask2 = 0xFFFFF0FF;
      setNibble(word, nibble1, mask1, PLACEMARK4, 7);
      setNibble(word, nibble2, mask2, PLACEMARK5, 7);
    }
    else if (pByteNumber == 1){
      //ASSERT: the byte with the nibbles user wants to but in Byte number
      //is in pByte's 3rd byte
      unsigned int nibble1 = getNibble(pByte, PLACEMARK2);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK3);
      int mask1 = 0xFF0FFFFF;
      int mask2 = 0xFFF0FFFF;
      setNibble(word, nibble1, mask1, PLACEMARK2, 7);
      setNibble(word, nibble2, mask2, PLACEMARK3, 7);
    }
    else if (pByteNumber == 0){
      unsigned int nibble1 = getNibble(pByte, PLACEMARK0);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK1);
      int mask1 = 0x0FFFFFFF;
      int mask2 = 0xF0FFFFFF;
      setNibble(word, nibble1, mask1, PLACEMARK0, 7);
      setNibble(word, nibble2, mask2, PLACEMARK1, 7);
    }
  }
  else if(byteNumber == 1){
    //ASSERT: User wants to replace the first byte
    if (pByteNumber == 3){
      //ASSERT: the byte with the nibbles user wants to but in Byte number
      //is in pByte's 3rd byte
      unsigned int nibble1 = getNibble(pByte, PLACEMARK6);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK7);
      int mask1 = 0xFFFFFF0F;
      int mask2 = 0xFFFFFFF0;
      setNibble(word, nibble1, mask1, PLACEMARK6, 7);
      setNibble(word, nibble2, mask2, PLACEMARK7, 7);
    }
    else if (pByteNumber == 2){
      //ASSERT: the byte with the nibbles user wants to but in Byte number
      //is in pByte's 3rd byte
      unsigned int nibble1 = getNibble(pByte, PLACEMARK4);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK5);
      int mask1 = 0xFFFF0FFF;
      int mask2 = 0xFFFFF0FF;
      setNibble(word, nibble1, mask1, PLACEMARK4, 7);
      setNibble(word, nibble2, mask2, PLACEMARK5, 7);
    }
    else if (pByteNumber == 1){
      //ASSERT: the byte with the nibbles user wants to but in Byte number
      //is in pByte's 3rd byte
      unsigned int nibble1 = getNibble(pByte, PLACEMARK2);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK3);
      int mask1 = 0xFF0FFFFF;
      int mask2 = 0xFFF0FFFF;
      setNibble(word, nibble1, mask1, PLACEMARK2, 7);
      setNibble(word, nibble2, mask2, PLACEMARK3, 7);
    }
    else if (pByteNumber == 0){
      unsigned int nibble1 = getNibble(pByte, PLACEMARK0);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK1);
      int mask1 = 0x0FFFFFFF;
      int mask2 = 0xF0FFFFFF;
      setNibble(word, nibble1, mask1, PLACEMARK0, 7);
      setNibble(word, nibble2, mask2, PLACEMARK1, 7);
    }
  }
  else if(byteNumber == 0){
    //ASSERT: User wants to replace the third byte
    if (pByteNumber == 3){
      //ASSERT: the byte with the nibbles user wants to but in Byte number
      //is in pByte's 3rd byte
      unsigned int nibble1 = getNibble(pByte, PLACEMARK6);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK7);
      int mask1 = 0xFFFFFF0F;
      int mask2 = 0xFFFFFFF0;
      setNibble(word, nibble1, mask1, PLACEMARK6, 7);
      setNibble(word, nibble2, mask2, PLACEMARK7, 7);
    }
    else if (pByteNumber == 2){
      //ASSERT: the byte with the nibbles user wants to but in Byte number
      //is in pByte's 3rd byte
      unsigned int nibble1 = getNibble(pByte, PLACEMARK4);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK5);
      int mask1 = 0xFFFF0FFF;
      int mask2 = 0xFFFFF0FF;
      setNibble(word, nibble1, mask1, PLACEMARK4, 7);
      setNibble(word, nibble2, mask2, PLACEMARK5, 7);
    }
    else if (pByteNumber == 1){
      //ASSERT: the byte with the nibbles user wants to but in Byte number
      //is in pByte's 3rd byte
      unsigned int nibble1 = getNibble(pByte, PLACEMARK2);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK3);
      int mask1 = 0xFF0FFFFF;
      int mask2 = 0xFFF0FFFF;
      setNibble(word, nibble1, mask1, PLACEMARK2, 7);
      setNibble(word, nibble2, mask2, PLACEMARK3, 7);
    }
    else if (pByteNumber == 0){
      unsigned int nibble1 = getNibble(pByte, PLACEMARK0);
      unsigned int nibble2 = getNibble(pByte, PLACEMARK1);
      int mask1 = 0x0FFFFFFF;
      int mask2 = 0xF0FFFFFF;
      setNibble(word, nibble1, mask1, PLACEMARK0, 7);
      setNibble(word, nibble2, mask2, PLACEMARK1, 7);
    }
  }
}

int main(){
  //test getNibble
  unsigned int word = 0x01234567;
  int number7 = getNibble(word, PLACEMARK7);
  int number0 = getNibble(word, PLACEMARK0);
  int number3 = getNibble(word, PLACEMARK3);
  cout << "7 = " << number7 << " 0 = " << number0 << " 3 = " << number3
       << endl;
  
  //test setNibble
  unsigned int pWord = 0xABCDEFFF;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~set 0th to 7th~~~~~~~~~~~~~~" << endl;
  int mask7 = 0x0FFFFFFF;
  setNibble(word, pWord, mask7, PLACEMARK0, 7);
  int mask0 = 0xFFFFFFF0;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~set 7th to 4th~~~~~~~~~~~~~~" << endl;
  setNibble(word, pWord, mask0, PLACEMARK7, 4);
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~get 3rd to 1st~~~~~~~~~~~~~~" << endl;
  int mask3 = 0xFF0FFFFF;
  setNibble(word, pWord, mask3, PLACEMARK3, 1);
  cout << "Thus word is: ";
  printf("%#010x\n", word);
  //test getByte
  word = 0x01234567;
  int num01 = getByte(word, 0);
  int num67 = getByte(word, 3);
  int num23 = getByte(word, 1);
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~BYTES 0,1,3: " << endl;
  printf("%#010x\n", num01);
  printf("%#010x\n", num23);
  printf("%#010x\n", num67);
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  //test setByte
  word = 0x01234567;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~setByte~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << "word is: 0x01234567" << endl;
  int dataByte0 = 0; //represents the byte number 0 of some word of
		     //data
  int dataByte1 = 1; //represents the byte number 1 of some word of
		     //data
  unsigned int byte0 = getByte(word, 0);
  cout << "BYTE 0 is: " << hex << byte0 << endl;
  unsigned int byte1 = getByte(word, 1);
  cout << "BYTE 1 is: " << hex << byte1 << endl;
  setByte(word, 3, byte0, 0);
  setByte(word, 2, byte1, 1);
  cout << "word should be: 0x01230123" << endl;
  printf("%#010x\n", word);
  
  
  return 0;
}
