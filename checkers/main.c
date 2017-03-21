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
// Types of moves
enum {WIN1, WIN2, MOVE, 
      RESTART, PAUSE,
      P1KING, P1REG,
      P2KING, P2REG,
      BLANK, INIT, 
      MADEMOVE, JUMP};
int STATE = INIT;
// board init
int BOARD[8][4] = {
  {P1REG, P1REG, P1REG, P1REG},
  {P1REG, P1REG, P1REG, P1REG},
  {P1REG, P1REG, P1REG, P1REG},
  {BLANK, BLANK, BLANK, BLANK},
  {BLANK, BLANK, BLANK, BLANK},
  {P2REG, P2REG, P2REG, P2REG},
  {P2REG, P2REG, P2REG, P2REG},
  {P2REG, P2REG, P2REG, P2REG}
};
// to keep track of total moves made this game
int MOVES = 0;
// to keep track of wins
int P1WINS = 0;
int P2WINS = 0;
// to keep track of number of pieces
int P1 = 12;
int P2 = 12;
int TURN = 0;

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

void drawCircle(int x0, int y0, int radius, int c, int filled){
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
    drawCircle(x0, y0, radius - 1, c, filled);
  }
}

void drawSplash(){
  f3d_lcd_fillScreen(WHITE);
}

void drawBoard(){
  int w = 8;
  int h = 8;
  int i = 0;
  int j = 0;
  
  while(i++ < 8){
    j = 0;
    while(j < 8){
      drawSquare(8*w - 8*i, 32 + 8*h - 8*j, 16, BLACK);
      j += 2;
    }
    j = 1;
    while(j < 8){
      drawSquare(8*w - 8*i, 32 + 8*h - 8*j, 16, WHITE);
      j += 2;
    }
  }
}

void drawPiece(int r, int c, int type){
  switch(type){
    case P1KING:
      drawCircle(8*r + 4, 8*c + 36, 4, RED, 1);
      break;
    case P1REG:
      drawCircle(8*r + 4, 8*c + 36, 4, RED, 1);
      break;
    case P2KING:
      drawCircle(8*r + 4, 8*c + 36, 4, BLACK, 1);
      break;
    case P2REG:
      drawCircle(8*r + 4, 8*c + 36, 4, BLACK, 1);
      break;
    }
}

void reDraw(){
  int i = 0;
  int j = 0;
  while(i++ < 8){
    j = 0;
    while(j++ < 4){
      drawPiece(i,j,BOARD[i][j]);
    }
  }
}

void wait(){
  while(!user_btn_read());
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
   int spacex = 0;
   int spacey = 0;
   int piecex = -1;
   int piecey = -1;

   // create arrays for strings
   char totMoves[5];
   char p1Wins[5];
   char p2Wins[5];
   char output1[10]; //string for snprintf() to use
   char output2[10]; //string for snprintf() to use
   char output3[10]; //string for snprintf() to use

   struct nunchuk_data nunchuck;

   //establish a blank white screen on LCD
   f3d_lcd_fillScreen(WHITE);
   drawSplash();
   // wait for user button to be pressed.
   wait();
   f3d_lcd_fillScreen(WHITE);
   drawBoard();
   while(1) {
     f3d_nunchuk_read(&nunchuck);
     if(!P1) STATE = WIN2;
     if(!P2) STATE = WIN1;

     switch(STATE){
     case INIT:
       break;
     case WIN1:
       P1WINS++;// add win to p1
       wait();
       STATE = RESTART;
       break;
       
     case WIN2:
       P2WINS++;// add win to p2
       break;
       
     case MOVE:
       if(nunchuck.c){
	 if(piecex == -1){
	   // c button pressed and no prev piece selected
	   if(TURN){
      	     if(BOARD[spacex][spacey] == P1REG || BOARD[spacex][spacey] == P1KING){
	       piecex = spacex;
	       piecey = spacey;
	       drawCircle(8*spacex + 4, 8*spacey + 36, 4, GREEN, 0);
	     }
	   }else{
	     if(BOARD[spacex][spacey] == P2REG || BOARD[spacex][spacey] == P2KING){
               piecex = spacex;
               piecey = spacey;
               drawCircle(8*spacex + 4, 8*spacey + 36, 4, GREEN, 0);
             }
	   }
	 }else{
	   // code here if there is a piece selected and c button pressed.
	 }
       }else if(nunchuck.z){
	 piecex = -1;
	 piecey = -1;
       }
       break;
       
     case MADEMOVE:
       break;
       
     case RESTART:
       for(j = 0; j < 3; j++){
	 for(k = 0; k < 4; k++){
	   BOARD[j][k] = P1REG;
	 }
       }
       for(j = 3; j < 5; j++){
	 for(k = 0; k < 4; k++){
	   BOARD[j][k] = BLANK;
	 }
       }
       for(j = 5; j < 8; j++){
         for(k = 0; k < 4; k++){
           BOARD[j][k] = P2REG;
         }
       }
       STATE = INIT;
       break;
       
     case PAUSE:
       f3d_lcd_fillScreen(WHITE);
       f3d_lcd_drawString(50, 60, "Game is paused", RED, WHITE);
       f3d_lcd_drawString(20, 70, "Press the user button to continue", BLACK, WHITE);
       wait();// wait for user button to continue
       drawBoard();
       reDraw();
       STATE = MOVE;
       break;
       
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
