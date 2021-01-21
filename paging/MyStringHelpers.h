//Author: Nicholas Ogbonna
#ifndef INCLUDED_HELPERS
#define INCLUDED_HELPERS
#include "constants.h"
// PRE: ch is defined.
// POST: RV is true iff ch is a lowercase letter ('a'..'z')
bool islowercase (char ch);

// PRE: Array1 and Array2 must be 2 arrays of characters. Array2 must
// be greater than array1. array1size is an integer that represents array1's
//size.
// POST: Every element in array1 is deep copied into Array2
void copyArray (const char* Array1, int array1size,  char* Array2);
#endif
