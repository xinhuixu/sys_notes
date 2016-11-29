#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

//1129

int main() {
  int sd;
  int *p;
  int f;
  sd = shmget( 23456, sizeof(int), IPC_CREAT | 0644 );

  f = fork();
  if (f == 0) {
    p = shmat( sd, 0, 0); //attach
    *p = 10; //deref
    printf("%d\n",*p);
  } else {
    int status;
    wait(&status);
    p = shmat( sd, 0, 0);
    printf("%d\n",*p);
  }
  return 0;
}
