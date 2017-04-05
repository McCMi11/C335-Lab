#include <stdio.h>
#include <string.h>


int stringLength_c(char* str){
  int len = 0;
  while(*(str + len)) len++;
  return len;
}
