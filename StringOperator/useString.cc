#include "MyString.h"
using namespace std;
int main () {
    MyString oneString;
    MyString twoString;
    MyString fixedString ("Hello ");
    cin >> oneString;
    // oneString contains all the characters on the first line of IS
    // until the end of line character.
    cout << "oneString: " << oneString << endl;
    cin >> twoString;
    // twoString contains all the characters on the second line of IS
    // until the end of line character.
    cout << "twoString: " << twoString << endl;

    MyString threeString;
    threeString = oneString + twoString;
    // threeString is the string obtained by concatenating the
    // characters of oneString  and the characters of twoString.

    cout << "Three String = " << threeString << endl;
    if (oneString == fixedString) {
      cout << "oneString equal to fixedString = " << oneString << endl;
    }
    else {
      MyString fourString;
      if (oneString < twoString) {
	fourString = oneString + 'A';
	// fourString contains the characters of oneString followed by a
	// capital A.
	cout << "Four String = " << fourString << endl;
      }
      else {
	oneString.toUpperCase();
	// All the characters in oneString are converted to uppercase.
	cout << "Upper case oneString = " << oneString << endl;
	
	oneString = oneString + oneString;
	fourString = oneString + 'B';
	cout<< "FourString is: " << fourString << endl;
	// fourString contains the characters of oneString twice
	// followed by a capital B.
	fourString.removeFirst (4);
	// If fourString = s before the statement, then now
	// fourString contains all the characters of s except the
	// first 4. If s has less than 5 characters, then fourString
	// is now the empty string (no characters).
	cout << "fourString with uppercase oneString twice and B, except first four characters = ";
	cout << fourString << " with " << fourString.length()
	     << " characters " << endl;
      }
    }
    return (0);
}
