/*    START game.c    */

#include "game.h"
#include "main.h"
#include "tank.h"
#include "asteroid.h"

extern struct Tank TANK;
static unsigned char MAXASTEROIDS = 50;  // allows for 50 asteroids total
unsigned char totalAsteroids = 0; // start with 0 Asteroids
static unsigned char BOTTOM = 145; // bottom line of game
int score = 0;

void start(){
  initGame();

  uint16_t ASTEROIDS[MAXASTEROIDS];
  enum {MOVE, DRAW, END};
  int STATE = DRAW;
  char rate = 2; // number spawning per second.
  // play the game

  uint16_t testAsteroid = 0b0111011111101011;
  drawAsteroid(&testAsteroid);
  while(1){
    switch(STATE){
      case MOVE: break;
      case DRAW: break;
      case END: break;
    }
  }
}

void initGame(){
  drawRect(0, 0, 128, BOTTOM, BLACK);
  drawRect(0, BOTTOM, 128, 160 - BOTTOM, WHITE);
  // set up default start location
  TANK.centerX = 64;
  TANK.centerY = 80;
  TANK.health = 100;
  // about the center
  drawRect(0, BOTTOM, 128, 1, RED);
  // time (5,150) -> (30,150)
  f3d_lcd_drawString(1, BOTTOM + 5, "Time:", BLACK, WHITE);
  f3d_lcd_drawString(31, BOTTOM + 5, "00:00", BLACK, WHITE);
  
  // divide time and total
  drawRect(63, BOTTOM, 3, 160 - BOTTOM, RED);

  // total (60,150) -> (90,150)
  f3d_lcd_drawString(68, BOTTOM + 5, "Total:", BLACK, WHITE);
  f3d_lcd_drawString(104, BOTTOM + 5, "0000", BLACK, WHITE);
}



/*    END game.c    */
