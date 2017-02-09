/************************** 
 *f3d_uart.c 
 *contains the initialization basic i/o functions for UART
****************************/ 

/* Code: */

#include <stm32f30x.h>
#include <f3d_uart.h>
//the initialization function to call
void f3d_uart_init(void) {
  //TX
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC,&GPIO_InitStructure); 

  //RX
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC,&GPIO_InitStructure); 
  
  //4.1 Alternate Function
  GPIO_PinAFConfig(GPIOC,4,GPIO_AF_7);
  GPIO_PinAFConfig(GPIOC,5,GPIO_AF_7);
  
  // UART init
  USART_InitTypeDef USART_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1 ,&USART_InitStructure);
  USART_Cmd(USART1 , ENABLE);
}
/*****************
 *   putchar
 *   
 *   Input: integer, used a char
 *   Assumptions of input: must be a valid char
 *   Guarantees about output: sends the int (the char)
 *   Description: Sends the desired char and returns 0
 *
 *
 */
int putchar(int c) {
  // makes sure the pin isnt being used already
  while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == (uint16_t)RESET){
    
  }
  USART_SendData(USART1, (char) c);// sends the char
  return 0;// returns 0, identicating success
} 
/*****************
 *   getchar
 *   
 *   Input: N/A
 *   Assumptions of input: N/A
 *   Guarantees about output: will output an int, which is a char
 *   Description: Waits until a char is recieved and returns it
 *
 *
 */
int getchar(void) {
  int c;// used to store the char
  // makes sure the pin isnt being used already
  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == (uint16_t)RESET){

  }
  // gets the char
  c = USART_ReceiveData(USART1);
  return c;// returns the char
}
/*****************
 *   function putstring
 *   
 *   Input: - pointer to a char, used as a string to send
 *   Assumptions of input: array that ends with null char
 *   Guarantees about output: sends every char until null char is found
 *   Description: Sends an entire string through putchar
 *
 *
 */
void putstring(char *s) {
  int i = 0;// used to increment
  while(*(s+i)){// loops until null char
    putchar((int) *(s+i));// sends char at posistion i
    i++;// adds one to i, to go to next char
  }
}



/* f3d_uart.c ends here */
