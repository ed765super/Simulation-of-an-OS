#include "start_shell.h"
#include "constants.h"
#include "Simulator.h"
#include "OS.h"
#include "PCB.h"
using namespace std;

int main(){
  cout << "TESTING CING IN THE CONFIG FILE" << endl;
  ifstream inFile (".lc_config");
  int requestedMemory;
  int stackMemory;
  int fitType;
  char curr_ch = inFile.get();
  while (!inFile.eof()){
    MyString curr_word;
    while(curr_ch != aSpace){
      curr_word.addchar(curr_ch);
      curr_ch = inFile.get();
    }
    //ASSERT: curr_ch = aSpace.
    //curr_word = a word from the inFile
    char* wordString = curr_word.getstring();
    cout << wordString << endl;
    if (isEqualString(wordString, MEMORY)){
      curr_ch = inFile.get(); //ch is now the first integer
      MyString wordInt; //will hold the integer that's next to memory
      while(isDigit(curr_ch)){
	wordInt.addchar(curr_ch);
	curr_ch = inFile.get();
      }
      //ASSERT: curr_ch is no longer an integer
      char* wordIntString = wordInt.getstring();
      requestedMemory = strToInt(wordIntString);
      //memory is now the integer after the word memory in the inFile
    }
    else if (isEqualString(wordString, STACKMEMORY)){
      curr_ch = inFile.get(); //ch is now the first integer
      MyString wordInt; //will hold the integer that's next to memory
      while(isDigit(curr_ch)){
	wordInt.addchar(curr_ch);
	curr_ch = inFile.get();
      }
      //ASSERT: curr_ch is no longer an integer
      char* wordIntString = wordInt.getstring();
      stackMemory = strToInt(wordIntString);
      //stackMemory is now the integer after the word stackMemory in
      //the inFile
    }
    else if (isEqualString(wordString, FITTYPE)){
      curr_ch = inFile.get();//Reads past space
      MyString wordInt; //will hold the integer that's next to memory
      while(isDigit(curr_ch)){
	wordInt.addchar(curr_ch);
	curr_ch = inFile.get();
      }
      //ASSERT: curr_ch is no longer an integer
      char* wordIntString = wordInt.getstring();
      fitType = strToInt(wordIntString);
      //fitType is now the integer after the word stackMemory in
      //the inFile
    }
    curr_ch = inFile.get();
  }
  cout << requestedMemory << endl << stackMemory << endl << fitType << endl;
  cout << "END TESTING CIN CONFIG FILE" << endl;
  cout << "INITIALIZE TESTING THE TOKENIZE" << endl;
  char cmdCH;
  MyString userCommand("Memory 4 8");
  char* userinput = userCommand.getstring();
  LinkedList<MyString> userCMD;//will hold the list of tokens from the
			       //user's input
  int user_index = 0;
  while (userinput[user_index] != EOS){
    MyString token; //Will hold a word from the user's input
    while ((userinput[user_index] != aSpace) &&
	   (userinput[user_index] != EOS)){
      //we have not read a word
      char ch = userinput[user_index];//will hold a letter from the userinput
      token.addchar(ch);
      user_index++;
    }
    //ASSERT: we have a full word to put in the userCMD
    //Collorary: user index is either a space or a newline
    userCMD.append(token);
    //ASSERT: token has been added to userCMD
    user_index++;
  }
  cout << "userCMD: " << userCMD << endl;
  cout << "END TESTING THE TOKENIZE" << endl;
  
  return (0);
}
