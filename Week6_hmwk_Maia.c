//
//  main.c
//  LearningC
//
//  Created by Maia Kaplan on 13-09-20.
//  Copyright (c) 2013 Maia Kaplan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



// for loops:
// int i;
// for (__'__;__)
// value at which it starts such as i=0;conditional statement such as i<x;after each itteration something happens such as i increases by one i++
//while time or while waiting ??

// fischer write, poisson distribution of offspring and drift or neutral mutant allele?
//N individuals
//1 == mutant
//0 ==resident
// i++ is 1+1 and i+=7 is i plus 7

#define N 100 // these are called preprocessor macros
#define startingP 0.5
#define REPS 100//((int)(1 / startingP * 1)) 
#define s 0.9 // selection

double total=0;

//My RAND_MAX isn't working, I'll just do it by hand while I see if it works
//double runif(){
    //return (double)(rand()/(RAND_MAX));
    // don't forget that int/int rounds down, we need to make one of them an double, casting.
    // sends it back into where it was in the main funciton
//}

// fitness, p, need to be standardized by dividing them by the total fitness. let's make each fitness = q.
double sum_array(double a[], double num_elements)
{
    int i, sum=0;
    for (i=0; i<num_elements; i++)
    {
        sum = sum + a[i];
    }
    return(sum);
}

int main(int argc,const char *argv[])
{
    srand ((unsigned int)time(NULL));
    int r;
    int result=0; // scope is where a variable is definied
    
//define population as halpoids, with no mutation. 
    int pop[N];    
//itterates a replicate, run it until allele is fixed or gone and record
    for(r=0;r<REPS;r++){
// this one will be the thing that assigns our population = settup
        int i;
        for(i=0;i<N;i++)
        {
            if(i<startingP*N) {
                pop[i]=1;
            }
            else//DO NOT seperate this from the abover curly bracket
            {
                pop[i]=0;
            }
            
        }
//uses casting to represent the number of indiv in the population with the mutation
        int x = (int)(startingP*N);         while(x<N && x>0)
        {// alternatively, (!(x==0||x==N)) which means or (while && means and) and ! means not that
// Choose parent for the next generation: SELECTION makes it such that fit parents have greater chance of being picked.
            int pop2[N];//Here we dont have to but a zero in each box, done with a for loop
            for(i=0;i<N;i++)
            {
                pop2[i]=pop[rand()%N];// we want RAND to have a range from 0 to N-1. rand(); we dont need to put anything into those brackets, but it IS a function, it has one result, and it's max value is a global variable RAND_MAX. x%N where the remainder is smaller than N.
                double *p=malloc(sizeof(double)*N);
                double randomnumber =0.1;
                //= runif();
                double total =0;
                double fitness[N];
                int i=0;
//fill the fitnesses array
                for (i=0;i<N;i++){
                    if (pop[i]==0) { //<1 =0 meaning not mutant, no selective advantage
                        fitness[i]=1.;
                    }
                    if (pop[i]==1) { //keeps telling me that this is unused..??
                        fitness[i]= 1+s;
                    }
                }

// create array, p, that holds each relative fitness (where fitness is 1 (if pop[1]=0, no mutation) or 1+s (if pop[i]=1 meaning it has the mutation)
                
                for(i=0;i<N;i++) // run once, going to create an object and that we will call back many times
                {
                    total+=(fitness[i])/sum_array(fitness, N);
                    p[i] = total;
                }
// I'm pretty sure I have a problem is around here somewhere...
                int indiv=0;
                if (randomnumber<p[indiv])
                {
                    pop2[i]=pop[indiv];
                    printf (" individual is: %d \n ",indiv); // just to check
                    break;
                }
                else {indiv ++;
                }
            
            
            }
            for(i=0;i<N;i++)
            {
                    pop[i]=pop2[i];
            }
            
            x = 0;
            //counts mutants, adds up everything in the boxes to see how many are mutated.
            for(i=0;i<N;i++)
            {
                x+=pop[i]; //
            }
         }
        if (x==N)
        {
            result++;//if the result of that itteration is that it fixed, add one. if it didn't fix, don't add anything.
        }
    }
    // at the end of the while loops, we need to record results
    
    
    
    

    printf ("Proportion is: %d %d %f \n ",result, REPS, (double)(result)/REPS); //summarize and output, the proportion: the number of times it was fixed/total number of REPS. double is casting that changes the type of one of the values, where the result would then be a decimal which is good (otherwise it would be a zero).
}
    // we want to print, number of success, number of trials, proportion.


//HW1 : run through this and find P/N as the prob.
//HW 2: try to set up a conf interval with the binom dist. to see if our value is true or not. 



//binomial distribution:
//P(x)=(n choose x)*p^x*(1-p)^(n-x)
//mean +/- z * standard deviation/sqrt(number of samples)
//mean±1.96*


// printf (STRING = "characters in an array %=where the variable will go followed by a letter: f= floating point number(like double), d= integer (like int), ", VARIABLES=)
// remember that in a bit, 8 digits, the first one is the sign, so the rest can rep resent 0-2^7-1. if we make it an unsigned number, then we can represent higher values, up to 2^8-1. % du = unsigned integer.
// "\" allows us not to take the next ne litterally, if we want to type a blackslash, write \\.
// interface of a funciton: what it expects as imput and what it gives as output. 


//What Kim wrote up:
//to run the program though the command line: >./prog 1000 0.1 where it takes each of the two arguments
// int N = atoi (argv[1])j // which translates the argument into an integer, atof () translates it into a floating point number
// int pint = atof(arg[2])j


