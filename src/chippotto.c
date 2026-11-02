#include "chippotto.h"
#include "stdio.h"
#include "memory_map.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int init_chippotto(chippotto *machine){
	if(machine == NULL) return -1;
	
	machine->PC = RAM_OFFSET_PROGRAM;
	for(int i = 0; i < RAM_SIZE; i++){
		machine->RAM[i] = 0;
	}

	for(int i = 0; i < REG_NUM; i++){
		machine->V[i] = 0;
	}
	
	machine->I = 0;

	
	machine->SP = -1;
	for(int i = 0; i < STACK_SIZE; i++){
		machine->STACK[i] = 0;
	}

	machine->DT = 255;
	machine->ST = 255;

	srand(time(NULL));
	return 0;
}

int load_ram_from_file(chippotto *machine, int fd){
	if(machine == NULL) return -1;

	ssize_t res = read(fd, machine->RAM+RAM_OFFSET_PROGRAM, RAM_SIZE-RAM_OFFSET_PROGRAM);
	if(res == 0) {
		printf("Empty File\n");
		exit(-1);
	}
	if(res == -1) {
		printf("Error reading the file\n");
		exit(-1);
	}
	if(res > RAM_SIZE-RAM_OFFSET_PROGRAM) {
		printf("File too big\n");
		exit(-1);
	}

	return 0;
} 

// Access to general purpose reg
int write_reg(chippotto *machine, int addr, int value){
	if(machine == NULL) return -1;
	if(addr >= REG_NUM || addr < 0) return -2;
	value &= 0xff;

	machine->V[addr] = value;
	return 0;
}
int read_reg(chippotto *machine, int addr, int *value){
	if(machine == NULL) return -1;
	if(addr >= REG_NUM || addr < 0) return -2;

	*value = machine->V[addr];
	return 0;
}

// Access to I
int write_I(chippotto *machine, int value){
	if(machine == NULL) return -1;
	value &= 0xff;

	machine->I = value;
	return 0;
	
}
int read_I(chippotto *machine, int *value){
	if(machine == NULL) return -1;

	*value = machine->I;
	return 0;
}

// Access to PC
int write_pc(chippotto *machine, int value){
	if(machine == NULL) return -1;
	value &= 0xff;
	
	machine->PC = value;
	return 0;
}
int read_pc(chippotto *machine, int *value){
	if(machine == NULL) return -1;
	
	*value = machine->PC;
	return 0;
}

// Access to the STACK
int pop(chippotto *machine, int *value){
	if(machine == NULL) return -1;
	if(machine->SP <= 0) return -2;

	*value = machine->STACK[machine->SP];
	machine->SP--;
	return 0;
}
int push(chippotto *machine, int value){
	if(machine == NULL) return -1;
	if(machine->SP >= STACK_SIZE-1) return -2;
	value &= 0xff;

	machine->SP++;
	machine->STACK[machine->SP] = value;
	return 0;
}

// Access to timers
int write_dt(chippotto *machine, int value){
	if(machine == NULL) return -1;
	
	machine->DT = value;
	return 0;
}
int write_st(chippotto *machine, int value){
	if(machine == NULL) return -1;
	
	machine->ST = value;
	return 0;
}
int read_dt(chippotto *machine, int *value){
	if(machine == NULL) return -1;
	
	*value = machine->DT;
	return 0;
}
int read_st(chippotto *machine, int *value){
	if(machine == NULL) return -1;
	
	*value = machine->ST;
	return 0;
}
