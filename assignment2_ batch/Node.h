/*************************************************
Schuyler van Tine
Node Class
**************************************************/

#ifndef NODE_INCLUDED
#define NODE_INCLUDED
#include <iostream>
using namespace std;

// CI: data may point to NULL or object of type T
//     prev/next may point to NULL or valid Node object
template <class T>
class Node {
 private:
  T * data; // points to the object of type T of this Node
  Node * prev; // points to the previous node (if any)
  Node * next; // points to the next node (if any)
  
 public:
  // ======================================== 
  // constructor functions
  // ======================================== 
  
  // PRE:
  // POST: No args given, so member data set to NULL
  Node() {
    data = NULL;
    prev = NULL;
    next = NULL;
  }

  // PRE: pData is defined
  // POST: data points to pData
  //       no nodes given, so prev, next set to NULL
  Node(T * pData) {
    data = pData;
    prev = NULL;
    next = NULL;
  }

  // PRE: pData defined, pPrev/pNext point to valid Nodes
  // POST: args set to respective member data
  Node(T * pData, Node * pPrev, Node * pNext){
    data = pData;
    prev = pPrev;
    next = pNext; 
  }

  // ======================================== 
  // accessor functions
  // ======================================== 

  // PRE:
  // POST: RV is data 
  T * getData () const {
    return (data);
  }

  // PRE:
  // POST: RV is prev
  Node * getPrev () const {
    return (prev);
  }

  // PRE:
  // POST: RV is next
  Node * getNext () const {
    return (next);
  }

  // ========================================
  // modifier functions
  // ======================================== 

  // PRE: pData is a valid T pointer
  // POST: data points to target of pData
  void setData(T * pData){
    data = pData;
  }

  // PRE: pPrev is a valid Node pointer
  // POST: prev points to target of pPrev
  void setPrev(Node * pPrev){
    prev = pPrev;
  }

  // PRE: pNext is a valid Node pointer
  // POST: next points to target of pNext
  void setNext(Node * pNext){
    next = pNext;
  }

  // ======================================== 
  //     Input/Output
  // ======================================== 


  // PRE: N is defined
  // POST: OS contains N's Data
  friend ostream & operator << (ostream & str, const Node<T> * N){
    str << *N->getData();
    return (str); 
  }

  // ======================================== 
  // destructor
  // ======================================== 
  
  // PRE: This object is defined. 
  // POST: the next node is deleted if it exists
  //       and this node is deleted
  ~Node(){
    if (next != NULL) {
      // ASSERT: this node is connected to another node
      // must delete the next node before this node can be deleted
      delete next; 
    }
    data = NULL;
    delete data;
  }

  
};

#endif
