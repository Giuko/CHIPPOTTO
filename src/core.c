#include "chippotto.h"
#include "display.h"
#include <stdlib.h>
#include <stdint.h>

int fetch(chippotto *machine, int *instr){
	if(machine == NULL) return - 1;	
	int pc;

	read_pc(machine, &pc);
	*instr = machine->RAM[pc];

	pc += 2;
	write_pc(machine, pc);
	return 0;
}

int decode_and_execute(chippotto *machine, int instr){
	if(machine == NULL) return - 1;	
	// From instr to be used for instr recognition
	int highest_nibble = (instr >> 12) & 0xf;       // 0xABCD -> 0xA
	int lowest_nibble  = instr & 0xf;               // 0xABCD -> 0xD
	int low_byte       = instr & 0xff;              // 0xABCD -> 0xCD
	
	// From instr to be used after instr recognition
	int raddr_1        = (instr >> 8) & 0xf;        // 0xABCD -> 0xB
	int raddr_2        = (instr >> 4) & 0xf;        // 0xABCD -> 0xC
	int rdata_1;
	int rdata_2;	
	int kk             = instr & 0xff;              // 0xABCD -> 0xCD
	int nnn            = instr & 0xfff;             // 0xABCD -> 0xCBD
	
	int V0_data;
	int VF_data;
	int I_data;
	int dt_data; 
	int st_data; 

	int pc;

	int res;
	int foo;


	// Retrieving register values alltogheter at the beginning
	read_reg(machine, raddr_1, &rdata_1);
	read_reg(machine, raddr_2, &rdata_2);

	read_reg(machine, 0x0, &V0_data);
	read_reg(machine, 0xF, &VF_data);

	read_pc(machine, &pc);
	read_I(machine, &I_data);

	read_dt(machine, &dt_data);
	read_st(machine, &st_data);

	switch (highest_nibble) {
		case 0x0:
			switch (lowest_nibble) {
				case 0xe0:
					// CLS
					clear();
					break;
				case 0xee:
					// RET
					pop(machine, &pc);
					write_pc(machine, pc);
					break;

				default:
					break;
			}
			break;

		case 0x1:	// 1nnn
			// JP addr
			write_pc(machine, nnn);
			break;

		case 0x2:	// 2nnn
			// CALL addr
			push(machine, pc);
			write_pc(machine, nnn);
			break;

		case 0x3:	// 3xkk
			// Skip next instr if Vx == kk
			pc += 2;
			if(rdata_1 == kk) write_pc(machine, pc);
			break;

		case 0x4:	// 4xkk
			// Skip next instr if Vx != kk
			pc += 2;
			if(rdata_1 != kk) write_pc(machine, pc);
			break;

		case 0x5:	// 5xy0
			// Skip next instr if Vx == Vy
			pc += 2;
			if(rdata_1 == rdata_2) write_pc(machine, pc);
			break;

		case 0x6:	// 6xkk
			// Set Vx = kk
			write_reg(machine, raddr_1, kk);
			break;

		case 0x7:	// 7xkk
			// Set Vx += kk
			rdata_1 += kk;
			write_reg(machine, raddr_1, rdata_1);
			break;

		case 0x8:	// 8xy?
			switch (lowest_nibble) {
				case 0x0:
					// Set Vx = Vy
					write_reg(machine, raddr_1, rdata_2);
					break;
				case 0x1:
					// Set Vx = Vx | Vy
					write_reg(machine, raddr_1, rdata_1 | rdata_2);
					break;
				case 0x2:
					// Set Vx = Vx & Vy
					write_reg(machine, raddr_1, rdata_1 & rdata_2);
					break;
				case 0x3:
					// Set Vx = Vx ^ Vy
					write_reg(machine, raddr_1, rdata_1 ^ rdata_2);
					break;
				case 0x4:
					// Set Vx = Vx + Vy, VF carry
					res = rdata_1 + rdata_2;
					foo = (res > 255) ? 1 : 0;
					
					write_reg(machine, raddr_1, res);
					write_reg(machine, VF, foo);
					break;
				case 0x5:
					// Set Vx = Vx - Vy, VF not borrow
					res = rdata_1 - rdata_2;
					foo = (rdata_1 >= rdata_2) ? 1 : 0;
					
					write_reg(machine, raddr_1, res);
					write_reg(machine, VF, foo);
					break;
				case 0x6:
					// Shift right Vx, VF borrow
					res = rdata_1 >> 0x1;
					foo = rdata_1 & 0x1;
					
					write_reg(machine, raddr_1, res);
					write_reg(machine, VF, foo);
					break;
				case 0x7:
					// Set Vx = Vy - Vx, VF not borrow
					res = rdata_2 - rdata_1;
					foo = (rdata_2 >= rdata_1) ? 1 : 0;
					
					write_reg(machine, raddr_1, res);
					write_reg(machine, VF, foo);
					break;
				case 0xe:
					// Shift left Vx, VF borrow 
					res = rdata_1 << 0x1;
					foo = (rdata_1>>0x7) & 0x1;
					
					write_reg(machine, raddr_1, res);
					write_reg(machine, VF, foo);
					break;

				default:
					break;
			}	
			
			break;

		case 0x9:	// 9xy0
			// Skip next instr if Vx != Vy
			pc += 2;
			if(rdata_1 != rdata_2) write_pc(machine, pc);
			break;
			break;

		case 0xA:	// Annn
			// Set value of I to nnn
			write_I(machine, nnn);
			break;

		case 0xB:	// Bnnn
			// Jump location to nnn + V0
			res = nnn + V0_data;
			write_pc(machine, res);
			break;

		case 0xC:	// Cxkk
			// Set Vx = rand & kk
			res = rand() & kk;
			break;

		case 0xD: 	// Dxyn
			// Display n-byte sprite starting at mem I at (Vx, Vy), set VF = collision 
			break;

		case 0xE:	// Ex??
			switch (low_byte) {
				case 0x9e:
					// Skip next instr if KEY=Vx is pressed
					break;
				case 0xA1:
					// Skip next instr if KEY=Vx is not pressed
					break;
				default:
					break;
			}
			break;

		case 0xF:	// Fx??
			switch (low_byte) {
				case 0x07:
					// Set Vx = delay timer
					write_reg(machine, raddr_1, dt_data);
					break;
				case 0x0a:
					// wait for a key press, store the value of the key in Vx
					break;
				case 0x15:
					// Set delay timer = Vx
					write_dt(machine, rdata_1);
					break;
				case 0x18:
					// Set sound timer = Vx
					write_st(machine, rdata_1);
					break;
				case 0x1e:
					// Set I = I + Vx
					res = I_data + rdata_1;
					write_I(machine, res);
					break;
				case 0x29:
					// Set I = location of sprite for digit Vx
					break;
				case 0x33:
					// Store BCD repr of Vx in I, I+1 and I+2
					break;
				case 0x55:
					// Store reg V0 through Vx in memory starting at I
					break;
				case 0x65:
					// Read reg V0 through Vx in memory starting at I
					break;
				default:
					break;
			}
			break;
		default:
			break;

	}
	
	return 0;
}

void step(chippotto *machine){
	int instr;

	fetch(machine, &instr);
	decode_and_execute(machine, instr);


}
