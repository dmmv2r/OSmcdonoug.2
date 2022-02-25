#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 52
#define MAX_PROC 20

struct shmseg {
   int choosing[MAX_PROC];
   int number[MAX_PROC];
};

int main(int argc, char* argv[]) {
   printf("in master\n");

   int opt;
   int time;
   int processes;

   time = 100;
   processes = 1;

   while((opt = getopt(argc, argv, "ht:n:")) != -1) {
      switch(opt) {
         case 'h':
            printf("Usage: use command ./master -t x -n y\n");
            printf("where x is max amount of time until the program terminates (deafult 100)\n");
            printf("and x is the number of processes to create (max is 20)\n");
            return -1;
         case 't':
            time  = atoi(optarg);
            break;
         case 'n':
            processes = atoi(optarg);
            break;
         default:
            printf("Arguments required\n");
            //return -1;
            exit(-1);
      }
   }

  // printf("time is %d\n", time);
  // printf("processes is %d\n", processes);

   if(processes > 20) {
      printf("Invalid number of processes. Must be below 20\n");
      exit(-1);
   }

   int shmid;
   struct shmseg *shmp;
   
   shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
   if(shmid == -1) {
      perror("Shared memory");
      exit(-1);
   }

   shmp = shmat(shmid, NULL, 0);
   if (shmp == (void *) -1) {
      perror("shared memory attach");
      exit(-1);
   }

   shmp->number[1] = 3;

   pid_t childpid = 0;
   char* args[] = {"./slave", "7", NULL};

   int i;

   for(i = 0; i < processes; i++) {
      if((childpid != fork())) { //child
         //wait(NULL);
         printf("execing\n");
         execv("./slave", args);
      }
      
      printf("past fork\n");
   }

   printf("waiting\n");
   wait(NULL);

  /* if((childpid = fork())) {
      shmp->number[1] = 3;
      printf("wait pid is %ld\n", (long)getpid());
      wait(NULL);
   } else {
      printf("exec pid is %ld\n", (long)getpid());
      execv("./slave", args);
   }*/

   //wait(NULL);
   //printf("\n");
   //char* args[] = {"./slave", "7", NULL};
   //execv("./slave", args);
   //printf("\n");


   if(shmdt(shmp) == -1) {
      perror("shmdt");
      exit(-1);
   }

   if(shmctl(shmid, IPC_RMID, 0) == -1) {
      perror("shmctl");
      exit(-1);
   }


   printf("leaving master\n");
   return 0;
}


