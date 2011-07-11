#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "gen/error_macros.h"
#define RUNS 10000
#define BOUND 1000000
#define BASE 0
#define NUMCASES 10

int32_t intcmp(const void *, const void *,size_t);
void  print(const void *);
void  ckfree(void *);
void *ckalloc(size_t);

int
main(void)
{
  List  object;
  List *l_copy;
  ListIter *ptr,*ptr2;
  unsigned int x, y;
  unsigned int *value;

  x = RUNS;
  memset(&object, 0, sizeof (object));
  construct(List, &object,sizeof(x),FREEOBJ);
  set_alloc(List, &object, ckalloc);
  set_dealloc(List, &object, ckfree);
  set_compare(List, &object, intcmp);
  set_print(List, &object, print);
  for (y = 0; y < x; y++) {
    srand((x * y) / (x - y) + (x + y / x));
    switch ((rand() % NUMCASES) + BASE) {
        case 0:
        case 10:
        case 11:
          value = ckalloc(sizeof *value);
          *value = rand() % BOUND;
          push_front(List, &object, value, DYNAMIC);
          break;
        case 1:
        case 12:
        case 13:
          value = ckalloc(sizeof *value);
          *value = rand() % BOUND;
          push_back(List, &object, value, DYNAMIC);
          break;
        case 2:
        case 14:
          pop_front(List, &object);
          break;
        case 3:
        case 15:
          pop_back(List, &object);
          break;
        case 4:
          front(List, &object);
          break;
        case 5:
          back(List, &object);
          break;
        case 6:
        case 16:
          value = ckalloc(sizeof *value);
          *value = rand() % BOUND;
          insert(List, &object, value, DYNAMIC);
          break;
        case 7:
        case 17:
          value = ckalloc(sizeof *value);
          *value = rand() % BOUND;
          delete(List, &object, value);
          free(value);
          break;
        case 8:
        case 9:
          sort(List, &object);
          break;
        default:
          break;
    };
  }
  destruct(List, &object);
  fprintf(stderr, "Now testing the iterators!\n");
  construct_func(List, &object,sizeof(x),FREEOBJ, ckalloc, ckfree, intcmp,  print,
                 memcpy);
  for (x = 0; x < RUNS; x++) {
	  value = ckalloc(sizeof *value);
	  *value = rand();
    push_back(List, &object, value,DYNAMIC);
  }

  ptr = create(ListIter, &object);
  head(ListIter, ptr);
  do {
    value = (unsigned int *) retrieve(ListIter, ptr);
  }
  while (!next(ListIter, ptr));
  assign(ListIter, ptr, &object);
  tail(ListIter, ptr);
  do {
    value = (unsigned int *) retrieve(ListIter, ptr);
  } while (!prev(ListIter, ptr));
  for(x = 0; x < RUNS; x++) {
	  switch(rand() % 2) {
		  default:
		  case 0:
			  next(ListIter,ptr);
			  break;
		  case 1:
			  prev(ListIter,ptr);
			  break;
	  }
  }
  destroy(ListIter, ptr);
  destruct(List, &object);
  memset(&object, 0, sizeof (object));
  construct(List, &object,sizeof(x),FREEOBJ);
  for(x = 0; x < 15; x++) {
	  push_back(List,&object,&x,STATIC);
  }
  l_copy = duplicate(List,&object);
  ptr2 = create(ListIter,l_copy);
  do{
  }while(!next(ListIter,ptr2));
  destruct(List,l_copy);
  destroy(ListIter,ptr2);
  ptr2 = create(ListIter,&object);
  while(!empty(List,&object)) {
	  head(ListIter,ptr2);
	  ptr = create(ListIter,&object);
	  if(!ptr) {
		  break;
	  }
	  do{ 
		  value = (unsigned int *)retrieve(ListIter,ptr);
		  if(value) {
		  }
	  }while(!next(ListIter,ptr));
	  destroy(ListIter,ptr);
	  x = rand() % size(List,&object);
	  while(x-- > 0) {
		  next(ListIter,ptr2);
	  }
	  value = (unsigned int *)retrieve(ListIter,ptr2);
	  if(value) {
	  }
	  ptr2 = extract(ListIter,ptr2);
	  value = (unsigned int *)retrieve(ListIter,ptr2);
	  if(value) {
	  }
  }
  destroy(ListIter,ptr2);
  destruct(List,&object);
  free(l_copy);
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
