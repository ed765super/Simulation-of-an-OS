#include <iostream>
#include <stdio.h>
using namespace std;
int main() {
  unsigned int data = 0x01000000;
  printf("%#08x\n", data);
  cout << "Data: " << hex << data << endl;
  unsigned int pType = 0x00000002;
  printf("%#08x\n", pType);
  cout << "pType: " << hex << pType << endl;
  unsigned int mask = 0x10111111; //create mask that will clear out the
				//placemark where the current type is at.
  printf("%#08x\n", mask);
  cout << "mask: " << hex << mask << endl;
  int temp = data & mask; //temp = data[0] where the type for data
			     //has been reset to 0
  printf("%#08x\n", temp);
  cout << "temp: " << hex << temp << endl;
  unsigned int shiftedP = pType << 4 * 6;//shifts pType s.t  pType's
					  //# is at the placemark
					  //where the original
					  //placemark was
  printf("%#08x\n", shiftedP);
  cout << "shiftedP: " << hex << shiftedP << endl;
  data = temp | shiftedP;//modifies this object's type
					 //s.t. it is equal to pType
  printf("%#08x\n", data);
  cout << "data: " << hex << data << endl;
  return 0;
}
