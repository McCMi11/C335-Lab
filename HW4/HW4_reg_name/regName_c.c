#include <stdio.h>
#include <string.h>
#include "regName_c.h"
const char *names[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"};
//char names[][4] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"};
char *regName_c(unsigned int x){
  if(x > 15) return 0;
  return names[x];
}
