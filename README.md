# SIC-Machine

Implementation of SIC Machine Architecture for  conversion of assembly into machine code.

The programs starts with "mainprogram.c".
It imports 2 header files pass1.h and pass2.h.

The program reads an "input.txt" file.
"Optab.txt" stores the various operands used in the program, along with size of each operand and their hexadecimal code.
"Symtab.txt" stores all the symbols or labels, along with the address they are pointing to. 

"Pass1" contains pass_1() function, that generates an "intermediate.txt" file, with the addressing for each line.

Then "Pass2" executes.
"Pass2" contains 2 functions, pass_2() and object_pro().


pass2() reads the intermediate.txt file and creates an "Output.txt" file that generates the object code for each line.

object_pro() reads the "output.txt" file and generates the "objectprogram.txt" file, that stores the object program for the given input.
object_pro() uses a temporary file "temp.txt" for generating the final object program.






