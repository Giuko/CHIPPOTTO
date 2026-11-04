#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "chippotto.h"

int DEBUG;
int REGS;

int open_file(char *filename){
	int fd;
	fd = open(filename, O_RDONLY);

	if(fd == -1){
		printf("Error on open file\n");
		exit(-1);
	}
	return fd;
}


int main(int argc, char *argv[]){
	int fd;
	int res;
	chippotto machine;

	DEBUG = 0;
	REGS = 0;

	if(argc < 2){
		printf("Usage: ./chippotto <path filename>\n");
		return -1;
	}

	if(argc > 2) DEBUG=1;
	if(argc > 3) REGS=1;
	
	res = init_chippotto(&machine);
//	if(!res) printf("CHIPPOTTO initialized correctly\n");

	fd = open_file(argv[1]);

	load_ram_from_file(&machine, fd);
//	printf("Program loaded correctly\n");

	close(fd);

	while(1){
		if(argc > 2){
			print_chippotto_info(&machine);
			getc(stdin);
		}
		step_machine(&machine);		
		
	}

	
	return 0;
}
