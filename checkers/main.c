/* 
* Filename: main.c
* Description:
* Author:
* Maintainer:
* Created: Thu Jan 10 11:23:43 2013
*/

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_gyro.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_led.h>
#include <stdio.h>
#include <math.h>
#include <f3d_nunchuk.h>

#define TIMER 20000
/*  Used to keep track of posistions
 *  Red is 1,2
 *  Black is 3,4
 *  1,3 is for normal
 *  2,4 is for kings
*/
int BOARD[][4] = {
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0}
};

int MOVES = 0;
int P1 = 0;
int P2 = 0;

//  used for player names, max 8 char.
char PLAYER1[9] = "Player 1";
char PLAYER2[9] = "Player 2";


void drawVertLine(uint8_t x, uint8_t y, int length, int c){
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

void drawVertBar(uint8_t x, uint8_t y, int length, int width, int c){
  int j = 0;
  while (j < width) {
    drawVertLine(x+j,y,length, c);
    j=j+1;
  }
}

void drawMiddleLine(int y) {
  int i = 0;
  while (i <= 127) {
    // colors the pixel blue at (i,y)
    // and then increments i
    f3d_lcd_drawPixel(i++,y,BLUE);
  }
}

void drawRect(int x, int y, int w, int h, int c){
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

void drawSquare(int x, int y, int side, int c){
  drawRect(x, y, side, side, c);
}

void drawcircle(int x0, int y0, int radius, int c, int filled){
  int x = radius;
  int y = 0;
  int err = 0;
  int i;
  
  if(radius <= 0){
    return;
  }
  while(x >= y){
    f3d_lcd_drawPixel(x0 + x, y0 + y, c);
    f3d_lcd_drawPixel(x0 + y, y0 + x, c);
    f3d_lcd_drawPixel(x0 - y, y0 + x, c);
    f3d_lcd_drawPixel(x0 - x, y0 + y, c);
    f3d_lcd_drawPixel(x0 - x, y0 - y, c);
    f3d_lcd_drawPixel(x0 - y, y0 - x, c);
    f3d_lcd_drawPixel(x0 + y, y0 - x, c);
    f3d_lcd_drawPixel(x0 + x, y0 - y, c);
    
    if(err <= 0){
      y += 1;
      err += 2*y + 1;
    }else{
      x -= 1;
      err -= 2*x + 1;
    }
  }
  if(filled){
    drawcircle(x0, y0, radius - 1, c, filled);
  }
}

void drawBoard(){
  int w = 8;
  int h = 8;
  int i, j;
  
  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j+= 2){
      drawSquare(8*w - 8*i, 32 + 8*h - 8*j, 16, BLACK);
    }
    for(j = 1; j < 8; j+= 2){
      drawSquare(8*w - 8*i, 32 + 8*h - 8*j, 16, WHITE);
    }
  }
}

int main(void) {
   setvbuf(stdin, NULL, _IONBF, 0);
   setvbuf(stdout, NULL, _IONBF, 0);
   setvbuf(stderr, NULL, _IONBF, 0);

  // Set up your inits before you go ahead

   f3d_uart_init();
   f3d_lcd_init();
   f3d_led_init();
   f3d_user_btn_init();
   f3d_gyro_init();

   //initialize with delays
   f3d_i2c1_init();
   delay(10);
   f3d_accel_init();
   delay(10);
   f3d_mag_init();
   delay(10);
   f3d_nunchuk_init();
   delay(10);

   //create floats for the accel, mag, and gyro
   float a[3];
   float m[3];
   float i[3];

   //create floats for the compass computations
   float pitch, roll, heading, xh, yh, degrees;
   float pitchnun, rollnun;

   //create ints for various loops and calls throughout
   int j, k;
   int x, y, xnun, ynun;
   int button = 0;

   char output1[10]; //string for snprintf() to use
   char output2[10]; //string for snprintf() to use
   char output3[10]; //string for snprintf() to use

   struct nunchuk_data test;

   //establish a blank white screen on LCD
   f3d_lcd_fillScreen(WHITE);
   drawBoard();
   while(1) {
     
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
