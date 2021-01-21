#include <iostream>
#include <fstream>
#include <stdio.h>
#include "LinkedList.h"
#include "MyString.h"
#include "symbol_table.h"
#include "constants.h"
#include "pass2.h"

using namespace std; 

// PRE: fileName corresponds to a valid assembly file, say f,
//        with extension .lc
//      symbolTable holds address, size for all variables
//        and labels in f
//      tokenList holds all opcodes and registers in f
//        in MyString objects 
// POST: opens two files, say f1 and f2
//       f1 contains contents of symbolTable
//       f1 contains contents of tokenList in the form of
//         hexadecimal words
//       f2 contains contents of tokenList in teh form of
//         ascii characters
void beginPass2(const symbol_table & symbolTable,
		const LinkedList<MyString> & tokenList,
		const char* fileName){
  LinkedList<unsigned int> intList; // this holds instructions in ints
  int numTokens = tokenList.getSize(); // retrieve number of elements
				       // in tokenList
  int currentIndex = 0; // initialize index to first element
  MyString* currentTok; //initialize token pointer
  currentTok = tokenList.getNth(currentIndex); // get first token
  MyString endOfInstruction; // the default constructor of this class
			     // holds only the \0 char
  int PC = 0; 
  while (currentIndex < numTokens) {
    LinkedList<MyString> currentInstruction; // holds this
					     // instruction's tokens
    PC += 4; 
    while (!(*currentTok == endOfInstruction)){
      // ASSERT: this token is within the current instruction
      currentInstruction.append(*currentTok); 
      currentIndex ++; // increment index to select next element
      currentTok = tokenList.getNth(currentIndex); // select next
						   // element 
    }
    unsigned int binInstruction = intConvert(currentInstruction,
					     symbolTable,
					     PC);
       // convert currInstrucion to 32 bit word
    intList.append(binInstruction); 
  }
  // ASSERT: intList holds all unsigned int instructions
  writeOutput(intList, symbolTable, fileName); 
}

// PRE: instruction holds tokens for a valid assembly instruction,
//      symbolTable holds all label references that
//      may be in instruction
// POST: RV is an unsigned int whose bytes correspond
//       to the operands in instruction 
unsigned int intConvert(const LinkedList<MyString> & instruction,
			const symbol_table & symbolTable,
			int PC) { 
  MyString opcode = *instruction.getNth(0); // get opcode from front
					    // of instruction
  unsigned int intInstruction;
  int index = 0;
  bool found = false; 
  while (found == false) {
    if (opcode == opcodes[index]) {
      found = true;
    } else {
      index ++;
    }
  }
  switch(index){
  case 0:
    // ASSERT: this opcode is ADD
    convertR(instruction, intInstruction, index); 
    break;
  case 1:
    // ASSERT: this opcode is NAND
    convertR(instruction, intInstruction, index); 
    break;
  case 2:
    // ASSERT: this opcode is ADDI
    convertI(instruction, symbolTable, intInstruction, index, PC); 
    break;
  case 3:
    // ASSERT: this opcode is LW
        convertI(instruction, symbolTable, intInstruction, index, PC);  
    break;
  case 4:
    // ASSERT: this opcode is SW
        convertI(instruction, symbolTable, intInstruction, index, PC);  
    break;
  case 5:
    // ASSERT: this opcode is BEQ
        convertI(instruction, symbolTable, intInstruction, index, PC);  
    break;
  case 6:
    // ASSERT: this opcode is JALR
    convertJ(instruction, intInstruction, index); 
    break;
  case 7:
    // ASSERT: this opcode is HALT
    convertO(instruction, intInstruction, index);
    break;
  case 9:
    // ASSERT: this opcode is IN
    convertU(instruction, intInstruction, index);
    break;
  case 10:
    // ASSERT: this opcode is OUT
    convertU(instruction, intInstruction, index);
    break;
  case 12:
    // ASSERT: this opcode is LA
    convertL(instruction, symbolTable, intInstruction, index, PC);
    break;
  case 13:
    // ASSERT: this opcode is BGT
        convertI(instruction, symbolTable, intInstruction, index, PC); 
    break;
  }
  return intInstruction; 
}

// PRE: instruction holds tokens for valid R-type assembly instruction
//      opcode is the integer value of the first token in instruction
// POST: returns unsigned int with 1:1 correlation to assembly tokens
void convertR(const LinkedList<MyString> & instruction,
	      unsigned int & intInstruction,
	      int opcode) {
  intInstruction +=  opcode;
  MyString* currentToken;
  int currentRegister; 
  for (int index = 1; index < 4; index ++) {
    if (index != 3) {
      // ASSERT: this register is registerZ
      intInstruction = intInstruction << 20; 
    } else {
      // ASSERT: this is registerX or registerY
      intInstruction = intInstruction << 4;
    }
    currentToken = instruction.getNth(index);
    currentRegister = getRegisterValue(currentToken->getstring());
      // pass this token's MyString's char* 
    intInstruction +=  currentRegister;
  }
}

// PRE: instruction holds tokens for valid I-type assembly instruction
//      symbolTable contains all labels used in this assembly program
//      opcode is the integer value of the first token in instruction
//      PC holds byte address of next instruction in program
// POST: returns unsigned int with 1:1 correlation to assembly tokens
void convertI(const LinkedList<MyString> & instruction,
	      const symbol_table & symbolTable, 
	      unsigned int & intInstruction,
	      int opcode, int PC) {
  intInstruction += opcode;
  MyString* currentToken;
  int currentRegister; 
  for (int index = 1; index < 3; index ++) {
    intInstruction = intInstruction << 4;
    currentToken = instruction.getNth(index);
    int currentRegister = getRegisterValue(currentToken->getstring());
      // pass this token's MyString's char* 
    intInstruction += currentRegister;
  }
  intInstruction = intInstruction << 20;
  currentToken  = instruction.getNth(3);
  int signedVal = handleSignedOffset(*currentToken, symbolTable, PC); 
  intInstruction += signedVal; // DEBUG check if too big
}

// PRE: instruction holds tokens for valid J-type assembly instruction
//      opcode is the integer value of the first token in instruction
// POST: returns unsigned int with 1:1 correlation to assembly tokens
void convertJ(const LinkedList<MyString> & instruction,
	      unsigned int & intInstruction,
	      int opcode) {
  intInstruction +=  opcode;
  MyString * currentToken;
  int currentRegister; 
  for (int index = 1; index < 4; index ++) {
    // ASSERT: this is registerX or registerY
    intInstruction = intInstruction << 4;
    currentToken = instruction.getNth(index);
    currentRegister = getRegisterValue(currentToken->getstring());
      // pass this token's MyString's char* 
    intInstruction +=  currentRegister;
  }
  intInstruction = intInstruction << 20; 
}

// PRE: instruction holds tokens for valid U-type assembly instruction
//      opcode is the integer value of the first token in instruction
// POST: returns unsigned int with 1:1 correlation to assembly tokens
void convertU(const LinkedList<MyString> & instruction,
	      unsigned int & intInstruction,
	      int opcode) {
  intInstruction +=  opcode;
  intInstruction = intInstruction = intInstruction << 4; 
  MyString* registerToken = instruction.getNth(1); // get register x
  int registerX = getRegisterValue(registerToken->getstring());
  intInstruction += registerX;
  intInstruction = intInstruction << 24; 
}

// PRE: instruction holds tokens for valid L-type assembly instruction
//      symbolTable contains all labels used in this assembly program
//      opcode is the integer value of the first token in instruction
//      PC holds byte address of next instruction in program
// POST: returns unsigned int with 1:1 correlation to assembly tokens
void convertL(const LinkedList<MyString> & instruction,
	      const symbol_table & symbolTable, 
	      unsigned int & intInstruction,
	      int opcode, int PC) {
  intInstruction += opcode;
  intInstruction = intInstruction << 4;
  MyString* currentToken = instruction.getNth(1); // get register x
  int currentRegister = getRegisterValue(currentToken->getstring());
  intInstruction += currentRegister;
  intInstruction = intInstruction << 4; // skip null byte
  intInstruction = intInstruction << 20;
  currentToken  = instruction.getNth(2);
  int signedVal = handleSignedOffset(*currentToken, symbolTable, PC); 
  intInstruction += signedVal; 
}

// PRE: instruction holds tokens for valid O-type assembly instruction
//      opcode is the integer value of the first token in instruction
// POST: returns unsigned int with 1:1 correlation to assembly tokens
void convertO(const LinkedList<MyString> & instruction,
	      unsigned int & intInstruction,
	      int opcode) {
  intInstruction += opcode;
  intInstruction = intInstruction << 28; 
}


// PRE: operand exists in registers array
// POST: returns index of char* in registers
//       that is equal to operand
int getRegisterValue(char* operand) {
  int index = 0;
  bool found = false; // true iff find match for
                      //operand in registers
  while (index < MAX_REGISTERS || !found) {
    if (operand == registers[index]) {
      found = true; 
    } else {
      index ++;
    }
  }
  return index; 
}

// PRE: token holds either a signed value or label operand
// POST: determines if token is signed value or offset
//       if token is signed value returns integer equal to
//          the signed value
//       else token is an offset return difference between
//          current PC and label location 
int handleSignedOffset(MyString token, symbol_table symbolTable, int PC){
  // determine type
  int answer; 
  int index = 0;
  bool found = false; 
  while (index < symbolTable.get_numrows() && !found) {
    if (*symbolTable.get_name(index) == token) {
      found = true;
    } else {
      index ++;
    }
  }
  if (found) {
    // ASSERT: token is a variable located in symbolTable at index
    int address = *symbolTable.get_address(index);
    answer = address - PC; 
  } else {
    // ASSERT: token is a signed value
    answer = charToInt(token.getstring()); 
  }
  return answer; 
  
}

// PRE: charArray contains only chars in the range 0 - 9
//      and the final char is \0
// POST: returns integer value of charArray
int charToInt(char* charArray) {
  int sum = 0;
  int index = 0;
  char tempChar = charArray[index];
  int tempInt; 
  while (charArray[index] != EOS) {
    tempInt = tempChar - '0'; 
    sum = (sum * 10) + tempInt;
    index ++;
    tempChar = charArray[index]; 
  }
  return sum; 
}

// PRE: fileName corresponds to a valid assembly file, say f,
//        with extension .lc
//       intList holds all instructions in f in the form of
//        unsigned ints
//      symbolTable holds address, size for all variables
//        and labels in f
// POST: opens two files, say f1 and f2
//       f1 contains contents of symbolTable
//       f1 contains contents of tokenList in the form of
//         hexadecimal words
//       f2 contains contents of tokenList in teh form of
//         ascii characters
void writeOutput(LinkedList<unsigned int> intList,
		 const symbol_table symbolTable,
		 const char* fileName) {
  char* asciiOutfile;
  char* hexOutfile;
  getOutfileNames(fileName, asciiOutfile, hexOutfile);
  ofstream asciiOut (asciiOutfile); 
  // ofstream hexout (hexOutfile);
  FILE * hexout = fopen (hexOutfile, "w"); 
  int index = 0;
  unsigned int currentInt; 
  while (index < intList.getSize()) {
    currentInt = *intList.getNth(index); 
    fprintf(hexout, "%#08x", currentInt);
    fputs("\n", hexout); // add newline to hexout
    asciiOut << (char)currentInt; 
    index ++; 
  }
}

// PRE: fileName ends in .lc extension
// POST:  points asciiOutfile and hexOutfile pointers to proper fileNames
void getOutfileNames(const char* fileName, char* asciiOutfile, char* hexOutfile) {
  bool inName = true;
  int index = 0; 
  MyString asciiString;
  MyString hexString; 
  while(inName) {
    if (fileName[index] == '.'){
      asciiString.addchar('.');
      hexString.addchar('.');
      asciiString.addchar('l');
      hexString.addchar('l');
      asciiString.addchar('c');
      hexString.addchar('c');
      asciiString.addchar('a');
      hexString.addchar('h');
    } else {
      asciiString.addchar(fileName[index]);
      hexString.addchar(fileName[index]);
      index ++;
    }
  }
  asciiOutfile = asciiString.getstring();
  hexOutfile = hexString.getstring();
}
