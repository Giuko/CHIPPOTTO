#ifdef __RAYLIB

#include "display.h"
#include "raylib.h"
#define TILE_SIZE 16
#define WIDTH_SIZE  (TILE_SIZE * SCREEN_WIDTH)
#define HEIGHT_SIZE (TILE_SIZE * SCREEN_HEIGHT)


// ------ Implementation specific functions ------

void drawTile(int x, int y, Color c){
  int posX = x * TILE_SIZE;
  int posY = y * TILE_SIZE;
  DrawRectangle(posX, posY, TILE_SIZE, TILE_SIZE, c); 
}

// ------ Implementation specific functions ------

void screen__init(){
  InitWindow(WIDTH_SIZE, HEIGHT_SIZE, "CHIPPOTTO");
}

void screen__close(){
  CloseWindow();
}

void screen__draw_row(int x, int y, uint8_t *row){
	// Each row has 8 point to draw 
  Color c;
	for(int i = 0; i < 8; i++){
    c = WHITE;
    if(row[x+i]) c = BLACK;
    drawTile(x+i, y, c);
  }	
}

void screen__disp_clear(){
  ClearBackground(WHITE);
}

#endif
