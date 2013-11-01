#include <sys/time.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define ITER 10000

char *a;
int pagesize;
int counter = ITER;
struct timeval begin, end;

void handler() {

    //mprotect changes protection for calling processes
    //memory page
    if(mprotect(a, pagesize, PROT_WRITE) < 0) { 
        perror("mprotect:");
        exit(0);
    }
}

int main() {
    struct sigaction sa;
    long diff;

    pagesize = sysconf(_SC_PAGESIZE);

    a = (char *)valloc(pagesize);

    sa.sa_handler = handler;
    //change action of process when it recievs a signal SGSEV to action specified by handle
    sigaction(SIGSEGV, &sa, NULL);

    if(mprotect(a, pagesize, PROT_NONE) <0) { 
        perror("mprotect:"); exit(0);
    }

    gettimeofday(&begin, NULL);

    *a = 1;

    diff = (end.tv_sec - begin.tv_sec)*1000000 + (end.tv_usec - begin.tv_usec);
    printf("fault time = %f microsecs\n", (float)diff/(ITER+1));
    return 0;
}
