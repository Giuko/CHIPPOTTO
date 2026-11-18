#include "keyboard.h"
#include <termios.h>
#include <stdio.h>
#define TERMIOS_SETTING (ICANON|ECHO)

#ifndef __RAYLIB
// Still not implemented outside RAYLIB
void device__key(int *value){}
void device__get_key(int *value){}
#endif

void enable_game_keyboard(){
	struct termios settings;
	printf("\033[?25l");                    // Hide cursor
	fflush(stdout);
	tcgetattr(0, &settings);
	settings.c_lflag &= ~TERMIOS_SETTING;
	tcsetattr(0, 0, &settings);
}

void disable_game_keyboard(){
	struct termios settings;
	tcgetattr(0, &settings);
	settings.c_lflag |= TERMIOS_SETTING;
	tcsetattr(0, 0, &settings);
	printf("\033[?25h");                   // Show cursor
	fflush(stdout);
}

void key(int *value){
  device__key(value);
}

void get_key(int *value){
  device__get_key(value);
}
