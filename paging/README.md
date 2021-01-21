# README #

Scotty's Assistance Level
=========================


ASSUMPTIONS:
============
0) All the parameters for the simulation should be in a file called .lc_config.

1) all valid commands will be lowercase.

2) Each line of the config file barring the final line starts with a keyword. The only valid keywords in the config file are as follows: memory, stack, timeslice, pagesize, fittype, swapspace, paging

2.5) the integer on the same line as memory, stack,& swapspace are in terms of number of pages

2.75) the integer on the same line as pagesize should indicate the size of a page.

2.8) the integer on the same line as paging should indicate the evictio stratagy where 0 = FIFO and 1 = LRU.

3) Each of the values for the above keywords must be non-zero positive numbers. 

4) The file should contain the name of the parameter followed by a value after one space.

5) The only valid commands are: load, step, mem, exit, kill, pages[<pid>], jobs, freemem, and cpu

6) The end of file character will be on a new line and will be the first character on that line for the config file.

INSTRUCTIONS:
=============
TO MAKE THE SIMULATOR
0) Make sure you have a .lc_config file and make sure it have the parameters you want that align with the assumptions above.

1) type the term "make" into the terminal to create your .o files and executable

2) run the executable by typing in: ./simulate

3) type in a command when you see '>' in the terminal along with any other thing you want to type

4) enjoy the result of said command if everything typed was valid. Otherwise enjoy your error.

FUNCTIONALITY:
===============
My program does not compile. and if it did it does not function properly.

I have a variety of objects and functions that I plan to use in various places of my OS and Simulator. My code is essentially pseudo code of how i want my program to work. I didn't modify findSpace for the paging project, not sure exactly what i was going to do, but I was planning some sort of "oranges in mailbox" type of algorithm for finding the space in memory. My shell & PCB are at a finished point. My OS needs a few quality of life changes and some touch ups. my main is at a finished point as well. My program still doesn't do anything to the stack other than allocate space for it. I cleaned up a lot of the huge functions and made them smaller functions.