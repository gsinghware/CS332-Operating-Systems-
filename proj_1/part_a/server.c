#include <stdio.h>
#include <stdlib.h>

int main( int argc, char* argv[])
{
	int result;

	int a;						
	sscanf(argv[1], "%d", &a);		// convert the 1 char to an int
	
	int b;
	sscanf(argv[3], "%d", &b);		// convert the 2nd char to an int
		
	printf("> %d %s %d \n", a, argv[2], b);	

	// int result = 0;					

	if (*argv[2] == '+') {			// if +, then add else subtract
		result = a + b;
	}
	else if (*argv[2] == '-') {
		result = a - b;				// subtract
	} else {
		printf("You must enter '+'' or '-'' \n");
	}

	// exit(result);				// exit returns the result to the parent process
	return result;					// return the result
}