sysOn: sysOn.o startShell.o evaluate.o MyString.o MyStringHelpers.o stringFunctions.o fileSys.o iNode.o utility.o superBlock.o directoryNode.o fileNode.o contentNode.o freeNode.o MyString.o MyStringHelpers.o
	g++ sysOn.o startShell.o evaluate.o MyString.o MyStringHelpers.o stringFunctions.o fileSys.o iNode.o utility.o superBlock.o directoryNode.o fileNode.o contentNode.o freeNode.o -o sysOn

startShell.o: startShell.h MyString.h stringFunctions.h constants.h LinkedList.h Node.h evaluate.h fileSys.h startShell.cc
	g++ -c startShell.cc

test: testSetData.o
	g++ testSetData.o -o test

testSetData.o: testSetData.cc
	g++ -c testSetData.cc

MyString.o: MyString.h MyStringHelpers.h constants.h MyString.cc
	g++ -c MyString.cc

MyStringHelpers.o: MyStringHelpers.h constants.h MyStringHelpers.cc
	g++ -c MyStringHelpers.cc

stringFunctions.o: stringFunctions.h constants.h stringFunctions.cc
	g++ -c stringFunctions.cc

evaluate.o: evaluate.h constants.h stringFunctions.h LinkedList.h Node.h fileSys.h MyString.h evaluate.cc
	g++ -c evaluate.cc

fileSys.o: iNode.h fileSys.h fileSys.cc constants.h
	g++ -c fileSys.cc

iNode.o: iNode.h iNode.cc utility.h constants.h
	g++ -c iNode.cc

utility.o: utility.h utility.cc constants.h
	g++ -c utility.cc

superBlock.o: superBlock.h superBlock.cc iNode.h
	g++ -c superBlock.cc

directoryNode.o: directoryNode.h directoryNode.cc iNode.h
	g++ -c directoryNode.cc

fileNode.o: fileNode.h fileNode.cc iNode.h
	g++ -c fileNode.cc

contentNode.o: contentNode.h contentNode.cc iNode.h
	g++ -c contentNode.cc

freeNode.o: freeNode.h freeNode.cc iNode.h
	g++ -c freeNode.cc

clean:
	rm sysOn.o startShell.o evaluate.o LinkedList.o Node.o stringFunctions.o fileSys.o iNode.o utility.o superBlock.o directoryNode.o fileNode.o contentNode.o freeNode.o MyString.o MyStringHelpers.o sysOn
