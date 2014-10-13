#include <stdio.h>												// for printf()
#include <fcntl.h>												// defines options flags
#include <unistd.h>												// for close()
#include <string.h>												// for strerror()
#include <errno.h>												// defines errno

int main(int argc, char* argv[])
{
	if (argc != 3) {											// chk if usr input correct args
        printf("Need 2 arguments (file_name1, file_name2) \n");
        return 1;
    }

    errno = 0;
	char *filepath1 = argv[1];									// file path from terminal arg

	/* 	open sys call will open the file, if it exists, specified in filepath in read
	 	and write mode. If the file does not exist, then a new file is created
	 	and then the permissions of the new file are set to RD WR and execu.

	 	O_CREAT | O_RDWR: bitwise or flag for creating a file if it does not exists,
	 	if the file exist then open the file in RDWR mode.

	 	S_IRWXU: gives read, write, execute/search permission for newly created file.
	*/

	int file_des1;
	file_des1 = open(filepath1, O_CREAT | O_RDWR, S_IRWXU);
	
	if (file_des1 >= 0) 										// if there was no error with opening
		printf("File 1 Open Successfully! \n");					// or creating new file, file_des is >= 0
	
	else														// if file_des is negative, then there was errors
	{
		printf("open() failed with error [%s]\n", strerror(errno));
		perror("open");
		return 0;
	}
	close(file_des1);											// closing the file in the end.

	char *filepath2 = argv[2];									// file path from terminal arg
	int file_des2;
	file_des2 = open(filepath2, O_CREAT | O_RDWR, S_IRWXU);
	
	if (file_des2 >= 0) 										// if there was no error with opening
		printf("File 2 Open Successfully! \n");					// or creating new file, file_des is >= 0
	
	else														// if file_des is negative, then there was errors
	{
		printf("open() failed with error [%s]\n", strerror(errno));
		perror("open");
		return 0;
	}

	close(file_des2);											// closing the file in the end.

	return 0;
}