// keyboard.h
#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#define C8_KEY_ONE   49
#define C8_KEY_TWO   50
#define C8_KEY_THREE 51
#define C8_KEY_FOUR  52
#define C8_KEY_Q     113
#define C8_KEY_W     119
#define C8_KEY_E     101
#define C8_KEY_R     114
#define C8_KEY_A     97
#define C8_KEY_S     115
#define C8_KEY_D     100
#define C8_KEY_F     102
#define C8_KEY_Z     122
#define C8_KEY_X     120
#define C8_KEY_C     99
#define C8_KEY_V     118

void enable_game_keyboard();
void disable_game_keyboard();
 
void key(int *value);
void get_key(int *value);

void device__key(int *value);
void device__get_key(int *value);
#endif
