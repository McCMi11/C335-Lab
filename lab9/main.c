
/******************************************
 *
 *
 *   File: main.c
 *   Author: Michael McCann- mimccann
 *   Partner: 
 *   School: Indiana University
 *   Assignment: Lab 9
 *   Part of: labs
 *   Description: Displays images from flash
 *   Date Created: 03/23/2017
 *   Date Modified: 03/28/2017
 *   Modified By: Michael McCann
 *
 *   Revision Description:  Should be done
 *            Directions work.
 *            Changing pictors work
 *            3 working pictures, 4 too big
 *
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
// 24 bit
#include "images.h"
//8 bit
#include "pokeball.h"
#include "mario1.h"


uint16_t rgb24_to_rgb16(uint16_t, uint16_t, uint16_t);
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
  f3d_nunchuk_init();
  delay(10);
  
  uint8_t dir = 1;
  uint8_t img_toggle = 1;
  uint16_t i, k;
  uint16_t hexColor;
  uint8_t drawn = 0;
  char pixel[3];
  unsigned char *data;
  // for accel and magg
  float accel[3];
  float pitch, roll;
  // create nunchuk to be used
  struct nunchuk_data nunck;
  
  while (1) {
    if(!drawn){
      // used so when image is redrawn it clears rest
      f3d_lcd_fillScreen(WHITE);
      /*if(img_toggle == 2){
	// color wheel, touches top, under white
	data = header_data_0;
	for(i = 0; i < width*height; i++){
	  HEADER_PIXEL_1(data,pixel);
	  RGB565(pixel, &hexColor);
	  if(dir == 0) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, down);
	  else if(dir == 1) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, up);
	  else if(dir == 2) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, left);
	  else if(dir == 3) f3d_lcd_drawPixelDir((i%128),(i/height),hexColor, right);
	}
      }else*/
	if(img_toggle == 0){
	  // 8 bit mario, faces to the right
	  data = header_data_1;
	  for(k = 0; k < height; k++){
	    for(i = 0; i < width; i++){
	      HEADER_PIXEL_1(data,pixel);
	      RGB565(pixel, &hexColor);
	      if(dir == 0) f3d_lcd_drawPixelDir(i,k,hexColor, down);
	      else if(dir == 1) f3d_lcd_drawPixelDir(i,k,hexColor, up);
	      else if(dir == 2) f3d_lcd_drawPixelDir(i,k,hexColor, left);
	      else if(dir == 3) f3d_lcd_drawPixelDir(i,k,hexColor, right);
	    }
	  }
	}else
	  if(img_toggle == 2){
	    // image 2,Pokeball
	    data = header_data_2;
	    for(k = 0; k < height_2; k++){
	      for(i = 0; i < width_2; i++){
		HEADER_PIXEL_2(data,pixel);
		RGB565(pixel, &hexColor);
		if(dir == 0) f3d_lcd_drawPixelDir(i,k,hexColor, down);
		else if(dir == 1) f3d_lcd_drawPixelDir(i,k,hexColor, up);
		else if(dir == 2) f3d_lcd_drawPixelDir(i,k,hexColor, left);
		else if(dir == 3) f3d_lcd_drawPixelDir(i,k,hexColor, right);
	      }
	    }
	  }else
	    if(img_toggle == 1){
	      // image number 3, Half Dome
	      data = header_data_3;
	      // for(i = 0; i < width*height; i++){
	      for(k = 0; k < height; k++){
		for(i = 0; i < width; i++){
		  HEADER_PIXEL(data,pixel);
		  RGB565(pixel, &hexColor);
		  if(dir == 0) f3d_lcd_drawPixelDir(i,k,hexColor, down);
		  else if(dir == 1) f3d_lcd_drawPixelDir(i,k,hexColor, up);
		  else if(dir == 2) f3d_lcd_drawPixelDir(i,k,hexColor, left);
		  else if(dir == 3) f3d_lcd_drawPixelDir(i,k,hexColor, right);
		}
	      }
	      // }
	    }
      drawn = 1;
    }else{
      delay(30);
      // check for direction change
      f3d_accel_read(accel);
      pitch = atan(accel[0]/sqrt(accel[1]*accel[1]+accel[2]*accel[2]));
      roll = atan(accel[1]/sqrt(accel[0]*accel[0]+accel[2]*accel[2]));
      if(((int) (pitch * 10)) < -1){
	drawn = dir == 1;
	dir = 1;
      }else
	if(((int) (pitch * 10)) > 1){
	  drawn = dir == 0;
	  dir = 0;
	}
	else if(((int) (roll * 10)) > 1){
	  drawn = dir == 2;
	  dir = 2;
	}
	else if(((int) (roll * 10)) < -1){
	  drawn = dir == 3;
	  dir = 3;
	}
      // check for left or right on joystick
      f3d_nunchuk_read(&nunck);
      if(nunck.jx == 255){
	img_toggle = (img_toggle + 1) % 3;
	drawn = 0;
      }
      else if(nunck.jx == 0){
	img_toggle = (img_toggle + 2) % 3;
	drawn = 0;
      }
    }
  }
}

uint16_t rgb24_to_rgb16(uint16_t R, uint16_t G, uint16_t B) {
  B = ((B & 0xFF) >> 3) << 11;
  G = ((G & 0xFF) >> 2) << 5;
  R = ((R & 0xFF) >> 3);
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
