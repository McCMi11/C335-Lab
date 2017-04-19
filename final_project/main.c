/*  begin main.c   */

// local includes
#include "game.h"
#include "main.h"
#include "draw.h"
#include "kickAsteroid.h" // title
#include "samFinger.h" // finger


void splash(){
  struct nunchuk_data nunck;

  f3d_lcd_fillScreen(WHITE); // remove at end
  int i, k;
  uint16_t hexColor;
  char *data = kickAsteroid_data;
  char pixel[3];
  uint16_t title[128];
  for(k = 0; k < kickAsteroid_height; k++){
    for(i = 0; i < kickAsteroid_width; i++){
      KICK_ASTEROID(data, pixel);
      RGB565(pixel, &hexColor);
      title[i] = hexColor;
    }
    f3d_lcd_setAddrWindow (0,k,ST7735_width-1,k,MADCTLGRAPHICS);
    f3d_lcd_pushColor(title,ST7735_width);
  }
  
  int moved = 1; // 0 = no
  int pos = 0; // 0 = start for drawing and end for selecting
  while(1){
    // code here for selecting on menu
    //start();
    // move finger
    if(moved){
      if(pos){
	 // 106 is Start
	drawRect(0, 106, samFinger_width, samFinger_height, BLACK);
	data = samFinger_data;
	for(k = 0; k < samFinger_height; k++){
	  for(i = 0; i < samFinger_width; i++){
	    SAM_FINGER(data, pixel);
	    RGB565(pixel, &hexColor);
	    title[i] = hexColor;
	  }
	  // 123 is Instructions
	  f3d_lcd_setAddrWindow (0,k+123, samFinger_width,k+123,MADCTLGRAPHICS);
	  f3d_lcd_pushColor(title,samFinger_width);
	}
	pos = 0;
      }else{
	 // 123 is Instructions
	drawRect(0, 123, samFinger_width, samFinger_height, BLACK);
	data = samFinger_data;
	for(k = 0; k < samFinger_height; k++){
	  for(i = 0; i < samFinger_width; i++){
	    SAM_FINGER(data, pixel);
	    RGB565(pixel, &hexColor);
	    title[i] = hexColor;
	  }
	  // 106 is Start
	  f3d_lcd_setAddrWindow (0,k+106, samFinger_width,k+106,MADCTLGRAPHICS);
	  f3d_lcd_pushColor(title,samFinger_width);
	}
	pos = 1;
      }
      moved = 0;
    }else{
      f3d_nunchuk_read(&nunck);
      if(nunck.jy == 255 || nunck.jy == 0){
	moved = 1;
	delay(200);
      }
      else delay(100);
    }
    if(nunck.c) break; // exit loop, c button was pressed
  }
  // ******* NOTE pos is flipped here  ********* //
  if(pos) start(); // start game
  else instructions(); // Instructions
}

void instructions(){
  struct nunchuk_data nunck;

  f3d_lcd_fillScreen(BLACK);
  char *rules[] = {
    "Rule1",
    "RUle2",
    "rule3",
    "...",
    ""
  }; // set of fules
  int i = 0;
  while(**(rules + i)){
    f3d_lcd_drawString(5, 10*i + 5, *(rules + i), WHITE, BLACK);
    i++;
  } // draw each rule line by line, starting at line 5, each 5 from left
  while(!nunck.c) f3d_nunchuk_read(&nunck); // wait for c button to be pressed
  splash(); // go back to splash
}

int main(){
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  f3d_timer2_init();
  f3d_dac_init();
  f3d_delay_init();
  f3d_rtc_init();
  f3d_systick_init();
  f3d_uart_init();
  f3d_lcd_init();
  f3d_i2c1_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);
  
  // START GAME
  splash();
  return 0;
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t * file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif
/*  END main.c   */
