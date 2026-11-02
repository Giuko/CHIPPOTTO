#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int open_file(char *filename){
	int fd;
	fd = open(filename, O_RDONLY);

	if(fd == -1){
		printf("Error on open file\n");
		exit(-1);
	}
	return fd;
};
