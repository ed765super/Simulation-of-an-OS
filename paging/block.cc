#include "block.h"
using namespace std;
//CONSTRUCTOR
//PRE:
//POST: Creates a Block object
Block::Block(){
  start = 0;
  end = 0;
}
//ACCESSORS
//PRE:
//POST: returns the amount of space this block takes up
int Block::getSize()const{
  int size = end - start;
  return size;
}
  
//PRE: This object must be declared and defined
//POST: RV = the start data object
int Block::getStart()const{
  return(start);
}

//PRE: This object must be declared and defined
//POST: RV = the end data object
int Block::getEnd()const{
  return(end);
}

//MODIFIERS
//PRE: This object must be declared and defined
//POST: Modifies the Start such that the start equals pStart
void Block::setStart(int pStart){
  start = pStart;
}

//PRE: This object must be declared and defined
//POST: Modifies the End such that the end equals pStart
void Block::setEnd(int pEnd){
  end = pEnd;
}

//OPERATOR
//PRE: pBlock must be a defined Block object
//POST: Performs a deep copy of pBlock on this object
Block Block::operator=(const Block pBlock){
  setStart(pBlock.getStart());
  setEnd(pBlock.getEnd());
  return (*this);
}

//PRE: pBlock must be a defined Block object
//POST: RV = true if pBlock is equivalent to this object
bool Block::operator==(const Block pBlock){
  bool valid = false; //will hold whether or not pBlock is equal to
                      //this object
  if ((start == pBlock.getStart()) &&
      (end == pBlock.getEnd())){
    valid = true;
  }
  return valid;
}

//IOSTREAM
//PRE: This object must be declared and defined
//POST: OS contains start and end in the form "<start> - <end>"
ostream & operator << (ostream & stream, Block & myBlock){
  stream << "start: " << myBlock.getStart() << "end: " << myBlock.getEnd();
  return (stream);
}
