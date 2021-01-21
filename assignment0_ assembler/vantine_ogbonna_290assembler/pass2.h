#ifndef INCLUDED_PASS2
#define INCLUDED_PASS2

#include "LinkedList.h"
#include "MyString.h"
#include "symbol_table.h"
//#include "constants.h"

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
		const char* fileName);

// PRE: instruction holds tokens for a valid assembly instruction,
//      symbolTable holds all label references that
//      may be in instruction
// POST: RV is an unsigned int whose bytes correspond
//       to the operands in instruction 
unsigned int intConvert(const LinkedList<MyString> & instruction,
			const symbol_table & symbolTable,
			int PC);

// PRE: instruction holds tokens for valid R-type assembly instruction
//      opcode is the integer value of the first token in instruction
// POST: returns unsigned int with 1:1 correlation to assembly tokens
void convertR(const LinkedList<MyString> & instruction,
	      unsigned int & intInstruction,
	      int opcode);

// PRE: instruction holds tokens for valid I-type assembly instruction
//      symbolTable contains all labels used in this assembly program
//      opcode is the integer value of the first token in instruction
//      PC holds byte address of next instruction in program
// POST: returns unsigned int with 1:1 correlation to assembly tokens
void convertI(const LinkedList<MyString> & instruction,
	      const symbol_table & symbolTable, 
	      unsigned int & intInstruction,
	      int opcode, int PC);

// PRE: instruction holds tokens for valid J-type assembly instruction
//      opcode is the integer value of the first token in instruction
// POST: returns unsigned int with 1:1 correlation to assembly tokens
void convertJ(const LinkedList<MyString> & instruction,
	      unsigned int & intInstruction,
	      int opcode);

// PRE: instruction holds tokens for valid U-type assembly instruction
//      opcode is the integer value of the first token in instruction
// POST: returns unsigned int with 1:1 correlation to assembly tokens
void convertU(const LinkedList<MyString> & instruction,
	      unsigned int & intInstruction,
	      int opcode);

// PRE: instruction holds tokens for valid L-type assembly instruction
//      symbolTable contains all labels used in this assembly program
//      opcode is the integer value of the first token in instruction
//      PC holds byte address of next instruction in program
// POST: returns unsigned int with 1:1 correlation to assembly tokens
void convertL(const LinkedList<MyString> & instruction,
	      const symbol_table & symbolTable, 
	      unsigned int & intInstruction,
	      int opcode, int PC);


// PRE: instruction holds tokens for valid O-type assembly instruction
//      opcode is the integer value of the first token in instruction
// POST: returns unsigned int with 1:1 correlation to assembly tokens
void convertO(const LinkedList<MyString> & instruction,
	      unsigned int & intInstruction,
	      int opcode);

// PRE: operand exists in registers array
// POST: returns index of char* in registers
//       that is equal to operand
int getRegisterValue(char* operand);

// PRE: token holds either a signed value or label operand
// POST: determines if token is signed value or offset
//       if token is signed value returns integer equal to
//          the signed value
//       else token is an offset return difference between
//          current PC and label location 
int handleSignedOffset(MyString token, symbol_table symbolTable, int PC);

// PRE: charArray contains only chars in the range 0 - 9
//      and the final char is \0
// POST: returns integer value of charArray
int charToInt(char* charArray);

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
void writeOutput(LinkedList<unsigned int> intList, const symbol_table symbolTable, const char* fileName);

// PRE: fileName ends in .lc extension
// POST:  points asciiOutfile and hexOutfile pointers to proper fileNames
void getOutfileNames(const char* fileName, char* asciiOutfile, char* hexOutfile);

#endif
