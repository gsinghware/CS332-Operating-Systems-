#include <stdio.h> 
#include <unistd.h>

int main (int argc, char *argv[]) 
{
	execv ("/bin/echo", &argv[0]); 	
	printf ("EXECV Failed\n");
	/* The above line will be printed only on error and not otherwise */
}