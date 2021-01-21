/* Author Schuyler van Tine*/
/* Convert hexadecimal code into char-encoded binary*/

#include <iostream>
#include <fstream>

using namespace std; 

int hexToInt(char ch) {
  int val = 0; 
  if (ch >= '0' && ch <= '9') {
    val = (int)ch - (int)'0'; 
  }
  else if(ch == 'a' || ch == 'A'){
    val = 10;
  }
    else if(ch == 'b' || ch == 'B'){
    val = 11;
  }
    else if(ch == 'c' || ch == 'C'){
    val = 12;
  }
    else if(ch == 'd' || ch == 'D'){
    val = 13;
  }
    else if(ch == 'e' || ch == 'E'){
    val = 14;
  }
    else if(ch == 'f' || ch == 'F'){
    val = 15;
  }
  return val; 
}

int main(int argc, char* argv[]) {
  if (argc == 3){
    ifstream infile;
    ofstream outfile; 
    infile.open(argv[1]);
    outfile.open(argv[2]);
    char tempChar; // hold current char in infile
    int tempInt = 0;  // hold integer value of tempChar
    infile.get(tempChar); // get first char
    int loopCount = 0; // number of times the following loop
                       // has completed
    int charIndex = 0; 
    while (!infile.eof()) {
      if (loopCount == 2){
    	outfile << (char)tempInt; // store these two bytes in outfile
	                          // in a char 
    	loopCount = 0; // reinitialize to 0
    	tempInt = 0; // reinitialize to 0
      }
      if (tempChar != '\n') {
    	int currentByte = hexToInt(tempChar); // get int value of this hex char
    	tempInt = tempInt << 4; // shift a byte to make room for currentByte
    	tempInt += currentByte; // append currentByte to this int
    	loopCount ++; // increment number of loops 
      }
      infile.get(tempChar); // get next char
      charIndex ++;
    }
  }
  return 0; 
}

