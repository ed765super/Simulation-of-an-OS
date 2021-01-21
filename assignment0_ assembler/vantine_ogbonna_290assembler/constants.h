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
#define CHAR0 '0'
#define CHAR9 '9'
#define CHARHEXA 'A'
#define CHARHEXF 'F'
#define DECIMAL_BASE 10
#define NEXTWORD 4

#define MAX_REGISTERS 16
#define MAX_OPCODES 14

#define VAR "VAR"
#define semicolon ';'
const char* const opcodes[] = {"ADD", "NAND", "ADDI", "LW", "SW", "BEQ", "JALR","HALT", "", "IN", "OUT", "", "LA", "BGT"};

const char* const registers[] = {"$zero", "$at", "$v0", "$a0", "$a1", "$a2", "$t0", "$t1","$t2", "$s0", "$s1", "$s2", "$k0", "$sp", "$fp", "$ra"};
  

#endif
