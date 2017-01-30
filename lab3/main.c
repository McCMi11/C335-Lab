#include <stdio.h>
#include <unistd.h>
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_user_btn.h>
//#include <stm32f30x_rcc.o>
//#include < stm32f30x_gpio.o> 

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {
  f3d_led_init();
  f3d_user_btn_init();


  while(1){
    int x;
    for(x = 0; x < 8; x++){
      while(user_btn_read()){
      }
      f3d_led_on(x);
      delay();
    }
    for(x = 0; x < 8; x++){
      while(user_btn_read()){
      }
      f3d_led_off(x);
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
