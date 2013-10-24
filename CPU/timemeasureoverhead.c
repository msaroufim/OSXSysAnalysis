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


inline volatile void timeMeasurementOveheadRead() {
    
    double timing = 0;
    int i=0;
    //long long startloop = rdtsc();
    for (i=0; i<MAX; i++) {
        long long start = rdtsc();
        long long end = rdtsc();
        //printf("the start time is %llu \n", start);
        //printf("the end time is %llu \n",end);
        timing += end - start;
        
    }
    //long long endloop = rdtsc();
    //double looptime = endloop - startloop;
    //printf("for loop overhead is %g ",(looptime/100));
    printf("Average number of cycles overhead is %g \n", (timing/MAX));

    //maybe should remove 10e9
    printf("Time measurement overhead is %g ns\n", (timing/(MAX*CPU_FREQ)));
}


inline volatile void loopMeasurementOverhead() {
    double timing = 0;
    int i =0;
    long long startloop = rdtsc();
    for (i=0;i<MAX;i++) {
    }
    long long endloop = rdtsc();
    double looptime = endloop - startloop;
    printf("loop measurement overhead %g\n",looptime/MAX);
}

int main() {

	timeMeasurementOveheadRead();
    loopMeasurementOverhead();
	return 0;
}