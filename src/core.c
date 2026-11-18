#include "chippotto.h"
#include "display.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

extern int DEBUG;

int fetch(chippotto *machine){
	if(machine == NULL) return - 1;	
	int pc;

	read_pc(machine, &pc);
	machine->instr = machine->RAM[pc] << 8 | machine->RAM[pc+1];

	pc += 2;
	write_pc(machine, pc);
	return 0;
}

int decode_and_execute(chippotto *machine){
	if(machine == NULL) return - 1;	
	// From instr to be used for instr recognition
	int highest_nibble = (machine->instr >> 12) & 0xf;       // 0xABCD -> 0xA
	int lowest_nibble  = machine->instr & 0xf;               // 0xABCD -> 0xD
	int low_byte       = machine->instr & 0xff;              // 0xABCD -> 0xCD
	
	// From instr to be used after instr recognition
	int raddr_1        = (machine->instr >> 8) & 0xf;        // 0xABCD -> 0xB
	int raddr_2        = (machine->instr >> 4) & 0xf;        // 0xABCD -> 0xC
	int rdata_1;
	int rdata_2;	
	int n              = machine->instr & 0xf;               // 0xABCD -> 0xD
	int kk             = machine->instr & 0xff;              // 0xABCD -> 0xCD
	int nnn            = machine->instr & 0xfff;             // 0xABCD -> 0xCBD
	
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
			switch (low_byte) {
				case 0xe0:
					// CLS
			    if(DEBUG) printf("Clears the screen\n");
					disp_clear(machine);
					break;
				case 0xee:
					// RET
			    if(DEBUG) printf("Returns from a subroutine\n");
					pop(machine, &pc);
					write_pc(machine, pc);
					break;

				default:
					break;
			}
			break;

		case 0x1:	// 1nnn
			// JP addr
			if(DEBUG) printf("Jumps to address 0x%04x\n", nnn);
			write_pc(machine, nnn);
			break;

		case 0x2:	// 2nnn
			// CALL addr
			if(DEBUG) printf("Calls subroutine 0x%04x\n", nnn);
			push(machine, pc);
			write_pc(machine, nnn);
			break;

		case 0x3:	// 3xkk
			// Skip next instr if Vx == kk
			if(DEBUG) printf("Skip next if V%d==0x%04x\n", raddr_1, kk);
			pc += 2;
			if(rdata_1 == kk) write_pc(machine, pc);
			break;

		case 0x4:	// 4xkk
			// Skip next instr if Vx != kk
			if(DEBUG) printf("Skip next if V%d!=0x%04x\n", raddr_1, kk);
			pc += 2;
			if(rdata_1 != kk) write_pc(machine, pc);
			break;

		case 0x5:	// 5xy0
			// Skip next instr if Vx == Vy
			if(DEBUG) printf("Skip next if V%d==V%d\n", raddr_1, raddr_2);
			pc += 2;
			if(rdata_1 == rdata_2) write_pc(machine, pc);
			break;

		case 0x6:	// 6xkk
			// Set Vx = kk
			if(DEBUG) printf("Set V%d=0x%04x\n", raddr_1, kk);
			write_reg(machine, raddr_1, kk);
			break;

		case 0x7:	// 7xkk
			// Set Vx += kk
			if(DEBUG) printf("Set V%d+=0x%04x\n", raddr_1, kk);
			rdata_1 += kk;
			write_reg(machine, raddr_1, rdata_1);
			break;

		case 0x8:	// 8xy?
			switch (lowest_nibble) {
				case 0x0:
					// Set Vx = Vy
			    if(DEBUG) printf("Set V%d==V%d\n", raddr_1, raddr_2);
					write_reg(machine, raddr_1, rdata_2);
					break;
				case 0x1:
					// Set Vx = Vx | Vy
			    if(DEBUG) printf("Set V%d|=V%d\n", raddr_1, raddr_2);
					write_reg(machine, raddr_1, rdata_1 | rdata_2);
					break;
				case 0x2:
					// Set Vx = Vx & Vy
			    if(DEBUG) printf("Set V%d&=V%d\n", raddr_1, raddr_2);
					write_reg(machine, raddr_1, rdata_1 & rdata_2);
					break;
				case 0x3:
					// Set Vx = Vx ^ Vy
			    if(DEBUG) printf("Set V%d^=V%d\n", raddr_1, raddr_2);
					write_reg(machine, raddr_1, rdata_1 ^ rdata_2);
					break;
				case 0x4:
					// Set Vx = Vx + Vy, VF carry
			    if(DEBUG) printf("Set V%d+=V%d\n", raddr_1, raddr_2);
					res = rdata_1 + rdata_2;
					foo = (res > 255) ? 1 : 0;
					
					write_reg(machine, raddr_1, res);
					write_reg(machine, VF, foo);
					break;
				case 0x5:
					// Set Vx = Vx - Vy, VF not borrow
			    if(DEBUG) printf("Set V%d-=V%d\n", raddr_1, raddr_2);
					res = rdata_1 - rdata_2;
					foo = (rdata_1 >= rdata_2) ? 1 : 0;
					
					write_reg(machine, raddr_1, res);
					write_reg(machine, VF, foo);
					break;
				case 0x6:
					// Shift right Vx, VF borrow
			    if(DEBUG) printf("Set V%d>>=1\n", raddr_1);
					res = rdata_1 >> 0x1;
					foo = rdata_1 & 0x1;
					
					write_reg(machine, raddr_1, res);
					write_reg(machine, VF, foo);
					break;
				case 0x7:
					// Set Vx = Vy - Vx, VF not borrow
			    if(DEBUG) printf("Set V%d=V%d-V%d\n", raddr_1, raddr_2, raddr_1);
					res = rdata_2 - rdata_1;
					foo = (rdata_2 >= rdata_1) ? 1 : 0;
					
					write_reg(machine, raddr_1, res);
					write_reg(machine, VF, foo);
					break;
				case 0xe:
					// Shift left Vx, VF borrow 
			    if(DEBUG) printf("Set V%d<<=1\n", raddr_1);
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
			if(DEBUG) printf("Skip next if V%d!=V%d\n", raddr_1, raddr_2);
			pc += 2;
			if(rdata_1 != rdata_2) write_pc(machine, pc);
			break;

		case 0xA:	// Annn
			// Set value of I to nnn
			if(DEBUG) printf("Set I=0x%04x\n", nnn);
			write_I(machine, nnn);
			break;

		case 0xB:	// Bnnn
			// Jump location to nnn + V0
			if(DEBUG) printf("Jumping to 0x%04x + V0\n", nnn);
			res = nnn + V0_data;
			write_pc(machine, res);
			break;

		case 0xC:	// Cxkk
			// Set Vx = rand & kk
			if(DEBUG) printf("Set V%d = rand + 0x%04x\n", raddr_1, kk);
			res = rand() & kk;
			write_reg(machine, raddr_1, res);
			break;

		case 0xD: 	// Dxyn
			// Display n-byte sprite starting at mem I at (Vx, Vy), set VF = collision 
			if(DEBUG) printf("Drawing\n");
			draw(machine, rdata_1, rdata_2, n);
			break;

		case 0xE:	// Ex??
			switch (low_byte) {
				case 0x9e:
			    if(DEBUG) printf("key() not implemented\n");
					// Skip next instr if KEY=Vx is pressed
					// if(key() == Vx)
					break;
				case 0xA1:
			    if(DEBUG) printf("key() not implemented\n");
					// Skip next instr if KEY=Vx is not pressed
					// if(key() != Vx)
					break;
				default:
					break;
			}
			break;

		case 0xF:	// Fx??
			switch (low_byte) {
				case 0x07:
					// Set Vx = delay timer
			    if(DEBUG) printf("Vx = delay timer\n");
					write_reg(machine, raddr_1, dt_data);
					break;
				case 0x0a:
					// wait for a key press, store the value of the key in Vx
			    if(DEBUG) printf("key() not implemented\n");
					// Vx = get_key()
					break;
				case 0x15:
					// Set delay timer = Vx
			    if(DEBUG) printf("Delay timer = Vx\n");
					write_dt(machine, rdata_1);
					break;
				case 0x18:
					// Set sound timer = Vx
			    if(DEBUG) printf("Delay timer = Vx\n");
					write_st(machine, rdata_1);
					break;
				case 0x1e:
					// Set I = I + Vx
			    if(DEBUG) printf("Set I = I + Vx\n");
					res = I_data + rdata_1;
					write_I(machine, res);
					break;
				case 0x29:
					// Set I = location of sprite for digit Vx
			    if(DEBUG) printf("Not implemented\n");
					break;
				case 0x33:
					// Store BCD repr of Vx in I, I+1 and I+2
			    if(DEBUG) printf("Store BCD\n");
          read_I(machine, &res); 
          machine->RAM[res + 0] = rdata_1 / 100;
          machine->RAM[res + 1] = (rdata_1 / 10)%10;
          machine->RAM[res + 2] = rdata_1 % 10;
					break;
				case 0x55:
					// Store reg V0 through Vx in memory starting at I
			    if(DEBUG) printf("Reg dump\n");
          read_I(machine, &res); 
          for(int i = 0; i <= raddr_1; i++) {
            read_reg(machine, i, &foo);
            machine->RAM[res+i] = foo;
          }
					break;
				case 0x65:
					// Read reg V0 through Vx in memory starting at I
			    if(DEBUG) printf("Reg load\n");
          read_I(machine, &res); 
          for(int i = 0; i <= raddr_1; i++) {
            foo = machine->RAM[res+i];
            write_reg(machine, i, foo);
          }
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

	fetch(machine);
	decode_and_execute(machine);


}
