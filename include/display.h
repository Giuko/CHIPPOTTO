// display.h
#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "chippotto.h"

#define SCREEN_WIDTH  64
#define SCREEN_HEIGHT 32

int draw(chippotto *machine, int x, int y, int n);
int disp_clear(chippotto *machine);

#endif
