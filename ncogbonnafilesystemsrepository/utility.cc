#include "utility.h"

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
//
//POST: modifies word[index] s.t. pNum is placed at the placemark where
//mask has a hexadecimal 0 at.
void setNibble(unsigned int & word, unsigned int pNum, unsigned int pMask,
	       int PLACEMARK, int nibbleLocation){
  pNum = getNibble(pNum, nibbleLocation);
  //ASSERT: pNum is now rightmost
  //ASSERT: the digit you want to put in the 
  int temp = word & pMask; //temp = word[0] where the type for word
			     //has been reset to 0
  unsigned int shiftedP = pNum << (NIBBLE * PLACEMARK);
                                          //shifts pNum s.t  pType's
					  //# is at the placemark
					  //where the original
					  //placemark was
  word = temp | shiftedP;//modifies this object's type
                            //s.t. it is equal to pType
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
