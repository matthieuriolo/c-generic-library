
/**
 * Copyright 2006, All Rights Reserved, Micah Villmow
 * @author Micah Villmow
 * @brief a reusable stack class that takes any object
 *
 * the stack class offers two flavors, a stacklist and
 * a stackvector, depending on which underlying structure
 * the programmer prefers
 */
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "stack.h"
#include "gen/error_macros.h"
#include "gen/access_macros.h"
#include "gen/control_macros.h"
#include "gen/function_macros.h"
#ifdef NUM_LINKS
#undef NUM_LINKS
#endif
#define NUM_LINKS 2

int8_t
push_StackList(StackList * stack, void *obj, size_t objsize, int8_t flag)
{
  Node *tmp;

  CHECK_VARN(stack, EINVAL);
  CHECK_VARN(obj, EINVAL);
  CHECK_OBJSIZE(stack,objsize,EINVAL);

  INITIALIZE_NODE(tmp,stack,obj,flag);

  if (!S(stack)) {
    H(stack) = T(stack) = tmp;
    S(stack)++;
  } else {
    ADD_BACK(tmp, stack);
  }
  return SUCCESS;
allocobjfail:
  ADD_FREE_NODE(stack,tmp);
allocfail:
  return EALLOCF;
}

int8_t
pop_StackList(StackList * stack)
{
  Node *tmp;

  CHECK_VARN(stack, EINVAL);

  if (!T(stack) || !S(stack)) {
    ERRORMSG(cannot pop top);
    return -1;
  }
  tmp = T(stack);
  REMOVE_BACK(stack);
  DELETE_OBJPTR(stack,tmp);
  ADD_FREE_NODE(stack, tmp);
  return SUCCESS;
}

void *
top_StackList(StackList * stack)
{
	CHECK_VARN(stack,CHECK(E(stack)));
	CHECK_VARN(T(stack),CHECK(E(stack)));
	return T(stack)->objptr;
}

int8_t
construct_StackList(StackList * stack,size_t objsize, int flag)
{
  int16_t x = 0;
  Node *ptr;

  CHECK_VARN(stack, EINVAL);
  if (S(stack)) {
    destruct(StackList, stack);
  }
  S(stack) = 0;
  H(stack) = T(stack) = NULL;
  E(stack) = NULL;
  stack->objfree = flag;
  stack->objsize = objsize;
  stack->API.cmp = NULL;
  stack->API.print = NULL;
  stack->API.rcmp = NULL;
  stack->API.alloc = malloc;
  stack->API.dealloc = free;
  stack->API.copy = memcpy;
  for (x = 0; x < INITIAL_SIZE; x++) {
    ptr = construct_Node(NUM_LINKS);
    N(ptr) = P(ptr) = NULL;
    ADD_FREE_NODE(stack, ptr);
  }
  return 0;
}

int8_t
construct_func_StackList(StackList * stack,size_t objsize, int flag,
                         void *(*alloc) (size_t),
                         void (*dealloc) (void *),
                         int (*cmp) (const void *, const void *),
                         int (*rcmp) (const void *, const void *),
                         void (*print) (const void *),
                         void *(*copy) (void *, const void *, size_t))
{
  S(stack) = 0;
  construct(StackList, stack,objsize,flag);
  stack->API.alloc = alloc;
  stack->API.dealloc = dealloc;
  stack->API.cmp = cmp;
  stack->API.rcmp = rcmp;
  stack->API.print = print;
  stack->API.copy = copy;
  return 0;
}

int8_t
destruct_StackList(StackList * stack)
{
  Node *tmp, *ptr;

  CHECK_VARN(stack, EINVAL);
  clear(StackList, stack);
  for (ptr = FL(stack); ptr; ptr = tmp) {
    tmp = N(ptr);
    destruct(Node, ptr);
  }
  if (E(stack)) {
    free(E(stack));
  }
  memset(stack,0,sizeof *stack);
  return 0;
}

int8_t 
clear_StackList(StackList* stack) {
  ptr_clear(StackList,stack);
  return 0;
}

/* Array based functions */

create_iter_func(Ptr_Based,StackList)
int8_t construct_StackVector(StackVector *stack,size_t objsize, int flag) {
	CHECK_VARN(stack,EINVAL);

	arr_construct(StackVector,stack,objsize,flag);

	return 0;
}

int8_t construct_func_StackVector(StackVector *stack,size_t objsize, int flag,
                         void *(*alloc) (size_t),
                         void (*dealloc) (void *),
                         int (*cmp) (const void *, const void *),
                         int (*rcmp) (const void *, const void *),
                         void (*print) (const void *),
                         void *(*copy) (void *, const void *, size_t)) {
	CHECK_VARN(stack,EINVAL);
	arr_construct(StackVector,stack,objsize,flag);
	stack->API.alloc = alloc;
	stack->API.dealloc = dealloc;
	stack->API.cmp = cmp;
	stack->API.rcmp = rcmp;
	stack->API.print = print;
	stack->API.copy = copy;
	return 0;
}

int8_t destruct_StackVector(StackVector *stack) {
	CHECK_VARN(stack,EINVAL);
	free(M(stack));
	memset(stack,0,sizeof *stack);
	return 0;
}

int8_t pop_StackVector(StackVector *stack) {
	CHECK_VARN(stack,EINVAL);
	CHECK_VARN(T(stack),EINVAL);
	if(!S(stack)) {
		return 0;
	}

	arr_pop_back(StackVector,stack);

	return 0;
}

void *top_StackVector(StackVector *stack) {
	CHECK_VARN(stack,NULL);
	CHECK_VARN(T(stack),NULL);
	return T(stack);
}

int8_t clear_StackVector(StackVector *stack) {
	CHECK_VARN(stack,EINVAL);
	if(!C(stack)) {
		return 0;
	}

	arr_clear(StackVector,stack);

	return 0;
}

int8_t push_StackVector(StackVector *stack, void *obj, size_t objsize, int flag) {
	CHECK_VARN(stack,EINVAL);
	CHECK_VARN(obj,EINVAL);
	if(objsize != O(stack)) {
		flag = 0;
		return EINVAL;
	}

	arr_push_back(StackVector,stack,obj,objsize);

	return 0;
}

int8_t resize_StackVector(StackVector *stack,size_t size) {
	void *ptr = NULL;
	CHECK_VARN(stack,EINVAL);
	CHECK_VARA(ptr = malloc(size * O(stack)),EALLOCF);
	
	arr_copy_wrap(StackVector,ptr,stack,size);

	arr_setup_pointers(StackVector,ptr,stack,size);
	return 0;
}

function(size_of, StackList)
function(set_compare, StackList)
function(set_rcompare, StackList)
function(set_print, StackList)
function(set_alloc, StackList)
function(set_dealloc, StackList)
function(set_copy, StackList)
function(set_object_size, StackList)
function(set_free_objects, StackList)




create_iter_func(Arr_Based,StackVector)

function(size_of, StackVector)
function(set_compare, StackVector)
function(set_rcompare, StackVector)
function(set_print, StackVector)
function(set_alloc, StackVector)
function(set_dealloc, StackVector)
function(set_copy, StackVector)
function(set_arr_object_size, StackVector)
function(set_free_objects, StackVector)

