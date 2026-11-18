#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#define KEY_ONE   49
#define KEY_TWO   50
#define KEY_THREE 51
#define KEY_FOUR  52
#define KEY_Q     113
#define KEY_W     119
#define KEY_E     101
#define KEY_R     114
#define KEY_A     97
#define KEY_S     115
#define KEY_D     100
#define KEY_F     102
#define KEY_Z     122
#define KEY_X     120
#define KEY_C     99
#define KEY_V     118

void enable_game_keyboard();
void disable_game_keyboard();
 
void key(int *value);
void get_key(int *value);

void device__key(int *value);
void device__get_key(int *value);
#endif
