
/**
 * Copyright 2006, All Rights Reserved, Micah Villmow
 * @author Micah Villmow
 * @brief a reusable queue class that takes any object
 */

#include <stdio.h> 
#include <string.h>

#include "node.h"
#include "queue.h"
#include "gen/error_macros.h"
#include "gen/access_macros.h"
#include "gen/control_macros.h"
#include "gen/function_macros.h"
#ifdef NUM_LINKS
#undef NUM_LINKS
#endif
#define NUM_LINKS 2

      
 int8_t
construct_QueueList(QueueList * queue,size_t objsize, int flag)
{
  int16_t x = 0;
  Node *ptr;

  CHECK_VARN(queue, EINVAL);
  if (S(queue)) {
    destruct(QueueList, queue);
  }
  S(queue) = 0;
  H(queue) = T(queue) = NULL;
  E(queue) = NULL;
  queue->objsize = objsize;
  queue->objfree = flag;
  queue->API.cmp = NULL;
  queue->API.print = NULL;
  queue->API.rcmp = NULL;
  queue->API.alloc = malloc;
  queue->API.dealloc = free;
  queue->API.copy = memcpy;
  for (x = 0; x < INITIAL_SIZE; x++) {
    ptr = construct_Node(NUM_LINKS);
    N(ptr) = P(ptr) = NULL;
    ADD_FREE_NODE(queue, ptr);
  }
  return 0;
}

 int8_t
construct_func_QueueList(QueueList * queue,size_t objsize, int flag,
                     void *(*alloc) (size_t),
                     void (*dealloc) (void *),
                     int (*cmp) (const void *, const void *,size_t),
                     int (*rcmp) (const void *, const void *,size_t),
                     void (*print) (const void *),
                     void *(*copy) (void *, const void *, size_t))
{
  S(queue) = 0;
  construct(QueueList, queue,objsize,flag);
  queue->API.alloc = alloc;
  queue->API.dealloc = dealloc;
  queue->API.cmp = cmp;
  queue->API.rcmp = rcmp;
  queue->API.print = print;
  queue->API.copy = copy;
  return 0;
}

 int8_t
destruct_QueueList(QueueList * queue)
{
  Node *tmp, *ptr;

  CHECK_VARN(queue, EINVAL);
  clear(QueueList, queue);
  for (ptr = FL(queue); ptr; ptr = tmp) {
    tmp = N(ptr);
    destruct(Node, ptr);
  }
  if (E(queue)) {
    free(E(queue));
  }
  memset(queue,0,sizeof *queue);
  return 0;
}

 int8_t
push_QueueList(QueueList * queue, void *obj, size_t objsize, int flag)
{
  Node *tmp;

  CHECK_VARN(queue, EINVAL);
  CHECK_VARN(obj, EINVAL);
  CHECK_OBJSIZE(queue,objsize,EINVAL);

  INITIALIZE_NODE(tmp,queue,obj,flag);

  if (!S(queue)) {
    H(queue) = T(queue) = tmp;
    S(queue)++;
  } else {
    ADD_BACK(tmp, queue);
  }
  return SUCCESS;
allocobjfail:
  ADD_FREE_NODE(queue,tmp);
allocfail:
  return EALLOCF;
}

 int8_t
pop_QueueList(QueueList * queue)
{
  Node *tmp;

  CHECK_VARN(queue, EINVAL);

  if (!H(queue) || !S(queue)) {
    ERRORMSG(cannot pop front);
    return -1;
  }
  tmp = H(queue);
  REMOVE_FRONT(queue);
  DELETE_OBJPTR(queue,tmp);
  ADD_FREE_NODE(queue, tmp);
  return SUCCESS;
}

 void *
front_QueueList(QueueList * queue)
{
  CHECK_VARN(queue, NULL);
  CHECK_VARE(H(queue), NULL);
  return H(queue)->objptr;
}

 int8_t
clear_QueueList(QueueList *queue) {
  ptr_clear(QueueList,queue);
  return 0;
}


create_iter_func(Ptr_Based,QueueList)

function(size_of, QueueList)
function(set_compare, QueueList)
function(set_rcompare, QueueList)
function(set_print, QueueList)
function(set_alloc, QueueList)
function(set_dealloc, QueueList)
function(set_copy, QueueList)
function(duplicate_ptr_struct,QueueList)

int8_t construct_QueueVector(QueueVector *queue,size_t objsize, int flag) {
	CHECK_VARN(queue,EINVAL);

	arr_construct(QueueVector,queue,objsize,flag);

	return 0;
}

int8_t construct_func_QueueVector(QueueVector *queue,size_t objsize, int flag,
                         void *(*alloc) (size_t),
                         void (*dealloc) (void *),
                         int (*cmp) (const void *, const void *,size_t),
                         int (*rcmp) (const void *, const void *,size_t),
                         void (*print) (const void *),
                         void *(*copy) (void *, const void *, size_t)) {
	CHECK_VARN(queue,EINVAL);
	arr_construct(QueueVector,queue,objsize,flag);
	queue->API.alloc = alloc;
	queue->API.dealloc = dealloc;
	queue->API.cmp = cmp;
	queue->API.rcmp = rcmp;
	queue->API.print = print;
	queue->API.copy = copy;
	return 0;
}

int8_t destruct_QueueVector(QueueVector *queue) {
	CHECK_VARN(queue,EINVAL);
	free(M(queue));
	memset(queue,0,sizeof *queue);
	return 0;
}

int8_t pop_QueueVector(QueueVector *queue) {
	CHECK_VARN(queue,EINVAL);
	CHECK_VARN(H(queue),EINVAL);
	if(!S(queue)) {
		return 0;
	}

	arr_pop_front(QueueVector,queue);

	return 0;
}

void *front_QueueVector(QueueVector *queue) {
	CHECK_VARN(queue,NULL);
	CHECK_VARN(H(queue),NULL);
	return H(queue);
}

int8_t clear_QueueVector(QueueVector *queue) {
	CHECK_VARN(queue,EINVAL);
	if(!C(queue)) {
		return 0;
	}

	arr_clear(QueueVector,queue);

	return 0;
}

int8_t push_QueueVector(QueueVector *queue, void *obj, size_t objsize, int flag) {
	CHECK_VARN(queue,EINVAL);
	CHECK_VARN(obj,EINVAL);
	if(objsize != O(queue)) {
		flag = 0;
		return EINVAL;
	}

	arr_push_back(QueueVector,queue,obj,objsize);

	return 0;
}

int8_t resize_QueueVector(QueueVector *queue,size_t size) {
	void *ptr = NULL;
	CHECK_VARN(queue,EINVAL);
	CHECK_VARA(ptr = malloc(size * O(queue)),EALLOCF);
	
	arr_copy_wrap(QueueVector,ptr,queue,size);

	arr_setup_pointers(QueueVector,ptr,queue,size);
	return 0;
}
create_iter_func(Arr_Based,QueueVector)

function(size_of, QueueVector)
function(set_compare, QueueVector)
function(set_rcompare, QueueVector)
function(set_print, QueueVector)
function(set_alloc, QueueVector)
function(set_dealloc, QueueVector)
function(set_copy, QueueVector)
function(duplicate_arr_struct,QueueVector)


