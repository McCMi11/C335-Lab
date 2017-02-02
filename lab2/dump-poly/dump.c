// partner Yixuan Wang

/******************************************
 *
 *
 *   File: dump.c
 *   Author: Michael McCann ( Copied from course website )
 *   School: Indiana University
 *   Assignment: Lab 2
 *   Part of: Lab Assignments
 *   Description: Prints out the data in different data types
 *      also uses byte allignment
 *   Date Created: 01/19/2017
 *   Date Modified: 01/25/2017
 *   Modified By: Michael McCann
 *
 *   Revision Description: Added comments
 */
#include <stdio.h>
void dump_memory(void *p, int len)
{
  int i;  // used to increment through the array
  int c; // Used to calculate the unsigned char
  printf("address\t\t char\t hexCH\t short\t integer\t float\t\t doubleFloat\n");
  for (i = 0; i < len; i++) {
    c =*(unsigned char *)(p+i);
    if(!(isprint((char)c))){
      c = '?';  // changes any unprintable character to the question mark
    }
    // prints the single byte chuncks( address, char, hecCH )
    printf("%8p\t %c\t 0x%x\t", p+i, c, *(unsigned char *)(p+i) & 0xff);
    if(i % 2 == 0){//  prints the double byte chunks on even blocks( short )
      printf(" +%hu\t",  *(unsigned int *)(p+i));
    }
    // prints the quad byte chunks on multiple of 4 blocks ( integer, float )
    if(i % 4 == 0){
      printf("+%d\t %g\t", *(unsigned int *)(p+i), *(float *)(p+i));
    }
    if(i % 8 == 0){// prints out the 8 byte chunks on multpile of 8 blocks ( double )
      printf("%g", *(double *)(p+i));
    }
    printf("\n");// adds newline after it printed everything
  }
}
