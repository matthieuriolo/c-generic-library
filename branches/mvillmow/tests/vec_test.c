#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gen/error_macros.h"
#define RUNS 10000


int
main(void)
{
  Vector *test;
  uint32_t input, x;

  test = malloc(sizeof *test);
  memset(test,0,sizeof( *test));
  construct(Vector,test,sizeof(x),FREEOBJ);
  printf("Testing auto-resize!\n");
  resize(Vector,test,RUNS);
  for(x = 0; x < RUNS; x++) {
	  insert_at_Vector(test,&x,x);
  }
  printf("Testing push_back\n");
  for (x = 0; x < RUNS; x++) {
    for (input = 10 * x; input < 10 * (x + 1); input++) {
      push_back(Vector,test, &input,sizeof(input));
    }
  }
  for (x = 0; x < RUNS; x++) {
    for (input = 10 * x; input < 10 * (x + 1); input++) {
      pop_front(Vector,test);
    }
  }
  for (x = 0; x < RUNS; x++) {
    for (input = 10 * x; input < 10 * (x + 1); input++) {
      push_front(Vector,test, &input,sizeof(input));
    }
  }
  printf("Testing destruction!\n");
  destruct(Vector,test);
  free(test);
  return EXIT_SUCCESS;
}
