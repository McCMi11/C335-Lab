/*   START asteroid.h   */

/*    Includes     */
#include <stdint.h>

/*     Variables    */
typedef struct Asteroid {
  uint8_t x;
  uint8_t y;
  unsigned char col;
  unsigned char dir;
}Asteroid_t;

// blue, red, yellow, white
static uint16_t AsteroidColors[] = {
  0xF800, 0x001F, 0x07FF, 0xFFFF
};

static char AsteroidLayout[] = { // circle of radius 10
//  0  1  2  3  4  5  6  7  8  9  10
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, //0
    0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, //1
    0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, //2
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, //3
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, //4
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //5
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, //6
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, //7
    0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, //8
    0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, //9
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0  //10
}; // can be drawn with 8 calls of putPixel
// col 0, col 10, row 0, row 10, 
// col 1, col 2, col 8, col 9
// and rect of (3,1) -> (7,9)



/*    Functions     */

void makeAsteroid();
void makeMakeMultAsteroid(unsigned char n);
void drawAsteroid(Asteroid_t * a);
void drawAllAsteroids();

/*   END asteroid.h   */
