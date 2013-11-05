
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 100 // these are called preprocessor macros
#define startingP 0.01
#define REPS 1000
#define s 0.05 // selection
#define Algo 1
double total=0;


double runif(){
    
    return (double)rand()/RAND_MAX;
    //don't forget that int/int rounds down, we need to make one of them an double, casting.
    // sends it back into where it was in the main funciton
}

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


int binary(double r, double *p, int low, int high, double mid)
{
    if(r<p[mid] && (mid==0 || r>=p[mid-1])){return mid;}
    else if (r>b[mid]){ return binary (r,p,mid+1,high);}
    else if (r<b[mid-1]) {return binary(r,p,low,mid-1);}
    else{printf ("Algo binary not working");}
}

int main(int argc,const char *argv[])
{
    srand ((unsigned int)time(NULL));
    int r;
    int result=0; // scope is where a variable is definied
    
    //define population as halpoids, with no mutation.
    double *pop=malloc(sizeof(double)*N);
    
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
        //number of indiv in the population with the mutation
        int x = (int)(startingP*N);
        
//#2 - Generations:
        while(x<N && x>0)
        {// alternatively, (!(x==0||x==N)) which means or (while && means and) and ! means not that
            //fill the fitnesses array
            double *pop2=malloc(sizeof(double)*N);
            double fitness[N];
            double *p=malloc(sizeof(double)*N); // boxedges

//#3 - each invid gets assigned box edges
            for (int i=0;i<N;i++){
                if (pop[i]==0) { //<1 =0 meaning not mutant, no selective advantage
                    fitness[i]=1.;
                }
                if (pop[i]==1) { //keeps telling me that this is unused..??
                    fitness[i]= 1.+s;
                }
            
                for(int i=0;i<N;i++) // run once, going to create an object and that we will call back many times
                {
                    double total =0;
                    total+=(fitness[i])/sum_array(fitness, N);
                    p[i] = total; //kim's equ'v of boxedges
                }
            }
//#4 - pick random parents to allow us to build the next generation
            
            
            // create array, p, that holds each cumulative relative fitness (where fitness is 1 (if pop[1]=0, no mutation) or 1+s (if pop[i]=1 meaning it has the mutation)

            double randomnumber = runif();
            for (int i=0;i<N;i++){
                if (Algo == 0){
                    for(int j=0; j<N; j++){
                        double randomnumber = runif();
                        int indiv=0;
                        while (1){
                            if (randomnumber<p[indiv]){
                                pop2[j]=pop[indiv];
                                break;
                            }
                            else{
                                indiv++;
                            }
                        }
                    }
                }
                else if (Algo ==1){
                    int low = 0;
                    int high = 1;
                    double mid = ((double)(low)+high)/2;
                    binary (randomnumber, p, low, high, mid);
                }
            }
            
            
// #7 - for each in the offspring generation, copy it to new working generation (getting rid of the parent generation)
            for(int j=0;j<N;j++)
            {
                pop[j]=pop2[j];
            }
            x = 0;
            
            //counts mutants, adds up everything in the boxes to see how many are mutated.
            for(i=0;i<N;i++)
            {
                x+=pop[i]; //
            }
            free (p);
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



