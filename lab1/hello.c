/******************************************
 *
 *
 *   File: hello.c
 *   Author: Michael McCann
 *   School: Indiana University
 *   Assignment: Lab 1
 *   Part of: Lab Assignments
 *   Description: Prints Hello World every
 *      3 seconds.  Also changes the colors
 *      of the terminal to random colors
 *   Date Created: 01/12/2017
 *   Date Modified: 01/19/2017
 *   Modified By: Michael McCann
 *
 *   Revision: Added the header and fixed
 *     some commenting to match requirements
 */

#include <stdio.h>

/*****************
 *   main()
 *
 *   Input: N/A
 *   Assumptions of input: N/A
 *   Guarantees about output: N/A, never returns
 *   Description: Will print "Hello World"
 *       infinitely every 3 seconds, changing
 *       the terminals colors each time too.
 *
 *
 */
int main(){
  while(1){ // allows to run forever
    int randomnumber; // used for storing a random number to dictate color

    randomnumber = rand() % 8; // generates the number
    
    /*
     *  Prints "Hello World"
     *
     *  %d is used as int placeholder
     * 
     *  \33[0;3%dm    --  changes font color
     *  \033[4%dm     --  changes background color
     *  \033[4;3%dm   --  changes underline color
     */
    printf("\33[0;3%dm\033[4%dm\033[4;3%dmHello World\n", randomnumber, randomnumber + 1 % 8, randomnumber + 3 % 8);
    sleep(3); // Pauses program for 3 seconds
  }
}
