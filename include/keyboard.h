// keyboard.h
#ifndef __KEYBOARD_H
#define __KEYBOARD_H

// keyboard.h  (Chip-8 key index for each physical key)
#define C8_KEY_ONE   0x1
#define C8_KEY_TWO   0x2
#define C8_KEY_THREE 0x3
#define C8_KEY_FOUR  0xC
#define C8_KEY_Q     0x4
#define C8_KEY_W     0x5
#define C8_KEY_E     0x6
#define C8_KEY_R     0xD
#define C8_KEY_A     0x7
#define C8_KEY_S     0x8
#define C8_KEY_D     0x9
#define C8_KEY_F     0xE
#define C8_KEY_Z     0xA
#define C8_KEY_X     0x0
#define C8_KEY_C     0xB
#define C8_KEY_V     0xF

void enable_game_keyboard();
void disable_game_keyboard();
 
void key(int *value);
void get_key(int *value);

void device__key(int *value);
void device__get_key(int *value);
#endif
