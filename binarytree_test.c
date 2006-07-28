#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"
#define RUNS 1000000
#define BOUND 10000
#define BASE 0
#define NUMCASES 10

int32_t intcmp(const void *, const void *);
int32_t intrcmp(const void *, const void *);
void  print(const void *);
void  ckfree(void *);
void *ckalloc(size_t);

int
main(void) {
  BinaryTree  object;
  BinaryTreeIter *ptr;
  unsigned int x, y;
  unsigned int value;
  memset(&object, 0, sizeof (object));
  x = RUNS;
  construct(BinaryTree, &object,sizeof(x),FREEOBJ);
  set_alloc(BinaryTree,  &object, ckalloc);
  set_dealloc(BinaryTree,  &object, ckfree);
  set_compare(BinaryTree,  &object, intcmp);
  set_rcompare(BinaryTree,  &object, intrcmp);
  set_print(BinaryTree,  &object, print);
  for (y = 0; y < x; y++) {
    srand((x * y) / (x - y) + (x + y / x));
    switch ((rand() % NUMCASES) + BASE) {
        case 0:
        case 10:
        case 12:
        case 13:
        case 2:
        case 17:
        case 8:
          value = rand() % BOUND;
          insert(BinaryTree,  &object, &value, STATIC);
          break;
        case 9:
        case 3:
        case 15:
        case 4:
        case 5:
        case 14:
        case 7:
	  value = rand() % BOUND;
          delete(BinaryTree,  &object,&value);
          break;
        case 11:
        case 1:
        case 6:
        case 16:
	  /*value = rand() % BOUND;
	  find(BinaryTree,&object,&value);
          break;*/
        default:
          value = rand() % BOUND;
          insert(BinaryTree,  &object, &value,STATIC);
          break;
    };
    /*dump(BinaryTree,&object);*/
  }
  destruct(BinaryTree,  &object);
  fprintf(stderr, "Now testing the iterators!\n");
  construct_func(BinaryTree,&object,sizeof(x),FREEOBJ, ckalloc, ckfree, intcmp, intrcmp, print,
                 memcpy);
  for (x = 0; x < 15; x++) {
	  value = rand() % 30;
    convert(BinaryTree,  &object, &value, sizeof(value),STATIC);
  }

  ptr = create(BinaryTreeIter,  &object);
  head(BinaryTreeIter, ptr);
  do {
    value = *(unsigned int*)retrieve(BinaryTreeIter, ptr);
  }
  while (!next(BinaryTreeIter, ptr));
  assign(BinaryTreeIter, ptr, &object);
  tail(BinaryTreeIter, ptr);
  do {
    value = *(unsigned int*) retrieve(BinaryTreeIter, ptr);
  } while (!prev(BinaryTreeIter, ptr));
  for(x = 0; x < RUNS; x++) {
	  switch(rand() % 2) {
		  case 1:
			  prev(BinaryTreeIter,ptr);
			  break;
		  case 0:
			  next(BinaryTreeIter,ptr);
			  break;
		  default:
			  break;
	  }
  }
  destroy(BinaryTreeIter, ptr);
  destruct(BinaryTree,  &object);
  return EXIT_SUCCESS;
}

int32_t
intcmp(const void *a, const void *b)
{
	return (*(int *)a > *(int *)b) - (*(int *)a < *(int *)b);
}

int32_t
intrcmp(const void *a, const void *b)
{
  if ((*(const int *) a) > (*(const int *) b)) {
    return -1;
  } else if ((*(const int *) a) < (*(const int *) b)) {
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
