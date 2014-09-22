/* Write a C program that mimics the cp command using open() system call to open source.txt file
in read-only mode and copy the contents of it to destination.txt using read() and write() system
calls. */

#include <stdio.h>												// Standard Input Output Functions
#include <fcntl.h>												// defines options flags
#include <unistd.h>												// Prototypes for many system calls
#include <string.h>												// Commenly used for string handling functions (strerror())
#include <errno.h>												// Declares errno and defines error constants

int main (int argc, char* argv[])							
{
	if (argc != 3) 												// 3 args required
	{			
        printf("Need 2 arguments for copy program\n");			// ./exec file1 file2 
        return 1;												// exit if false args provided
    }

	char *source = argv[1];										// source file
	char *destination = argv[2];								// destination file
		
	int fd, dd, n;
	fd = open(source, O_RDONLY);								// open the source file with RD only access
	
	if (fd >= 0)												// file opened successfully
	{
		int dummy_var = access(destination, F_OK);				// check if destination file exists
		if (dummy_var == 0)										// if it does
			unlink(destination);								// delete it because we don't want to overwrite it
		
		dd = open(destination, O_CREAT | O_RDWR, S_IRWXU);		// new file created with read and write access using flags
																// S_IRWXU, mode, provides read write exec access
		if (dd >= 0)											// if file opened successfully
		{
			char buff[BUFSIZ];									// create a buff which will read content
																// of size BUFSIZ (1024 on my system)
			while((n = read(fd, buff, BUFSIZ)) > 0)				// read file until n is 0
	        	write(dd, buff, n);								// write to file dd buff of size n
        }
        else
			perror("open");										// print error if file doesn't open

		close (fd);												// close the source file
		close (dd);												// close the dest file
	} 
	else 
		perror("open");											// print error if any

	return 0;
}