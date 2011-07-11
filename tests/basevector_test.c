#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
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
  Vector  object;
  VectorIter *ptr;
  unsigned int x, y;
  unsigned int value;
  memset(&object, 0, sizeof (object));
  x = RUNS;
  construct(Vector, &object,sizeof x,FREEOBJ);
  set_alloc(Vector,  &object, ckalloc);
  set_dealloc(Vector,  &object, ckfree);
  set_compare(Vector,  &object, intcmp);
  set_print(Vector,  &object, print);
  for (y = 0; y < x; y++) {
    srand((x * y) / (x - y) + (x + y / x));
    switch ((rand() % NUMCASES) + BASE) {
        case 0:
        case 10:
        case 11:
        case 1:
          value = rand() % BOUND;
          push_back(Vector,  &object, &value, STATIC);
          break;
        case 12:
        case 13:
        case 2:
          value = rand() % BOUND;
          push_front(Vector,  &object, &value, STATIC);
          break;
        case 3:
        case 15:
        case 4:
          pop_back(Vector,  &object);
          break;
        case 5:
        case 6:
        case 16:
          pop_front(Vector,  &object);
          break;
        case 14:
        case 7:
        case 17:
        case 8:
          back(Vector,  &object);
          break;
        case 9:
          front(Vector,  &object);
          break;
        default:
          break;
    };
  }
  destruct(Vector,  &object);
  fprintf(stderr, "Now testing the iterators!\n");
  memset(&object,0,sizeof(object));
  construct_func(Vector,  &object,sizeof(x),FREEOBJ, ckalloc, ckfree, intcmp, print,
                 memcpy);
  for (x = 0; x < RUNS; x++) {
	  value = rand();
    convert(Vector,  &object, &value, sizeof(x),STATIC);
  }

  ptr = create(VectorIter,  &object);
  head(VectorIter, ptr);
  do {
    value = *(unsigned int*)retrieve(VectorIter, ptr);
  }
  while (!next(VectorIter, ptr));
  assign(VectorIter, ptr, &object);
  tail(VectorIter, ptr);
  do {
    value = *(unsigned int*) retrieve(VectorIter, ptr);
  } while (!prev(VectorIter, ptr));
  for(x = 0; x < RUNS; x++) {
	  switch(rand() % 2) {
		  case 1:
			  prev(VectorIter,ptr);
			  break;
		  case 2:
			  next(VectorIter,ptr);
			  break;
	  }
  }
  destroy(VectorIter, ptr);
  destruct(Vector,  &object);
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
