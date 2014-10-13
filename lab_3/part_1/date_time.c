#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (void)
{	
	pid_t pid1 = fork();									// fork for child 1 

	int status1;
	if (pid1 == -1) 										// if fork() returns -1, an error.
	{
		perror("The fork failed to create child 1.");
		exit(EXIT_FAILURE);
	}

	else if (pid1 == 0)										// child 1 successfully forked
	{		
		printf("I am child one, my pid is: %d.\n", getpid());
		/*
			The first argument to execl is the filename of the command; 
			The second argument is conventionally the program name.
			If the command takes arguments, they are strung out after this; 
			The end of the list is marked by a NULL argument.
		*/
		execl("/bin/date", "date", NULL);					// read date file, date is the date command
    	printf ("EXECL Failed, date not found. \n");						
	}
	else {

		printf("I am the parent process, my pid is: %d\n", getpid());
		
		waitpid(pid1, &status1, 0);						// wait for process 1 to be completed
		
		if (WIFSIGNALED(status1) == 0)					// WIFSIGNALED chks if child process if finished
		{
			printf("The child one process terminated normally.\n");
		}
   	}

   	printf("The parent process also terminated.: %d\n", getpid());

	return 0;
}