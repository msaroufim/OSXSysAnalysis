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
#include <math.h>
#include <sys/types.h>
#include <unistd.h>

       

#define MAX 100
#define MIN 50
#define CPU_FREQ 2.66

/* does not clean local name space of method after going out of scope
void method() {
	_exit()
}
*/

  typedef unsigned long long cycles_t;
inline cycles_t rdtsc() {
    cycles_t result;
    __asm__ __volatile__ ("rdtsc" : "=A" (result));
    return result;
}

//minimal system call is working
inline int mimimalSysCall() {  
	long long timing = 0; 
	int i = 0;
	for (i; i < MAX; i++) {
		long long start = rdtsc();
		pid_t getpid(void);
		long long end = rdtsc();
		timing += end - start; }
	
  timing = timing / MAX;
  return timing;
  //printf("the average time the minimal syscall took was %llu",(timing));
}

int main() {
	long long a;
	a = mimimalSysCall();
	printf("the average number of cycles %llu  \n",(a));
	printf("the average time a syscall takes  %f ns",(a/CPU_FREQ));
	return 0;
}