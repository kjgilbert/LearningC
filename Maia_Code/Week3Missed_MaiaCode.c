
// for loops:
// int i;
// for (__'__;__)
// value at which it starts such as i=0;conditional statement such as i<x;after each iteration something happens such as i increases by one i++
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

#define N 1000  //pre-processor macros, does it before looking at code, "rewrites" code by replacing certain patterns with other things, so you can name something that is just a number, so rather than setting a variable you don't have to worry about scope and memory
#define REPS (N + 1000)  //much better because don't have to write numbers in the code and lose track of them
#define startingP 0.01
//#define a (10 + 5)  C puts these in literally so use parentheses

int main(int argc,const char *argv[]){
    int fixations = 0;  //outside replication block
    int r; //count reps
    int pop[N];  //define population -an array of size N to hold our pops (same size each time so defined outside)
    
    //start loop to replicate
    for (r = 0; r < REPS; r++)
    {
        int i;  // this one will be the thing that assigns our population
        
        //start loop to follow one pop at a time
        for(i = 0; i < N; i++) // initiate loop, continue while true, iterate
        {
            if (i < startingP * N)  // based on initial freq assign either a 1 or 0, if startP=0.01, so inds 0-9 get 1's everyone else gets 0's
            { 			
                pop[i]=1;
            } //end if statement
            else{
            pop[i]=0;
            } //end else statement
            
        } // end for loop 'i=0' is start
        
        //casting, taking one variable and treating it like another, put parenthesis of type you want it to be in front of it (doesn't actually change it though), we're not using the round function, so it rounds down b/c it just elimiates anything past decimal
   	 	int x = (int)(startingP * N); //might not be a round number when we multiply, so round down and make it an int from a double
    	while(x < N && x > 0)
    	{ //until fixes or goes extinct, keep track of pop by monitoring ind's with a 1 (mutants)
           // double && means AND, single & means something different but related
           //both parts of an AND statement must be true for it to be true
           //skips second part if first part is false b/c it will never as a whole be true ***********  e.g can use it to prevent actions that aren't allowed, like dividing by zero
           
           //Reproduction
           // count mutants, x
           		for(i = 0; i < N; i++)
           		{
                	x += pop[i]; //add up all genotype values to get # mutants  += means add to existing value, same as x = x+
            	} //end for loop
        } // end while loop 'x<N & x>0
    	//Evolve 
        //store
        
    } //end for loop 'r=0' is start
} //end main