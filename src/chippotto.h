#ifndef __CHIPPOTTO_H
#define __CHIPPOTTO_H

#include "memory_map.h"
#include <stdint.h>

#define REG_NUM    16
#define STACK_SIZE 16

#define V0         0x0
#define VF         0xf

typedef struct{
	uint8_t  RAM[RAM_SIZE];  // Memory where the programs and space reserved for interpeter is
	uint8_t  V[REG_NUM];     // General Purpose registers
	uint16_t I;		         // Register used to store mem addresses

	uint16_t PC;             // Program Counter

	// Stack pointer and stack mem
	uint8_t  SP;
	uint16_t STACK[STACK_SIZE];

	uint8_t DT;              // Delay Timer
	uint8_t ST;              // Sound Timer
}chippotto;

int init_chippotto(chippotto *machine);

// Access to general purpose reg
int write_reg(chippotto *machine, int addr, int value);
int read_reg(chippotto *machine, int addr, int *value);

// Access to I
int write_I(chippotto *machine, int value);
int read_I(chippotto *machine, int *value);

// Access to PC
int write_pc(chippotto *machine, int value);
int read_pc(chippotto *machine, int *value);

// Access to the STACK
int pop(chippotto *machine, int *value);
int push(chippotto *machine, int value);

// Access to timers
int write_dt(chippotto *machine, int value);
int write_st(chippotto *machine, int value);
int read_dt(chippotto *machine, int *value);
int read_st(chippotto *machine, int *value);

#endif
