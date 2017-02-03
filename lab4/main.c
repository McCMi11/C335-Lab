/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */
/* Code: */

#include <f3d_uart.h>
#include <stdio.h>
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {
  f3d_uart_init();

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  int c ;  // used to check current char value
  int wc = 0; // used to count words
  int l = 0;  // used to count lines
  int ch = 0;  // used to count chars
  int prev = 1;  // used to check what prev is, 1 = non space char, 0 = space char
  int curr = 1;  // same as prev, but used as current
  
  // runs until End of File char is found
  while((c = getchar()) != 0x1b){
    switch (c){ // will find firs true and run all until first found break below it
    case ' ':  // literal space char
    case '\t':  // literal tab char
    case '\r':  // literal carriage return char
    case '\f':  // literal from feed char
    case '\v': curr = 0;  curr = 0; break; // literal vertical tab char
    case '\n': curr = 0; l++; curr = 0; break;  // literal newline char
    default: curr = 1; // any other char
    }
    ch++; // increments char
    if(!curr && prev){  // checks for current to be space char and prev to be non space char
      wc++; // increments word count
    }
    prev = curr;  // sets previous char as current
  }

  printf("words: %d\nChars: %d\nLines: %d\n", wc, ch, l);
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
