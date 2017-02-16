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
void delay(){
  int i = 2000000;
  while(i-- > 0){
    asm("nop");
  }
}

int main(void){
  f3d_uart_init();// initiates the uart driver
  f3d_led_init();// initiates the led driver for use
  f3d_user_btn_init();// initiates the button driver for use
  f3d_gyro_init();// initiates the gyro
  float ax[] = {1, 2, 3};
  float val = 0;
  int axis = 0;
  int i = 0;
  int c = 0;
  
  while(1){
    if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != (uint16_t)RESET){
      c = USART_ReceiveData(USART1);
      if(c == 'x'){
	axis = 0;
      }else if(c == 'y'){
	axis = 1;
      }else if(c == 'z'){
	axis = 2;
      }
    }
    if(user_btn_read()){
      axis = (axis + 1) % 3;
    }
    f3d_gyro_getdata(ax);
    val = ax[axis];
    printf("axis %c: %f\n", c, val);
    if(val > 50 || val < -50){
      f3d_led_on(1);
    }else{
      f3d_led_off(1);
    }
    if(val > 100){
      f3d_led_on(0);
    }else{
      f3d_led_off(0);
    }
    if(val > 150){
      f3d_led_on(7);
    }else{
      f3d_led_off(7);
    }
    if(val > 200){
      f3d_led_on(6);
    }else{
      f3d_led_off(6);
    }
    if(val > 250 || val < -250){
      f3d_led_on(5);
    }else{
      f3d_led_off(5);
    }
    if(val < -100){
      f3d_led_on(2);
    }else{
      f3d_led_off(2);
    }
    if(val < -150){
      f3d_led_on(3);
    }else{
      f3d_led_off(3);
    }
    if(val < -200){
      f3d_led_on(4);
    }else{
      f3d_led_off(4);
    }
    delay();
  }
}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
