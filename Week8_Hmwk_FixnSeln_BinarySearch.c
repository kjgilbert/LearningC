
///   WEEK 8 **
///  Use binary search to try to improve the speed of last week's code. Make the code so one can easily switch between speed algorithms. I did this via the command line input; could also do with the macro which is currently commented out.


//Homework -- have (up to) 4 versions of this code: original + 3 improvements OR something with an if statement that lets you choose which way of improving the code to do that time
// e.g. #define AlGo(numbers)
// have each number run a different code, e.g. 1== binary search, 2==...., 3==...
// if(AlGo==0){...}
// if(AlGo==1){...}  etc...


// to time something in the command line, instead of ">  ./program" do ">  time ./program"
// that will return something like: real 1:51, user 1:27, system 0:05   meaning: time elapsed in real time, time elapsed for running only the code if my computer was not otherwise occupied, and time spent on things like reading/writing files


//standard boxedges : 	real = 0.107s, 	user = 0.107s, sys = 0.002s
//binary search : 		real = 0.247s, 	user = 0.080s, sys = 0.002s



///   WEEK 8 **

//Haldane's prob of fixation of a beneficial allele = 2s
// Kimura's more accurate form = (1-e^-2s)/(1-e^-2Ns)
	// these both start with one individual mutant !!!!


// measure p(s)  -- probability of fixation
// start with 1 copy of the allele -> x=1, Pinit = 1/N
// vary s and N
// under the Wright-Fisher model, everyone survives to adulthood, and number of offspring that survive is proportional to your fitness


//follow a pop unknown time until fixation occurs, so you end with a zero or 1 each time, so that tells us when to stop
// also need to replicate over these trials to get avg fixation prob.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// what is the probability of fixation in a population  P(p)_fixation

//#define AlgChoice 1  //make code run so that changing this number changes the algorithm used for selection
	// 0 = standard, 1 = binary search, 2 = ...
	// I like this better as a command line argument, makes more sense to me and means I don't have to recompile each time	

// make the binary search recursive function
int binary(double randnum, double *boxedges, int LowestPossibleValueOfTrueValue, int HighestPossibleValueOfTrueValue){
	int middle = (LowestPossibleValueOfTrueValue+HighestPossibleValueOfTrueValue)/2;
	if(randnum < boxedges[middle] && (middle==0 || randnum >= boxedges[middle-1]) ){ // BUT if runif draws a zero?, we don't want to ask for boxedge-1, so just make sure we don't do that middle-1 if middle=0, but we know if middle=0 then we know we have the leftmost box as our answer
			// so if true AND (True OR don't evaluate past there if both were true)
			// if FALSE, stops
			// if true AND ((false or true)=TRUE)
		return middle;		
		}else if(randnum >= boxedges[middle]){
			return binary(randnum, boxedges, middle+1, HighestPossibleValueOfTrueValue); // we were guessing too low at first, now just look between our highest number and our previous middle+1 as the new lowest number
			}else{
				return binary(randnum, boxedges, LowestPossibleValueOfTrueValue, middle-1); // we were guessing to high at first, now just look between our lowest number and our previous middle-1 as the new highest number
				}
		
	}

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

	// do this once per running the program - seed the random number generator
	// could do it like this if didn't want to print:  srand((unsigned int)time(NULL));  // cast time as an unsigned int
	unsigned int seed = (unsigned int)time(NULL);
	srand(seed);
	//printf("%d\n",seed);


// stop me if I don't feed arguments in
	if(argc<=1) {
    	    printf("You did not feed me arguments for N, Pinit, Reps, s, or algorithm choice.\n");
        	exit(1);
     	}

// assign some variables I'll take from the command line
	int N = atoi(argv[1]);  /// converts ascii to int  (there's also an atof, and there's not one for characters because things are already characters
	double Pinit = atof(argv[2]);
	int REPS = atoi(argv[3]);
	double s = atof(argv[4]); // selection coefficient
	int AlgChoice = atoi(argv[5]);  
	
	// show me which algorithm I chose
	if(AlgChoice == 0){printf("Simple search \n");}
	if(AlgChoice == 1){printf("Binary search \n");}
	
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
        //printf("%d\n", r);
        
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




// now the parent population exists, need some variables to characterize it        
        
        //casting, taking one variable and treating it like another, put parenthesis of type you want it to be in front of it (doesn't actually change it though), we're not using the round function, so it rounds down b/c it just elimiates anything past decimal
   	 	int x = (int)(Pinit * N); //might not be a round number when we multiply, so round down and make it an int from a double
		//x will record number of copies of mutant in the pop
		int t = 0;
// start a while loop to run the program until fixation occurs		
    	while(x < N && x > 0) // go generation by generation until fixes or goes extinct, keep track of pop by monitoring ind's with a 1 (mutants)
    	{  
    	
		
		// make an array to hold each ind's fitness        
        double *popfitness = malloc(sizeof(double)*N);  
        int j;
        for(j=0; j<N; j++)
       		{
        		if(pop[j] == 1){popfitness[j] = 1+s;
        		}else{
        			popfitness[j]=1;
        			}
        	}
		
		
		
		// make an array of standardized values -> relative fitnesses
		double *probchosen = malloc(sizeof(double)*N); // probability of being chosen to have offspring is the relative fitness
		int cat;
		for(cat=0; cat<N; cat++){
			probchosen[cat] = popfitness[cat]/sum_array(popfitness, N); 
			}    	
    	
           //both parts of an AND statement must be true for it to be true
           //so sample with replacement: make a second pop and use the first pop (parents)
           //printf("%d %d\n", t, x);
           int *pop2 = malloc(sizeof(int)*N);  
           
           
           // THIS PROCESS WILL BE MADE FASTER IN THE FUTURE BY A DIFFERENT APPROACH
           
           
        // set up boxedges here
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
           			

// make the offspring generation population
           for(i=0; i<N; i++)
           {
           		// modify rand to get a uniform distribution from 0 to 1 to draw from for selecting an individual
           		double randnum = runif();
        
	// get one individual offspring
           		// which individual does our random number correspond to?
      		int who = 0;

           	
           	if(AlgChoice==0){
           		while(who < N)
           			{ // could also have this be while(1){... so that it always continues until we break
           			//printf("%d %f %f\n", who, randnum, boxedges[who]);
           				if(randnum < boxedges[who]){
           				// if randnum is less than the value, then we've found the individual to choose -- the first box that randnum is less than means that is the box it falls into
           				break; // exits the loop
           				}else{
           				who++;
           				} // who will equal the location in the array of the ind we want
           			}
           		} // else{printf("Algorithm 0 not chosen \n");}
           		
           	if(AlgChoice==1){
          		who = binary(randnum, boxedges, 0, N-1);
           		}
           			// the above picks one individual -> then ramp up to get whole population
    // put that one offspring into our offspring population
           		//probchosen = normalized probability of being chosen
           		//printf("%d %d %d\n", t, i, who);
	           pop2[i] = pop[who]; //pick someone out of the parent pop
	           		//printf("%d \n", who);
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
            
            t++; // for when I was debugging, print t as it updates
            free(pop2);
        	free(boxedges); 
           	free(probchosen);
   	    	free(popfitness);
   	    	
        } // end while loop 'x<N & x>0
    	

    	
        //store result, the variable was defined above and set as 0 initially
        //every time a population fixes, increment the value every time a population results in a fixation
        if(x==N) result++; // increment if pop was fixed
        
    } //end for loop 'r=0' is start
    
    // summarize and output result
    printf("Number of successes: %d \nNumber of replicates: %d \nProportion fixed: %f \n", result, REPS, (double)(result)/REPS); //stands for print format, contains the format and the variable within the parentheses
   
} //end main
