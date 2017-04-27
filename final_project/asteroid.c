/*   END asteroid.h   */

#include "asteroid.h"
#include "main.h"
extern unsigned char BOTTOM;
extern unsigned int SEED;
// makes pseudo random asteroid and adds to belt
void makeAsteroid(Asteroid_t *a){
  srand(SEED);
  int randN = rand() % 4;
  int randX = rand() % 117;
  int randY = rand() % 134;
  if (randN == 0) {
    // TOP
    a->y = 0;
    a->x = randX;
    a->dx = 0;
    a->dy = 1;
  } else if (randN == 1) {
    // RIGHT
    a->y = randY;
    a->x = 116;
    a->dx = -1;
    a->dy = 0;
  } else if (randN == 2){
    // BOTTOM
    a->y = 133;
    a->x = randX;
    a->dx = 0;
    a->dy = -1;
  } else{
    // LEFT
    a->y = randY;
    a->x = 0;
    a->dx = 1;
    a->dy = 0;
  }
  a->col = rand() % 4;
}
void makeMakeMultAsteroid(unsigned char n){
}
void clearAsteroid(Asteroid_t *a){
  uint8_t x = a->x;
  uint8_t y = a->y;
  //uint16_t color = AsteroidColors[a->col];
  // may need to add a border to allow for this drawing method
  //int offset = 0; 
  // there is an offset when the circle is too close to the bottom
  // middle 
  drawRect(x+3, y+1, 5, 9, BLACK);
  // 3 edges
  drawRect(x+5, y, 1, 1, BLACK);
  drawRect(x, y+5, 1, 1, BLACK);
  drawRect(x+10, y+5, 1, 1, BLACK);
  // 2 sides, length 5
  drawRect(x+1, y+3, 1, 5, BLACK);
  drawRect(x+9, y+3, 1, 5, BLACK);
  // 2 sides, length 7
  drawRect(x+2, y+2, 1, 7, BLACK);
  drawRect(x+8, y+2, 1, 7, BLACK);
}
void drawAsteroid(Asteroid_t *a){
  uint8_t x = a->x;
  uint8_t y = a->y;
  uint16_t color = AsteroidColors[a->col];
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
void drawAllAsteroids(Asteroid_t *a, int n){
  int i = 0;
  while(n--){
    drawAsteroid(a+i);
    i++;
  }
}

int moveAsteroid(Asteroid_t *a){
  a->x = a->x + a->dx;
  a->y = a->y + a->dy;
  // return 1 if no error
  // return 0 if error, meaning off screen
  if(a->x > 117 || a->y > 145 - 11) return 0;
  else return 1;

}



/*   END asteroid.c   */
