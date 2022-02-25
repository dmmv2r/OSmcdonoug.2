#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>

#define SHM_KEY 52
#define MAX_PROC 20

struct shmseg {
   int choosing[MAX_PROC];
   int number[MAX_PROC];
};

int main(int argc, char* argv[]) {
   printf("in slave\n");

   int shmid;
   struct shmseg *shmp;
   shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
   if(shmid == -1) {
      perror("Shared memory");
      exit(-1);
   }

   shmp = shmat(shmid, NULL, 0);
   if(shmp == (void *) -1) {
      perror("shared memory attach");
      exit(-1);
   }

   int number;
   number = atoi(argv[1]);
   printf("argument is %d\n", number);

   int x;
   x = shmp->number[1];
   printf("shared number is %d\n", x);


   if(shmdt(shmp) == -1) {
      perror("shmdt");
      exit(-1);
   }

   printf("leaving slave\n");
   return 0;
}


