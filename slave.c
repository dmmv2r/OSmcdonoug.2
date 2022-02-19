#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
   printf("in slave\n");

   int number;
   number = atoi(argv[1]);
   printf("argument is %d\n", number);

   printf("leaving slave\n");
   return 0;
}


