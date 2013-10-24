
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include <sched.h>
#include <pthread.h> 
#include <sys/times.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>

#define MAX 100
#define MIN 50
#define CPU_FREQ 2.66

typedef unsigned long long cycles_t;


inline cycles_t rdtsc() {
    cycles_t result;
    __asm__ __volatile__ ("rdtsc" : "=A" (result));
    return result;
}

/**********************************/

void taskCreationProcess() {
  
  int i, status;
  pid_t pid;
  double timing;
  
  long long start1 = rdtsc();

  for(i=0; i<MAX; i++) {
      pid = fork();
      if (pid == 0) {
		  exit(0);
      }
  }
  long long end1 = rdtsc();
  
  //divide by max if you want the  time in ns
  timing = (((end1 - start1)/ CPU_FREQ)); 
  
  printf("Average time to creat a process: %g ns\n", timing);
}

/**********************************/


int main() {
 
  taskCreationProcess();
  
  return 0; 
}