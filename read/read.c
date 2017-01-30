#include <stdio.h>
#include "buf.h"
#include <unistd.h>

int main (int argc, char *argv[]) {
  
  int check;
  char c;
  
  sleep(5);
  check = buf_init();
  if (!check) {
    printf("Creating buffer error\n");
    return 1;
  }
  
  while(1) {
    check = buf_get(&c);
    if (c == 'q') break;
    if (!check) continue;
    putchar(c);
  }
  if(c == 'q') {
    printf("\n");
  }
  check = buf_destroy();
  if (!check) {
	 printf("ERROR destroying storage\n");
  }
  return 0;
}
