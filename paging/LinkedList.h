/***************************************************
Schuyler van Tine
Linked List Class
****************************************************/

#ifndef INCLUDED_LINKEDLIST
#define INCLUDED_LINKEDLIST

#include <iostream>
#include "Node.h"
using namespace std; 

// CI: head and tail may point to NULL or valid Node object
//     numItems must be equal to the amount of Nodes this object holds
//     if numItems > 0, then head and tail point to valid node object
template <class T>
class LinkedList {
 private:
  Node<T> * head; // points to first Node in the list
  Node<T> * tail; // points to last Node in the list
  int numItems;  // represents number of elements held in list
  
 public:
  // ======================================== 
  // constructor functions
  // ========================================

  // PRE:
  // POST: No args given, so member data set to NULL
  LinkedList() {
    head = NULL;
    tail = NULL;
    numItems = 0; 
  }

  
  // copy constructor
  // PRE: L is defined.
  // POST: This object is defined and is a deep copy of L.
  LinkedList<T>(const LinkedList<T> & L) {
    numItems = 0;
    for (int index = 0; index < L.getSize(); index++){
      T* TObject = L.getNth(index);
      append(*TObject);
    }
  }

  //assignment operator
  // PRE: L is defined.
  // POST: This object is defined and is a deep copy of L.
  LinkedList<T> & operator= (const LinkedList<T> & L) {
    if (numItems != 0){
      delete head;
    }
    numItems = 0;
    //ASSERT: L is not empty
    for (int index = 0; index < L.getSize(); index++){
      T* TObject = L.getNth(index);
      append(*TObject);
    }
  }
    

  // ======================================== 
  // destructor
  // ======================================== 
  
  // PRE: This object is defined.
  // POST: This object has no elements. 
  ~LinkedList() {
    if (numItems != 0){
      delete head;
    }
    numItems = 0;
  }
  
  // ======================================== 
  //       accessor functions
  // ======================================== 

  // PRE: This object is defined.
  // POST: RV is numItems
  int getSize () const {
    return (numItems); 
  }

  // PRE: This object is defined.
  // POST: RV is the T* pointer to the data in head iff
  //       head does not equal null else RV is null 
  T* getHead() const {
    T* data = NULL;
    if (head != NULL) {
      data = head->getData();
    }
    return (data);
  }

  // PRE: This object is defined.
  // POST: RV is the T* pointer to the data in tail iff
  //       tail does not equal null else RV is null 
  T* getTail() const {
    T* data = NULL;
    if (tail != NULL) {
      data = tail->getData();
    }
    return (data);
  }

  // PRE: N is less than numItems
  // POST: RV is the node at index N 
  T* getNth (int N) const {
    int currentIndex = 0;
    Node<T> * currNode = head;
    // ASSERT: currNode points to node at index 0 
    while (currentIndex < N) {
      currNode = currNode->getNext();
      currentIndex ++;
      // ASSERT: currNode points to node at
      //         index currentIndex
    }
    // ASSERT: currentIndex = N
    T * data = currNode->getData();
    
    return(data);

  }

  // ======================================== 
  // modifier functions
  // ======================================== 

  // PRE: item is defined
  // POST: item placed in Node at index in list equal to numItems
  //       numItems incremented
  void append(T item) {
    T* itemPointer = new T;
    *itemPointer = item;
    Node<T> * newNode = new Node<T>(itemPointer); 
    if (numItems == 0) {
      // ASSERT: No elements in list
      head = newNode;
      tail = newNode; 
    } else {
      // ASSERT: At least one element in list
      tail->setNext(newNode);
      newNode->setPrev(tail);
      tail = newNode; 
    }
    numItems ++;
  }
  // PRE: item a pointer to a defined item
  // POST: item placed in Node at index in list equal to numItems
  //       numItems incremented
  void append(T* item) {
    T* itemPointer = new T;
    *itemPointer = item;
    Node<T> * newNode = new Node<T>(itemPointer); 
    if (numItems == 0) {
      // ASSERT: No elements in list
      head = newNode;
      tail = newNode; 
    } else {
      // ASSERT: At least one element in list
      tail->setNext(newNode);
      newNode->setPrev(tail);
      tail = newNode; 
    }
    numItems ++;
  }

  // PRE: item is defined
  // POST: item placed in Node at index 0
  //       numItems incremented
  void prepend(T item) {
    T* itemPointer = new T;
    *itemPointer = item; 
    Node<T> * newNode = new Node<T>(itemPointer); 
    if (numItems == 0) {
      // ASSERT: No elements in list
      head = newNode;
      tail = newNode; 
    } else {
      // ASSERT: At least one element in list
      head->setPrev(newNode);
      newNode->setNext(head);
      head = newNode; 
    }
    numItems ++; 
  }

  // PRE: 
  // POST: If there exists a node whose data is equal to existingItem,
  //         say at index I, then a new node will be created, say n,
  //         and the node at I-1, if any, will have its "next" pointer
  //         updated to n. n's prev will be set to node at I-1, if any,
  //         and n's next will be set to node at I.
  //         numItems incremented
  //       else do nothing
  void insertBefore(T existingItem, T newItem) {
    Node<T>* currNode = head;
    bool looking = true; // true iff we have not found node with data
			 // equal to existingItem
    while (currNode != NULL && looking) {
      if (*currNode->getData() == existingItem) {
	looking = false;
      } else {
	// ASSERT: currNode's data does not equal existingItem
	currNode = currNode->getNext();
      }
    }
    if (looking == false) {
      // ASSERT: currNode's data is equal to existingItem

      if (currNode->getPrev() == NULL) {
	// ASSERT: currNode is the head of the list
	prepend(newItem); // this call will insert newItem
			  // appropriately and increment numItems
      } else {
	// ASSERT: currNode is in range (0, numItems - 2)
	T* itemPointer = new T; // create pointer for newItem
	*itemPointer = newItem; // point itemPointer to correct target
	Node<T> * newNode = new Node<T>(itemPointer); // create node to
	                                              // hold newItem
	currNode->getPrev()->setNext(newNode);
	newNode->setPrev(currNode->getPrev());
	newNode->setNext(currNode);
	currNode->setPrev(newNode);
	numItems ++; 
      }
      // ASSERT: insert completed

    }
  }

  // PRE: 
  // POST: If there exists a node whose data is equal to existingItem,
  //         say at index I, then a new node will be created, say n,
  //         and the node at I+1, if any, will have its "prev" pointer
  //         updated to n. n's next will be set to node at I+1, if any,
  //         and n's prev will be set to node at I.
  //         numItems incremented
  //       else do nothing
  void insertAfter(T existingItem, T newItem) {
    Node<T>* currNode = head;
    bool looking = true; // true iff we have not found node with data
			 // equal to existingItem
    while (currNode != NULL && looking) {
      if (*currNode->getData() == existingItem) {
	looking = false;
      } else {
	// ASSERT: currNode's data does not equal existingItem
	currNode = currNode->getNext();
      }
    }
    if (looking == false) {
      // ASSERT: currNode's data is equal to existingItem
      if (currNode->getNext() == NULL) {
	// ASSERT: currNode is the tail of the list
	append(newItem); // this call will insert newItem
			 // appropriately and increment numItems
      } else {
	// ASSERT: currNode is in range (0, numItems - 2)
	T* itemPointer = new T; // create pointer for newItem
	*itemPointer = newItem; // point itemPointer to correct target
	Node<T> * newNode = new Node<T>(itemPointer); // create node to
	                                              // hold newItem
	currNode->getNext()->setPrev(newNode);
	newNode->setNext(currNode->getNext());
	newNode->setPrev(currNode);
	currNode->setNext(newNode);
	numItems ++;
      }
      // ASSERT: insert completed
    }
  }

  // PRE: index < numItems
  // POST: finds node located at value of index,
  //       data pointer of that node points to update_value
  void update(int index, T updateValue){
    T* itemPointer = new T;
    *itemPointer = updateValue; 
    int currIndex = 0;
    Node<T>* currNode = head; 
    while (currIndex < index) {
      currNode = currNode->getNext(); // select next node in list
      currIndex ++; // increment currIndex because to
                    // reflect current position in list
    }
    // currNode is node located at specified index
    currNode->setData(itemPointer); 
  }
  
  // PRE: 
  // POST: if index <= numItems then
  //         if index < numItems place item at index before
  //           node currently at index,
  //         else if index = numItems, item placed at tail
  //         numItems incremented
  //       else do nothing
  void insert(int index, T item){
    if (index <= numItems) {
      // ASSERT: index is a valid location in this list
      int currentIndex = 0;
      Node<T>* currNode = head; 
      while (currentIndex < index) {
	currNode = currNode->getNext();
	currentIndex ++; 
      }
      if (currentIndex == 0){
	// ASSERT: insert requested at head
	prepend(item); // this call will insert newItem appropriately
               	       //and increment numItems
      } else {
	if(currentIndex == numItems) {
	  // ASSERT: insert requested after tail
	  append(item); // this call will insert newItem appropriately
			// and increment numItems
	} else{
	  // ASSERT: insert requested in index range (1, numItems - 1)
	  T* itemPointer = new T; // create pointer for newItem
	  *itemPointer = item; // point itemPointer to correct target
	  Node<T> * newNode = new Node<T>(itemPointer);
	  currNode->getPrev()->setNext(newNode); // currNode's prev
						 // set to newNode 
	  newNode->setPrev(currNode->getPrev()); // newNode's prev set
						 // to currNode's prev
	  newNode->setNext(currNode); // newNode's next set to currNode
	  currNode->setPrev(newNode); // currNode's prev set to newNode
	  numItems ++; 
	}
      }
      // ASSERT: insert completed
    }
  }
	    

  // PRE: N < numItems
  // POST: Node at index N is removed from linked list
  void deleteNth(int N) {
    int index = 0;
    Node<T>* currNode = head; 
    while (index < N) {
      currNode = currNode->getNext();
      index ++;
    }
    // ASSERT: currNode is the Nth element in this list
    Node<T>* prev = currNode->getPrev();
    Node<T>* next = currNode->getNext();
    currNode->setNext(NULL); // node destructor is recursive, so next
                             // must be set to null
    if (currNode == head){
      // Nth node is head, so new head is N+1
      head = next;
    }
    if (currNode == tail){
      // Nth node is tail, so new tail is N-1
      tail = prev;
    }
    if (prev != NULL) {
      // ASSERT: There is a node before the Nth node in list
      prev->setNext(next);
    }
    if (next != NULL) {
      // ASSERT: There is a node after the Nth node in list
      next->setPrev(prev);
    }
    delete(currNode);
    numItems --;
  }

  // ======================================== 
  //     Input/Output
  // ======================================== 

  // PRE: L is defined
  // POST: OS contains L's Nodes 
  friend ostream & operator<< (ostream & str, const LinkedList<T> & L){
    str << "[";
    Node<T>* currNode = L.head;
    while (currNode != NULL){
      str << currNode;
      currNode = currNode->getNext();
      if (currNode != NULL) {
    	str << ", ";
      }
    }
    str << "]";
    return (str); 
  }

};

#endif
