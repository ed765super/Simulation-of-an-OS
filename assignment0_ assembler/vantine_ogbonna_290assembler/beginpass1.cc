#include "beginpass1.h"
#include <fstream>
#include "constants.h"

//PRE: tokenList must be an empty LinkedList of MyString objects object
//POST: tokenList contains all the relevant data from the inFile
void tokenizeFile(istream & inFile, LinkedList<MyString> & tokenList){
  char curr_code;
  curr_code = inFile.get();
  while (!(inFile.eof())){
    MyString token;
    while ((curr_code != aSpace) && (curr_code != newLine) &&
	   (curr_code != semicolon) && (curr_code != leftparen) &&
	   (curr_code != rightparen) && (!(inFile.eof()))){
      //ASSERT curr_code is a leter to a word
      token.addchar(curr_code);
      curr_code = inFile.get();
    }
    if (curr_code == semicolon){
	token.addchar(curr_code);
      }
    //ASSERT: I have a word/semicolon to add to the tokenList
    cout << "curr token is: " << token << endl;
    cout << "is it an OPCODE? " << checkInOpcodes(token.getstring()) << endl;
    cout << "is it a register? " << checkInRegisters(token.getstring()) << endl;
    cout << "is it a semicolon?" << (*token.getstring() == semicolon) << endl;
    if (*token.getstring() == semicolon){
      //ASSERT: token is a semicolon
      tokenList.append(token);
    }
    if (checkInOpcodes(token.getstring())){
      //token is an OPCODE
      tokenList.append(token);
    }
    if(checkInRegisters(token.getstring())){
      //token is a register
      tokenList.append(token);
    }
    curr_code = inFile.get();
  }
  MyString endofstring;
  tokenList.append(endofstring);
  cout << "tokenList = " << tokenList << endl;
}
//PRE:
//POST: RV = true iff tokenString is in operators
bool checkInOpcodes(const char* tokenString){
  bool OPCODEFOUND = false;
  if (isEqualString(tokenString, opcodes[0])){
    OPCODEFOUND = true;
  }
  else if (isEqualString(tokenString, opcodes[1])){
    OPCODEFOUND = true;
  }
  else if (isEqualString(tokenString, opcodes[2])){
    OPCODEFOUND = true;
  }
  else if (isEqualString(tokenString, opcodes[3])){
    OPCODEFOUND = true;
  }
  else if (isEqualString(tokenString, opcodes[4])){
    OPCODEFOUND = true;
  }
  else if (isEqualString(tokenString, opcodes[5])){
    OPCODEFOUND = true;
  }
  else if (isEqualString(tokenString, opcodes[6])){
    OPCODEFOUND = true;
  }
  else if (isEqualString(tokenString, opcodes[7])){
    OPCODEFOUND = true;
  }
  else if (isEqualString(tokenString, opcodes[9])){
    OPCODEFOUND = true;
  }
  else if (isEqualString(tokenString, opcodes[10])){
    OPCODEFOUND = true;
  }
  else if (isEqualString(tokenString, opcodes[12])){
    OPCODEFOUND = true;
  }
  else if (isEqualString(tokenString, opcodes[13])){
    OPCODEFOUND = true;
  }
  return (OPCODEFOUND);
}
//PRE:
//POST: RV = true iff curr_token is in registers
bool checkInRegisters(const char* tokenString){
  bool REGISTERFOUND = false;
  if (isEqualString(tokenString, registers[0])){
    REGISTERFOUND = true;
  }
  else if (isEqualString(tokenString, registers[1])){
    REGISTERFOUND = true;
  }
  else if (isEqualString(tokenString, registers[2])){
    REGISTERFOUND = true;
  }
  else if (isEqualString(tokenString, registers[3])){
    REGISTERFOUND = true;
  }
  else if (isEqualString(tokenString, registers[4])){
    REGISTERFOUND = true;
  }
  else if (isEqualString(tokenString, registers[5])){
    REGISTERFOUND = true;
  }
  else if (isEqualString(tokenString, registers[6])){
    REGISTERFOUND = true;
  }
  else if (isEqualString(tokenString, registers[7])){
    REGISTERFOUND = true;
  }
  else if (isEqualString(tokenString, registers[8])){
    REGISTERFOUND = true;
  }
  else if (isEqualString(tokenString, registers[9])){
    REGISTERFOUND = true;
  }
  else if (isEqualString(tokenString, registers[10])){
    REGISTERFOUND = true;
  }
  else if (isEqualString(tokenString, registers[11])){
    REGISTERFOUND = true;
  }
  else if (isEqualString(tokenString, registers[12])){
    REGISTERFOUND = true;
  }
  else if (isEqualString(tokenString, registers[13])){
    REGISTERFOUND = true;
  }
  else if (isEqualString(tokenString, registers[14])){
    REGISTERFOUND = true;
  }
  else if (isEqualString(tokenString, registers[15])){
    REGISTERFOUND = true;
  }
  return (REGISTERFOUND);
}

//PRE: symbolTable is a NULL symbol_table object.
//POST: symbolTable is filled with the various relevant daa from
//      the inFile
void populateSymbolTable(LinkedList<MyString> & tokenList,
			 symbol_table & symbolTable){
  int index = 0;
  int curr_word = 0; //will hold what word we are on.
  char variable = 'V';
  char label = 'L';
  while (index < tokenList.getSize()){
    MyString* curr_token = tokenList.getNth(index);
    char* tokenString = curr_token->getstring();
    bool isOpCode = checkInOpcodes(tokenString);
    bool isRegister = checkInRegisters(tokenString);
    if ((!isOpCode) && (!isRegister)){
      if(isEqualString(tokenString, VAR)){
	MyString* vari_name_token = tokenList.getNth(index+1);
	MyString* amountofSpace = tokenList.getNth(index+2);
	char* amountofSpace_String = amountofSpace->getstring();
	char* vari_name_String = curr_token->getstring();
	int integerofSpace = strToInt(amountofSpace_String);
	symbolTable.addrow(*vari_name_token, -1, variable, integerofSpace,
			   true);
      }
      else{
	//ASSERT: curr_token == Label
	MyString* semicolonOropcode = tokenList.getNth(index+1);
	char* semiOrcodeString = semicolonOropcode->getstring();
	if (*semiOrcodeString == semicolon){
	  //ASSERT: We have the label but don't know it's location
	  symbolTable.addrow(*semicolonOropcode, -1, label, -1, false);
	}
	else{
	  //ASSERT: we have the label and know the address
	  symbolTable.addrow(*semicolonOropcode, curr_word, label, -1, true);
	}
	//ASSERT: We have added a label row
      }
      //ASSERT: We've added a label or variable row
    }
    // cout<< "index: " << index << endl;
    // cout<< "token size: " << tokenList.getSize() << endl;
    index++;
    if (*tokenString == semicolon){
    curr_word += NEXTWORD;
    }
  }
}

//PRE: symbolTable is a populated symbol_table object. syntaxValid is
//initialized as true.
//POST: syntaxValid is true iff symbolTable has no syntactical
//      errors.
void checkSymbolTable(symbol_table & symbolTable, bool & syntaxValid){
  int symbolTableRows = symbolTable.get_numrows();
  int index = 0;
  while ((index < symbolTableRows) && (!syntaxValid)){
    bool* curr_addressStatus = symbolTable.get_addressfound(index);
    //ASSERT: curr_addressStatus is now the current label's address
    //status
    if (*curr_addressStatus == false){
    //ASSERT: the address of this label has not been found
    //COLLORARY: the file is not syntactically correct
    syntaxValid = false;
    
    }
    index++;
  }
}
//PRE: tokenList must be populated. syntaxValid must be initially true.
//POST: syntaxValid is true iff all the op codes in the token list
//      are actual opcodes and have the correct number of operands and operands
//are actual opcodes and operands
void checkOpCodesnumoperands(LinkedList<MyString> & tokenList, bool & syntaxValid){
  int tokenListindex = 0;
  MyString* curr_token = tokenList.getNth(tokenListindex);
  char* curr_string = curr_token->getstring();
  int sizeoftokenList = tokenList.getSize();
  
  while ((tokenListindex < sizeoftokenList) && (syntaxValid)){
    bool isOPCODE = checkInOpcodes(curr_string);
    if (isOPCODE){
      //ASSERT: curr_string is an OPCODE
      if (curr_string == opcodes[0]){
	//ASSERT: ADD needs 3 operands x, y, and z s.t. x = y + z
	MyString* MyOperand1 = tokenList.getNth(tokenListindex+1);
	char* operand1 = MyOperand1->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	MyString* MyOperand2 = tokenList.getNth(tokenListindex+2);
	char* operand2 = MyOperand2->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	MyString* MyOperand3 = tokenList.getNth(tokenListindex+3);
	char* operand3 = MyOperand3->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	if ((!checkInRegisters(operand1)) || (!checkInRegisters(operand2)) ||
	    (!checkInRegisters(operand3))){
	  //ASSERT: either x, y, or z is an invalid operand
	  syntaxValid = false;
	}
	//ASSERT: We have checked a line of the assemble code
	tokenListindex += 4;
	//The reason the program is adding that magic number to tokenListindex
	//is so next time around the while loop, when the token is pulled, we
	//pull the next OPCODE
      }
       
      else if (curr_string == opcodes[1]){
	//ASSERT: NAND needs 3 operands x, y, and z s.t. x = ~(ynz)
	MyString* MyOperand1 = tokenList.getNth(tokenListindex+1);
	char* operand1 = MyOperand1->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	MyString* MyOperand2 = tokenList.getNth(tokenListindex+2);
	char* operand2 = MyOperand2->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	MyString* MyOperand3 = tokenList.getNth(tokenListindex+3);
	char* operand3 = MyOperand3->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	if ((!checkInRegisters(operand1)) || (!checkInRegisters(operand2)) ||
	    (!checkInRegisters(operand3))){
	  //ASSERT: either x, y, or z is an invalid operand
	  syntaxValid = false;
	}
	//ASSERT: We have checked a line of the assemble code
	tokenListindex += 4;
	//The reason the program is adding that magic number to tokenListindex
	//is so next time around the while loop, when the token is pulled, we
	//pull the next OPCODE
      }
       
      else if (curr_string == opcodes[2]){
	//ASSERT: ADDI needs 3 operands x, y, and <integer>
	//s.t. x = y + <integer>
	MyString* MyOperand1 = tokenList.getNth(tokenListindex+1);
	char* operand1 = MyOperand1->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	MyString* MyOperand2 = tokenList.getNth(tokenListindex+2);
	char* operand2 = MyOperand2->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	MyString* MyOperand3 = tokenList.getNth(tokenListindex+3);
	char* operand3 = MyOperand3->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	bool isINT = false;
	int intindex = 0;
	while (!(operand3[intindex] == EOS)){
	  isINT = isHexDigit(operand3[intindex]);
	  intindex++;
	}
       
	if ((!checkInRegisters(operand1)) || (!checkInRegisters(operand2)) ||
	    (!isINT)){
	  //ASSERT: either x, y, or z is an invalid operand
	  syntaxValid = false;
	}
	//ASSERT: We have checked a line of the assemble code
	tokenListindex += 4;
	//The reason the program is adding that magic number to tokenListindex
	//is so next time around the while loop, when the token is pulled, we
	//pull the next OPCODE
      }
       
      else if (curr_string == opcodes[3]){
	//ASSERT: LW needs 3 operands x, <integer>, and y
	//s.t. x <= Contents at (<integer> + y) address
	MyString* MyOperand1 = tokenList.getNth(tokenListindex+1);
	char* operand1 = MyOperand1->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	MyString* MyOperand2 = tokenList.getNth(tokenListindex+2);
	char* operand2 = MyOperand2->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	MyString* MyOperand3 = tokenList.getNth(tokenListindex+3);
	char* operand3 = MyOperand3->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	bool isINT = false;
	int intindex = 0;
	while (!(operand2[intindex] == EOS)){
	  isINT = isHexDigit(operand2[intindex]);
	  intindex++;
	}
	  
	if ((!checkInRegisters(operand1)) || (!checkInRegisters(operand2)) ||
	    (!isINT)){
	  //ASSERT: either x, y, or z is an invalid operand
	  syntaxValid = false;
	}
	//ASSERT: We have checked a line of the assemble code
	tokenListindex += 4;
	//The reason the program is adding that magic number to tokenListindex
	//is so next time around the while loop, when the token is pulled, we
	//pull the next OPCODE
      }
       
      else if (curr_string == opcodes[4]){
	//ASSERT: SW needs 3 operands x, <integer>, and y
	//s.t. Contents from x => (<integer> + y) address
	MyString* MyOperand1 = tokenList.getNth(tokenListindex+1);
	char* operand1 = MyOperand1->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	MyString* MyOperand2 = tokenList.getNth(tokenListindex+2);
	char* operand2 = MyOperand2->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	MyString* MyOperand3 = tokenList.getNth(tokenListindex+3);
	char* operand3 = MyOperand3->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	bool isINT = false;
	int intindex = 0;
	while (!(operand2[intindex] == EOS)){
	  isINT = isHexDigit(operand2[intindex]);
	  intindex++;
	}
	  
	if ((!checkInRegisters(operand1)) || (!checkInRegisters(operand2)) ||
	    (!isINT)){
	  //ASSERT: either x, y, or z is an invalid operand
	  syntaxValid = false;
	}
	//ASSERT: We have checked a line of the assemble code
	tokenListindex += 4;
	//The reason the program is adding that magic number to tokenListindex
	//is so next time around the while loop, when the token is pulled, we
	//pull the next OPCODE
      }
       
      else if (curr_string == opcodes[5]){
	//ASSERT: BEQ needs 3 operands x, y, and z
	//s.t. If (x == y) set PC to <label> address
	//COLLORARY: No need to check z for the syntax check has checked
	//the labels already
	MyString* MyOperand1 = tokenList.getNth(tokenListindex+1);
	char* operand1 = MyOperand1->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	MyString* MyOperand2 = tokenList.getNth(tokenListindex+2);
	char* operand2 = MyOperand2->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	if ((!checkInRegisters(operand1)) || (!checkInRegisters(operand2))){
	  //ASSERT: either x or y is an invalid operand
	  syntaxValid = false;
	}
	//ASSERT: We have checked a line of the assemble code
	tokenListindex += 3;
	//The reason the program is adding that magic number to tokenListindex
	//is so next time around the while loop, when the token is pulled, we
	//pull the next OPCODE
      }
       
      else if (curr_string == opcodes[6]){
	//ASSERT: JALR needs 2 operands x and y
	//s.t. the simulator copies PC to y. Then, copy x to PC
	MyString* MyOperand1 = tokenList.getNth(tokenListindex+1);
	char* operand1 = MyOperand1->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	MyString* MyOperand2 = tokenList.getNth(tokenListindex+2);
	char* operand2 = MyOperand2->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	if ((!checkInRegisters(operand1)) ||
	    (!checkInRegisters(operand2))){
	  //ASSERT: either x, y is an invalid operand
	  syntaxValid = false;
	}
	//ASSERT: We have checked a line of the assemble code
	tokenListindex += 3;
	//The reason the program is adding that magic number to tokenListindex
	//is so next time around the while loop, when the token is pulled, we
	//pull the next OPCODE
      }
       
      else if (curr_string == opcodes[9]){
	//ASSERT: IN needs 1 operand x
	//s.t. The simulator gets a number from user and stores it in x
	MyString* MyOperand1 = tokenList.getNth(tokenListindex+1);
	char* operand1 = MyOperand1->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	if (!checkInRegisters(operand1)){
	  //ASSERT: x is an invalid operand
	  syntaxValid = false;
	}
	//ASSERT: We have checked a line of the assemble code
	tokenListindex += 2;
	//The reason the program is adding that magic number to tokenListindex
	//is so next time around the while loop, when the token is pulled, we
	//pull the next OPCODE
      }
	   
      else if (curr_string == opcodes[10]){
	//ASSERT: OUT needs 1 operand x
	//s.t. The simulator outputs x in hex and dec
	MyString* MyOperand1 = tokenList.getNth(tokenListindex+1);
	char* operand1 = MyOperand1->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	if (!checkInRegisters(operand1)){
	  //ASSERT: x is an invalid operand
	  syntaxValid = false;
	}
	//ASSERT: We have checked a line of the assemble code
	tokenListindex += 2;
	//The reason the program is adding that magic number to tokenListindex
	//is so next time around the while loop, when the token is pulled, we
	//pull the next OPCODE
      }
	    
      else if (curr_string == opcodes[12]){
	//ASSERT: LA needs 1 operand x
	//s.t. The simulator stores the address of label in x
	MyString* MyOperand1 = tokenList.getNth(tokenListindex+1);
	char* operand1 = MyOperand1->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	if (!checkInRegisters(operand1)){
	  //ASSERT: x is an invalid operand
	  syntaxValid = false;
	}
	//ASSERT: We have checked a line of the assemble code
	tokenListindex += 2;
	//The reason the program is adding that magic number to tokenListindex
	//is so next time around the while loop, when the token is pulled, we
	//pull the next OPCODE
      }
	  
      else if (curr_string == opcodes[13]){
	//ASSERT: BGT needs 3 operands x, y, and z
	//s.t. If (x > y) set PC to <label> address
	//COLLORARY: No need to check z for the syntax check has checked
	//the labels already
	MyString* MyOperand1 = tokenList.getNth(tokenListindex+1);
	char* operand1 = MyOperand1->getstring();
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	MyString* MyOperand2 = tokenList.getNth(tokenListindex+2);
	//That magic number represents how far away the operand should be from
	//the OPCODE
	//ASSERT: if this is a correct line: got operand <magic number> away
	//from OPCODE
	char* operand2 = MyOperand2->getstring();
	if ((!checkInRegisters(operand1)) ||
	    (!checkInRegisters(operand2))){
	  //ASSERT: either x, y is an invalid operand
	  syntaxValid = false;
	}
	//ASSERT: We have checked a line of the assemble code
	tokenListindex += 3;
	//The reason the program is adding that magic number to tokenListindex
	//is so next time around the while loop, when the token is pulled, we
	//pull the next OPCODE
      }
    }
    else if(checkInRegisters(curr_string)){
      //ASSERT: register is in the spot where the OPCODE should be
      syntaxValid = false;
    }
    else if(curr_string[0] == semicolon){
      //DONT CHANGE SYNTAXVALID
    }
    else{
      //curr_token is neither an OPCODE, REGISTER, NOR SEMICOLON
      syntaxValid = false;
    }
  curr_token = tokenList.getNth(tokenListindex);
  curr_string = curr_token->getstring();
  }
  //We have checked all tokens
}
//PRE: inFile must be a non-NULL file containing assembly
//     code. symbolTable should be a NULL symbol_table object.
//     tokenList must be an empty LinkedList of
//     MyString objects that will represents all the relevant data in the
//     infile. syntax valid must be a boolean that starts out
//     false that represents whether or not the given infile has any
//     syntactical errors.
//POST: syntaxValid is true iff there are no syntactical errors
//      in the given infile
//      symbolTable is filled with the various symbols found in
//      the infile.
//      tokenList contains all the relevant data from the infile
void beginpass1(istream & inFile, symbol_table & symbolTable,
		LinkedList<MyString> & tokenList, bool & syntaxValid){
  tokenizeFile(inFile, tokenList);
  //ASSERT: tokenList contains all the relevant data from the inFile
  populateSymbolTable(tokenList, symbolTable);
  //ASSERT: symbolTable is filled with the various relevant daa from
  //the inFile
  checkSymbolTable(symbolTable, syntaxValid);
  //ASSERT: syntaxValid is true iff symbolTable has no syntactical
  //errors.
  if (syntaxValid == true){
    checkOpCodesnumoperands(tokenList, syntaxValid);
  //ASSERT: syntaxValid is true iff all the op codes in the token list
  //have the correct number of operands and both opcodes and operands
  //are actual opcodes and operands
  }
}

