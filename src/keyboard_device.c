#ifdef __RAYLIB
#include <stdio.h>
#include "raylib.h"
#include "keyboard.h"

void device__key(int *value);
void device__get_key(int *value);

void device__key(int *value){
   if(IsKeyDown(KEY_ONE))   *value = KEY_ONE;
   if(IsKeyDown(KEY_TWO))   *value = KEY_TWO;
   if(IsKeyDown(KEY_THREE)) *value = KEY_THREE;
   if(IsKeyDown(KEY_FOUR))  *value = KEY_FOUR;
   if(IsKeyDown(KEY_Q))     *value = KEY_Q;
   if(IsKeyDown(KEY_W))     *value = KEY_W;
   if(IsKeyDown(KEY_E))     *value = KEY_E;
   if(IsKeyDown(KEY_R))     *value = KEY_R;
   if(IsKeyDown(KEY_A))     *value = KEY_A;
   if(IsKeyDown(KEY_S))     *value = KEY_S;
   if(IsKeyDown(KEY_D))     *value = KEY_D;
   if(IsKeyDown(KEY_F))     *value = KEY_F;
   if(IsKeyDown(KEY_Z))     *value = KEY_Z;
   if(IsKeyDown(KEY_X))     *value = KEY_X;
   if(IsKeyDown(KEY_C))     *value = KEY_C;
   if(IsKeyDown(KEY_V))     *value = KEY_V;
}

// Will wait till one is pressed
void device__get_key(int *value){
  int pressed = 0;
  while(pressed == 0) {
    if(IsKeyDown(KEY_ONE))  { *value = KEY_ONE;   pressed = 1;} 
    if(IsKeyDown(KEY_TWO))  { *value = KEY_TWO;   pressed = 1;} 
    if(IsKeyDown(KEY_THREE)){ *value = KEY_THREE; pressed = 1;} 
    if(IsKeyDown(KEY_FOUR)) { *value = KEY_FOUR;  pressed = 1;} 
    if(IsKeyDown(KEY_Q))    { *value = KEY_Q;     pressed = 1;} 
    if(IsKeyDown(KEY_W))    { *value = KEY_W;     pressed = 1;} 
    if(IsKeyDown(KEY_E))    { *value = KEY_E;     pressed = 1;} 
    if(IsKeyDown(KEY_R))    { *value = KEY_R;     pressed = 1;} 
    if(IsKeyDown(KEY_A))    { *value = KEY_A;     pressed = 1;} 
    if(IsKeyDown(KEY_S))    { *value = KEY_S;     pressed = 1;} 
    if(IsKeyDown(KEY_D))    { *value = KEY_D;     pressed = 1;} 
    if(IsKeyDown(KEY_F))    { *value = KEY_F;     pressed = 1;} 
    if(IsKeyDown(KEY_Z))    { *value = KEY_Z;     pressed = 1;} 
    if(IsKeyDown(KEY_X))    { *value = KEY_X;     pressed = 1;} 
    if(IsKeyDown(KEY_C))    { *value = KEY_C;     pressed = 1;} 
    if(IsKeyDown(KEY_V))    { *value = KEY_V;     pressed = 1;} 
  }
}

#endif
