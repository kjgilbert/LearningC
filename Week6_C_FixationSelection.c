
///   WEEK 6 **
/// ADD SELECTION  **

//prob of fixation of a beneficial allele = 2s
// Kimura's more accurate form = (1-e^-2s)/(1-e^-2Ns)


// measure p(s)  -- probability of fixation
// start with 1 copy of the allele -> x=1, Pinit = 1/N
// vary s and N
// under the Wright-Fisher model, everyone survives to adulthood, and number of offspring that survive is proportional to your fitness


//follow a pop unknown time until fixation occurs, so you end with a zero or 1 each time, so that tells us when to stop
// also need to replicate over these trials to get avg fixation prob.

#include <stdio.h>
#include <stdlib.h>


// what is the probability of fixation in a population  P(p)_fixation




// first make our own rand function to sample from a uniform distribution 0-1
  	// modify rand to get a uniform distribution from 0 to 1 to draw from
	double runif(){ // doesn't need any info, it will just spit out a random number
		// use casting so the division doesn't come out as a rounded integer
		return((double)rand() / RAND_MAX);  // the return function "returns control of the program back to the main function where it left off before being called
	}
	
// make a sum function for standardizing fitnesses
	double sum_array(double a[], int num_elements)
	{
   		int i; 
   		double sum=0;
   		for (i=0; i<num_elements; i++)
   		{
			 sum = sum + a[i];
 		}
   	return(sum);
	}

// start the body of the program

int main(int argc,const char *argv[]){


// stop me if I don't feed arguments in
	if(argc<=1) {
    	    printf("You did not feed me arguments for N, Pinit, or Reps.\n");
        	exit(1);
     	}

// assign some variables I'll take from the command line
	int N = atoi(argv[1]);  /// converts ascii to int  (there's also an atof, and there's not one for characters because things are already characters
	double Pinit = atof(argv[2]);
	int REPS = atoi(argv[3]);
	double s = atof(argv[4]); // selection coefficient

	// resident has fitness of 1
	// mutant has fitness of 1+s

	// to make the most general case, want to pick individuals weighted based on their fitnesses
	// e.g.  fitnesses for N=3 are 1, 1.1, 0.97, prob of each getting picked = 1/(1+1.1+0.97), 1.1/sum(...), 0.97/sum(...)

    int fixations = 0;  //outside replication block
    int r; //count reps
    int *pop = malloc(sizeof(int)*N); // wasn't in a loop so it was okay not to free
    int result = 0; //put outside the for loop so that we can store the results from the replicates that are within the for loop
    
//start loop to run through replicates
    for (r = 0; r < REPS; r++)
    {
        int i;  // iterate
        
//start loop to make one pop at a time
        for(i = 0; i < N; i++) // initiate loop, continue while true (so up until we are one less than N which is correct to the end because N is length 0 to N-1), iterate
        {
            if (i < Pinit * N)  // based on initial freq assign either a 1 or 0, if startP=0.01, so inds 0-9 get 1's everyone else gets 0's
            { 			
                pop[i]=1; // 1's are mutants, need to assign their fitness somewhere
            } //end if statement
            else{ //else statements must always be directly after the bracket or the following line like this, but no further
            pop[i]=0;
            } //end else statement
            
        } // end for loop 'i=0' is start

// make an array to hold each ind's fitness        
        double popfitness[N];
        int j;
        for(j=0; j<N; j++){
        	if(pop[j] == 1){popfitness[j] = 1+s;
        	}else{
        		popfitness[j]=1;
        		}
        }
// make an array of standardized values -> relative fitnesses
		double probchosen[N]; // probability of being chosen to have offspring is the relative fitness
		int jj;
		for(jj=0; j<N; j++){
			probchosen[jj] = popfitness[jj]/sum_array(popfitness, N); // ERRORS COMING UP HERE, something wrong with the sum function?
		}

// now the parent population exists, need some variables to characterize it        
        
        //casting, taking one variable and treating it like another, put parenthesis of type you want it to be in front of it (doesn't actually change it though), we're not using the round function, so it rounds down b/c it just elimiates anything past decimal
   	 	int x = (int)(Pinit * N); //might not be a round number when we multiply, so round down and make it an int from a double
		//x will record number of copies of mutant in the pop
		
// start a while loop to run the program until fixation occurs		
    	while(x < N && x > 0) // go generation by generation //until fixes or goes extinct, keep track of pop by monitoring ind's with a 1 (mutants)
    	{  //could also do:  while( !(x==0 || x==N)) //which are our stopping conditions, we want the opposite of it, so the exclamation point goes in front, using an OR operator
           // double && means AND, single & means something different but related
           //both parts of an AND statement must be true for it to be true
           //skips second part if first part is false b/c it will never as a whole be true ***********  e.g can use it to prevent actions that aren't allowed, like dividing by zero
           
           // Reproduction (make children, then replace adults with children) = evolution/drift
           //so sample with replacement: make a second pop and use the first pop (parents)
           int pop2[N];    //WHY WAS IT OKAY THAT THIS WAS NOT DYNAMICALLY ALLOCATED????

// make the offspring generation population
           for(i=0; i<N; i++)
           {
           		// modify rand to get a uniform distribution from 0 to 1 to draw from for selecting an individual
           		double randnum = runif();
           		double *boxedges = malloc(sizeof(double)*N);
           		double total = 0;
           		// set up the box for the "right edge" of each box in our distribution of probabilities of a given mutant/ind being chosen
           		
           		int k;
           		for(k=0; k<N; k++)
           			{
           				// take our array of probabilities and make them into an array of cumulative probabilities to define a "box" within which we randomly draw a number and depending on size of box determines prob of landing there thus defining prob of an ind being chosen
           				total += probchosen[k]; // total is tracking the right edge of each box
           				boxedges[k] = total;
           			}
           		
	// get one individual offspring
           		// which individual does our random number correspond to?
           		int who = 0;
           		while(who < N)
           			{ // could also have thie be while(1){... so that it always continues until we break
           				if(randnum < boxedges[who]){
           				// if randnum is less than the value, then we've found the individual to choose -- the first box that randnum is less than means that is the box it falls into
           				break; // exits the loop
           				}else{
           				who++;
           				} // who will equal the location in the array of the ind we want
           			}
           			// the above picks one individual -> then ramp up to get whole population
    // put that one offspring into our offspring population
           		//probchosen = normalized probability of being chosen
	           pop2[i] = pop[who]; //want a random integer between (and including) 0 and N-1 to pick someone out of the parent pop
	           //rand(); //spits out an int between 0 and RAND_MAX-1, takes no arguments
	           //RAND_MAX // a global variable that always exists and contains the maximum number for the rand function
	           // % can also be a modulus, so do long division and give the remainder, e.g. x % b gives something never bigger than b (i.e. ranges from 0 to b-1)         
             //free(probchosen);
             free(boxedges); // I think this is the one I want to free?
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
    	
    	
    	// if I wanted to, could release the pointer here:
    		// free(pop);
    	
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
