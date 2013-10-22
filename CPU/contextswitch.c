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





void ContextSwitchProcess() { // & TaskCreationProcess () ??
	int i, status;
	    pid_t pid;
	    time_t currentTime;
	    struct tms cpuTime;

		long long start1 = rdtsc();

		for (i=0; i<MAX; i++) { 
			
	    if ((pid = fork()) == -1) {         
	         perror("fork error");
	         exit(EXIT_FAILURE);
	    }
	    else if (pid == 0) {                
	       time(&currentTime);
	       printf("Child process started at %s", ctime(&currentTime));
	       for (i = 0; i < 5; ++i) {
	          printf("Counting: %dn", i);  
	          sleep(1);
	       }
	       time(&currentTime);
	       printf("Child process ended at %s", ctime(&currentTime));
	       exit(EXIT_SUCCESS);
	    }
	    else {                              
	       time(&currentTime);
	       printf("Parent process started at %s", ctime(&currentTime));

	       if (wait(&status) == -1 )        
	          perror("wait error");
	       if (WIFEXITED(status))
	          printf("Child process ended normally.n");
	       else
	          printf("Child process did not end normally.n");

	       if (times(&cpuTime) < 0)         
	          perror("times error");
	       else {
	          printf("Parent process user time = %fn",
	               ((double) cpuTime.tms_utime)/CLOCKS_PER_SEC);
	          printf("Parent process system time = %fn",
	               ((double) cpuTime.tms_stime)/CLOCKS_PER_SEC);
	          printf("Child process user time = %fn",
	               ((double) cpuTime.tms_cutime)/CLOCKS_PER_SEC);
	          printf("Child process system time = %fn",
	               ((double) cpuTime.tms_cstime)/CLOCKS_PER_SEC);
	       }
	       time(&currentTime);
	       printf("Parent process ended at %s", ctime(&currentTime));
	       exit(EXIT_SUCCESS);
	    }
	}
	
	long long end1 = rdtsc();
	
	
	long long start2 = rdtsc();
	for (i=0; i<MIN; i++) { 
	    if ((pid = fork()) == -1) {         
	         perror("fork error");
	         exit(EXIT_FAILURE);
	    }
	    else if (pid == 0) {                
	       time(&currentTime);
	       printf("Child process started at %s", ctime(&currentTime));
	       for (i = 0; i < 5; ++i) {
	          printf("Counting: %dn", i);  
	          sleep(1);
	       }
	       time(&currentTime);
	       printf("Child process ended at %s", ctime(&currentTime));
	       exit(EXIT_SUCCESS);
	    }
	    else {                              
	       time(&currentTime);
	       printf("Parent process started at %s", ctime(&currentTime));

	       if (wait(&status) == -1 )        
	          perror("wait error");
	       if (WIFEXITED(status))
	          printf("Child process ended normally.n");
	       else
	          printf("Child process did not end normally.n");

	       if (times(&cpuTime) < 0)         
	          perror("times error");
	       else {
	          printf("Parent process user time = %fn",
	               ((double) cpuTime.tms_utime)/CLOCKS_PER_SEC);
	          printf("Parent process system time = %fn",
	               ((double) cpuTime.tms_stime)/CLOCKS_PER_SEC);
	          printf("Child process user time = %fn",
	               ((double) cpuTime.tms_cutime)/CLOCKS_PER_SEC);
	          printf("Child process system time = %fn",
	               ((double) cpuTime.tms_cstime)/CLOCKS_PER_SEC);
	       }
	       time(&currentTime);
	       printf("Parent process ended at %s", ctime(&currentTime));
	       exit(EXIT_SUCCESS);
	    }
	}
	long long end2 = rdtsc();
	
}
  
  
pthread_t tid[2];

void* ContextSwitchThread(void *arg)
{
       int i=0;
       double time = 0;
	
long long start1 = rdtsc();
 for (i=0; i<MAX; i++) {
	//Create a thread
    pthread_t id = pthread_self();
    if(pthread_equal(id,tid[0]))
    {
        printf("\n First thread processing\n");
    }
    else
    {
        printf("\n Second thread processing\n");
	
    }
 }
long long end1 = rdtsc();


long long start2 = rdtsc();
for (i=0; i<MIN; i++) {
	//Create a thread
    pthread_t id = pthread_self();
    if(pthread_equal(id,tid[0]))
    {
        printf("\n First thread processing\n");
    }
    else
    {
        printf("\n Second thread processing\n");
	
    }
}
long long end2 = rdtsc();

	
    return NULL;
}
  
 

  
int main() {

  
  int i = 0;
      int err;

      while(i < 2)
      {
          err = pthread_create(&(tid[i]), NULL, &ContextSwitchThread, NULL);
          if (err != 0)
              printf("\n can't create thread :[%s]", strerror(err));
          else
              printf("\n Thread created successfully\n");

          i++;
      }

     // sleep(5);
	  
	  ContextSwitchProcess();
	  
  
  return 0; 
}

