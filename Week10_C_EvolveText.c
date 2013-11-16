
///   WEEK 10 **
/// using text
/// Dawkins' evolving words/letters example






// ************ the infinite monkey example, evolve strings, how to change one word into another through intermediate words


	// create a random initial sequence
	// mutate a sequence of letters and numbers
	// need to know if we're getting closer to our target sequence or not: compare strings
		//calculate for a pair of strings, the number of mismatches between them
		// or could break something up by words and see where those match
		// or could slide two characters along each other and see where the best match is
		// or can do that with allowing gaps in the middle which is basically a BLAST search
		
		//to split a string into words is to "tokenize" a string
	//evolve
	
// to write the code, best to put those tasks that are repeated into functions:
	//produce random character - FUNCTION
	//compare strings - FUNCTION
	//create initial sequence - MAIN
	//evolve - MAIN
	
	
	
	
	

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>



int rand_between(int max) { // return a random int between 0 and max
    return rand() % max;
}


char randChar(){  //produce a random character, to: 1. mutate and 2. to create our initial random sequence
	char finalChar;
	int choices = 26*2+4; //length of our library of all possible characters, see comments in MAIN
	int draw = rand_between(choices-1); // minus 1 because 52 is going from 0 to 51
	//make letters out of the numbers we drew
	if(draw < 26) finalChar = 'a'+draw; // so 0-25 in our library is now lowercase a-z
	else if(draw < 52)  finalChar = 'A'+(draw-26);//if 26-51, then it's an uppercase letter A-Z
	else{
	//use a switch statement, in some situations, where there are lots of choices, it's better than a bunch of if statements
		switch(draw){  //C will look at draw and then proceed into one of the things following in the curly brackets
			//so these are all case statements: case, value of draw, colon, do everything here
			case 52: finalChar = '\''; // need to escape into the apostrophe because otherwise C would read it as a single quote
				break; // NEED these here because the switch statement goes to the matching 'case' then proceeds through all following unless the breaks stop it
			case 53: finalChar = '!';
				break;
			case 54: finalChar = ' ';
				break;
			case 55: finalChar = '.';
				break;
		}
	}
	return(finalChar);
}


// alternatively could make the library manually then call random pieces of it to get the random character
	//char choices[]="abcdefghijklmnopqrstuvwxyABCDEFGHIJKLMNOPQRSTUVWXYZ. '!"; 


int main(int argc,const char *argv[]){

	unsigned int seed = (unsigned int)time(NULL);
	srand(seed);
	//printf("%d\n",seed);


// test printing out a random character
	char test;
	test = randChar();
	printf("%c \n", test);
	
	
/*	BLOCK COMMENT

	// play around with chars
	char letter='a';
	printf("%c \n", letter);
	printf("%c \n", letter+2);

	// make a string
	char *x=malloc(sizeof(char)*10); // it's 10 spaces long, so I can make a longer word if I need to at any point, probably best to make it even longer to accomadate any word
	x[0]='c';
	x[1]='a';
	x[2]='t';
	x[3]='\0';
	printf("%s \n", x);
	
	//side note, can make an array like this:
	int y[] = {10,2,3};  // not dynamically allocated
	char z[]="cat2"; // this automatically tells C it's a string and puts the null terminator in there
	printf("%s \n", z);
	
END BLOCK COMMENT */

	// final phrase we want to make:   "It's going to snow this weekend!"
		// so need a library of all possible things in this phrase, we'll throw a few extra ones in to make it harder
		// we have 56 is use a-z, A-Z, ', space, ., !
	
}