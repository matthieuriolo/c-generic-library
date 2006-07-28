
/**
 * Copyright 2006, All Rights Reserved, Micah Villmow
 * @author Micah Villmow
 * @brief a reusable deque class that takes any object
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "node.h"
#include "deque.h"
#include "gen/error_macros.h"
#include "gen/access_macros.h"
#include "gen/control_macros.h"
#include "gen/function_macros.h"

#ifdef NUM_LINKS
#undef NUM_LINKS
#endif
#define NUM_LINKS 2
      
 int8_t
construct_DequeList(DequeList* deque,size_t objsize, int flag)
{
  int16_t x = 0;
  Node *ptr;

  CHECK_VARN(deque, EINVAL);
  if (S(deque)) {
    destruct(DequeList, deque);
  }
  S(deque) = 0;
  H(deque) = T(deque) = NULL;
  E(deque) = NULL;
  deque->objfree = flag;
  deque->objsize = objsize;
  deque->API.cmp = NULL;
  deque->API.print = NULL;
  deque->API.rcmp = NULL;
  deque->API.alloc = malloc;
  deque->API.dealloc = free;
  deque->API.copy = memcpy;
  for (x = 0; x < INITIAL_SIZE; x++) {
    ptr = construct_Node(NUM_LINKS);
    N(ptr) = P(ptr) = NULL;
    ADD_FREE_NODE(deque, ptr);
  }
  return 0;
}

 int8_t
construct_func_DequeList(DequeList * deque,size_t objsize, int flag,
                     void *(*alloc) (size_t),
                     void (*dealloc) (void *),
                     int (*cmp) (const void *, const void *),
                     int (*rcmp) (const void *, const void *),
                     void (*print) (const void *),
                     void *(*copy) (void *, const void *, size_t))
{
  S(deque) = 0;
  construct(DequeList, deque,objsize,flag);
  deque->API.alloc = alloc;
  deque->API.dealloc = dealloc;
  deque->API.cmp = cmp;
  deque->API.rcmp = rcmp;
  deque->API.print = print;
  deque->API.copy = copy;
  return 0;
}

 int8_t
destruct_DequeList(DequeList * deque)
{
  Node *tmp, *ptr;

  CHECK_VARN(deque, EINVAL);
  clear(DequeList, deque);
  for (ptr = FL(deque); ptr; ptr = tmp) {
    tmp = N(ptr);
    destruct(Node, ptr);
  }
  if (E(deque)) {
    free(E(deque));
  }
  FL(deque) = NULL;
  memset(deque,0,sizeof *deque);
  return 0;
}

int8_t convert_DequeList(DequeList *deque, void *obj, size_t objsize, int flag) {
	return push_back_DequeList(deque,obj,objsize,flag);
}
 int8_t
push_back_DequeList(DequeList * deque, void *obj, size_t objsize, int flag)
{
  Node *tmp;

  CHECK_VARN(deque, EINVAL);
  CHECK_VARN(obj, EINVAL);
  CHECK_OBJSIZE(deque,objsize,EINVAL);

  INITIALIZE_NODE(tmp,deque,obj,flag);

  if (!S(deque)) {
    H(deque) = T(deque) = tmp;
    S(deque)++;
  } else {
    ADD_BACK(tmp, deque);
  }
  return SUCCESS;
allocobjfail:
  ADD_FREE_NODE(deque,tmp);
allocfail:
  return EALLOCF;
}

int8_t
push_front_DequeList(DequeList *deque, void *obj, size_t objsize, int flag) {
  Node *tmp;

  CHECK_VARN(deque, EINVAL);
  CHECK_VARN(obj, EINVAL);
  CHECK_OBJSIZE(deque,objsize,EINVAL);

  INITIALIZE_NODE(tmp,deque,obj,flag);

  if (!S(deque)) {
    H(deque) = T(deque) = tmp;
    S(deque)++;
  } else {
    ADD_FRONT(tmp, deque);
  }

  return SUCCESS;
allocobjfail:
  ADD_FREE_NODE(deque,tmp);
allocfail:
  return -EALLOCF;
}

 int8_t
pop_front_DequeList(DequeList * deque)
{
  Node *tmp;

  CHECK_VARN(deque, EINVAL);

  if (!H(deque) || !S(deque)) {
    ERRORMSG(cannot pop front);
    return -1;
  }
  tmp = H(deque);
  REMOVE_FRONT(deque);
  DELETE_OBJPTR(deque,tmp);
  ADD_FREE_NODE(deque, tmp);
  return SUCCESS;
}

int8_t 
pop_back_DequeList(DequeList *deque) {
	Node *tmp;
	CHECK_VARN(deque,EINVAL);

	if(!T(deque) || !S(deque)) {
		ERRORMSG(cannot pop back);
		return -1;
	}
	tmp = T(deque);
	REMOVE_BACK(deque);
	DELETE_OBJPTR(deque,tmp);
	ADD_FREE_NODE(deque,tmp);
	return SUCCESS;
}

 void *
front_DequeList(DequeList * deque)
{
  CHECK_VARN(deque, NULL);
  CHECK_VARE(H(deque), NULL);
  return H(deque)->objptr;
}

void *
back_DequeList(DequeList *deque) {
	CHECK_VARN(deque,NULL);
	CHECK_VARE(T(deque),NULL);
	return T(deque)->objptr;
}

 int8_t
clear_DequeList(DequeList *deque) {
  ptr_clear(DequeList,deque);
  return 0;
}

create_iter_func(Ptr_Based,DequeList)

function(size_of, DequeList)
function(set_compare, DequeList)
function(set_rcompare, DequeList)
function(set_print, DequeList)
function(set_alloc, DequeList)
function(set_dealloc, DequeList)
function(set_copy, DequeList)

int8_t construct_DequeVector(DequeVector *deque,size_t objsize, int flag) {
	CHECK_VARN(deque,EINVAL);

	arr_construct(DequeVector,deque,objsize,flag);

	return 0;
}

int8_t construct_func_DequeVector(DequeVector *deque,size_t objsize, int flag,
                         void *(*alloc) (size_t),
                         void (*dealloc) (void *),
                         int (*cmp) (const void *, const void *),
                         int (*rcmp) (const void *, const void *),
                         void (*print) (const void *),
                         void *(*copy) (void *, const void *, size_t)) {
	CHECK_VARN(deque,EINVAL);
	arr_construct(DequeVector,deque,objsize,flag);
	deque->API.alloc = alloc;
	deque->API.dealloc = dealloc;
	deque->API.cmp = cmp;
	deque->API.rcmp = rcmp;
	deque->API.print = print;
	deque->API.copy = copy;
	return 0;
}

int8_t destruct_DequeVector(DequeVector *deque) {
	CHECK_VARN(deque,EINVAL);
	free(M(deque));
	memset(deque,0,sizeof *deque);
	return 0;
}

int8_t pop_front_DequeVector(DequeVector *deque) {
	CHECK_VARN(deque,EINVAL);
	CHECK_VARN(H(deque),EINVAL);
	if(!S(deque)) {
		return 0;
	}

	arr_pop_front(DequeVector,deque);

	return 0;
}
int8_t pop_back_DequeVector(DequeVector *deque) {
	CHECK_VARN(deque,EINVAL);
	CHECK_VARN(T(deque),EINVAL);
	if(!S(deque)) {
		return 0;
	}

	arr_pop_back(DequeVector,deque);

	return 0;
}

void *back_DequeVector(DequeVector *deque) {
	CHECK_VARN(deque,NULL);
	CHECK_VARN(T(deque),NULL);
	return T(deque);
}
void *front_DequeVector(DequeVector *deque) {
	CHECK_VARN(deque,NULL);
	CHECK_VARN(H(deque),NULL);
	return H(deque);
}

int8_t clear_DequeVector(DequeVector *deque) {
	CHECK_VARN(deque,EINVAL);
	if(!C(deque)) {
		return 0;
	}

	arr_clear(DequeVector,deque);

	return 0;
}

int8_t push_front_DequeVector(DequeVector *deque, void *obj, size_t objsize, int flag) {
	CHECK_VARN(deque,EINVAL);
	CHECK_VARN(obj,EINVAL);
	if(objsize != O(deque)) {
		flag = 0;
		return EINVAL;
	}

	arr_push_front(DequeVector,deque,obj,objsize);

	return 0;
}

int8_t push_back_DequeVector(DequeVector *deque, void *obj, size_t objsize, int flag) {
	CHECK_VARN(deque,EINVAL);
	CHECK_VARN(obj,EINVAL);
	if(objsize != O(deque)) {
		flag = 0;
		return EINVAL;
	}

	arr_push_back(DequeVector,deque,obj,objsize);

	return 0;
}

int8_t resize_DequeVector(DequeVector *deque,size_t size) {
	void *ptr = NULL;
	CHECK_VARN(deque,EINVAL);
	CHECK_VARA(ptr = malloc(size * O(deque)),EALLOCF);
	
	arr_copy_wrap(DequeVector,ptr,deque,size);

	arr_setup_pointers(DequeVector,ptr,deque,size);
	return 0;
}
create_iter_func(Arr_Based,DequeVector)

function(size_of, DequeVector)
function(set_compare, DequeVector)
function(set_rcompare, DequeVector)
function(set_print, DequeVector)
function(set_alloc, DequeVector)
function(set_dealloc, DequeVector)
function(set_copy, DequeVector)
