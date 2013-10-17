

//my first C program  11 Sep 2013

/* why doesn't this work?
int main(){
	printf("It's working!\n");
}

warning: incompatible implicit declaration of built-in function ‘printf’
*/

/*
int main(){
	printf("It's working!\n");
	return(0); // do I need this part?? -- for some compilers yes, sometimes no
}
*/

// so it actually works without doing any includes and gives the warning, how is that possibel if the standard library is the onte that contains printf?


#include <stdio.h>

int main(){
	printf("It's working!\n");
}