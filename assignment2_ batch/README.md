# README #

Scotty's Assistance Level
=========================
Scotty helped me with planning out what I want to do and occasionally gave me his opinion when I was left in an either or situation. For example, I would think out as far as I can about what situations a block of memory could be in. I got all but one but couldn't remember what the last part was. Scotty gave me a hint by using the terms I was spouting and I figured out the final situation. At no point was I simply given an answer unless it was on something minor like an emacs command to do something. I solve all of my compiler errors myself barring some of the stuff I was a little foggy on for example on February 24th, Christopher helped me clear a misconception I had about pointers and reminded me that I can write &<name> of some variable to get the reference of that variable (which I originally thought you could only do with parameters.) I wanted to use that in an earlier version of my project and wanted to try something. I asked Scotty just for confirmation on what Chris told me (I ultimately found something better and scrapped it, but the clarity was good for me). Everything else has been documented in my commits in the repository.

ASSUMPTIONS:
============
0) All the parameters for the simulation should be in a file called .lc_config.

1) The configuration file must be named ".lc_config" and should contain the values for the memory size in number of words, the stack size in number of words to be allocated to fetch program, and the memory management policy (best fit or first fit). 

1.5) Each of these values should be non-zero numbers. 

1.75) The file should contain the name of the parameter followed by a value after one space.

2) valid commands are lowercase

3) The only valid commands are: load, step, run, mem, exit, kill, jobs, freemem, and cpu

4) For the memory management policy, 0 will denote first fit and 1 will denote best fit. 

5) each line of the config file begins with one of the keywords memory, stack or mem-management.

6) there is one space after the keyword followed by the number specification for the keyword. 

7) the numbers specified are valid (i.e., for memory and stack, the numbers are positive integers greater than 0, and for mem-management the number is 0 or 1).

8) The end of file character will be on a new line and will be the first character on that line.

INSTRUCTIONS:
=============
TO MAKE THE SIMULATOR
0) Make sure you have a .lc_config file and make sure it have the parameters you want that align with the assumptions above.

1) type the term "make" into the terminal to create your .o files and executable

2) run the executable by typing in: ./simulate, where n is the amount of memory you want allocated

3) type in a command along with those command's arguments

4) enjoy the result of said command if everything typed was valid. Otherwise enjoy your error.

FUNCTIONALITY:
===============
along with the original stuff that worked in the previous project
fremem works
kill works
jobs works
im modifying freeBlocks correctly
the translation from file to my program is not functioning but if it did, my entire project would work.
and i covered a ton of other error cases
my test cases should prove these claims (i have 2 files of testcases)
I believe I've done enough on this project to at least pass.