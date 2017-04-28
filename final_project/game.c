/*    START game.c    */

#include "game.h"
#include "main.h"
#include "tank.h"
#include "asteroid.h"


//Tank_t TANK;
uint8_t tankX, tankY;
int tankDx, tankDy;
Asteroid_t ASTEROIDS[];
static unsigned char MAXASTEROIDS = 10;  // allows for 36 asteroids total
unsigned char totalAsteroids = 10; // start with 0 Asteroids
static unsigned char BOTTOM = 145; // bottom line of game
unsigned int SEED = 54654;
unsigned int totalTime = 1;
//int nuke;
//int cycles = 0;
void start(){
  //nuke = 0;
  initGame();
  float accel[3], magg[3];
  float pitch, roll, xh, yh, degrees, heading;
  int i;

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
  char rate = 2; // number spawning per second.
  // play the game
  Asteroid_t ASTEROIDS[MAXASTEROIDS];
  for(i = 0; i < totalAsteroids; i++){
    SEED = SEED + ((int) ((((float) SEED) * pitch * totalTime + roll*xh) * heading / pitch)  * totalTime) % (4294967295/2);
    makeAsteroid(&ASTEROIDS[i]);
  }
  // set up default start location
  tankX = 75;
  tankY = 60;
  tankDx = 0;
  tankDy = 0;
  struct nunchuk_data nunck;
  f3d_nunchuk_read(&nunck);

  uint8_t nukeX, nukeY;
  while(1){
    f3d_nunchuk_read(&nunck);
    f3d_accel_read(accel);
    f3d_mag_read(magg);
    /* if(nuke == 2){ */
    /*   // create nuke */
    /*   SEED = SEED + ((int) ((((float) SEED) * pitch * totalTime + roll*xh) * heading / pitch)  * totalTime) % (4294967295/2); */
    /*   nukeX = rand() % 85 + 20; */
    /*   nukeY = rand() % 90 + 20; */
    /*   drawTank(nukeX, nukeY); */
    /* } */

    
    if(nunck.jx == 255 && tankX <= 105) tankX++;
    else if(nunck.jx == 0 && tankX >= 12) tankX--;
    if(nunck.jy == 255 && tankY >= 12) tankY--;
    else if(nunck.jy == 0 && tankY <= 122) tankY++;
    
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

    drawRect(11, 11, 106, 1, RED);
    drawRect(11, BOTTOM - 11, 106, 1, RED);
    drawRect(11, 11, 1, BOTTOM - 22, RED);
    drawRect(117, 11, 1, BOTTOM - 22, RED);
    // draws all Asteroids
    for(i = 0; i < totalAsteroids; i++){
      drawAsteroid(&ASTEROIDS[i]);
    }
    drawTank(tankX, tankY);
    delay(3); // used to slow down production, make dynamic
    // clears all Asteroids that are off the screen
    // moves all the other Asteroids
    for(i = 0; i < totalAsteroids; i++){
       clearAsteroid(&ASTEROIDS[i]);
      if(!moveAsteroid(&ASTEROIDS[i])){
      	// remove that asteroid.
      	// set current last as prevois
	SEED = SEED + ((int) ((((float) SEED) * pitch * totalTime + roll*xh) * heading / pitch)  * totalTime) % (4294967295/2);
	makeAsteroid(&ASTEROIDS[i]);
      	//drawRect(11, 11, 106, BOTTOM - 22, RED);
      }
    }
    clearTank(tankX, tankY);
    for(i = 0; i < totalAsteroids; i++){
          if(!dist(ASTEROIDS[i].x+5, tankX+5, ASTEROIDS[i].y+5, tankY+5, 10)){
           // loss
	    f3d_lcd_fillScreen(RED);
	    play();
      	    return;
        }
    }
  }
}

void initGame(){

  drawRect(0, 0, 128, BOTTOM, BLACK);
  drawRect(0, BOTTOM, 128, 160 - BOTTOM, WHITE);
  // about the center
  drawRect(0, BOTTOM, 128, 1, RED);
  f3d_lcd_drawString(1, BOTTOM + 5, "Kick Asteroid", BLACK, WHITE);
}

int dist(int x1, int x2, int y1, int y2, int allowed){
  if((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) <= allowed*allowed){
    return 0;
  }else return 1;
}

/*    END game.c    */
