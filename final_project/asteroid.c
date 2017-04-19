/*   END asteroid.h   */

#include "asteroid.h"
#include "main.h"

// makes pseudo random asteroid and adds to belt
void makeAsteroid(){

}
void makeMakeMultAsteroid(unsigned char n){
  while(n){
    makeAsteroid();
    n--;
  }
}
void drawAsteroid(uint16_t *a){
  uint8_t x = (*a >> 12) & 0b1111;
  uint8_t y = (*a >> 8) & 0b1111;
  uint16_t color = AsteroidColors[(*a >> 2) & 0b11];
  /* uint8_t x = 50; */
  /* uint8_t y = 50; */
  /* uint16_t color =  */
  // add clear if needed.
  // may need to add a border to allow for this drawing method
  
  // middle
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
void drawAllAsteroids(){
  /* struct AsteroidBelt *curr = &ASTEROIDS; */
  /* while((curr->curr) != NULL){ */
  /*   drawAsteroid(curr->curr); */
  /*   curr = curr->next; */
  /* } */
}



/*   END asteroid.c   */
