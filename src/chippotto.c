#include "chippotto.h"
#include "core.h"
#include "stdio.h"
#include "memory_map.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern int font[];
int init_chippotto(chippotto *machine){
	if(machine == NULL) return -1;
	
	machine->PC = PROGRAM_START;
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
	load_font(machine);
	return 0;
}

int load_ram_from_file(chippotto *machine, int fd){
	if(machine == NULL) return -1;

	ssize_t res = read(fd, machine->RAM+PROGRAM_START, RAM_SIZE-PROGRAM_START);
	if(res == 0) {
		printf("Empty File\n");
		exit(-1);
	}
	if(res == -1) {
		printf("Error reading the file\n");
		exit(-1);
	}
	if(res > RAM_SIZE-PROGRAM_START) {
		printf("File too big\n");
		exit(-1);
	}

	return 0;
} 

int load_font(chippotto *machine){
	if(machine == NULL) return -1;

	for(int i = 0; i < 16*5; i++){
		machine->RAM[FONT_START+i] = font[i];
	}

	return 0;
}

int step_machine(chippotto *machine){
	if(machine == NULL) return -1;
	
	step(machine);
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
	value &= 0xffff;

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
	value &= 0xffff;
	
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
	value &= 0xffff;

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

extern int REGS;

// Debug info
void print_chippotto_info(chippotto *machine){
	if(machine == NULL){
		printf("CHIPPOTTO is NULL\n");
		return;
	}

	printf("PC: 0x%x\n", machine->PC);
	printf("\t Program[0x%x]: 0x%04x\n", machine->PC, machine->instr);
	printf("SP: 0x%x\n", machine->SP);
	printf("I:  0x%x\n", machine->I);
	if(REGS){
		printf("GP Regs:\n");
		for(int i = 0; i < 16; i++)
			printf("\t V%d: 0x%x\n", i, machine->V[i]);
	}
	printf("Delay Timer: 0x%x\n", machine->DT);
	printf("Sound Timer: 0x%x\n", machine->ST);
	
/*	printf("RAM content:\n");
	for(int i = PROGRAM_START; i < RAM_SIZE; i++){
		printf("0x%04x\t", machine->V[i]);
		if((i-PROGRAM_START) % 8 == 0 && i != PROGRAM_START) printf("\n");
	}
*/
	
}
