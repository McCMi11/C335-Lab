
/******************************************
 *
 *
 *   File: filename.c
 *   Author: Michael McCann- mimccann
 *   Partner: 
 *   School: Indiana University
 *   Assignment: Lab 9
 *   Part of: labs
 *   Description: Displays images from flash
 *   Date Created: 03/23/2017
 *   Date Modified: 03/27/2017
 *   Modified By: Michael McCann
 *
 *   Revision Description:  2 Working images.
 *            Directions work.
 *            Testing changing directions.
 *            Testing changing images.
 */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <stdio.h>
#include <math.h>

//images
#include "images.h"
#include "mario1.h" //8bit


int rgb24_to_rgb16(int, int, int);
void RGB565(char *, uint16_t *);
// L:R, T:B, P:L 
uint8_t right = 0b011;
uint8_t left = 0b101;
uint8_t up = 0b110;
uint8_t down = 0b000;

int main(void) { 
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_uart_init();
  f3d_lcd_init();
  f3d_delay_init();
  f3d_rtc_init();
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);
  
  int dir = 0;
  int img_toggle = 1;
  char *color;
  int i, k;
  uint16_t hexColor;
  int drawn = 0;
  char pixel[3];
  unsigned char *data = header_data;
  // for accel and magg
  float accel[3]; float magg[3];
  float pitch, roll, xh, yh;
  // create nunchuk to be used
  struct nunchuk_data nunck;
  
  while (1) {
    if(!drawn){
      // used so when image is redrawn it clears rest
      f3d_lcd_fillScreen(WHITE);
      if(img_toggle == 0){
	// color wheel, touches top, under white
	for(i = 0; i < width*height; i++){
	  HEADER_PIXEL_0(data,pixel);
	  RGB565(pixel, &hexColor);
	  if(dir == 0) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, down);
	  else if(dir == 1) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, up);
	  else if(dir == 2) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, left);
	  else if(dir == 3) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, right);
	}
      }else
	if(img_toggle == 1){
	  // 8 bit mario, faces to the right
	  for(i = 0; i < width_1; i++){
	    for(k = 0; k < height_1; k++){
	      color = header_data_cmap_1[header_data_1[i + k*128]];
	      hexColor = rgb24_to_rgb16((int) *(color), (int) *(color+1), (int) *(color+2));
	      if(dir == 0) f3d_lcd_drawPixelDir(i,k,hexColor, down);
	      else if(dir == 1) f3d_lcd_drawPixelDir(i,k,hexColor, up);
	      else if(dir == 2) f3d_lcd_drawPixelDir(i,k,hexColor, left);
	      else if(dir == 3) f3d_lcd_drawPixelDir(i,k,hexColor, right);
	    }
	  }
	}else
	  if(img_toggle == 2){
	    // image number 2
	    /*
	    for(i = 0; i < width*height; i++){
	      HEADER_PIXEL_2(data,pixel);
	      RGB565(pixel, &hexColor);
	      if(dir == 0) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, down);
	      else if(dir == 1) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, up);
	      else if(dir == 2) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, left);
	      else if(dir == 3) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, right);
	    }
	    */
	  }else
	    if(img_toggle == 3){
	      // image number 2
	      /*
	      for(i = 0; i < width*height; i++){
		HEADER_PIXEL_2(data,pixel);
		RGB565(pixel, &hexColor);
		if(dir == 0) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, down);
		else if(dir == 1) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, up);
		else if(dir == 2) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, left);
		else if(dir == 3) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, right);
	      }
	      */
	    }
      drawn = 1;
    }else{
      // check for direction change
      f3d_accel_read(accel);
      f3d_mag_read(magg);
      pitch = atan(accel[0]/sqrt(accel[1]*accel[1]+accel[2]*accel[2]));
      roll = atan(accel[1]/sqrt(accel[0]*accel[0]+accel[2]*accel[2]));
      xh = (magg[0]*cos(pitch)) + (magg[2]*sin(pitch));
      yh = (magg[0]*sin(roll)*sin(pitch))+(magg[1]*cos(roll))-(magg[2]*cos(pitch));
      heading = atan2f(yh,xh);
      if(((int) pitch * 40) < -5){
	drawn = dir == 1;
	dir = 1;
      }else
	if(((int) pitch * 40) > 5){
	  drawn = dir == 0;
	  dir = 0;
	}
	else if(((int) roll * 40) > 5){
	  drawn = dir == 2;
	  dir = 2;
	}
	else if(((int) roll * 40) < -5){
	  drawn = dir == 3;
	  dir = 3;
	}
      // check for left or right on joystick
      f3d_nunchuk_read(&nunck);
      if(nunck.jx == 255){
	dir = (dir + 1) % 4;
	drawn = 0;
      }
      else if(nunck.jx == 0){
	dir = (dir + 3) % 4;
	drawn = 0;
      }
    }
  }
}

int rgb24_to_rgb16(int R, int G, int B) {
  B = ((B & 255) >> 3) << 11;
  G = ((G & 255) >> 2) << 5;
  R = ((R & 255) >> 3);
  return ((R | G) | B);
}
void RGB565(char *pix, uint16_t *image){
  uint16_t color;
  color = rgb24_to_rgb16(pix[0], pix[1], pix[2]);
  *image = color;
}



#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif
