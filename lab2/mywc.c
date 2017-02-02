/******************************************
 *
 *
 *   File: mywc.c
 *   Author: Michael McCann
 *   School: Indiana University
 *   Assignment: Lab 2
 *   Part of: Lab Assignments
 *   Description: Counts the words, chars, 
 *      and lines in a document
 *   Date Created: 01/19/2017
 *   Date Modified: 01/19/2017
 *   Modified By: Michael McCann
 *
 *   Revision Description: N/A
 */

#include <stdio.h>

/*****************
 *   main
 *   
 *   Input: N/A
 *   Assumptions of input: N/A
 *   Guarantees about output: Outputs word count
 *   Description: Will count words, chars, and lines
 *      Prints them all out with lables.
 *      Reads from standard input
 *
 *
 */


int main(int argc, char **argv){
  int c = 0;  // used to check current char value
  int wc = 0; // used to count words
  int l = 0;  // used to count lines
  int ch = 0;  // used to count chars
  int prev = 1;  // used to check what prev is, 1 = non space char, 0 = space char
  int curr = 1;  // same as prev, but used as current
  
  // runs until End of File char is found
  while((c = getchar()) != EOF){
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
  return wc;  // returns number words
}
