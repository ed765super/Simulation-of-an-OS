#ifndef INCLUDED_BLOCK
#define INCLUDED_BLOCK
#include <iostream>
using namespace std;
class Block{
 //CI: start must be an integer that represents the start of this block,
 //    end must represent an integer that represents the end of this block.
 private:
  int start;
  int end;
 public:
  //CONSTRUCTOR
  //PRE:
  //POST: Creates a block object
  Block();

  //ACCESSORS
  //PRE:
  //POST: returns the amount of space this block takes up
  int getSize()const;
  
  //PRE: This object must be declared and defined
  //POST: RV = the start data object
  int getStart()const;

  //PRE: This object must be declared and defined
  //POST: RV = the end data object
  int getEnd()const;

  //MODIFIERS
  //PRE: This object must be declared and defined
  //POST: Modifies the Start such that the start equals pStart
  void setStart(int pStart);

  //PRE: This object must be declared and defined
  //POST: Modifies the End such that the end equals pStart
  void setEnd(int pEnd);

  //OPERATOR
  //PRE: pBlock must be a defined Block object
  //POST: Performs a deep copy of pBlock on this object
  Block operator=(const Block pBlock);
  
  //PRE: pBlock must be a defined Block object
  //POST: RV = true if pBlock is equivalent to this object
  bool operator==(const Block pBlock);
  
  //IOSTREAM
  //PRE: This object must be declared and defined
  //POST: OS contains start and end in the form "start: <start> - end: <end>"
  friend ostream & operator << (ostream & stream, Block & myBlock);
};
#endif
