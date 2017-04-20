/*    START game.c    */

#include "game.h"
#include "main.h"
#include "tank.h"
#include "asteroid.h"
extern Tank_t TANK;
static unsigned char MAXASTEROIDS = 50;  // allows for 50 asteroids total
unsigned char totalAsteroids = 0; // start with 0 Asteroids
static unsigned char BOTTOM = 145; // bottom line of game
int score = 0;
unsigned int SEED = 54654;
unsigned int totalTime = 1;
void start(){
  initGame();
  float accel[3], magg[3];
  float pitch, roll, xh, yh, degrees, heading;

  f3d_accel_read(accel);
  f3d_mag_read(magg);

  //calculate pitch and roll
  pitch = atan(accel[0]/sqrt(((accel[1]) * (accel[1])) + ((accel[2]) * (accel[2]))));
  roll = atan(accel[1]/sqrt(((accel[0]) * (accel[0])) + ((accel[2]) * (accel[2]))));

  //calculate xh and yh
  xh = (magg[0] * cos(pitch)) + (magg[2] * sin(pitch));
  yh = (magg[0]*sin(roll)*sin(pitch))+(magg[1]*cos(roll))-(magg[2]*sin(roll)*cos(pitch));

  //combine xh and yh to get heading
  heading = atan(yh/xh);

  //convert heading to degrees
  degrees = (heading * 180) / 3.14159265;
  SEED +=(int) ((((float) SEED) * pitch * totalTime + roll*xh) * heading / pitch)  * totalTime;
  srand(SEED);
  int randN = 0;
  randN = rand() % (116 + 1 - 0) + 0;
  Asteroid_t ASTEROIDS[MAXASTEROIDS];
  enum {MOVE, DRAW, END};
  int STATE = DRAW;
  char rate = 2; // number spawning per second.
  // play the game

  Asteroid_t testAsteroid;
  testAsteroid.x = 0;
  testAsteroid.y = 0;
 
  while(1){
    /* SEED = SEED + ((int) ((((float) SEED) * pitch * totalTime + roll*xh) * heading / pitch)  * totalTime) % (4294967295/2); */
    /* srand(SEED); */
    /* randN = rand() % (116 + 1 - 0) + 0; */
    /* if(!(randN % 5)){ */
    /*   testAsteroid.x = randN; */
    /*   testAsteroid.y = 0; */
    /* } else if(!(randN % 4)){ */
    /*   randN = rand() % (BOTTOM-11 - 0) + 0; */
    /*   testAsteroid.y = randN; */
    /*   testAsteroid.x = 0; */
    /* }else if(!(randN % 3)){ */
    /*   randN = rand() % (BOTTOM-11 - 0) + 0; */
    /*   testAsteroid.y = randN; */
    /*   testAsteroid.x = 127-11; */
    /* }else{ */
    /*   testAsteroid.x = randN; */
    /*   testAsteroid.y = BOTTOM-11; */
    /* } */
    /* testAsteroid.col = rand() % 4; */
    /* drawAsteroid(&testAsteroid); */


    drawRect(11, 11, 106, 1, RED);
    drawRect(11, BOTTOM - 11, 106, 1, RED);
    drawRect(11, 11, 1, BOTTOM - 22, RED);
    drawRect(117, 11, 1, BOTTOM - 22, RED);
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
