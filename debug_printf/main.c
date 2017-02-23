/*
Michael McCann- mimccann
Partner: Taylor Smith - tayjsmit


 */
#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>
#include <f3d_gyro.h>
void delay(){// copied from previous labs
  int i = 2000000;
  while(i-- > 0){
    asm("nop");
  }
}


int main(){
  f3d_uart_init();// initiates the uart driver
  f3d_led_init();// initiates the led driver for use
  f3d_user_btn_init();// initiates the button driver for use
  int i = 1;
  int j = 0;
  while(1){
    if(user_btn_read()){
      i = (i + 1) % 2;
    }
    f3d_led_on(1);
    for(j = 0; j < 15; j ++){
      printf("Hello World %d\n", j);
    }
    if(i){
      delay();
      delay();
      delay();
    }
    delay();
    f3d_led_off(1);
    delay();
  }
}


void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
