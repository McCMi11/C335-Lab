/******************************************
 *
 *
 *   File: main.c
 *   Author: Michael McCann - mimccann
 *   Partner: Bridges, Dyson - drbridge
 *   School: Indiana University
 *   Assignment: Lab 3
 *   Part of: Labs
 *   Description: Turns on and off led, allowing button interface
 *   Date Created: 01/26/17
 *   Date Modified: 01/30/17
 *   Modified By: Michael McCann
 *
 *   Revision Description:  Added comments
 */

#include <stdio.h>
#include <unistd.h>
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local led drivers
#include <f3d_user_btn.h>  // Pull in include file for the local button driver

/*****************
 *   delay
 *
 *   Input: N/A
 *   Assumptions of input: N/A
 *   Guarantees about output: delays for 10 ms
 *   Description: A simple delay function
 *
 *
 */
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

/*****************
 *   main
 *
 *   Input: N/A
 *   Assumptions of input: N/A
 *   Guarantees about output: Turns on/off led, button haults
 *   Description: A simple program that runs automatically
 *      it will start at led 0 and turn them on in an inceasing
 *      number until all are on.  Repeats proccess, but turning
 *      them off.  Button will hault this proccess.
 *
 *
 */
int main(void) {
  f3d_led_init();// initiates the led driver for use
  f3d_user_btn_init();// initiates the button driver for use

  // allows program to run without stopping
  while(1){
    int x;// used to increment through the leds
    for(x = 0; x < 8; x++){// goes through all 8 leds
      while(user_btn_read()){// checks if button is being pressed
	// if pressed it pauses and does nothing.
      }
      f3d_led_on(x);// turns on led x
      delay();// pauses the system so a change can be noticed.
    }
    for(x = 0; x < 8; x++){// repeats same as above
      while(user_btn_read()){
      }
      f3d_led_off(x);// except turns off led x
      delay();
    }  
    //--end first while
  }
  //--end main
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
