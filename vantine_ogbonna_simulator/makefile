simulate: start_shell.o evaluate.o MyString.o MyStringHelpers.o Register.o Simulator.o stringFunctions.o simulate.o utility.o
	g++ start_shell.o evaluate.o MyString.o MyStringHelpers.o Register.o Simulator.o stringFunctions.o simulate.o utility.o -o simulate

testSimulator: Register.o Simulator.o MyString.o utility.o MyStringHelpers.o stringFunctions.o testSimulator.o 
	g++ Register.o Simulator.o MyString.o utility.o MyStringHelpers.o stringFunctions.o testSimulator.o -o testSimulator

testSimulator.o: Simulator.h testSimulator.cc LinkedList.h Register.h
	g++ -c testSimulator.cc

testString: testMyString.o MyString.o MyStringHelpers.o
	g++ testMyString.o MyString.o MyStringHelpers.o -o testString

testMyString.o: MyString.h testMyString.cc
	g++ -c testMyString.cc

testNick: start_shell.o evaluate.o MyString.o MyStringHelpers.o Register.o Simulator.o stringFunctions.o test_start_shell.o utility.o
	g++ start_shell.o evaluate.o MyString.o MyStringHelpers.o Register.o Simulator.o stringFunctions.o utility.o test_start_shell.o -o testNick

test_start_shell.o: test_start_shell.cc start_shell.o evaluate.o MyString.o MyStringHelpers.o Register.o Simulator.o stringFunctions.o test_start_shell.o utility.o
	g++ -c test_start_shell.cc

simulate.o: start_shell.h stringFunctions.h simulate.cc
	g++ -c simulate.cc

start_shell.o: start_shell.h MyString.h constants.h LinkedList.h evaluate.h Simulator.h start_shell.cc
	g++ -c start_shell.cc

evaluate.o: evaluate.h constants.h stringFunctions.h LinkedList.h Register.h Simulator.h MyString.h evaluate.cc
	g++ -c evaluate.cc

MyString.o: MyString.h MyStringHelpers.h constants.h MyString.cc
	g++ -c MyString.cc

MyStringHelpers.o: MyStringHelpers.h constants.h MyStringHelpers.cc
	g++ -c MyStringHelpers.cc

Register.o: MyString.h constants.h Register.h Register.cc
	g++ -c Register.cc

Simulator.o: Simulator.h Register.h LinkedList.h constants.h utility.h Simulator.cc
	g++ -c Simulator.cc

stringFunctions.o: stringFunctions.h constants.h stringFunctions.cc
	g++ -c stringFunctions.cc

utility.o: utility.h utility.cc
	g++ -c utility.cc

clean: 
	rm start_shell.o evaluate.o MyString.o MyStringHelpers.o Register.o Simulator.o stringFunctions.o simulate.o utility.o simulate testNick test_start_shell.o testString testMyString.o
