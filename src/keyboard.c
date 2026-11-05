#include "keyboard.h"
#include <termios.h>
#include <stdio.h>
#define TERMIOS_SETTING (ICANON|ECHO)

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
