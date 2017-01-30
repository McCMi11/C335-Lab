/**********************************************
 *
 *
 *   File: f3d_led.c
 *   Author: Michael McCann
 *   School: Indiana University
 *   Assignment: Lab 3
 *   Part of: Labs
 *   Description: Contains inializations/functions for then leds
 *   Date Created: 01/26/17
 *   Date Modified: 01/30/17
 *   Modified By: Michael McCann
 *
 *   Revision Description:  Added comments
 */

#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <f3d_led.h>

/*****************
 *   f3d_led_init
 *
 *   Input: N/A
 *   Assumptions of input: N/A
 *   Guarantees about output: Initiates all the leds for future use
 *   Description: Will run scripts to initate all the leds for use
 *
 *
 */
void f3d_led_init(void) {
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);// starts the clock for the leds
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);// sets the structure to initiated
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; //  initializes the pin
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;// sets the mode to output
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;// sets the OType to default
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;// sets the speed, fast speed
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;// sets the led to default values
  GPIO_Init(GPIOE, &GPIO_InitStructure);// finalizes the initialization
}

/*****************
 *   f3d_led_on
 *
 *   Input: int led
 *   Assumptions of input: 0 <= led < 8
 *   Guarantees about output: Will turn on desired led
 *   Description: Turns desired led by its corresponding number
 *
 *
 */
void f3d_led_on(int led) {
  GPIOE->BSRR = GPIO_Pin_8 << led;// bitshift as many times as the led number
}

/*****************
 *   f3d_led_off
 *
 *   Input: int led
 *   Assumptions of input: 0 <= led < 8
 *   Guarantees about output: Will turn off desired led
 *   Description: Turns off desired led by its corresponding number.
 *
 *
 */
void f3d_led_off(int led) {
  GPIOE->BRR = GPIO_Pin_8 << led;// bitshift the led number to turn off the led
} 

/*Turns on all LEDs*/
/*****************
 *   f3d_led_ass_on
 *
 *   Input: N/A
 *   Assumptions of input: N/A
 *   Guarantees about output: Turns all leds on
 *   Description: Will turn all leds of
 *
 *
 */
void f3d_led_all_on(void) {
  int x;// used as the led number
  for(x = 0; x < 8; x++){// goes through all the leds
    f3d_led_on(x);// calls a function to turn on led number x
  }
 
} 

/*****************
 *   f3d_led_all_off
 *
 *   Input: N/A
 *   Assumptions of input: N/A
 *   Guarantees about output: All leds will be off
 *   Description: Turns off each led
 *
 *
 */
void f3d_led_all_off(void) {
  int x;// used to store led number
  for(x = 0; x < 8; x++){// goes through all the leds
    f3d_led_off(x);// uses the led off function to turn off led number x
  }
} 

/* led.c ends here */

