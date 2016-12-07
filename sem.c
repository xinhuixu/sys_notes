#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
			      (Linux-specific) */
};

int main(int argc, char *argv[]){
  int semid, key;
  key = ftok("sem.c",22);
  int sc;
  if (strncmp(argv[1], "-c", strlen(argv[1])) == 0) {
    
    semid = semget( key, 1, IPC_CREAT | IPC_EXCL | 0644 );
    if (semid >= 0) {
      int value = atoi(argv[2]); //alphanum to int
      union semun su;
      su.val = value;
      sc = semctl( semid, 0, SETVAL, su );
      printf("val set: %d\n",sc);
    } else {
      printf("smp already exists\n");
    }
  } else if (strncmp(argv[1], "-g", strlen(argv[1])) == 0) {
    semid = semget(key,1,0);
    sc = semctl( semid, 0, GETVAL);
    printf("smp val: %d\n",sc);
  } else if (strncmp(argv[1], "-r", strlen(argv[1])) == 0) {
    semid = semget(key,1,0);
    sc = semctl( semid, 0, IPC_RMID );
  }

  return 0;
}
