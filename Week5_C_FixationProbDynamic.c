// Week 5 of learning C, build upon last week's program of neutral fixation probabilities.  Now use dynamic memory allocation.
// THE UPDATED version that actually includes the dynamic memory allocation is in the week 5 homework file.



// for loops:
// int i;
// for (__;__;__)
// value at which it starts such as i=0; conditional statement such as i<x;after each iteration something happens such as i increases by one i++
//while time or while waiting ??

//N individuals
//1 == mutant  for genotypes
//0 ==resident
// i++ is i + 1 and i += 7 is i plus 7

//fixation prob of a neutral allele

//follow a pop unknown time until fixation occurs, so you end with a zero or 1 each time, so that tells us when to stop
// also need to replicate over these trials to get avg fixation prob.

#include <stdio.h>
#include <stdlib.h>


// what is the probability of fixation in a population  P(p)_fixation

#define N 1000  //pre-processor macros, does it before looking at code, "rewrites" code by replacing certain patterns with other things, so you can name something that is just a number, so rather than setting a variable you don't have to worry about scope and memory
#define REPS (N + 4000)  //much better because don't have to write numbers in the code and lose track of them
#define Pinit 0.99
//#define a (10 + 5)  C puts these in literally so use parentheses
//can force one of these to be floating point by having a decimal, e.g. 10.  or if really is floating point, it understands 10.01

int main(int argc,const char *argv[]){

//read from command line -- can't do yet because pre-processing macros are needed for compiling the code
//int N 
//int REPS
//int Pinit

    int fixations = 0;  //outside replication block
    int r; //count reps
    int pop[N];  //define population -an array of size N to hold our pops (same size each time so defined outside)
    int result = 0; //put outside the for loop so that we can store the results from the replicates that are within the for loop
    
    //start loop to replicate
    for (r = 0; r < REPS; r++)
    {
        int i;  // this one will be the thing that assigns our population
        
        //start loop to make and follow one pop at a time
        for(i = 0; i < N; i++) // initiate loop, continue while true (so up until we are one less than N which is correct to the end because N is length 0 to N-1), iterate
        {
            if (i < Pinit * N)  // based on initial freq assign either a 1 or 0, if startP=0.01, so inds 0-9 get 1's everyone else gets 0's
            { 			
                pop[i]=1;
            } //end if statement
            else{ //else statements must always be directly after the bracket or the following line like this, but no further
            pop[i]=0;
            } //end else statement
            
        } // end for loop 'i=0' is start
        
        
        //casting, taking one variable and treating it like another, put parenthesis of type you want it to be in front of it (doesn't actually change it though), we're not using the round function, so it rounds down b/c it just elimiates anything past decimal
   	 	int x = (int)(Pinit * N); //might not be a round number when we multiply, so round down and make it an int from a double
    	//x will record number of copies of mutant in the pop
    	while(x < N && x > 0) // go generation by generation //until fixes or goes extinct, keep track of pop by monitoring ind's with a 1 (mutants)
    	{  //could also do:  while( !(x==0 || x==N)) //which are our stopping conditions, we want the opposite of it, so the exclamation point goes in front, using an OR operator
           // double && means AND, single & means something different but related
           //both parts of an AND statement must be true for it to be true
           //skips second part if first part is false b/c it will never as a whole be true ***********  e.g can use it to prevent actions that aren't allowed, like dividing by zero
           
           // Reproduction (make children, then replace adults with children) = evolution/drift
           //so sample with replacement: make a second pop and use the first pop (parents)
           int pop2[N];
           // fill in this pop with inds
           for(i=0; i<N; i++){
           		//rand is usually NOT good to use
	           pop2[i] = pop[rand() % N]; //want a random integer between (and including) 0 and N-1 to pick someone out of the parent pop
	           //rand(); //spits out an int between 0 and RAND_MAX, takes no arguments
	           //RAND_MAX // a global variable that always exists and contains the maximum number for the rand function
	           // % can also be a modulus, so do long division and give the remainder, e.g. x % b gives something never bigger than b (i.e. ranges from 0 to b-1)         
           }
           //put pop2 into pop to replace adults with offspring
           for(i=0; i<N; i++){
           	pop[i]=pop2[i];
           }
           
           // update x after the pop has evolved:
           x = 0; // this is okay b/c the while loop won't check x until the end
           		for(i = 0; i < N; i++)
           		{
                	x += pop[i]; //add up all genotype values to get # mutants  += means add to existing value, same as x = x+
            	} //end for loop
        } // end while loop 'x<N & x>0
    	//Evolve 
    	
    	
        //store result, the variable was defined above and set as 0 initially
        //every time a population fixes, increment the value every time a population results in a fixation
        //if(fixed) result++
        if(x==N) result++;
        
    } //end for loop 'r=0' is start
    
    // summarize and output result
    //the proportion will be number of results/total number of runs
    printf("Number of successes: %d \nNumber of replicates: %d \nProportion fixed: %f \n", result, REPS, (double)(result)/REPS); //stands for print format, contains the format and the variable within the parentheses
    //what follows the percent tells C how to treat that variable (its type)  %f means floating point number/double; %d means integer
    //%d has sub options if you want a signed or unsigned integer
    // can also have special characters in the print thing, e.g. a newline  \n  backslash is an "escape character" saying don't take this character literally
    // can output multiple variables just by putting them in order respectively
    // because result and REPS are integers, the division is weird.  if one of them was a double we'd be fine, so just make one of them a double right there by casting
    // have to think about order of operations with casting, so that's what the parentheses are for.  Verify that this worked
   
} //end main
