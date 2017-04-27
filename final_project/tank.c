/*   START tank.c   */

#include "tank.h"
#include "main.h"


void moveTank(int X, int Y){
  
}

void rotateTank(){
 
}

void drawTank(uint8_t x, uint8_t y){
  uint16_t color = GREEN;
  // may need to add a border to allow for this drawing method
  //int offset = 0; 
  // there is an offset when the circle is too close to the bottom
  // middle 
  drawRect(x+3, y+1, 5, 9, color);
  // 3 edges
  drawRect(x+5, y, 1, 1, color);
  drawRect(x, y+5, 1, 1, color);
  drawRect(x+10, y+5, 1, 1, color);
  // 2 sides, length 5
  drawRect(x+1, y+3, 1, 5, color);
  drawRect(x+9, y+3, 1, 5, color);
  // 2 sides, length 7
  drawRect(x+2, y+2, 1, 7, color);
  drawRect(x+8, y+2, 1, 7, color);
}

void clearTank(uint8_t x, uint8_t y){
  uint16_t color = BLACK;
  // may need to add a border to allow for this drawing method
  //int offset = 0; 
  // there is an offset when the circle is too close to the bottom
  // middle 
  drawRect(x+3, y+1, 5, 9, color);
  // 3 edges
  drawRect(x+5, y, 1, 1, color);
  drawRect(x, y+5, 1, 1, color);
  drawRect(x+10, y+5, 1, 1, color);
  // 2 sides, length 5
  drawRect(x+1, y+3, 1, 5, color);
  drawRect(x+9, y+3, 1, 5, color);
  // 2 sides, length 7
  drawRect(x+2, y+2, 1, 7, color);
  drawRect(x+8, y+2, 1, 7, color);
}

/*   END tank.c  */
