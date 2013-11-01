#include <stdlib.h>
#include <stdio.h>

//sizeof item is 16 bytes, sizeof curr is 8 bytes
   int val;
   struct list_el * next;
}item;



int main() {
   item * curr, * head;
   int i;

   head = NULL;

   for(i=1;i<=10;i++) {
      curr = (item *)malloc(sizeof(item));
      printf("sizeof curr %lu \n", sizeof(curr));
      printf("sizeof item %lu \n", sizeof(item));
      curr->val = (double)i;
      curr->next  = head;
      head = curr;
   }

   curr = head;

   while(curr) {
      printf("size of curr->val and item %d %lu\n", curr->val,sizeof(item));
      curr = curr->next ;
   }
   return 0;
}
