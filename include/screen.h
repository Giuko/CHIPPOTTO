#ifndef __SCREEN_H
#define __SCREEN_H

#include <stdint.h>

void screen__init();
void screen__close();
void screen__draw_row(int x, int y, uint8_t *row);
void screen__disp_clear();

#endif
