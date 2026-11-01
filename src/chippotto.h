#ifndef __CHIPPOTTO_H
#define __CHIPPOTTO_H

#include "memory_map.h"
#include <stdint.h>

#define REG_NUM    16
#define STACK_SIZE 16

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

void init_chippotto(chippotto *machine);
int write_reg(int addr, int value);
int read_reg(int addr, int *value);

#endif
