/******************************************
 *
 *
 *   File: main.c
 *   Author: Michael McCann
 *   Partner: Taylor Smith   - tayjsmit
 *   School: Indiana University
 *   Assignment: Lab 7
 *   Part of: Labs
 *   Description: Calculates and displays
 *      information gathered from accelerometer
 *      and magnometer.
 *   Date Created: 2/23/17
 *   Date Modified: 2/27/17
 *   Modified By: Michael McCann
 *
 *   Revision Description: Added comment heading
 */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_led.h>
#include <stdio.h>
#include <math.h>

#define TIMER 20000
char dirr[][11] =  
  {"NORTH", "NORTH-EAST",
   "EAST", "SOUTH-EAST",
   "SOUTH", "SOUTH-WEST",
   "WEST", "NORTH-WEST"};

/*****************
 *   drawVertLine
 *
 *   Input: - uint8_t x, used to specify
 *                    x cordinate.
 *          - uint8_t y, used to specify
 *                    y start cordinate.
 *          - int length, used to say how
 *                    long the line will be.
 *   Assumptions of input: Inputs will stay on screen.
 *   Guarantees about output: Draws a line on the LCD
 *   Description: Draws a line on the LCD, starting
 *      at the given x and y.  If the length is negative,
 *      it draws the line downward, else upwards.
 *
 */
void drawVertLine(uint8_t x, uint8_t y, int length,int c){
  int i = 0;
  if (length > 0) {
    while (i < length) {
      f3d_lcd_drawPixel(x,y-i,c);
      i = i+1;
    }
  } else {
    while(i < (-1*length)) {
      f3d_lcd_drawPixel(x,y+i,c);
      i=i+1;
    }
  }
}

/*****************
 *   drawVertBar
 *
 *   Input: - uint8_t x, used to specify
 *                    x cordinate.
 *          - uint8_t y, used to specify
 *                    y start cordinate.
 *          - int length, used to say how
 *                    long the line will be.
 *          - int width, used to say how wide
 *                    the bar will be.
 *   Assumptions of input: Inputs will stay on screen.
 *   Guarantees about output: Draws a thick line on the LCD
 *   Description: Draws a bar on the LCD, starting
 *      at the given x and y.  If the length is negative,
 *      it draws the line downward, else upwards.  Uses
 *      the function drawVertLine the number of times as
 *      width
 *
 */
void drawVertBar(uint8_t x, uint8_t y, int length, int width, int c){
  int j = 0;
  while (j < width) {
    drawVertLine(x+j,y,length,c);
    j=j+1;
  }
}

/*this draws a line in the middle of the screen so we know where the middle is
  and hence know if the value is positive or negative*/

/*****************
 *   drawMiddleLine
 *
 *   Input: - int y, used to specify where to draw line
 *   Assumptions of input: y is positive
 *   Guarantees about output: a line is drawn accross
 *      the screen at posistion (*,y) for all * on the screen.
 *   Description: Draws a line in the middle of the screen
 *      at the given y value.
 *
 *
 */
void drawMiddleLine(int y, int c) {
  int i = 0;
  while (i <= 127) {
    // colors the pixel blue at (i,y)
    // and then increments i
    f3d_lcd_drawPixel(i++,y,c);
  }
}

void clearBars(){
  int i = 22;
  while(i < 90){
    drawMiddleLine(i++, WHITE);
  }
  i=160;
  while(i > 90){
    drawMiddleLine(i--, WHITE);
  }
  drawMiddleLine(90, BLUE); //draw the diving line at y=90
}

void drawRect(int c, int x, int y, int w, int h){
  int height = h;
  while(x+w >= x){
    while(y+h >= y){
      f3d_lcd_drawPixel(x+w,y+h,c);
      h--;
    }
    w--;
    h = height;
  }
}

int lightCompas(int dir){
  f3d_led_all_off();
  if(dir > -22 && dir < 22){
    f3d_led_on(1); // North
    return 0;
  }else if(dir >=22 && dir < 67){
    f3d_led_on(2); // North East
    return 1;
  }
  if(dir >= 67 && dir < 112){
    f3d_led_on(3); // East
    return 2;
  }else if(dir >= 112 && dir < 157){
    f3d_led_on(4); // South East
    return 3;
  }else if((dir >= 157 || dir <= -157)){
    f3d_led_on(5); // South
    return 4;
  }else if(dir > -67 && dir <= -22){
    f3d_led_on(0); // North West
    return 7;
  }else if(dir > -112 && dir <= -67){
    f3d_led_on(7); // West
    return 6;
  }else if(dir > -157 && dir <= -112){
    f3d_led_on(6); // South West
    return 5;
  }
}

int main(void) {
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  
  // Set up your inits before you go ahead
  f3d_uart_init();
  f3d_led_init();
  f3d_user_btn_init();
  f3d_lcd_init();
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);
  float accel[3];
  float magg[3];
  float pitch;
  float roll;
  float xh;
  float yh;
  float heading;
  char output[10]; //string for snprintf() to use
  int usr = 1; // 1 = accel, 0 = mag
  int def = 1; // 1 = drawn, 0 = not drawn
  int direct = 0;// used to store the direction
  int dir;
  int prev = 0;
  LCD_BKL_ON();
  f3d_lcd_fillScreen2(WHITE);
  drawMiddleLine(90, BLUE); //draw the diving line at y=90
  f3d_lcd_drawString(20,0,"Pitch: ",RED,WHITE);
  f3d_lcd_drawString(20,10,"Roll: %f",BLACK,WHITE);
  LCD_BKL_OFF();
  while(1){
    f3d_accel_read(accel);
    f3d_mag_read(magg);
    pitch = atan(accel[0]/sqrt(accel[1]*accel[1]+accel[2]*accel[2]));
    roll = atan(accel[1]/sqrt(accel[0]*accel[0]+accel[2]*accel[2]));
    xh = (magg[0]*cos(pitch)) + (magg[2]*sin(pitch));
    yh = (magg[0]*sin(roll)*sin(pitch))+(magg[1]*cos(roll))-(magg[2]*cos(pitch));
    heading = atan2f(yh,xh);
    if(usr){
      if(!def){
	LCD_BKL_ON();
	f3d_lcd_fillScreen2(WHITE);
	def = 1; // 1 = drawn, 0 = not drawn
	drawMiddleLine(90, BLUE); //draw the diving line at y=90
	f3d_lcd_drawString(20,0,"Pitch: ",RED,WHITE);
	f3d_lcd_drawString(20,10,"Roll: ",BLACK,WHITE);
	LCD_BKL_OFF();
      }
      //display X value
      snprintf(output, 10, "%f", pitch);
      f3d_lcd_drawString(55,0,output,RED,WHITE);
      //display Y value
      snprintf(output, 10, "%f", roll);
      f3d_lcd_drawString(55,10,output,BLACK,WHITE);
      //draw X line
      drawVertBar(39,90,(int) (pitch*40),6,RED);
      
      //draw Y line
      drawVertBar(78,90,(int) (roll*40),6,BLACK);
      clearBars();
    }else{
      if(def){
	LCD_BKL_ON();
	def = 0;
	f3d_lcd_fillScreen2(BLACK);
	f3d_lcd_drawString(20,50,"Direction:",WHITE,BLACK);
	LCD_BKL_OFF();
      }
      dir = (int)(heading * (180/3.141592));
      direct = lightCompas(dir);
      if(prev != direct){
	drawRect(BLACK, 20, 60, 90, 10);
	f3d_lcd_drawString(20,60,dirr[direct],WHITE,BLACK);
	prev = direct;
      }
    }
    delay(100);
    if(user_btn_read()){
      usr = !usr;
    }
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */

