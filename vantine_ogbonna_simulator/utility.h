#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED

#include <fstream>
using namespace std;

// PRE: file refers to valid file
// POST: returns the number of lines in the given file
int countLines(ifstream & file);

// PRE: file refers to valid file, whose contents are
//        chars representing bytes
// POST: returns the number of 32 bit words represented
//         by the chars in file
int countBinLines(ifstream & file);

// PRE: index in range (0, 7)
// POST: index is big-endian
//       returns byte located at index
int getByte(unsigned int word, int index);



#endif
