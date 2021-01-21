//Author: Nicholas Ogbonna
#include "start_shell.h"
#include <iostream>
using namespace std;

int main(){
  //TEST CIN
  char curr_ch;
  MyString userCommand;
  bool done = false; //represents when the main while loop is done
  cout << ">";
  curr_ch = cin.get();
  while(curr_ch != newLine){
    userCommand.addchar(curr_ch);
    curr_ch = cin.get();
  }
  cout << "user typed: " << userCommand << endl;
  //The User's command has been shown on the terminal
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //TEST LINKEDLIST
  char* curr_command = userCommand.getstring();
  LinkedList<MyString> tokenList = tokenize(curr_command);
  cout << "tokenList: " << tokenList << endl;
  //Note: because we initiallized the max number of stuff the user
  //can type to 20 there will be a ton of garbage values after the
  //initial stuff the user typed. But that doesnt matter because in my
  //other functions I care about the first, second(sometimes), and
  //third(rare) items in the LinkedList
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  //TEST checkToken
  //Espect It will return true if everything about tokenList is valid
  //for commands
  bool isValid = checkToken(tokenList, 10);
  if(isValid){
    cout << "valid" << endl;
  }
  else{
    cout << "invalid" << endl;
  }
  /*~~~~~~~~~~~~~~~~~~evaluate testing below~~~~~~~~~~~~~~~~~~~~~~~*/
  MyString* command = tokenList.getHead(); 
  if (isEqualString(command->getstring(), LOAD)) {
    cout << "it's in LOAD" << endl;
  }
  else if (isEqualString(command->getstring(), MEM)) {
    cout << "it's in MEM" << endl;
  }
  else if (isEqualString(command->getstring(), CPU)) {
    cout << "it's in CPU" << endl;
  }
  else if (isEqualString(command->getstring(), STEP)) {
    cout << "it's in STEP" << endl;
  }
  else if (isEqualString(command->getstring(), RUN)) {
    cout << "it's in RUN" << endl;
  }
  
  int cpuRegisters[MAX_REGISTERS];
  for (int index = 0; index < MAX_REGISTERS; index++){
    cpuRegisters[index] = index;
  }
  //cpuRegisters = a list of integers from 0 to 15
  int numRegPrinted = 1;
  for (int index = 0; index < MAX_REGISTERS; index++){
    //cout << registerStatusList[index] << ", ";
    cout << cpuRegisters[index] << ", ";
    int DIVISIBLEBYFOUR = 4;
    if (numRegPrinted%DIVISIBLEBYFOUR == 0){
      //ASSERT: there are 4 registers on the current line of the terminal
      cout << endl;
    }
    numRegPrinted++;
  }
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  return (0);
}
