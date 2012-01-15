#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"
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
  BinaryTree  object,*dupe;
  BinaryTreeIter *ptr;
  BinaryTreeDFSIter *dfsptr;
  BinaryTreeBFSIter *bfsptr;
  unsigned int x, y;
  unsigned int value;
  memset(&object, 0, sizeof (object));
  x = RUNS;

  construct(BinaryTree, &object,sizeof(x),FREEOBJ);
  
set_alloc(BinaryTree,  &object, ckalloc);
  set_dealloc(BinaryTree,  &object, ckfree);
  set_compare(BinaryTree,  &object, intcmp);
  set_print(BinaryTree,  &object, print);

	
  for (y = 0; y < x; y++) {
	  if (!(y % (RUNS/10))) fprintf(stderr, ".");
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
  printf("\n");
  destruct(BinaryTree,  &object);
  fprintf(stderr, "Now testing the iterators!\n");
  construct_func(BinaryTree,&object,sizeof(x),FREEOBJ, ckalloc, ckfree, intcmp,  print,
                 memcpy);
  for (x = 0; x < 15; x++) {
	  if (!(x % (RUNS/10))) fprintf(stderr, ".");
	  value = rand() % 30;
    convert(BinaryTree,  &object, &value, sizeof(value),STATIC);
  }

  ptr = create(BinaryTreeIter,  &object);
  head(BinaryTreeIter, ptr);
  do {
    value = *(unsigned int*)retrieve(BinaryTreeIter, ptr);
/*	printf("%d ",value);*/
  }
  while (!next(BinaryTreeIter, ptr));
  /*printf("\n");*/
  assign(BinaryTreeIter, ptr, &object);
  tail(BinaryTreeIter, ptr);
  do {
    value = *(unsigned int*) retrieve(BinaryTreeIter, ptr);
  } while (!prev(BinaryTreeIter, ptr));
  for(x = 0; x < RUNS; x++) {
	  if (!(x % (RUNS/10))) fprintf(stderr, ".");
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
  printf("\n");
  destroy(BinaryTreeIter, ptr);
  dupe = duplicate(BinaryTree,&object);
  ptr = create(BinaryTreeIter,  dupe);
  head(BinaryTreeIter, ptr);
  do {
    value = *(unsigned int*)retrieve(BinaryTreeIter, ptr);
	/*printf("%d ",value);*/
  }
  while (!next(BinaryTreeIter, ptr));
  /*printf("\n");*/
  assign(BinaryTreeIter, ptr, dupe);
  tail(BinaryTreeIter, ptr);
  do {
    value = *(unsigned int*) retrieve(BinaryTreeIter, ptr);
  } while (!prev(BinaryTreeIter, ptr));
  for(x = 0; x < RUNS; x++) {
	  if (!(x % (RUNS/10))) fprintf(stderr, ".");
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
  printf("\n");
  destroy(BinaryTreeIter, ptr);

  bfsptr = create(BinaryTreeBFSIter,&object);
  do {
	  value = *(unsigned int *)retrieve(BinaryTreeBFSIter, bfsptr);
	  /*fprintf(stderr,"%d ",value);*/
  }while(!next(BinaryTreeBFSIter,bfsptr));
  /*printf("\n");*/
  dfsptr = create(BinaryTreeDFSIter,&object);
  do {
	  value = *(unsigned int *)retrieve(BinaryTreeDFSIter, dfsptr);
	  /*fprintf(stderr,"%d ",value);*/
  }while(!next(BinaryTreeDFSIter,dfsptr));
  /*printf("\n");*/
  destroy(BinaryTreeDFSIter,dfsptr);
  destroy(BinaryTreeBFSIter,bfsptr);
  destruct(BinaryTree,  &object);
  destruct(BinaryTree,dupe);
  free(dupe);
  printf("\n");
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
