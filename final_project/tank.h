/*    START tank.h    */

#include <stdint.h>

/*     Variables    */
typedef struct Tank {
  char centerX;
  char centerY;
  char health;
}Tank_t;

Tank_t TANK;

/*    Functions    */

void moveTank(int X, int Y);
void rotateTank();


/*    END tank.h    */
