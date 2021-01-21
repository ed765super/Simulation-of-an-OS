# README #
Who did what?
=============
N = Nick

S = Skye

B = Both

B: constants

N: evaluate

S: hexToBin

S: LinkedList, Node

N: MyString, MyStringHelpers

N: stringFunctions

S: Register

S: Simulator

S: simulate.cc

N: start_shell

N: testMyString

N: test_start_shell

S: utility

B: testcases.txt

N: TC files

N: prog0 & prog2

S: prog1

N: makefile


ASSUMPTIONS:
============
1) Max number of characters the user will type in the terminal is 20

2) valid commands are lowercase

3) The only valid commands are: load, step, run, mem, exit, and cpu

4) For valid input the user types in 1 command line argument that represents the amount of memory the user wants allocated

INSTRUCTIONS:
=============
1) type make into the terminal to create your .o files and executable

2) run the executable by typing in: ./simulate <n>, where n is the amount of memory you want allocated

3) type in a command along with those command's arguments

4) enjoy the result of said command if everything typed was valid. Otherwise enjoy your error.

FUNCTIONALITY:
===============

Nick is confident that the shell functions work properly when the users input is valid. Many general error cases are caught, but there are cases that errors are not caught however. 
Nick's test file is called test_start_shell.cc 

Skye is confident that the simulator is able to load, output cpu, output memory, step and run. Not all instructions were thoroughly tested however. Arithmetic instructions (add, addi) have been verified. In and out have been verified. Lw, Sw, Beq, Bgt, Jalr, La seem to work, but they have not been thoroughly tested.
Skye's test file is called testSimulator.cc