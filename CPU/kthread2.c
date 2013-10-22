#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <time.h>
#include <sched.h>
#include <pthread.h> 
#include <sys/times.h>

#define MAX 100
#define MIN 50
#define CPU_FREQ 2.66


  
typedef unsigned long long cycles_t;

inline cycles_t rdtsc() {
    cycles_t result;
    __asm__ __volatile__ ("rdtsc" : "=A" (result));
    return result;
}
 
pthread_t tid[2];

void* taskCreationThread(void *arg)
{
       int i=0;
       double timing = 0;
  
long long start1 = rdtsc();
 for (i=0; i<MAX; i++) {
  //Create a thread
    pthread_t id = pthread_self();

    /*
    pthread_equal returns 1 there both threads have the same handle
    */
    if(pthread_equal(id,tid[0]))
    {
        printf("\n First thread processing\n");
    }
    else
    {
        printf("\n Second thread processing\n");
  
    }
 }

 printf("getting outside the for loop");
long long end1 = rdtsc();

timing = (end1 - start1)/(CPU_FREQ *  MAX);

printf("Average time to create a process: %g ns\n", timing);
  
    return NULL;
}
  
  

  
int main() {
 
  
  int i = 0;
      int err;

      while(i < 2)
      {
          err = pthread_create(&(tid[i]), NULL, &taskCreationThread, NULL);
          if (err != 0)
              printf("\n can't create thread :[%s]", strerror(err));
          else
              printf("\n Thread created successfully\n");

          i++;
      }

    
    
  
  return 0; 
}

