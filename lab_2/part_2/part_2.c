#include <stdio.h>
#include <stdlib.h>    /* exit */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (void)
{
	int a = 10, b = 25, pid = 0;
	printf("Initial -> a: %d, b: %d, pid: %d\n", a, b, getpid());

	pid = fork();
	if (pid == 0) 
	{	
		// Child successfully forked
		a = a + b;
		printf("Q       -> a: %d, b: %d, pid: %d\n", a, b, getpid());

		// fork another child - call it process R
		pid = fork();
		if (pid != 0)
		{
			b = b + 20;
			printf("Q       -> a: %d, b: %d, pid: %d\n", a, b, getpid());
		}
		else 
		{
			a = (a * b) + 30;
			printf("R       -> a: %d, b: %d, pid: %d\n", a, b, getpid());
		}
	}

	else {
		b = a + b - 5;
		printf("P       -> a: %d, b: %d, pid: %d\n", a, b, getpid());
	}

	return 0;
}