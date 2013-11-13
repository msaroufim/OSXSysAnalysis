/* calloc example */
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* calloc, exit, free */
#include "rdtsc.h"
#define MAX 10000
#define STRIDE 1000

//L2 cache size is 256KB (64000 integers)
//L3 cache size is 4MB   (1000000 integers)

int main ()
{
  int i,n;
  int size_pData2 = 64000;
  int size_pData3 = 100000000;
  int * pData2;
  int * pData3;
  long long int start2 , end2 , start3 , end3,timing;
  pData2 = (int*) calloc (size_pData2,sizeof(int));

  pData3 = (int*) calloc (size_pData3,sizeof(int));
 



  printf("----------------------\nstarting bandwidth measurements\n");
  for (n=0;n<size_pData2;n++) {
    start2 = rdtsc(); 
    pData2[n];
    end2 = rdtsc();
    timing = end2 - start2;
    printf("%llu\n",timing);
      }
printf("---------------------------\n");
  for (n = 0; n < size_pData3;n++)
  {
    start3 = rdtsc(); 
    pData3[n];
    end3 = rdtsc();
    timing = end3 - start3;
    printf("%llu\n",timing);

  }

 printf("-----------------------\nstarting latency measurements\n");

//make the arrays circular
 *(pData2 + size_pData2) = *(pData2);
 *(pData3 + size_pData3) = *(pData3);

for (n=0,i=0;n<size_pData2, i < MAX;n + STRIDE,i++) {
    start2 = rdtsc(); 
    pData2[n];
    end2 = rdtsc();
    timing = end2 - start2;
    printf("%llu\n",timing);
      }
printf("---------------------------\n");
  for (n = 0,i=0; n < size_pData3, i < MAX ; n + STRIDE,i++)
  {
    start3 = rdtsc(); 
    pData3[n];
    end3 = rdtsc();
    timing = end3 - start3;
    printf("%llu\n",timing);

  }


  free (pData2);
  free (pData3);
  return 0;
}