/*  begin main.c   */

// local includes
#include "game.h"
#include "main.h"

void splash(){
  // code here for splash
  while(1){
    // code here for selecting on menu
    start();
  }
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
