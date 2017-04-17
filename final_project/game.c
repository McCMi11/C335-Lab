/*    START game.c    */

#include "game.h"
#include "tank.h"
#include "asteroid.h"

extern struct Tank TANK;
void start(){
  // set up default start location
  TANK.centerX = 64;
  TANK.centerY = 80;
  TANK.health = 100;
  // about the center
}



/*    END game.c    */
