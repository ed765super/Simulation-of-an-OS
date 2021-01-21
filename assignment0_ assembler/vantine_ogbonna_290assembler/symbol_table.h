#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE
#include "MyString.h"
#include "LinkedList.h"
class symbol_table{
  //CI: symbol_table is defined when all member data objects contain
  //a node that satisfies what the member data objects are supposed to
  //represent. The representaiton of the member data objects are as
  //follows:
  //name_list is a pointer to the linked list of
  //MyString objects that represent the name of the labels/variables found in
  //the assembly code.  
  //address_list is a pointer to the linked
  //list of integers that represent the addresses associated with the
  //names found in the assembly code. If an address node's data is -1
  //this then considered empty.
  //variOrLabel is a pointer to the linked list of
  //characters that represents whether the associated name represents
  //a variable or a label. If variOrLabel had the data 'V' then the name with
  //the same index is a variable. Likewise, if variOrLabel had the
  //data 'L' then the name with the same index is a label.
  //amountofspace_list is a point to the linked list of integers that
  //represent the number of words the associated variable
  //allocated. This can be -1, which represents that the associated
  //name is a label.
  //addressfound_list is a pointer to
  //the linked list of booleans that represent
  //whether we have found the address that is associated to the name
  //found in the assembly code that this data object is associated with.
  //Variables are vacuously true.
  //This object (symbol_table) can be NULL. This object is considered NULL iff
  //the member data objects point to NULL and numrows = 0.
private:
  LinkedList<MyString>* name_list; //will point to  the linked
  //list of MyString 
  //objects that represent the name of the
  //labels/variable if this object is defined. Points
  //to NULL otherwise
  LinkedList<int>* address_list; // will point to  the
  // linked list of integers 
  // that represent the addresses
  //associated with the names from the
  // assembly code if this object
  //is defined. Points to NULL otherwise
  LinkedList<char>* variOrLabel;//will point to  the
  //linked list of characters 
  //that represents whether the associated
  //name represents a variable or
  //a label if this object is defined. Points
  //to NULL otherwise.
  LinkedList<int>* amountofspace_list; //will point to 
  //the linked list of integers 
  //that represent the number of words the
  //associated variable allocated if
  //this object is
  //defined. Points to NULL otherwise.
  LinkedList<bool>* addressfound_list;//will point to  the
  //linked list of booleans that
  //represent whether we have
  //found the address that is
  //associated to the name this data
  //object is associated with if this
  //object is defined. Points to NULL
  //otherwise.
  int numrows; //will hold the number of rows in this object
  

 public:
   //CONSTRUCTOR:
   //PRE:
   //POST: Creates a NULL symbol_table object on the stack.
  symbol_table();

  //COPY CONSTRUCTOR:
  //PRE: This object is defined and satisfies the CI.
  //POST: makes a deep copy off pSymbol_List
  symbol_table(const symbol_table & pSymbol_table);

  //DESTRUCTOR
  //PRE: this object is declared and defined.
  //POST: all allocated memory has been returned to the computer
  ~symbol_table();
   
  //ACCESSOR:
  //PRE: This object is defined and satisfies the CI
  //POST: RV = the number of rows created in this object
  int get_numrows() const;
  
  //PRE: This object is defined and satisfies the CI
  //POST: RV = the pointer to the name_list @ index
  MyString* get_name(int index) const;

  //PRE: This object is defined and satisfies the CI
  //POST: RV = The pointer to the address_list @ index
  int* get_address(int index) const;

  //PRE: This object is defined and satisfies the CI
  //POST: RV = The pointer to the VariorLabel list @ index
  char* get_variOrLabel(int index) const;

  //PRE: This object is defined and satisfies the CI
  //POST: RV = the pointer to the amountofspace list @ index
  int* get_amountofspace(int index) const;

  //PRE: This object is defined and satisfies the CI
  //POST: RV =  the pointer to the addressfound list @ index
  bool* get_addressfound(int index) const;

  //MODIFIERS:
  //PRE: This object is defined and satisfies the CI. name must be a
  //MyString object that represents a single name in the assembly code.
  //POST: Modifies this object s.t. this object's member data objects
  //are equal to the respective data passed as parameters
  void addrow(MyString name, int address, char VarLab,
	       int amountofspace, bool addressStatus);

  //PRE: This object is defined and satisfies the CI. pName must be a
  //MyString object that is associated with the address you wish to change
  //pName_index should be initialized at 0. This number
  //will represent what indecie the pName is on the symbol_table.
  //POST: modifies this object s.t. this object's address list associated
  //with the pName's data is equal to the new_address
  void modify_address(MyString pName, int new_address, int pName_index);

  //PRE: This object is defined and satisfies the CI. addressStatus
  //must be a boolean that represents whether or not an address has
  //been found. pName_index should be initialized at 0. This number
  //will represent what indecie the pName is on the symbol_table.
  //POST: modifies this object s.t. the address status associated to
  //the pName to addressStatus.
  void modify_addressStatus(MyString pName, bool addressStatus,
			    int pName_index);

  //IOs
  //PRE: my_table must be defined
  //POST: output file contains the symbol file
  friend ostream & operator << (ostream & stream,
				 const symbol_table & my_table);
};
#endif
