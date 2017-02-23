/******************************************
 *
 *
 *   File: main.c
 *   Author: Michael McCann  - mimccann
 *   Partner: Taylor Smith   - tayjsmit
 *   School: Indiana University
 *   Assignment: Lab 6
 *   Part of: Labs
 *   Description: Uses the LCD and displays,
 *      both graphically and in text the 
 *      values produced by the Gyro.
 *   Date Created: 02/16/17
 *   Date Modified: 02/23/17
 *   Modified By: Michael McCann
 *
 *   Revision Description:  Added Comments.
 */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_led.h> // Pull in include file for the led driver
#include <f3d_uart.h> // Pull in include file for uart driver
#include <f3d_gyro.h>  // Pull in include file for the gyro driver
#include <f3d_lcd_sd.h>  // Pull in include file for the lcd driver
#include <stdio.h>  // Pull in include file for standard input/output

#define TIMER 20000

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
void drawVertLine(uint8_t x, uint8_t y, int length){
  int i = 0;
  if (length > 0) {
    while (i < length) {
      f3d_lcd_drawPixel(x,y-i,BLACK);
      i = i+1;
    }
  } else {
    while(i < (-1*length)) {
      f3d_lcd_drawPixel(x,y+i,BLACK);
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
void drawVertBar(uint8_t x, uint8_t y, int length, int width){
  int j = 0;
  while (j < width) {
    drawVertLine(x+j,y,length);
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
void drawMiddleLine(int y) {
  int i = 0;
  while (i <= 127) {
    // colors the pixel blue at (i,y)
    // and then increments i
    f3d_lcd_drawPixel(i++,y,BLUE);
  }
}

/*****************
 *   main
 *
 *   Input: N/A
 *   Assumptions of input: N/A
 *   Guarantees about output: Draws on the screen
 *      the data from the gyro
 *   Description: Continusouly draws on the screen
 *      both a visual and textual representation of
 *      the gyroscope data.
 *
 */
int main(void) {
  //initalize stuff
  f3d_uart_init();
  f3d_led_init();
  f3d_user_btn_init();
  f3d_gyro_init();
  f3d_lcd_init();

  char output[10]; //string for snprintf() to use
  float gyro[3]; //gyro data
  /*Note: I am using snprintf to convert the gyro float value to a string*/
  while (1) {
    f3d_gyro_getdata(gyro);
    f3d_lcd_fillScreen(WHITE);
    drawMiddleLine(90); //draw the diving line at y=90

    //display X value
    snprintf(output, 10, "%f", gyro[0]);
    f3d_lcd_drawString(20,0,"X: ",BLACK,WHITE);
    f3d_lcd_drawString(35,0,output,BLACK,WHITE);

    //display Y value
    snprintf(output, 10, "%f", gyro[1]);
    f3d_lcd_drawString(20,10,"Y: ",BLACK,WHITE);
    f3d_lcd_drawString(35,10,output,BLACK,WHITE);

    //display Z value
    snprintf(output, 10, "%f", gyro[2]);
    f3d_lcd_drawString(20,20,"Z: ",BLACK,WHITE);
    f3d_lcd_drawString(35,20,output,BLACK,WHITE);
    
    //draw X line
    drawVertBar(7,90,(int) gyro[0]/10,6);//divide by 10 so it fits on the screen

    //draw Y line
    drawVertBar(61,90,(int) gyro[1]/10,6);

    //draw Z line
    drawVertBar(114,90,(int) gyro[2]/6,6);
    
    delay(100);
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
