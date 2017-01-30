#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/stat.h>
#include "buf.h"

#define SIZE 10
#define SHMKEYPATH "/dev/null"
#define SHMKEYID 1

//apothiki
typedef struct buf {
  char array[SIZE];
  int in, out;
}buf_T;


buf_T *buffer;
int shmid = -2;
key_t shm_key;

  int buf_init() {
    
    shm_key = ftok(SHMKEYPATH, SHMKEYID);
    if ( shm_key == (key_t)-1 ) {
      printf("main: ftok() for shm failed\n");
      return -1;
    }
    shmid = shmget(shm_key, sizeof(buf_T), IPC_CREAT | S_IRWXU);
    if (shmid == -1) return 0;
    buffer = (buf_T*) shmat(shmid, NULL, 0);
    
    return 1;
  }
  
  int buf_destroy() {
    
    shmdt(buffer);
    if( shmctl(shmid, IPC_RMID, NULL) == -1 ) return 0;
 
    return 1;
  }
  
  int buf_put(char c) {
    
    if(shmid < 0 ) return -1;
    if((*buffer).out == ((((*buffer).in) + 1 ) % SIZE ) ) return 0;
    (*buffer).array[(*buffer).in] = c;
    (*buffer).in = (((*buffer).in) + 1) % SIZE;
    
    return 1;
  }
  
  int buf_get(char *c) {
    
    if(shmid < 0 ) return -1;
    if( (*buffer).out == (*buffer).in ) return 0;
    *c = (*buffer).array[(*buffer).out];
    (*buffer).out = ((((*buffer).out) + 1 ) % SIZE );
    
    return 1;
  }