/*   START asteroid.h   */

/*    Includes     */
#include <stdint.h>

/*     Variables    */
// Let an Asteroid be a unint16_t
// such 0b1 is dir up 0b0 is  down
//      0b10 is dir down
//      0b11100 is color, allows for 8 colors
//      0b11100000 is health, out of 8
//      0b111100000000 is posn y
//      0b1111000000000000 is posn x

/* struct Asteroid { // 6 bytes (8 alligned) */
/*   char centerX; */
/*   char centerY; */
/*   uint16_t color; */
/*   char upDown;    // 1 = Up,   0 = Down */
/*   char leftRight; // 1 = Left, 0 = Right */
/* }; */

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
void drawAsteroid(uint16_t * a);
void drawAllAsteroids();

/*   END asteroid.h   */
