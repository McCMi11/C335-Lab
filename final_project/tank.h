/*    START tank.h    */

#include <stdint.h>

/*     Variables    */
typedef struct Tank {
  uint8_t x, y;
  int dx, dy;
}Tank_t;

typedef struct Bullet {
  uint8_t x, y;
  int dx, dy;
  // square size 2x2
}Bullet_t;



/*    Functions    */

void moveTank(int X, int Y);
void rotateTank();
void drawTank(uint8_t, uint8_t);
void clearTank(uint8_t x, uint8_t y);

/*    END tank.h    */
