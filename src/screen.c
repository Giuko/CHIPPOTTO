#include "display.h"
#include "screen.h"
#include <stdint.h>
#include <stdio.h>

// This file define how effectivly the output is displayed

void screen__draw(int x, int y, int clear){
	char c;
	if(x >= SCREEN_WIDTH)  x = SCREEN_WIDTH - 1;
	if(x < 0)              x = 0;

	if(y >= SCREEN_HEIGHT) y = SCREEN_HEIGHT - 1;
	if(y < 0)              y = 0;
	
	// Since in Unix Terminal (0;0) is equal to (1;1) shift everything to +1
	x++;
	y++;
	c = (clear) ? ' ' : '*';
	printf("\033[%d;%dH%c", x, y, c);
}

void screen__draw_row(int x, int y, uint8_t *row){
	// Each row has 8 point to draw 
	char c;
	for(int i = 0; i < 8; i++){
		c = (row[i]) ? '*' : ' ';
		printf("\033[%d;%dH%c", x+i, y, c);
	}
}

void screen__disp_clear(){
	printf("\e[1;1H\e[2J");
}
