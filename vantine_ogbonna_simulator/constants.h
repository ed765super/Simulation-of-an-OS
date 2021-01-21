#ifndef INCLUDED_CONSTANTS
#define INCLUDED_CONSTANTS

#define EOS '\0'
#define LOWERA 'a'
#define LOWERZ 'z'
#define aSpace ' '
#define newLine '\n'
#define leftparen '('
#define rightparen ')'
#define lowerTOupper 32 //The amount of integers between any letter
			//from upper to lower case
#define MAX_USER_INPUT 20 //tHE MAX memory the user could ask for we are
                          //assuming to be 20 because no valid command could
                          //exceed this
#define semicolon ';'
#define CHAR0 '0'
#define CHAR9 '9'
#define CHARHEXA 'A'
#define CHARHEXF 'F'

#define DEFAULT_STACK 64
#define DECIMAL_BASE 10
#define NEXTWORD 4

#define LOAD "load"
#define MEM "mem"
#define CPU "cpu"
#define STEP "step"
#define RUN "run"
#define EXIT "exit"

#define MAX_REGISTERS 16
#define MAX_OPCODES 14
#define BYTE 4
#define VAR "VAR"
#define WORDSIZE 12 // "0x" + 8 bytes + '\n'  + EOS 



static const char* const opcodes[] = {"ADD", "NAND", "ADDI", "LW", "SW", "BEQ", "JALR","HALT", "", "IN", "OUT", "", "LA", "BGT"};

static const char* registers[] = {"$zero", "$at", "$v0", "$a0", "$a1", "$a2", "$t0", "$t1","$t2", "$s0", "$s1", "$s2", "$k0", "$sp", "$fp", "$ra"};
  

#endif
