
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

  
void contextSwitchProcess() {
    
    int     fd[2], r, i=0, status;
    pid_t   pid;
    char    string[] = "";
    char    readbuffer[1];

    double timing;
	
	long long start1 = rdtsc();
	
	for (i=0; i<MAX; i++) { 
	  
	    pid = fork();
	    pipe(fd);
	    
	    if (pid == 0) {
	  
		  close(fd[0]);
		  write(fd[1], string, (strlen(string)+1));
		  exit(0);
		  
	    } else {

		  close(fd[1]);
		  waitpid(pid, &status,  0);
		  r = read(fd[0], readbuffer, sizeof(readbuffer));
		  
	    }
	}
	long long end1 = rdtsc();
	
	long long start2 = rdtsc();
	for (i=0; i<MIN; i++) {
	  
	    pid = fork();
	    pipe(fd);
	  
	    if (pid == 0) {
	          
		  close(fd[0]);
		  write(fd[1], string, (strlen(string)+1));
		  exit(0);
		  
	    } else {
	      
		  close(fd[1]);
		  waitpid(pid, &status,  0);
		  r = read(fd[0], readbuffer, sizeof(readbuffer));
		  
	    }
	}
	long long end2 = rdtsc();
	
	
	timing = (((((end1 - start1) - (end2 - start2)))/ CPU_FREQ) / (MAX - MIN)); 
	
	printf("Average time to process context switch: %g ns\n", timing);   
}


/**********************************/


int main() {
 
  contextSwitchProcess();
  
  return 0; 
}