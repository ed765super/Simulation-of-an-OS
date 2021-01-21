/* Author: Schuyler van Tine */
/* Utility Functions         */

#include <fstream>
#include "utility.h"
using namespace std; 

// PRE: file refers to valid file
// POST: returns the number of lines in the given file
int countLines(ifstream & file){
  int numLines = 0; 
  char temp;
  while (!file.eof()) {
    if (temp == '\n'){
      numLines ++;
    }
    file.get(temp);
  }
  return numLines;
}

// PRE: file refers to valid file, whose contents are
//        chars representing bytes
// POST: returns the number of 32 bit words represented
//         by the chars in file
int countBinLines(ifstream & file){
  int numLines  = 0;
  int charCount = 0; 
  char temp;
  while (!file.eof()) {
    if (charCount == 4) {
      // ASSERT: read 4 chars
      numLines ++;
      charCount = 0; 
    } else {
      charCount ++;
    }
    file.get(temp);
  }
  return numLines;
}

// PRE: index in range (0, 7)
// POST: index is big-endian
//       returns byte located at index
int getByte(unsigned int word, int index){
  word = word << 4 * index;
  int MAX_INDEX = 7
  word = word >> (MAX_INDEX - index) * 4;
  return word; 
}

