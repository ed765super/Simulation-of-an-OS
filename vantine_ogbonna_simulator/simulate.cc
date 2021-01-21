#include <iostream>
#include "start_shell.h"
#include "stringFunctions.h"
#include "Simulator.h"

using namespace std; 

int main(int argc, char* argv[]) {
  // check arguments
  bool valid = true; 
  if (argc != 2){
    // ASSERT: there is an invalid number of arguments
    valid = false;
  }
  else {
    // verify all chars in argv[1] are in the range (0, 9)
    int index = 0;
    char temp = argv[1][index];
    while (temp != '\0'){
      if(!isDigit(temp)){
	valid = false;
      }
      index ++;
      temp = argv[1][index];
    }
  }
  if (valid) {
    // ASSERT: user has provided valid arguments
    int const requestedMemory = strToInt(argv[1]);
    Simulator sim = Simulator(requestedMemory);
    start_shell(sim);
  } else{
    cout << "User has given invalid arguments" << endl;
  }
}
