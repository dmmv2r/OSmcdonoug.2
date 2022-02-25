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


/*
   do
      shmp->choosing[i] = true;  
      shmp->number[i] = 1 + max(shmp->number[0], ..., shmp->number[n-1]);  
      shmp->choosing[i] = false;  
      for ( int j = 0; j < n; j++ ) {  
         while ( shmp->choosing[j] ); // Wait if j happens to be choosing  
         while ( (shmp->number[j] != 0)  
           &&  ( shmp->number[j] < shmp->number[i] || (shmp->number[j] == shmp->number[i] && j < i) );  
      }  
*/


   int number;
   number = atoi(argv[1]);
   printf("argument is %d\n", number);

   int x;
   x = shmp->number[1];
   printf("shared number is %d\n", x);    //just used for checking shared mem


/*
      shmp->number[i] = 0;  
      //remainder_section();  
   while ( 1 );  
*/


   if(shmdt(shmp) == -1) {
      perror("shmdt");
      exit(-1);
   }

   printf("leaving slave\n");
   return 0;
}


