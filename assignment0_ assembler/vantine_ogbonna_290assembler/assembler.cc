#include <iostream>
#include <fstream>
#include "symbol_table.h"
#include "beginpass1.h"
#include "pass2.h"

using namespace std; 
//PRE: Infile's name must be the second arguement else OS contains
//error. all characters of correct OPCODES must be capitalized.
//all characters of correct registers must be lowercase.
//before using a vaiable name, the token prior to the
//correct variables must be capitalized.
//POST: If infile is valid in terms of syntax, translates code found
//in the inFile and outputs  the machine code, symbol table, and machine
//code hextable to an outFile.
int main (int argc, char* argv[] ) {
  // check args
  bool argError = false;//true iff there are errors in either the cmdline or
                        //in the name of the inFile
  if (argc != 2) {
    argError = true;
  }
  char * inFileName = argv[1];
  ifstream inFile (inFileName);
  if (inFile == NULL) {
    argError = true;
  }

  if (argError) {
    cout << "Error: Invalid argument supplied" << endl;
  }
  else{
    //There are no errors concerning the name of the inFile and amount of
    //arguements
    symbol_table symbolTable;//will contain all the symbols from the
    //infile including names,
    //addresses(labels only), whether the
    //name is a variable or label, amount of
    //space (variables only), and whether or
    //not the address was found or not.
    LinkedList<MyString> tokenList;//will contain all the relevant
    //data from the infile
    bool syntaxValid = true; //will turn false iff there are
    //syntactical errors in the infile
    // populate symbolTable, tokenList
    // verify syntax of infile
    beginpass1(inFile, symbolTable, tokenList, syntaxValid);
    // these params passed by reference
    //ASSERT: syntaxValid is true if there are no syntactical errors
    //        in the given file
    //        symbolTable is filled with the various
    //        symbols found in the infile
    //        tokenlist contains all the relevant data from the infile
    inFile.close();
    
    cout << "tokenList: " << tokenList << endl;
    cout << "symbolTable: " << symbolTable << endl;
    if (syntaxValid) {
      // generate output files 
      beginPass2(symbolTable, tokenList, inFileName); 
    }
    else {
      //ASSERT: The infile did not have the correct code to run pass
      //two.
      cout << "Error: Syntax of supplied program invalid" << endl; 
    }
  }
}
