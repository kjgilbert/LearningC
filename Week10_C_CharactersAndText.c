

///   WEEK 10 **
/// using text
/// Dawkins' evolving words/letters example


#include <stdio.h>
#include <stdlib.h>

int main(int argc,const char *argv[]){
	
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
	
	
	// ************ the infinite monkey example, evolve strings, how to change one word into another through intermediate words
	
}