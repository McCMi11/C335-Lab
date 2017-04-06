/*
 *   File: main.c
 *   Author: Michael McCann- mimccann
 *   Partner: Samuel Carter- sambcart
 *   School: Indiana University
 *   Assignment: Lab 10
 *   Part of: Labs
 *   Description: Turns on LED at interval, with echo
 *                using systic.
 *   Date Created: 03/30/2017
 *   Date Modified: 04/06/2017
 *   Modified By: Michael McCann
 *
 *   Revision Description:  Added comment block
 */

//#include <stdio.h>
#include <f3d_user_btn.h>
#include <f3d_systick.h>
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_delay.h>
#include <f3d_lcd_sd.h>
#include <glcdfont.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_tim.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_usart.h>
#include <stm32f30x_spi.h>

int main(void) {
    f3d_led_init();
    f3d_user_btn_init();
    f3d_uart_init();
    f3d_systick_init(100);
    // see f3d_systic in drivers
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
    while (1);
}
#endif
