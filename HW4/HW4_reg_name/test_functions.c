/* Code: */

#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "regName_c.h"

void regName_test(void) {
  int error_count=0;
  int i;
  // test goes here
  for(i = 0; i < 20; i++){
    if(regName(i) != regName_c(i)){
      error_count++;
      printf("Error... Recieved: %s, Expected: %s at %d\n",regName(i), regName_c(i), i);
    }
  }
  if (!error_count) {
    printf("Reg Name Tests Passed\n");
  }
  else {
    printf("Reg Name Test: %d errors\n",error_count);
  }
}
