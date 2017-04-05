#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "multBy5_c.h"

void multBy5_test(void) {
  int i;
  int error_count=0;
  for (i=0;i<=46;i++) {
    //printf("Fib Error: Input %d, Expected %d, Received %d\n",i,fib_c(i),fib(i));
    if (multBy5(i) != multBy5_c(i)) {
      printf("Mult by 5 Error: Input %d, Expected %d, Received %d\n",i,multBy5_c(i),multBy5(i));
      error_count++;
    }
  }
  if (!error_count) {
    printf("Mult by 5 Tests Passed\n");
  }
  else {
    printf("Mult by 5 Test: %d errors\n",error_count);
  }
}


/* test.c ends here */
