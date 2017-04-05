#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "maxArray_c.h"

void maxArray_test(void) {
  int error_count=0;
  int i = 0;
  unsigned int list[30] = 
    {
      1, 50, 9, 7, 100,
      1, 87, 20, 44, 4,
      88, 14, 102, 103,
      47, 55, 58, 105,
      45, 50, 66, 10,
      41, 501, 545, 5,
      41, 55, 10, 600
    };
  for(i = 0; i < 30; i++){
    // test code here
    if(maxArray(list, i) != maxArray_c(list, i)){
      error_count++;
      printf("Max Array error: recieved %d, expected  %d\n",maxArray(list, i), maxArray_c(list, i));
    }
  }
  if (!error_count) {
    printf("Max Array Tests Passed\n");
  }
  else {
    printf("Max Array Test: %d errors\n",error_count);
  }
}


/* test.c ends here */
