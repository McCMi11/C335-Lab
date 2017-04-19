/*    START game.c    */

#include "game.h"
#include "main.h"
#include "tank.h"
#include "asteroid.h"

extern struct Tank TANK;
extern struct AsteroidBelt ASTROIDS;

void start(){
  enum {MOVE, DRAW, END};
  f3d_lcd_fillScreen(WHITE); // remove at end
  // set up default start location
  TANK.centerX = 64;
  TANK.centerY = 80;
  TANK.health = 100;
  // about the center
  ASTEROIDS.curr = NULL;
  ASTEROIDS.next = NULL;

  int STATE = DRAW;
  char rate = 2; // number spawning per second.
  // play the game
  while(1){
    switch(STATE){
      case MOVE: break;
      case DRAW: break;
      case END: break;
    }
  }
}



/*    END game.c    */
