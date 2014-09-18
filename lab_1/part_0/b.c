/*
	Write a C program where open system call creates a new file (say, destination.txt) 
	and then opens it. (Hint: use the bitwise OR flag).
*/

#include <stdio.h>												// for printf()
#include <fcntl.h>												// defines options flags
#include <unistd.h>												// for close()
#include <string.h>												// for strerror()
#include <errno.h>												// defines errno

int main(int argc, char* argv[])
{
	if (argc != 2) {											// chk if usr input correct args
        printf("Need 1 arguments (file name) \n");
        return 1;
    }

    errno = 0;
	char *filepath = argv[1];									// file path from terminal arg

	/* 	open sys call will open the file, if it exists, specified in filepath in read
	 	and write mode. If the file does not exist, then a new file is created
	 	and then the permissions of the new file are set to RD WR and execu.

	 	O_CREAT | O_RDWR: bitwise or flag for creating a file if it does not exists,
	 	if the file exist then open the file in RDWR mode.

	 	S_IRWXU: gives read, write, execute/search permission for newly created file.
	 */

	int file_des;
	file_des = open(filepath, O_CREAT | O_RDWR, S_IRWXU);
	
	if (file_des >= 0) 											// if there was no error with opening
		printf("Open Successfully! \n");						// or creating new file, file_des is >= 0
	
	else														// if file_des is negative, then there was errors
	{
		printf("open() failed with error [%s]\n", strerror(errno));
		perror("open");
		return 0;
	}

	close(file_des);											// closing the file in the end.

	/*
	int return_val;
	errno = 0;

	// check file existance
	return_val = access (filepath, F_OK);

	int fd;
	if (return_val == 0)									// if F_OK is 0, file exists
	{
		printf("%s does exist\n", filepath);
		fd = open(argv[1], O_RDWR);							// allow RD and WR
		printf("%s opened Successfully with read write accessiblity\n", filepath);
		printf("open() failed with error [%s]\n",strerror(errno));
	}
	else {
		if (errno == ENOENT) 								// errno - ENOENT - Error NO ENTry
		{
			printf("%s does not exist\n", filepath);
			printf("\n open() failed with error [%s]\n",strerror(errno));
			fd = open(argv[1], O_CREAT, S_IRWXU);			// if file does not exist, create one, give it RDWR access
			printf("%s created now and opened Successfully with read write accessiblity\n", filepath);
		}
		else if (errno == EACCES)							// EACCESS - permisssion denied
		{
			printf("%s is not accessible\n", filepath);
			printf("open() failed with error [%s]\n", strerror(errno));
		}
	}

	close (fd);
	*/

	return 0;
}