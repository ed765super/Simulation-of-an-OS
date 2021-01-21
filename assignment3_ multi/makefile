simulate: start_shell.o evaluate.o MyString.o MyStringHelpers.o Register.o Simulator.o stringFunctions.o simulate.o utility.o OS.o PCB.o block.o 
	g++ start_shell.o evaluate.o MyString.o MyStringHelpers.o Register.o Simulator.o stringFunctions.o simulate.o utility.o OS.o PCB.o block.o  -o simulate

OS.o: OS.h OS.cc LinkedList.h PCB.h Simulator.h block.h Node.h
	g++ -c OS.cc

PCB.o: MyString.h PCB.h Register.h LinkedList.h block.h
	g++ -c PCB.cc

block.o: block.h
	g++ -c block.cc

simulate.o: start_shell.h stringFunctions.h simulate.cc Exception.h block.h
	g++ -c simulate.cc

start_shell.o: start_shell.h MyString.h constants.h LinkedList.h Node.h evaluate.h Simulator.h start_shell.cc
	g++ -c start_shell.cc

evaluate.o: evaluate.h constants.h stringFunctions.h LinkedList.h Node.h Register.h Simulator.h MyString.h evaluate.cc
	g++ -c evaluate.cc

MyString.o: MyString.h MyStringHelpers.h constants.h MyString.cc
	g++ -c MyString.cc

MyStringHelpers.o: MyStringHelpers.h constants.h MyStringHelpers.cc
	g++ -c MyStringHelpers.cc

Register.o: MyString.h constants.h Register.h Register.cc
	g++ -c Register.cc

Simulator.o: Simulator.h Register.h LinkedList.h Node.h block.h constants.h utility.h OS.h PCB.h stringFunctions.h Simulator.cc 
	g++ -c Simulator.cc

stringFunctions.o: stringFunctions.h constants.h stringFunctions.cc
	g++ -c stringFunctions.cc

utility.o: utility.h utility.cc constants.h
	g++ -c utility.cc

clean: 
	rm start_shell.o evaluate.o MyString.o MyStringHelpers.o Register.o Simulator.o stringFunctions.o simulate.o utility.o simulate testNick test_start_shell.o testString testMyString.o OS.o PCB.o block.o  testNick.o
