useString: MyString.o useString.o MyStringHelpers.o
	g++ MyString.o useString.o MyStringHelpers.o -o useString

MyString.o: MyString.h MyString.cc constants.h MyStringHelpers.h
	g++ -c MyString.cc

useString.o: useString.cc MyString.h
	g++ -c useString.cc

MyStringHelpers.o: MyStringHelpers.h MyStringHelpers.cc constants.h
	g++ -c MyStringHelpers.cc

clean:
	rm MyString.o useString.o MyStringHelpers.o useString
