#include "chippotto.h"
#include "stdio.h"

int init_chippotto(chippotto *machine){
	if(machine == NULL) return -1;
	
	for(int i = 0; i < RAM_SIZE; i++){
		machine->RAM[i] = 0;
	}

	for(int i = 0; i < REG_NUM; i++){
		machine->V[i] = 0;
	}
	
	machine->I = 0;

	
	machine->SP = STACK_SIZE - 1;
	for(int i = 0; i < STACK_SIZE; i++){
		machine->STACK[i] = 0;
	}

	machine->DT = 255;
	machine->ST = 255;

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
	if(machine->SP >= STACK_SIZE-1) return -2;

	machine->SP++;
	*value = machine->STACK[machine->SP];
	return 0;
}
int push(chippotto *machine, int value){
	if(machine == NULL) return -1;
	if(machine->SP <= 0) return -2;
	value &= 0xff;

	machine->STACK[machine->SP] = value;
	machine->SP--;
	return 0;
}
