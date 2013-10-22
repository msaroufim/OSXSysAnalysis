#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <sched.h> 



#define bufferSize 56
#define fileSize 1048576
#define STACK_SIZE 65536
#define MAX 100
#define MIN 50
#define CPU_FREQ 2.66

typedef unsigned long long cycles_t;

inline cycles_t rdtsc() {
    cycles_t result;
    __asm__ __volatile__ ("rdtsc" : "=A" (result));
    return result;
}


int taskCreationThread() {
  
   int  i = 0;
   char *stack[MAX];

   long long timing;
   
   int child(void *args) {
     return 0;
   }

  
   //printf("Before allocating stacks\n");
   
   //allocate stacks
   for (i; i<MAX; i++) {
     stack[i] = malloc(STACK_SIZE);
   }
   
   //printf("Stacks allocated\n");
  
   long long start = rdstc();
   for (i; i<MAX; i++) {
     //printf("Allocated %d stacks\n", i);
     clone(child, stack[i] + STACK_SIZE, NULL);
   }
   long long end = rdtsc();

   /*
   long long start2 = rdtsc();
   for (i=0; i<MIN; i++) {
     clone(child, stack[i] + STACK_SIZE, NULL);
   }
   long long end2 = rdtsc();

   
  
   time = ((((end - start) - (end2 - start2)))/ (CPU_FREQ * (MAX - MIN)); //time in nanoseconds
   printf("Avg time to create a thread: %g ns\n", timing);
*/
   timing = end - start;
   printf("%llu \n",(timing) );
   return 0;
}







