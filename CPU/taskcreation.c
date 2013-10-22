
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

inline void taskCreationProcess() {
  
  int i, status;
  pid_t pid;
  double time, time_m;
  
  long long start1 = rdtsc();

  for(i=0; i<MAX; i++) {
      /* if pid = -1 means we got an error
            pid =  0 means we are in a child process
            pid >  0 means we are in a parent process
      */
      pid = fork();
      if (pid == 0) {
		  exit(0);
      }
  }

  /*

  */
  waitpid(pid, &status,  0);
  long long end1 = rdtsc();
  
  ////
  
  long long start2 = rdtsc();
  
  for(i=0; i<MIN; i++) {
      pid = fork();
      if (pid == 0) {
		  exit(0);
      }
  }
  waitpid(pid, &status,  0);
  long long end2 = rdtsc();
  
  timing = (((((end1 - start1) - (end2 - start2)))/ (CPU_FREQ) * (MAX - MIN))); 
  //time = (((((end1 - start1) - (end2 - start2)))/ CPU_FREQ) / (MAX - MIN)); 
  printf("Average time to create a process: %g ns\n", timing);
  
  
}

/**********************************/


int main() {
 
  taskCreationProcess();
  
  return 0; 
}