#ifndef INCLUDED_PASS1
#define INCLUDED_PASS1
#include "symbol_table.h"
#include "stringFunctions.h"
#include "constants.h"
//PRE: tokenList must be an empty LinkedList of MyString objects object
//POST: tokenlist contains all the relevant data from the inFile
void tokenizeFile(istream & inFile, LinkedList<MyString> & tokenList);

//PRE: symbolTable is a NULL symbol_table object.
//POST: symbolTable is fulled with the various relevant daa from
//      the inFile
void populateSymbolTable(LinkedList<MyString> & tokenList,
			 symbol_table & symbolTable);
//PRE:
//POST: RV = true iff tokenString is in operators
bool checkInOpcodes(const char* tokenString);

//PRE:
//POST: RV = true iff curr_token is in registers
bool checkInRegisters(const char* curr_token);
  
//PRE: symbolTable is a populated symbol_table object. syntaxValid is
//initialized as false.
//POST: syntaxValid is true iff symbolTable has no syntactical
//      errors.
void checkSymbolTable(symbol_table & symbolTable, bool & syntaxValid);

//PRE: tokenList must be populated. syntaxValid must be initially false.
//POST: syntaxValid is true iff all the op codes in the token list
//      are actual opcodes and have the correct number of operands and operands
//are actual opcodes and operands
void checkOpCodesnumoperands(LinkedList<MyString> & tokenList, bool & syntaxValid);

//PRE: inFile must be a non-NULL file containing assembly
//     code. symbolTable should be a NULL symbol_table object.
//     tokenlist must be an empty LinkedList of
//     MyString objects that will represents all the relevant data in the
//     infile. syntax valid must be a boolean that starts out
//     false that represents whether or not the given infile has any
//     syntactical errors.
//POST: syntaxValid is true iff there are no syntactical errors
//      in the given infile
//      symbolTable is filled with the various symbols found in
//      the infile.
//      tokenlist contains all the relevant data from the infile
void beginpass1(istream & inFile, symbol_table & symbolTable,
		LinkedList<MyString> & tokenList, bool & syntaxValid);
#endif
