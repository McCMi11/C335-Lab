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
 *   Date Modified: 03/23/2017
 *   Modified By: Michael McCann
 *
 *   Revision Description:  Initial
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
//#include "mario0.h"
#include "color_wheel.h"
#include "mario1.h"
//#include "mario2.h"

int rgb24_to_rgb16(int, int, int);
void RGB565(char *, uint16_t *);

int main(void) { 
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_uart_init();
  f3d_lcd_init();
  f3d_delay_init();
  f3d_rtc_init();
  int direction = 0;
  int img_toggle = 1;
  char *color;
  int i, j, hexColor, k;
  int drawn = 0;
  char *pixel[3];
  char *pix;
  unsigned char *data = header_data;
  uint16_t image[width*height];
  f3d_lcd_fillScreen(WHITE);
  while (1) {
    if(!drawn){
      /*
      if(img_toggle == 0){
	printf("Image 0\n");
	for(i = 0; i < width*height; i++){
	  HEADER_PIXEL(data, pixel);
	  pix = pixel;
	  RGB565(pix,&image[i]);
	}
	for(i = 0; i < width_1; i++){
	  for(k = 0; k < height_1; k++){
	    f3d_lcd_drawPixel(i,k,image[i+160*k]);
	  }
	}
	}else*/ 
      if(img_toggle == 1){
	for(i = 0; i < width_1; i++){
	  for(k = 0; k < height_1; k++){
	    color = header_data_cmap_1[header_data_1[i + k*128]];
	    hexColor = rgb24_to_rgb16((int) *(color), (int) *(color+1), (int) *(color+2));
	    f3d_lcd_drawPixel(i,k,hexColor);
	  }
	} 
      }
      drawn = 1;
    }else{
      
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
  uint16_t *color;
  *color = rgb24_to_rgb16(pix[0], pix[1], pix[2]);
  *image = *color;
}



#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */

