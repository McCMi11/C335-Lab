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

/* Asteroid movement
 * as.dir is of form 0b0000____, where last four bits
 *   correspond to UP, RIGHT, DOWN, LEFT
 *   eg. 0b00000110 means move RIGHT and DOWN (1 pixel each)
 * as.x = as.x + (as.dir & 0b0100) - (as.dir & 0b0001);
 * as.y = as.y + (as.dir & 0b0010) - (as.dir & 0b1000);
 */

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
void clearAsteroid(Asteroid_t *a);
int moveAsteroid(Asteroid_t *a);

/*   END asteroid.h   */
