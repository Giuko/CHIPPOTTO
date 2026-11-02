#include "display.h"
#include "chippotto.h"
#include "screen.h"
#include <stdint.h>
#include <stdio.h>

// This define the middleman between the chippotto specification 
// and the used implementation to display the output

uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];

const int font[] = {0xf0, 0x90, 0x90, 0x90, 0xf0,
                    0x20, 0x60, 0x20, 0x20, 0x70,
                    0xf0, 0x10, 0xf0, 0x80, 0xf0,
                    0xf0, 0x10, 0xf0, 0x10, 0xf0,
                    0x90, 0x90, 0xf0, 0x10, 0x10,
                    0xf0, 0x80, 0xf0, 0x10, 0xf0,
                    0xf0, 0x80, 0xf0, 0x90, 0xf0,
                    0xf0, 0x10, 0x20, 0x40, 0x40,
                    0xf0, 0x90, 0xf0, 0x90, 0xf0,
                    0xf0, 0x90, 0xf0, 0x10, 0xf0,
                    0xf0, 0x90, 0xf0, 0x90, 0x90,
                    0xe0, 0x90, 0xe0, 0x90, 0xe0,
                    0xf0, 0x80, 0x80, 0x80, 0xf0,
                    0xe0, 0x90, 0x90, 0x90, 0xe0,
                    0xf0, 0x80, 0xf0, 0x80, 0xf0,
                    0xf0, 0x80, 0xf0, 0x80, 0x80};

int draw(chippotto *machine, int x, int y, int n){
	// Width of 8 pixels and height of n pixels
	if(machine == NULL) return -1;
	
	int idx; 
	uint8_t RAM_byte;
	read_I(machine, &idx);
	int collision = 0;

	for(int i = 0; i < n; i++){
		// I = height
		if((i + y) >= SCREEN_HEIGHT) continue;
		RAM_byte = machine->RAM[idx+i];
		
		for(int j = 0; j < 8; j++){
			// J = width
			if((j + x) >= SCREEN_WIDTH) continue;
			int current_collision;
			int k = 8 - j - 1;
			int current_bit = (RAM_byte & (1 << k)) >> k;
			current_collision = screen[i][j] & current_bit;    // If both 1 collision = 1
			collision |= current_collision;
			screen[i+y][j+x] = (!current_collision) & current_bit;
		}
		screen__draw_row(x, y, screen[i+y]);
	}

	write_reg(machine, VF, collision);
	return 0;
}

int disp_clear(chippotto *machine){
	if(machine == NULL) return -1;

	for(int i = 0; i < SCREEN_HEIGHT; i++)
		for(int j = 0; j < SCREEN_WIDTH; j++)
			screen[i][j] = 0;
	screen__disp_clear();

	return 0;
}
