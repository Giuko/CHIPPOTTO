// keyboard_device.c
#ifdef __RAYLIB
#include <stdio.h>
#include "raylib.h"
#include "keyboard.h"

void device__key(int *value);
void device__get_key(int *value);

void device__key(int *value){
  *value = -1;
  if(IsKeyDown(KEY_ONE))   *value = C8_KEY_ONE;
  if(IsKeyDown(KEY_TWO))   *value = C8_KEY_TWO;
  if(IsKeyDown(KEY_THREE)) *value = C8_KEY_THREE;
  if(IsKeyDown(KEY_FOUR))  *value = C8_KEY_FOUR;
  if(IsKeyDown(KEY_Q))     *value = C8_KEY_Q;
  if(IsKeyDown(KEY_W))     *value = C8_KEY_W;
  if(IsKeyDown(KEY_E))     *value = C8_KEY_E;
  if(IsKeyDown(KEY_R))     *value = C8_KEY_R;
  if(IsKeyDown(KEY_A))     *value = C8_KEY_A;
  if(IsKeyDown(KEY_S))     *value = C8_KEY_S;
  if(IsKeyDown(KEY_D))     *value = C8_KEY_D;
  if(IsKeyDown(KEY_F))     *value = C8_KEY_F;
  if(IsKeyDown(KEY_Z))     *value = C8_KEY_Z;
  if(IsKeyDown(KEY_X))     *value = C8_KEY_X;
  if(IsKeyDown(KEY_C))     *value = C8_KEY_C;
  if(IsKeyDown(KEY_V))     *value = C8_KEY_V;
}

// Will wait till one is pressed
void device__get_key(int *value){
  *value = -1;

  while(*value < 0 && !WindowShouldClose()){
    PollInputEvents();
    if(IsKeyDown(KEY_ONE))   *value = C8_KEY_ONE;
    if(IsKeyDown(KEY_TWO))   *value = C8_KEY_TWO;
    if(IsKeyDown(KEY_THREE)) *value = C8_KEY_THREE;
    if(IsKeyDown(KEY_FOUR))  *value = C8_KEY_FOUR;
    if(IsKeyDown(KEY_Q))     *value = C8_KEY_Q;
    if(IsKeyDown(KEY_W))     *value = C8_KEY_W;
    if(IsKeyDown(KEY_E))     *value = C8_KEY_E;
    if(IsKeyDown(KEY_R))     *value = C8_KEY_R;
    if(IsKeyDown(KEY_A))     *value = C8_KEY_A;
    if(IsKeyDown(KEY_S))     *value = C8_KEY_S;
    if(IsKeyDown(KEY_D))     *value = C8_KEY_D;
    if(IsKeyDown(KEY_F))     *value = C8_KEY_F;
    if(IsKeyDown(KEY_Z))     *value = C8_KEY_Z;
    if(IsKeyDown(KEY_X))     *value = C8_KEY_X;
    if(IsKeyDown(KEY_C))     *value = C8_KEY_C;
    if(IsKeyDown(KEY_V))     *value = C8_KEY_V;
  }
}

#endif
