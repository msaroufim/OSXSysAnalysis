
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
 

void *functionPrint()
{    
	
}

void taskCreationThread(){

     pthread_t thread1;
     int  th, i;
     double timing;
	 
     //const char *message = "";


     long long start = rdtsc();
	 
     for(i=0; i<MAX; i++) 
	 {
     th = pthread_create( &thread1, NULL, functionPrint, NULL); //(void*) message);
     }
	 
     long long end = rdtsc();


     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

     //pthread_join( thread1, NULL);
     //pthread_join( thread2, NULL);

//divide by CPU_FREQ if youre looking for the time in ns
     timing = (end - start) / MAX; 
  
     printf("Average time to creat a process: %g ns\n", timing);
	 
     exit(0);
}


  
int main() {
 
 taskCreationThread();
    
  return 0; 
}

