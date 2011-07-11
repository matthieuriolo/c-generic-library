#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
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
  QueueList  object;
  QueueListIter *ptr;
  unsigned int x, y;
  unsigned int *value;
  memset(&object, 0, sizeof (object));
  x = RUNS;
  construct(QueueList, &object,sizeof(x),FREEOBJ);
  set_alloc(QueueList,  &object, ckalloc);
  set_dealloc(QueueList,  &object, ckfree);
  set_compare(QueueList,  &object, intcmp);
  set_print(QueueList,  &object, print);
  for (y = 0; y < x; y++) {
    srand((x * y) / (x - y) + (x + y / x));
    switch ((rand() % NUMCASES) + BASE) {
        case 0:
        case 10:
        case 11:
        case 1:
        case 12:
        case 7:
        case 17:
        case 8:
        case 13:
        case 2:
        case 14:
          value = ckalloc(sizeof *value);
          *value = rand() % BOUND;
          push(QueueList,  &object, value, DYNAMIC);
          break;
        case 3:
        case 15:
        case 4:
        case 5:
        case 6:
        case 16:
          pop(QueueList,  &object);
          break;
        case 9:
          front(QueueList,  &object);
          break;
        default:
          break;
    };
  }
  destruct(QueueList,  &object);
  fprintf(stderr, "Now testing the iterators!\n");
  construct_func(QueueList,&object,sizeof(x),FREEOBJ, ckalloc, ckfree, intcmp,  print,
                 memcpy);
  for (x = 0; x < RUNS; x++) {
	  value = ckalloc(sizeof *value);
	  *value = rand();
    push(QueueList,  &object, value,DYNAMIC);
  }

  ptr = create(QueueListIter,  &object);
  head(QueueListIter, ptr);
  do {
    value = (unsigned int *) retrieve(QueueListIter, ptr);
  }
  while (!next(QueueListIter, ptr));
  assign(QueueListIter, ptr, &object);
  tail(QueueListIter, ptr);
  do {
    value = (unsigned int *) retrieve(QueueListIter, ptr);
  } while (!prev(QueueListIter, ptr));
  for(x = 0; x < RUNS; x++) {
	  switch(rand() % 2) {
		  case 1:
			  next(QueueListIter,ptr);
			  break;
		  case 2:
			  prev(QueueListIter,ptr);
			  break;
	  }
  }
  destroy(QueueListIter, ptr);
  destruct(QueueList,  &object);
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
