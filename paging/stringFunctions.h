//Author: Nicholas Ogbonna
#ifndef INCLUDED_stringFunctions
#define INCLUDED_stringFunctions
// PRE: ch is defined.
// POST: RV is true iff ch is a digit ('0'..'9')
bool isHexDigit (char ch);

// PRE: token is a string of digits end with an end of string character.
// POST: RV is the decimal value of the string.
int strToInt (const char token[]);

// PRE: ch is defined.
// POST: RV is true iff ch is a digit ('0'..'9')
bool isDigit (char ch);

// PRE: string1 and string2 are defined and have the end of string
// character  at the end.
// POST: RV is true iff string1 has the same characters as string2.
bool isEqualString (const char string1[], const char string2[]);
#endif
