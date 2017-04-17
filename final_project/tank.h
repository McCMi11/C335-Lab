/*    START tank.h    */

#include <stdint.h>

/*     Variables    */
struct Tank {
  char centerX;
  char centerY;
  char health;
};

struct Tank TANK;

/*    Functions    */

void moveTank(int X, int Y);
void rotateTank();


/*    END tank.h    */
