#ifndef INCLUDED_UTILITY
#define INCLUDED_UTILITY
#include "constants.h"
// PRE: index in range (0, 7)
// POST: index is big-endian
//       returns nibble located at index
int getNibble(unsigned int word, int index);

// PRE: index in range (0, 3) where 3 is the leftmost digit & 0 is the
// rightmost digit
//con only do 1 word at a time
// POST: index is big-endian
//       returns nibble located at index
unsigned int getByte(unsigned int word, int index);
  
//PRE: word represents the index of data of the word you wish to
//modify.
// pNum must be the number that you want to change the nibble mask has
//a 0 in.
// pMask should be an 8 digit hexadecimal # where the number 0 is in
//the place of the number you wish to modify and a 1 everywhere else.
// PLACEMARK should be the placemark of the nibble you wish to modify
//POST: modifies data[word] s.t. pNum is placed at the placemark where
//mask has a hexadecimal 0 at.
void setNibble(unsigned int & word, unsigned int pNum, unsigned int pMask,
	       int PLACEMARK, int nibbleLocation);

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
	     unsigned int pByte, unsigned int pByteNumber);

#endif
