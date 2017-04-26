/*  START main.h   */

// drivers
#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_led.h> // Pull in include file for the local drivers
//#include <f3d_uart.h>
#include <f3d_i2c.h>
#include <f3d_rtc.h>
#include <f3d_systick.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <f3d_lcd_sd.h>
#include <f3d_nunchuk.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_led.h>
#include <math.h>

/*   VARIABLES   */
char pixel[3];
uint16_t title[128];
int timer;
enum {MOVE, DRAW, END, NONGAME};
int STATE;
int timeMin;
int timeSec;
int scoreChanged;
int timeChanged;

/*   FUNCTIONS     */

void boot();
void splash();
void instructions();


/*   END main.h   */
