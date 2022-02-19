#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
            printf("help message\n");
            return -1;
         case 't':
            time  = atoi(optarg);
            break;
         case 'n':
            processes = atoi(optarg);
            break;
         default:
            printf("Arguments required\n");
            return -1;
      }
   }

   printf("time is %d\n", time);
   printf("processes is %d\n", processes);

   printf("forking\n");
   pid_t childpid = 0;
   char* args[] = {"./slave", "7", NULL};

   if((childpid = fork())) {
      printf("wait pid is %ld\n", (long)getpid());
      wait(NULL);
   } else {
      printf("exec pid is %ld\n", (long)getpid());
      execv("./slave", args);
   }

   //wait(NULL);
   //printf("\n");
   //char* args[] = {"./slave", "7", NULL};
   //execv("./slave", args);
   //printf("\n");

   printf("leaving master\n");
   return 0;
}


