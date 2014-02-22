#include <stdio.h>
#include "readline.h"

void testTokenize(char c){
	putchar(c);
}

int main(void){
	readline(fopen("testreadline.txt", "r"), EOF, testTokenize);
	readline(stdin, '\n', testTokenize);
	printf("\nend test\n");	
	return  0;
}
