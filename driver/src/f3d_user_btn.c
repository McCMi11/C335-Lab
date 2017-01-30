/******************************************
 *
 *
 *   File: f3d_user_btn.c
 *   Author: Michael McCann/
 *   School: Indiana University
 *   Assignment: Lab 3
 *   Part of: Driver files
 *   Description: contains the init and read functions for the User Button
 *   Date Created: 01/26/2017
 *   Date Modified: 01/30/2017
 *   Modified By: Michael McCann
 *
 *   Revision Description:  Added comments
 */

#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>

/*****************
 *   f3d_user_btn_init
 *
 *   Input: N/A
 *   Assumptions of input: N/A
 *   Guarantees about output: Gets the user button ready to be called in other functions
 *   Description: Initialization of the UserButton
 *
 *
 */
void f3d_user_btn_init(void){
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);//used to initialize the structure
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;// used to initialize the pin
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;// allows for user input
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;// sets the user button state to default
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);// starts the user button clock
  GPIO_Init(GPIOA, &GPIO_InitStructure);// finializes the initialization  
}

/*****************
 *   user_btn_read
 *
 *   Input: N/A
 *   Assumptions of input: N/A
 *   Guarantees about output: 1 if pressed, otherwise 0
 *   Description: Reads the user button
 *
 *
 */
int user_btn_read(void){
  return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
}
