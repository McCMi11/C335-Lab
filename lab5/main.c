/******************************************
 *
 *
 *   File: main.c
 *   Author: Michael McCann - mimccann
 *   Partner: Simpson, Ross - 	rosssimp, I think
 *   School: Indiana University
 *   Assignment: Lab 5
 *   Part of: Labs
 *   Description: 
 *   Date Created: 02/15/17
 *   Date Modified: 02/15/17
 *   Modified By: Michael McCann
 *
 *   Revision Description: Initial
 */
#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>

int main(void){
  f3d_led_init();// initiates the led driver for use
  f3d_user_btn_init();// initiates the button driver for use
  f3d_gyro_init();// initiates the gyro
  while(1){
    while(user_btn_read()){// while user button is being pressed.

    }
  }
}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
