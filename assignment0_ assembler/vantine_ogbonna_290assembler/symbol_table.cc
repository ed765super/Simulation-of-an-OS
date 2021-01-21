#include "symbol_table.h"
#include <fstream>
#include <iostream>
using namespace std;
//CONSTRUCTOR:
//PRE: this object is declared and defined
//POST: Creates a NULL symbol_table object on the stack.
symbol_table::symbol_table(){
  name_list = new LinkedList<MyString>;
  address_list = new LinkedList<int>;
  variOrLabel = new LinkedList<char>;
  amountofspace_list = new LinkedList<int>;
  addressfound_list = new LinkedList<bool>;
}

//DESTRUCTOR
//PRE: this object is declared and defined
//POST: all allocated memory has been returned to the computer
symbol_table::~symbol_table(){
  delete name_list;
  delete address_list;
  delete variOrLabel;
  delete amountofspace_list;
  delete addressfound_list;
}
  
//COPY CONSTRUCTOR:
//PRE: This object is defined and satisfies the CI.
//POST: makes a deep copy off pSymbol_Table
symbol_table::symbol_table(const symbol_table & pSymbol_Table){
  for (int index = 0; index < name_list->getSize(); index++){
    MyString* pName = pSymbol_Table.get_name(index);
    int* pAddress = pSymbol_Table.get_address(index);
    char* pVariOrLabel = pSymbol_Table.get_variOrLabel(index);
    int* pamountofspace = pSymbol_Table.get_amountofspace(index);
    bool* paddressfound_list = pSymbol_Table.get_addressfound(index);
    //ASSERT: all data of a single row of the symbol table has been
    //set to a variable
    name_list->update(index, *pName);
    address_list->update(index, *pAddress);
    variOrLabel->update(index, *pVariOrLabel);
    amountofspace_list->update(index, *pamountofspace);
    addressfound_list->update(index, *paddressfound_list);
    //modifies the node located at value of index
  }
}

//ACCESSOR:
//PRE: This object is defined and satisfies the CI
//POST: RV = the number of rows created in this object
int symbol_table::get_numrows() const{
  return(numrows);
}

//PRE: This object is defined and satisfies the CI
//POST: RV = the pointer to the data in the name @ index
MyString* symbol_table::get_name(int index) const{
  return(name_list->getNth(index));
}

//PRE: This object is defined and satisfies the CI
//POST: RV = The pointer to the data in the address @ index
int* symbol_table::get_address(int index) const{
  return(address_list->getNth(index));
}

//PRE: This object is defined and satisfies the CI
//POST: RV = The pointer to the data in the VariorLabel list @ index
char* symbol_table::get_variOrLabel(int index) const{
  return(variOrLabel->getNth(index));
}

//PRE: This object is defined and satisfies the CI
//POST: RV = the pointer to the data in the amountofspace list @ index
int* symbol_table::get_amountofspace(int index) const{
  return(amountofspace_list->getNth(index));
}

//PRE: This object is defined and satisfies the CI
//POST: RV =  the pointer to the addressfound list @ index
bool* symbol_table::get_addressfound(int index) const{
  return(addressfound_list->getNth(index));
}

//MODIFIERS:
//PRE: This object is defined and satisfies the CI. name must be a
//MyString object that represents a single name in the assembly code.
//POST: Modifies this object s.t. this object's member data objects
//are equal to the respective data passed as parameters
void symbol_table::addrow(MyString name, int address, char VarLab,
	     int amountofspace, bool addressStatus){
  name_list->append(name);
  address_list->append(address);
  variOrLabel->append(VarLab);
  amountofspace_list->append(amountofspace);
  addressfound_list->append(addressStatus);
  numrows++;
}

//PRE: This object is defined and satisfies the CI. pName must be a
//MyString object that is associated with the address you wish to
//change. pName_index should be initialized at 0. This number
//will represent what indecie the pName is on the symbol_table.
//POST: modifies this object s.t. this object's address list associated
//with the pName's data is equal to the new_address
void symbol_table::modify_address(MyString pName, int new_address,
				 int pName_index){
  MyString* curr_name = name_list->getNth(pName_index);
  cout << "curr_name: " << *curr_name << endl;
  cout << "pName: " << pName << endl;
  if (*curr_name == pName){
    //ASSERT: pName_index is equal to the number that represents what
    //indecie the pName is on the symbol_table 
    address_list->update(new_address, pName_index);
    //sets the data of the address node corresponding to the name node
    //with pName to new_address
  }
  else{
    pName_index++;
    modify_address(pName, new_address, pName_index);
  }
}

//PRE: This object is defined and satisfies the CI. addressStatus
//must be a boolean that represents whether or not an address has
//been found.
//POST: modifies this object s.t. the address status associated to
//the pName to addressStatus.
void symbol_table::modify_addressStatus(MyString pName, bool addressStatus,
				       int pName_index){
  MyString* curr_name = name_list->getNth(pName_index);
  if (*curr_name == pName){
    //ASSERT: pName_index is equal to the number that represents what
    //indecie the pName is on the symbol_table 
    addressfound_list->update(addressStatus, pName_index);
    //sets the data of the address node corresponding to the name node
    //with pName to addressStatus
  }
  else{
    pName_index++;
    modify_addressStatus(pName, addressStatus, pName_index);
  }
}

//IOs
//PRE: my_table must be defined
//POST: output file contains the symbol table
ostream & operator << (ostream & stream, const symbol_table & my_table){
  for (int index = 0; index < my_table.get_numrows(); index++){
    MyString* pName = my_table.get_name(index);
    int* pAddress = my_table.get_address(index);
    char* pvariOrLabel = my_table.get_variOrLabel(index);
    int* pSpace = my_table.get_amountofspace(index);
    bool* status = my_table.get_addressfound(index);
    
    stream << "Name: " << *pName << endl << "address: "
	   << *pAddress << endl << "Variable/Label: "
	   << *pvariOrLabel << endl << "space: "
	   << *pSpace << endl << "addr. Found?: "
	   << *status <<  endl;
  }
  return (stream);
}
 
