// Week 2 of learning C, create a program that adds two numbers together. Further extended to feed those numbers in through the command line.


#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){  //return value/output will be int because of the very first part of the line, the inputs and types are listed in the parentheses
	//argc receives the number of things that are passed as an argument to the program, i.e. 2 numbers would be 3 things: the numbers plus the name of the program
	//argv[] is an array of flexible size, the * makes it flexible, char makes it able to take any characters

/* if we weren't feeding in values from the command line, could do the following:

	int a = 5;///the numbers are assigned differently when we actually feed in from the command line
	int b = 7;
	int c; //if we exceed the memory allocation from making c an int, things can go wonky; may not give an error but just a nonsensical result like a negative number
	//ints are usually up to 2^32 -1 bits big (because use 4 bytes)
	// could equally define c as int c = a/b;
	c=a+b;

	//if b was accidentally a double, e.g. double b = 7.2;
	// c will come out equalling 12.2, but then because you're trying to fit that into an int, it will give an error or a warning that you're losing precision
	// if we defined c as a double then it would work okay

	//if we defined c as int c = a/b;  then C would throw away the remainder and give back 5/2 as 2!
	//there's a corresponding function to give you ust the remainder so that wou can then add the remainder on to the number:  int c = a % b;
	// if you want a decimal point, must tell it not to do integer division: can do this by making a or b a floating point number and c a double OR tell it it's a decimal by putting (double) in front of it, e.g.  double c = (double) a/b;  OR do double c = (a+0.0)/b; because adding a floating point number to an int makes it a floating point number

	// operators = + - * / %

*/  //end block comment  -- the above block of code is working if uncommented



// now writing the code to take inputs from command line arguments

if(argc<=1) {
        printf("You did not feed me arguments, I will die now :( ...\n");
        exit(1);
     }  //otherwise continue on our merry way...


int a = atoi(argv[1]);  /// converts ascii to int  (there's also an atof, and there's not one for characters because things are already characters
int b = atoi(argv[2]);
int c = a+b;


//then get our answer by:
printf("%d\n", c); // still need to specify if it's a floating point or integer, that's done there by saying the format of what's being printed in the quotes and what follows the comma is the item(s) that fits that description
// int = %d, double = %f
//using the wrong symbol, it would interpret that value from the bits wrong and be gibberish

return(0); //tells the computer it has successfully finished, i.e. the OS receives the 0, not the command line interface, so we don't see what is returned here. Must print or do other things for output to do stuff.
}