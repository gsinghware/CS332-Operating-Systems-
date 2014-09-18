/* Write a C program to implement a command called displaycontent that takes a (text) file name as
argument and display its contents. Report an appropriate message if the file does not exist or can’t
be opened (i.e. the file doesn’t have read permission). You are to use open(), read(), write() and
close() system calls. */

#include <stdio.h>											// Standard Input Output Functions
#include <fcntl.h>											// defines options flags
#include <unistd.h>											// Prototypes for many system calls
#include <string.h>											// Commenly used for string handling functions (strerror())
#include <errno.h>											// Declares errno and defines error constants

int main (int argc, char* argv[])							
{
	if (argc != 2) {										// check if argument is provided
        printf("Need 1 argument (file name) \n");
        return 1;											// return if < | > args are provided
    }

	char *filepath = argv[1];								// filepath from terminal argument
	
	int return_val;											// return_val is a dummy var
	return_val = access (filepath, F_OK);					// access checks if file exits

	if (return_val == 0) 									// if return_val is 0, file exists
		printf("%s does exist\n", filepath);
	
	else													// if return_val is negative
	{
		if (errno == ENOENT) 								// The named file does not exist.
			printf("cat: %s: No such file or directory\n", filepath);
		
		else if (errno == EACCES)							// EACCESS - permisssion denied
			printf("%s is not accessible (permisssion denied)\n", filepath);
		
		return 0;
	}

	int fd, n;												// fd - file descriptor, n - bytes read
	fd = open(filepath, O_RDWR);							// try file opened for RDWR access
	if (fd != -1)											// file successfully opened 
	{
		char buff[BUFSIZ];									// buffer where the data is written

		printf("%s opened for read/write access! \n", filepath);
		
		/*	ssize_t read(int fd, void *buf, size_t count)
			read() attempts to read up to count bytes from file descriptor fd
       		into the buffer starting at buf. */

		while((n = read(fd, buff, BUFSIZ)) > 0)				// n bytes are read, zero indicates end of file
        	write(1, buff, n);
	}

	close (fd);												// close the file in the end

	return 0;
}