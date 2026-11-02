#ifndef __SCREEN_H
#define __SCREEN_H

#include <stdint.h>

void screen__draw(int x, int y, int clear);
void screen__draw_row(int x, int y, uint8_t *row);
void screen__disp_clear();

#endif
