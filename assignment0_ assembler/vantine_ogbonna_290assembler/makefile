translate: symbol_table.o MyString.o MyStringHelpers.o assembler.o beginpass1.o pass2.o stringFunctions.o
	g++ symbol_table.o MyString.o MyStringHelpers.o assembler.o beginpass1.o pass2.o stringFunctions.o -o translate

printST: symbol_table.o MyString.o MyStringHelpers.o assembler.o beginpass1.o stringFunctions.o
	g++ symbol_table.o MyString.o MyStringHelpers.o assembler.o beginpass1.o stringFunctions.o -o translate

assembler.o: assembler.cc symbol_table.h
	g++ -c assembler.cc
symbol_table.o: symbol_table.cc symbol_table.h LinkedList.h MyString.h
	g++ -c symbol_table.cc
MyStringHelpers.o: MyStringHelpers.cc MyStringHelpers.h constants.h
	g++ -c MyStringHelpers.cc
MyString.o: MyString.h MyString.cc MyStringHelpers.h constants.h
	g++ -c MyString.cc
stringFunctions.o: constants.h stringFunctions.h stringFunctions.cc
	g++ -c stringFunctions.cc
beginpass1.o: symbol_table.h stringFunctions.h constants.h beginpass1.cc
	g++ -c beginpass1.cc
pass2.o: symbol_table.h stringFunctions.h constants.h pass2.cc LinkedList.h
	g++ -c pass2.cc
clean:
	rm symbol_table.o MyString.o MyStringHelpers.o assembler.o beginpass1.o pass2.o stringFunctions.o translate

