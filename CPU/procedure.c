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

 
/*
  __inline__ uint64_t rdtsc() {
    uint32_t lo, hi;
    __asm__ __volatile__ (      // serialize
    "xorl %%eax,%%eax \n        cpuid"
    ::: "%rax", "%rbx", "%rcx", "%rdx");
    // We cannot use "=A", since this would use %rax on x86_64
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return (uint64_t)hi << 32 | lo;
  }

  */

  typedef unsigned long long cycles_t;
inline cycles_t rdtsc() {
    cycles_t result;
    __asm__ __volatile__ ("rdtsc" : "=A" (result));
    return result;
}

inline void procedure(int count, ...)
{
    long long timing = 0;
    long long start = rdtsc();
    va_list ap;
    int j;
    double tot = 0;
    va_start(ap, count); //Requires the last fixed parameter (to get the address)
    va_end(ap);
    printf("Created a function with %d arguments \n", (count));
    long long end = rdtsc();
    timing = (start - end)/2.66;
     //printf("the start time for procedure with parameter count %llu is %llu \n", (count,start));
    //printf("the end time for procedure with parameter count %llu is %llu \n",(count,end));
    printf("the time overhead for procedure is %llu \n",(timing));
}


int main() {
  procedure(1,1);
  procedure(2,1,2);
  procedure(3,1,2,3);
  procedure(4,1,2,3,4);
  procedure(5,1,2,3,4,5);
  procedure(6,1,2,3,4,5,6);
  procedure(7,1,2,3,4,5,6,7);
}