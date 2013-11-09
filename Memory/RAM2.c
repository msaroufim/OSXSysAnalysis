#include <stdlib.h>
#include <stdio.h>
#define MAX 100

  
typedef unsigned long long cycles_t;

inline cycles_t rdtsc() {
    cycles_t result;
    __asm__ __volatile__ ("rdtsc" : "=A" (result));
    return result;
}

typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
  a->array = (int *)malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, int element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (int *)realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

/*Main Idea is dynamically allocate array and keep track
of how much times it takes to add one
once the time increases dramatically we know we are at lower
layer of memory
*/
int main() {
//initialize array
//array of rdstc
Array a;
Array RDT;
Array RDTread;
int i;

initArray(&a, 5);  // initially 5 elements
initArray(&RDT,5);
initArray(&RDTread,5);


//time writing to memory
for (i = 0; i < MAX; i++) {
  insertArray(&RDT,rdstc())
  insertArray(&a, i);  // automatically resizes as necessary
}


//time reading the array
for(i = 0; i < MAX ; i++) {
  A[i];
  insertArray(&RDTread,rdtsc);
}

//plots are simple latrenvy is average time for a single operation
//bandwith is the number of operations we can perform in a unit time interval


printf(" The number of used elements is%d\n", a.used);  // print number of elements
for(i = 0; i <MAX; i++) {
printf("The %d'ith iteration took, %llu cycles",(i,RDT[i]));
}
freeArray(&a);
freeArray(&RDT);
freeArray(&RDTread);

  return 0;
}