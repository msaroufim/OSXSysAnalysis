
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
int fd[2];

void* PipeWriterThread(void* arg)
{
   char ch[32];
   strcpy(ch, "abcd");
   write(fd[1], ch, 4);
   return NULL;
}


void taskCreationThread()
{
     pthread_t thread1, thread2;
     int  i, th1, th2, r;
     double timing;

     char    string[] = "";

     const char *message = "Thread is created";

	 /// THREAD 1
     long long start1 = rdtsc();
	
     for(i=0; i<MAX; i++) 
	 {
		 
	     th1 = pthread_create( &thread1, (pthread_attr_t *)NULL,PipeWriterThread, NULL);
 	     pipe(fd);
	  
         close(fd[1]);
         r = read(fd[0], string, 10);
		 		   
		 /*
         if (th1 != 0)
             printf("\n can't create thread :[%s]", strerror(th1));
         else{
             printf("\n Thread 1 created successfully\n");*/
	       
   }
	 
     long long end1 = rdtsc();


	 /// THREAD 2
     long long start2 = rdtsc();
	 
     for(i=0; i<MIN; i++) 
	 {
		 
	     th2 = pthread_create( &thread1, (pthread_attr_t *)NULL,PipeWriterThread, NULL);
	
 	     pipe(fd);
		       
         close(fd[1]);
         r = read(fd[0], string, 10);
	        
     }
	 
     long long end2 = rdtsc();

     //pthread_join( thread1, NULL);
     //pthread_join( thread2, NULL);

 	timing = (((((end1 - start1) - (end2 - start2)))/ CPU_FREQ) / (MAX - MIN) ); 
  
     printf("Time to context switch from one thread to another: %g ns\n", timing);
	 
}


  
int main() {
 
 taskCreationThread();
    
  return 0; 
}

