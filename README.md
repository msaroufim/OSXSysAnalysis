Full System Analysis of OS X 10.8.5
Part 1 is CPU and scheduling operations
The included files in CPU are
* timemeasureoverhead.c which calculates the average time rdtsc() takes
* procedure.c which calculates the average time a loop with 0-7 arguments takes
* syscall.c which calculates the average time a minimal system call takes
* tascreation.c which calculates the average time it takes to create a process
* kthread.c which calculates the average time it takes to create a thread
* contextswitch.c which calculates the average time it takes to perform a context switch for both threads and processes
