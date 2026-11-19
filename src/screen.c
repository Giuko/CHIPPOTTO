// screen.c
#ifndef __RAYLIB

#include "display.h"
#include "screen.h"
#include <stdint.h>
#include <stdio.h>

// This file define how effectivly the output is displayed

void screen__init(){}
void screen__close(){}
void screen__draw_row(int x, int y, uint8_t *row){
	// Each row has 8 point to draw 
	for(int i = 0; i < 8; i++){
    if(row[x+i])
		  printf("\033[%d;%dH█", y, x+i);
    else
		  printf("\033[%d;%dH ", y, x+i);
	}
	fflush(stdout);
}

void screen__disp_clear(){
	printf("\e[1;1H\e[2J");
	fflush(stdout);
}

#endif
