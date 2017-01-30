#include <stdio.h>
#include "buf.h"

int main (int argc, char *argv[]) {
  
  int check;
  char c;
  
  check = buf_init();
  if (!check) {
    printf("Creating buffer error\n");
    return 1;
  }
  
  printf("Terminating character: q.\nEnter expression\n");
  c = getchar();
  if(check == -1) {
    printf("Creating buffer error\n");
    return 1;
  }

  while(c != 'q') {
    check = buf_put(c);
    if (!check) continue;
    c = getchar();
  }

  do {
    check = buf_put(c);
  } while(check == 0);
  
  return 0;
}