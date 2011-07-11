#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
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
	Heap object;
	unsigned int x, y;
	unsigned int value;
	memset(&object,0,sizeof(object));
	x = RUNS;
	construct(Heap,&object,sizeof(x),FREEOBJ);
	set_alloc(Heap,  &object, ckalloc);
	set_dealloc(Heap,  &object, ckfree);
	set_compare(Heap,  &object, intcmp);
	set_print(Heap,  &object, print);
	for(y = 0; y < x; y++) {
		srand((x * y) / (x - y) + (x + y / x));
		switch((rand() % NUMCASES) + BASE) {
			case 0:
				value = rand() % BOUND + 1;
				insert(Heap,&object,&value,STATIC);
				break;
			case 1:
				pop(Heap,&object);
				break;
			default:
				break;
		};
	}
	/*print_all(Heap,&object);
	dump(Heap,&object);*/
	destruct(Heap,&object);
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
