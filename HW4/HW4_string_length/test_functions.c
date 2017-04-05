#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "stringLength_c.h"

void stringLength_test(void) {
  int error_count=0;
  int i;
  char str[75];
  for(i = 0; i < 75; i++) str[i] = 0;
  // test code here
  for(i = 0; i < 74; i++){
    str[i] = (char)('a' + (i % 26));
    if(stringLength(str) != stringLength_c(str)){
      error_count++;
      printf("String Length error: stringLength() = %d, expected stringLength_c() = %d\n", stringLength(str), stringLength_c(str));
    }
  }
  if (!error_count) {
    printf("String Length Tests Passed\n");
  }
  else {
    printf("String Length Test: %d errors\n",error_count);
  }
}


/* test.c ends here */
