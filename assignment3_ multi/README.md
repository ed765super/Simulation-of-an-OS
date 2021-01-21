# README #

Scotty's Assistance Level
=========================
Scotty gave me a refresher course on destructors and exceptions & I used that knowledge in my project (most of the exception things i tried to implement I took out due to compiler complaints).
When every I finished handtracing and think of an idea to fix something, I practice translating my ideas to words by telling Scotty what I want to do, how I want to implement it, why I believe it should work, and ask whether he was able to understand what i was trying to say to which he would respond with a definite yes, a kinda yes, a meh, a kinda no, or a flat out "take a deep breath and reState what you want to say." I feel like im getting better at speaking.
Other than that, the specifics of my interactions with scotty have been jotted down in my commits.

ASSUMPTIONS:
============
0) All the parameters for the simulation should be in a file called .lc_config.

1) The configuration file must be named ".lc_config" and should contain the values for the memory size in number of words, the stack size in number of words to be allocated to fetch program, and the memory management policy (best fit or first fit), and timeslice which represents the number of instructions you want to execute in a single timeslice.

1.5) Each of these values should be non-zero numbers. 

1.75) The file should contain the name of the parameter followed by a value after one space.

2) valid commands are lowercase

3) The only valid commands are: load, step, mem, exit, kill, jobs, freemem, and cpu

4) For the memory management policy, 0 will denote first fit and 1 will denote best fit. 

5) each line of the config file begins with one of the keywords memory, timeslice, stack, or mem-management.

6) there is one space after the keyword followed by the number specification for the keyword. 

7) the numbers specified must be valid (i.e., for memory and stack, the numbers are positive integers greater than 0, and for mem-management the number is 0 or 1).

8) The end of file character will be on a new line and will be the first character on that line for the config file.

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
The multip-processing works. Every command except for mem is seperated from the simulator/OS respectively. In the last 40 minuted I managed to break the cout that stated "the program has halted" so that's back in the simulator for now. I did not manage to come up with a better (actual) algorithm fix best/first fit so Ileft them the way they were. I plan to fix them in paging if I can. The extra space allocated in freemem is due to my best/first fit algorithms so once I figure out an algorithm for those two freemem should fix itself. Round robin works perfectly.