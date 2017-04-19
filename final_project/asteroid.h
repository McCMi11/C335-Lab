/*   START asteroid.h   */

/*    Includes     */
#include <stdint.h>

/*     Variables    */
struct Asteroid { // 6 bytes (8 alligned)
  char centerX;
  char centerY;
  uint16_t color;
  char upDown;    // 1 = Up,   0 = Down
  char leftRight; // 1 = Left, 0 = Right
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
  };

struct AsteroidBelt {
  struct Asteroid *curr;
  struct AsteroidBelt *next;
};

struct AsteroidBelt ASTEROIDS;

/*    Functions     */

void makeAsteroid();
void makeMakeMultAsteroid(unsigned int n);
void addAsteroid(struct Asteroid);
void drawAsteroid(struct Asteroid *);
void drawAllAsteroids();

/*   END asteroid.h   */
