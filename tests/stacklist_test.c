#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "gen/error_macros.h"
#define RUNS 10000
#define BOUND 10000
#define BASE 0
#define NUMCASES 10

int32_t intcmp(const void *, const void *,size_t);
void  print(const void *);
void  ckfree(void *);
void *ckalloc(size_t);

int
main(void) {
  StackList  object;
  StackListIter *ptr;
  unsigned int x, y;
  unsigned int *value;
  memset(&object, 0, sizeof (object));
  x = RUNS;
  construct(StackList, &object,sizeof(x),FREEOBJ);
  set_alloc(StackList,  &object, ckalloc);
  set_dealloc(StackList,  &object, ckfree);
  set_compare(StackList,  &object, intcmp);
  set_print(StackList,  &object, print);
  for (y = 0; y < x; y++) {
    srand((x * y) / (x - y) + (x + y / x));
    switch ((rand() % NUMCASES) + BASE) {
        case 0:
        case 10:
        case 11:
        case 1:
        case 12:
        case 13:
        case 2:
          value = ckalloc(sizeof *value);
          *value = rand() % BOUND;
          push(StackList,  &object, value, DYNAMIC);
          break;
        case 3:
        case 15:
        case 4:
        case 5:
        case 6:
        case 16:
          pop(StackList,  &object);
          break;
        case 14:
        case 7:
        case 17:
        case 8:
        case 9:
          top(StackList,  &object);
          break;
        default:
          break;
    };
  }
  destruct(StackList,  &object);
  fprintf(stderr, "Now testing the iterators!\n");
  construct_func(StackList,&object, sizeof(x),FREEOBJ, ckalloc, ckfree, intcmp,  print,
                 memcpy);
  for (x = 0; x < RUNS; x++) {
	  value = ckalloc(sizeof *value);
	  *value = rand();
    push(StackList,  &object, value, DYNAMIC);
  }

  ptr = create(StackListIter,  &object);
  head(StackListIter, ptr);
  do {
    value = (unsigned int *) retrieve(StackListIter, ptr);
  }
  while (!next(StackListIter, ptr));
  assign(StackListIter, ptr, &object);
  tail(StackListIter, ptr);
  do {
    value = (unsigned int *) retrieve(StackListIter, ptr);
  } while (!prev(StackListIter, ptr));
  for(x = 0; x < RUNS; x++) {
	  switch(rand() % 2) {
		  case 1:
			  next(StackListIter,ptr);
			  break;
		  case 2:
			  prev(StackListIter,ptr);
			  break;
	  }
  }
  destroy(StackListIter, ptr);
  destruct(StackList,  &object);
  return EXIT_SUCCESS;
}

int32_t
intcmp(const void *a, const void *b,size_t x UNUSED)
{
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
