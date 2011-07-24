#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"
#include "gen/error_macros.h"
#define RUNS 10000
#define BOUND 1000000
#define BASE 0
#define NUMCASES 2


int32_t intcmp(const void *, const void *,size_t);
void  print(const void *);
void  ckfree(void *);
void *ckalloc(size_t);

int main(void) {
	PrioQueue object;
	unsigned int x, y;
	unsigned int value;
	int32_t priority;
	memset(&object,0,sizeof(object));
	x = RUNS;
	construct_func(PrioQueue,&object,sizeof(x),FREEOBJ,ckalloc,ckfree,intcmp,print,memcpy);
	for(y = 0; y < x; y++) {
		srand((x * y) / (x - y) + (x + y / x));
		switch((rand() % NUMCASES) + BASE) {
			case 0:
				value = rand() % BOUND + 1;
				priority = rand()% BOUND;
				insert_PrioQueue(&object,priority,&value,sizeof value);
				break;
			case 1:
				pop(PrioQueue,&object);
				break;
			default:
				break;
		};
	}
	/*print_all(PrioQueue,&object);
	dump(PrioQueue,&object);*/
	destruct(PrioQueue,&object);
	return EXIT_SUCCESS;
}

int32_t intcmp(const void *a, const void *b,size_t x UNUSED) {
	return (*(const int *)a > *(const int *)b) - (*(const int *)a < *(const int *)b); 
}
void
print(const void *a)
{
  printf("%d ", (*(const int *) a));
}

void *
ckalloc(size_t size)
{
  void *ptr;

  do {
    ptr = malloc(size);
  }
  while (!ptr);
  return ptr;
}

void
ckfree(void *ptr)
{
  free(ptr);
}
