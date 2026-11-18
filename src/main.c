#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "chippotto.h"
#include "display.h"
#include "screen.h"
#include "keyboard.h"
#include <signal.h>

int DEBUG;
int EXTRA;
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

void signalHandler(int sig){
	const char msg[] = "Caught SIGINT\n";
	write(STDOUT_FILENO, msg, sizeof(msg)-1);
	disable_game_keyboard();
	screen__disp_clear();	
	_exit(sig);
}

int main(int argc, char *argv[]){
	int fd;
	chippotto machine;

	DEBUG = 0;
	EXTRA = 0;
	REGS = 0;

	if(argc < 2){
		printf("Usage: ./chippotto <path filename>\n");
		return -1;
	}

	if(argc > 2) DEBUG=1;
	if(argc > 3) EXTRA=1;
	if(argc > 4) REGS=1;
	
	init_chippotto(&machine);
	printf("CHIPPOTTO initialized correctly\n");

	fd = open_file(argv[1]);

	load_ram_from_file(&machine, fd);
	printf("Program loaded correctly\n");

	close(fd);
	enable_game_keyboard();
	disp_clear(&machine);
	
	
	signal(SIGINT, signalHandler);

	while(1){
		step_machine(&machine);		
		if(argc > 2){
			getc(stdin);
			print_chippotto_info(&machine);
      printf("\n");
			getc(stdin);
		}
		
	}

	
	return 0;
}
