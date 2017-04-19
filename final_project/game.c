/*    START game.c    */

#include "game.h"
#include "main.h"
#include "tank.h"
#include "asteroid.h"

extern struct Tank TANK;
void start(){
  f3d_lcd_fillScreen(WHITE); // remove at end
  // set up default start location
  TANK.centerX = 64;
  TANK.centerY = 80;
  TANK.health = 100;
  // about the center
  // play the game
  while(1){

  }
}



/*    END game.c    */
