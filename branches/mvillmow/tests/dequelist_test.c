#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"
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
  DequeList  object;
  DequeListIter *ptr;
  unsigned int x, y;
  unsigned int *value;
  memset(&object, 0, sizeof (object));
  x = RUNS;
  construct(DequeList, &object,sizeof(x),FREEOBJ);
  set_alloc(DequeList,  &object, ckalloc);
  set_dealloc(DequeList,  &object, ckfree);
  set_compare(DequeList,  &object, intcmp);
  set_print(DequeList,  &object, print);
  for (y = 0; y < x; y++) {
    srand((x * y) / (x - y) + (x + y / x));
    switch ((rand() % NUMCASES) + BASE) {
        case 0:
        case 10:
        case 11:
        case 1:
        case 12:
          value = ckalloc(sizeof *value);
          *value = rand() % BOUND;
          push_back(DequeList,  &object, value, DYNAMIC);
          break;
        case 13:
        case 2:
        case 14:
          value = ckalloc(sizeof *value);
          *value = rand() % BOUND;
          push_front(DequeList,  &object, value, DYNAMIC);
          break;
        case 3:
        case 15:
        case 4:
          pop_front(DequeList,  &object);
          break;
        case 5:
        case 6:
        case 16:
          pop_back(DequeList,  &object);
          break;
        case 7:
        case 17:
          back(DequeList,  &object);
          break;
        case 8:
        case 9:
          front(DequeList,  &object);
          break;
        default:
          break;
    };
  }
  destruct(DequeList,  &object);
  fprintf(stderr, "Now testing the iterators!\n");
  construct_func(DequeList,&object,sizeof(x),FREEOBJ, ckalloc, ckfree, intcmp,  print,
                 memcpy);
  for (x = 0; x < RUNS; x++) {
	  value = ckalloc(sizeof *value);
	  *value = rand();
    push_back(DequeList,  &object, value, DYNAMIC);
  }

  ptr = create(DequeListIter,  &object);
  head(DequeListIter, ptr);
  do {
    value = (unsigned int *) retrieve(DequeListIter, ptr);
  }
  while (!next(DequeListIter, ptr));
  assign(DequeListIter, ptr, &object);
  tail(DequeListIter, ptr);
  do {
    value = (unsigned int *) retrieve(DequeListIter, ptr);
  } while (!prev(DequeListIter, ptr));
  for(x = 0; x < RUNS; x++) {
	  switch(rand() % 2) {
		  case 1:
			  prev(DequeListIter,ptr);
			  break;
		  case 2:
			  next(DequeListIter,ptr);
			  break;
	  }
  }
  destroy(DequeListIter, ptr);
  destruct(DequeList,  &object);
  return EXIT_SUCCESS;
}

int32_t
intcmp(const void *a, const void *b,size_t x UNUSED)
{
  if ((*(const int *) a) < (*(const int *) b)) {
    return -1;
  } else if ((*(const int *) a) > (*(const int *) b)) {
    return 1;
  } else {
    return 0;
  }
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
