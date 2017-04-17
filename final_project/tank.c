/*   START tank.c   */

#include "tank.h"
#include "main.h"


void moveTank(int X, int Y){
  
}

void rotateTank(){
  float accel[3], magg[3];
  float pitch, roll, xh, yh, degrees, heading;

  f3d_accel_read(accel);
  f3d_mag_read(magg);

  //calculate pitch and roll
  pitch = atan(accel[0]/sqrt(((accel[1]) * (accel[1])) + ((accel[2]) * (accel[2]))));
  roll = atan(accel[1]/sqrt(((accel[0]) * (accel[0])) + ((accel[2]) * (accel[2]))));

  //calculate xh and yh
  xh = (magg[0] * cos(pitch)) + (magg[2] * sin(pitch));
  yh = (magg[0]*sin(roll)*sin(pitch))+(magg[1]*cos(roll))-(magg[2]*sin(roll)*cos(pitch));

  //combine xh and yh to get heading
  heading = atan(yh/xh);

  //convert heading to degrees
  degrees = (heading * 180) / 3.14159265;
}


/*   END tank.c  */
