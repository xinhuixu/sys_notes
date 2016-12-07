#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
  srand( time(NULL));
  int x = random() % 10 + 5;
  int semid = semget( ftok("sem.c",22), 1, 0);
  printf("%d before access\n", getpid());
  
  struct sembuf sb;

  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;

  semop(semid, &sb, 1);
  printf("%d im in\n", getpid());
  sleep(x);
  sb.sem_op = 1; //UP
  semop(semid, &sb, 1);
  return 0;
}
