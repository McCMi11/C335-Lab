/*   END asteroid.h   */

#include "asteroid.h"
#include "main.h"
extern unsigned char BOTTOM;

// makes pseudo random asteroid and adds to belt
void makeAsteroid(){
  
}
void makeMakeMultAsteroid(unsigned char n){
  while(n){
    makeAsteroid();
    n--;
  }
}
void drawAsteroid(Asteroid_t *a){
  uint8_t x = a->x;
  uint8_t y = a->y;
  uint16_t color = AsteroidColors[a->col];
  // may need to add a border to allow for this drawing method
  int offset = 0; 
  // there is an offset when the circle is too close to the bottom
  // middle 
  if(offset == 1){
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
  else{
    drawRect(x+3, y+1, 5, 9, color);
    // four edges
    drawRect(x+5, y, 1, 1, color);
    drawRect(x, y+5, 1, 1, color);
    drawRect(x+5, y+10, 1, 1, color);
    drawRect(x+10, y+5, 1, 1, color);
    // 2 sides, length 5
    drawRect(x+1, y+3, 1, 5, color);
    drawRect(x+9, y+3, 1, 5, color);
    // 2 sides, length 7
    drawRect(x+2, y+2, 1, 7, color);
    drawRect(x+8, y+2, 1, 7, color);
  }
}
void drawAllAsteroids(Asteroid_t *a, int n){
  int i = 0;
  while(n--){
    drawAsteroid(a+i);
    i++;
  }
}



/*   END asteroid.c   */
