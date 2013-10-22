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


inline volatile timeMeasurementOveheadRead() {
    
    double time = 0;
    int i=0;
    int a =0;
    for (i=0; i<MAX; i++) {
        long long start = rdtsc();
        a = i;
        long long end = rdtsc();
        printf("the start time is %llu \n", start);
        printf("the end time is %llu \n",end);
        time += end - start;
        
    }
    printf("Average number of cycles overhead is %g\n", (time/(MAX)));

    //maybe should remove 10e9
    printf("Time measurement overhead is %g ns\n", (time/(MAX*CPU_FREQ))*10e9);
}

int main() {

	timeMeasurementOveheadRead();
	return 0;
}