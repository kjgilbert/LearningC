
///   WEEK 11 **

/// mutate a string of text to the desired string
/// Dawkins' evolving words/letters example



/// not sure yet how to feed in starting string from command line, Jeremy will go over this next week
/// currently must go in and edit value of "target"





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
#include <string.h>


// make a static variable so that this value is defined throughout the whole extent of the program
static int length;


int rand_between(int max) { // return a random int between 0 and max-1, i.e will never get a number = to max, only max-1
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


int stringEval(char *s1, char *s2){   // make our "evaluate" function
	//string 1 and 2 are fed in to the function
	//get length of strings -- this was defined globally as a static variable
	//hamming distance
	int hdist =0;
	int i;
	for(i = 0; i < length; i++){ // go through all the spots in the string
		if(s1[i]!=s2[i]) hdist++;  // if a spot doesn't match between the 2 strings, add 1 to dist, ot get our final Haming distance at the end
	}
	return(hdist);
}


// alternatively could make the library manually then call random pieces of it to get the random character
	//char choices[]="abcdefghijklmnopqrstuvwxyABCDEFGHIJKLMNOPQRSTUVWXYZ. '!"; 


int main(int argc,const char *argv[]){

	
	// set seed for random number generator
	unsigned int seed = (unsigned int)time(NULL);
	srand(seed);
	//printf("%d\n",seed);
	
	
	// what is the starting string
	char target[]="Target string";
	length = (int)strlen(target);  // use length of string function, cast it as an int because otherwise it's an unsigned int
		//strlen doesn't include the /0 in the length of the string
	
	//make a random starting sequence of letters
	char *startString = malloc((length+1)*sizeof(char));  /// BECAUSE strlen doesn't include the /0 in the length of the string
	int i;
	for(i=0; i < length; i++){
		startString[i]= randChar();
	}
	startString[length]='\0'; /// BECAUSE the array starts with a zero and goes to length (rather than length-1) then we just put the null character in there
	
	int muts = 0; //how many mutations happen to get to the target sequence
	int mutationsAtMismatches;
	
	while(stringEval(startString, target)>0){  // evolve the string of characters
		//mutate
		int site;
		do{
			site = rand_between(length);
			muts++;
		}while(startString[site]==target[site]);
		
		startString[site]=randChar();
		//evaluate how close the two strings are -- Hamming distance ( sum over units for if 1 when units are different and 0 if same )
			//--inherent in the loop
		//decide --inherent in the loop
		//stop when we get the phrase we want--inherent in the loop
		mutationsAtMismatches++;
		printf("%s \n", startString); //Print mutations to console as they happen
	}
	
printf("Number of mutations to target= %d \n", mutationsAtMismatches); //print the number of steps it takes to get to the target sequence
	
	
}