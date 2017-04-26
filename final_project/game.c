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
  int i;
  char timeStr[6];
  char scoreStr[5];
  timeStr[5] = '\0';
  scoreStr[2] = ':';
  scoreStr[4] = '\0';

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
  Asteroid_t *ASTEROIDS[MAXASTEROIDS];
  char rate = 2; // number spawning per second.
  // play the game

  Asteroid_t testAsteroid;
  testAsteroid.x = 128-11;
  testAsteroid.y = BOTTOM - 11;
  // move asteroid down right
  testAsteroid.dir = 0b00001001;
  totalAsteroids = 1;
  ASTEROIDS[0] = &testAsteroid;
  while(1){
    drawRect(11, 11, 106, 1, RED);
    drawRect(11, BOTTOM - 11, 106, 1, RED);
    drawRect(11, 11, 1, BOTTOM - 22, RED);
    drawRect(117, 11, 1, BOTTOM - 22, RED);
    // draws all Asteroids
    for(i = 0; i < totalAsteroids; i++){
      drawAsteroid(ASTEROIDS[i]);
    }
    delay(100); // used to slow down production, make dynamic
    // clears all Asteroids that are off the screen
    // moves all the other Asteroids
    for(i = 0; i < totalAsteroids; i++){
       clearAsteroid(ASTEROIDS[i]);
      if(!moveAsteroid(ASTEROIDS[i])){
      	// remove that asteroid.
      	// set current last as prevois
      	ASTEROIDS[i] = ASTEROIDS[totalAsteroids - 1];
      	totalAsteroids--;
      	drawRect(11, 11, 106, BOTTOM - 22, RED);
      }
    }
    switch(STATE){
    case MOVE: break;
    case DRAW: break;
    case END: break;
    }
    /* //if(timeChanged){ */
    /* sprintf(timeStr, "%02d", timeMin); */
    /* sprintf(timeStr+3, "%02d", timeSec); */
    /* timeStr[5] = '\0'; */
    /* timeStr[2] = ':'; */
    /* f3d_lcd_drawString(31, BOTTOM + 5, timeStr, BLACK, WHITE); */
    /* timeChanged = 0; */
    /* //} */
    /* //if(scoreChanged){ */
    /* sprintf(scoreStr, "%04d", score); */
    /* scoreStr[4] = '\0'; */
    /* f3d_lcd_drawString(104, BOTTOM + 5, scoreStr, BLACK, WHITE); */
    /* scoreChanged = 0; */
    //}
  }
}

void initGame(){
  timeChanged = 0;
  scoreChanged = 0;
  timeMin = 10;
  timeSec = 15;
  timer = 1000;

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
