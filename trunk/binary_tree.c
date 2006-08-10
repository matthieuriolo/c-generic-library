
/**
 * Copyright 2006, Micah Villmow, All Rights Reserved
 * @file tree.c
 * @author Micah Villmow
 * @brief a generic binary tree that can handle any sized
 * object
 */

#include <stdio.h>
#include <string.h>

#include "node.h"
/*#include "queue.h"
#include "stack.h"*/
#include "binary_tree.h"
#include "gen/error_macros.h"
#include "gen/access_macros.h"
#include "gen/control_macros.h"
#include "gen/function_macros.h"


#ifdef NUM_LINKS
#undef NUM_LINKS
#endif

#define NUM_LINKS 3

#ifdef PARENT
#undef PARENT
#endif

#define PARENT (NUM_LINKS-1)

void dump_node(Node *ptr);
void move_to_free(BinaryTree *tree, Node *root);


#ifndef INSERT_RIGHT
#define INSERT_RIGHT(P,C)\
{\
	(C)->ptr[RIGHT] = (P)->ptr[RIGHT];\
	(P)->ptr[RIGHT] = C;\
	(C)->ptr[PARENT] = P;\
  	S(tree)++;\
}
#endif

#ifndef INSERT_LEFT
#define INSERT_LEFT(P,C)\
{\
	(C)->ptr[LEFT] = (P)->ptr[LEFT];\
	(P)->ptr[LEFT] = C;\
	(C)->ptr[PARENT] = P;\
  	S(tree)++;\
}
#endif

int8_t
construct_BinaryTree(BinaryTree * tree,size_t objsize, int flag)
{
  int16_t x = 0;
  Node *ptr = NULL;

  CHECK_VARN(tree, -1);
  if (S(tree)) {
    destruct(BinaryTree, tree);
  }
  S(tree) = tree->objsize = 0;
  tree->objfree = 0;
  H(tree) = FL(tree) = NULL;
  E(tree) = NULL;
  tree->objfree = FREEOBJ;
  tree->API.cmp = memcmp;
  tree->API.print = NULL;
  tree->API.rcmp = NULL;
  tree->API.alloc = malloc;
  tree->API.dealloc = free;
  tree->API.copy = memcpy;
  tree->objsize = objsize;
  tree->objfree = flag;
  for (x = 0; x < INITIAL_SIZE; x++) {
    ptr = construct_Node(NUM_LINKS);
    N(ptr) = P(ptr) = NULL;
    ADD_FREE_NODE(tree, ptr);
  }
  return SUCCESS;
}

int8_t
construct_func_BinaryTree(BinaryTree * tree,size_t objsize, int flag,
                           void *(*alloc) (size_t),
                           void (*dealloc) (void *),
                           int (*cmp) (const void *, const void *,size_t),
                           int (*rcmp) (const void *, const void *,size_t),
                           void (*print) (const void *),
                           void *(*copy) (void *, const void *, size_t))
{
  memset(tree, 0, sizeof (tree));
  construct(BinaryTree, tree,objsize,flag);
  tree->API.alloc = alloc;
  tree->API.dealloc = dealloc;
  tree->API.cmp = cmp;
  tree->API.rcmp = rcmp;
  tree->API.print = print;
  tree->API.copy = copy;
  return SUCCESS;
}

int8_t
destruct_BinaryTree(BinaryTree * tree)
{
  Node *tmp = NULL, *ptr = NULL;


  CHECK_VARN(tree, EINVAL);

  clear(BinaryTree, tree);

  for (ptr = FL(tree); ptr; ptr = tmp) {
    tmp = N(ptr);
    destruct(Node, ptr);
  }
  if (E(tree)) {
    free(E(tree));
  }
  memset(tree,0,sizeof *tree);
  return SUCCESS;
}
void move_to_free(BinaryTree *tree, Node *root) {
	if(root->ptr) {
		if(root->ptr[LEFT]) {
			move_to_free(tree,root->ptr[LEFT]);
		}
		if(root->ptr[RIGHT]) {
			move_to_free(tree,root->ptr[RIGHT]);
		}
	} else {
		root->ptr = malloc(sizeof *root->ptr * NUM_LINKS);
	}
	DELETE_OBJPTR(tree,root);
	ADD_FREE_NODE(tree,root);
}
int8_t
clear_BinaryTree(BinaryTree * tree)
{
  CHECK_VARN(tree, EINVAL);
  move_to_free(tree,H(tree));
  H(tree) = NULL;
  S(tree) = 0;
  return SUCCESS;
}

void *
insert_BinaryTree(BinaryTree * tree, void *obj, size_t objsize, int flag)
{
  Node *ptr = NULL, *tmp = NULL;
  int res = 0;
  CHECK_VARN(tree,CHECK(E(tree)));
  CHECK_VARN(obj,CHECK(E(tree)));
  CHECK_OBJSIZE(tree, objsize,CHECK(E(tree)));
  INITIALIZE_NODE(tmp,tree,obj,flag);

  if(!S(tree)) {
	  H(tree) = tmp;
	  tmp->ptr[PARENT] = NULL;
	  S(tree)++;
  } else {
	  ptr = H(tree);
	  TRAVERSE_TREE(ptr,tree,tmp->objptr,res,objsize);
	  if(res < 0) {
		  if(ptr->ptr[RIGHT] == T(tree)) {
			  T(tree) = tmp;
		  }
		  INSERT_RIGHT(ptr,tmp);
	  } else if(res > 0) {
		  INSERT_LEFT(ptr,tmp);
	  } else {
		  DELETE_OBJPTR(tree,tmp);
		  ADD_FREE_NODE(tree,tmp);
	  }
  }
  return tmp;
allocobjfail:
  ADD_FREE_NODE(tree,tmp);
allocfail:
  ALLOCFAIL(object);
  return CHECK(E(tree));
}

int8_t
delete_BinaryTree(BinaryTree * tree, void *obj, size_t objsize)
{
  Node *ptr = NULL;
  int res = 0;
  CHECK_VARN(tree, EINVAL);
  CHECK_VARN(obj, EINVAL);
  CHECK_OBJSIZE(tree, objsize, EINVAL);
  CHECK_VARE(S(tree),EEMPTY);

  ptr = H(tree);

repeat_delete:
  TRAVERSE_TREE(ptr,tree,obj,res,objsize);
  
  if(res == 0) {
	  Node* tmp = ptr,*pnt = ptr->ptr[PARENT];
	  int x =0;
	  if(L(ptr) && R(ptr)) {
		  Node *ptr2;
		  /* there are two children present,
		   * need to handle this accordingly
		   */
		  ptr2 = R(ptr);
		  while(L(ptr2)) {
			  ptr2 = L(ptr2);
		  }
		  DELETE_OBJPTR(tree,ptr);
		  ptr->objptr = tree->API.alloc(O(tree));
		  tree->API.copy(ptr->objptr,ptr2->objptr,O(tree));
		  obj = ptr->objptr;
		  ptr = R(ptr);
		  if(T(tree) == ptr2) {
			  T(tree) = ptr2->ptr[PARENT];
		  }
		  goto repeat_delete;
	  } else if(L(ptr)) {
		  /* only the left child is present
		   * update is simple
		   */
		  if(!pnt) {
			  H(tree) = L(ptr);
		  } else {
			  for(x = 0; x < PARENT; x++) {
				  if(pnt->ptr[x] == tmp) {
					  pnt->ptr[x] = L(ptr);
				  }
			  }
		  }
		  L(ptr)->ptr[PARENT] = pnt;
		  DELETE_OBJPTR(tree,tmp);
		  ADD_FREE_NODE(tree,tmp);
	  } else if(R(ptr)) {
		  /* only the right child is present
		   * update is simple
		   */
		  if(!pnt) {
			  H(tree) = R(ptr);
		  } else {
			  for(x = 0; x < PARENT;x++) {
				  if(pnt->ptr[x] == tmp) {
					pnt->ptr[x] = R(ptr);	  
				  }
			  }
		  }
		  R(ptr)->ptr[PARENT] = pnt;
		  DELETE_OBJPTR(tree,tmp);
		  ADD_FREE_NODE(tree,tmp);
	  } else {
		  /* no children are present,
		   * just remove the node
		   */
		  if(!pnt) {
			  H(tree) = NULL;
		  } else {
			  for(x = 0; x < PARENT; x++) {
				  if(pnt->ptr[x] == tmp) {
					  pnt->ptr[x] = NULL;
				  }
			  }
		  }
		  DELETE_OBJPTR(tree,tmp);
		  ADD_FREE_NODE(tree,tmp);
	 }
  } else {
	  return ENOVAL;
  }
  S(tree)--;
  return SUCCESS;
}

void *
find_BinaryTree(BinaryTree * tree, void *obj, size_t objsize)
{
  Node *ptr = NULL;
  int res = 0;
  CHECK_VARN(tree, NULL);
  CHECK_VARN(obj, NULL);
  CHECK_OBJSIZE(tree, objsize,NULL);
  CHECK_VARE(S(tree),NULL);
  ptr = H(tree);
  TRAVERSE_TREE(ptr,tree,obj,res,objsize);
  if(res == 0) {
	  return ptr->objptr;
  } else {
	  return NULL;
  }
}

BinaryTree* duplicate_BinaryTree(BinaryTree* src) {
	BinaryTree *dst;
	BinaryTreeDFSIter *dfsiter;
	Node *tmp;
	size_t x;
	CHECK_VARN(src,NULL);
	CHECK_VARA(dst = malloc(sizeof *dst),NULL);
	dst->objfree = FREEOBJ;
	dst->objsize = src->objsize;
	dst->API.alloc = src->API.alloc;
	dst->API.dealloc = src->API.dealloc;
	dst->API.cmp = src->API.cmp;
	dst->API.rcmp = src->API.rcmp;
	dst->API.print = src->API.print;
	dst->API.copy = src->API.copy;
	dst->error = src->error;
	dst->size = 0;
	FL(dst) = H(dst) = T(dst) = NULL;
	for(x = 0; x < (INITIAL_SIZE + src->size); x++) {
		tmp = construct_Node(NUM_LINKS);
		ADD_FREE_NODE(dst,tmp);
	}
	dfsiter = create(BinaryTreeDFSIter,src);
	do {
		insert_BinaryTree(dst,retrieve(BinaryTreeDFSIter,dfsiter),dst->objsize,STATIC);
	}while(!next(BinaryTreeDFSIter,dfsiter));
	destroy(BinaryTreeDFSIter,dfsiter);
	return dst;
allocobjfail:
allocfail:
	destruct_BinaryTree(dst);
	return NULL;
}

void*
max_BinaryTree(BinaryTree* tree) {
	Node * ptr = NULL;
	CHECK_VARN(tree,NULL);
	CHECK_VARN(H(tree),NULL);
	ptr = H(tree);
	while(L(ptr)) {
		ptr = L(ptr);
	}
	return ptr;
}

void *
min_BinaryTree(BinaryTree* tree) {
	Node* ptr = NULL;
	CHECK_VARN(tree,NULL);
	CHECK_VARN(H(tree),NULL);
	ptr = H(tree);
	while(R(ptr)) {
		ptr = R(ptr);
	}
	return ptr;
}

void dump_BinaryTree(BinaryTree* tree) {
	fprintf(stderr,"Tree = %p, objfree = %u, objsize = %u, size = %u\n",tree,tree->objfree,O(tree),S(tree));
	fprintf(stderr,"head = %p, tail = %p, FL = %p, E = %p\n",H(tree),T(tree),FL(tree),E(tree));
	dump_node(H(tree));
}

void dump_node(Node *root) {
	int x = 0;
	if(!root) {
		return;
	}
	fprintf(stderr,"node = %p, parent = %p, flags = %p, objptr = %u children:\n",root,root->ptr[PARENT],root->flags,*(int *)root->objptr);
	for(x = 0; x < NUM_LINKS-1; x++) {
		fprintf(stderr,"%d) %p ",x,root->ptr[x]);
	}
	fprintf(stderr,"\n");
	for(x = 0; x < NUM_LINKS-1; x++) {
		dump_node(root->ptr[x]);
	}
}


function(size_of, BinaryTree)
function(set_compare, BinaryTree)
function(set_rcompare, BinaryTree)
function(set_print, BinaryTree)
function(set_alloc, BinaryTree)
function(set_dealloc, BinaryTree)
function(set_copy, BinaryTree)

void destroy_BinaryTreeIter(BinaryTreeIter* iter) {
	if(iter) {
		free(iter);
	}
}
void destroy_BinaryTreeDFSIter(BinaryTreeDFSIter* iter) {
	if(iter) {
		destruct(StackList,&iter->stack);
		free(iter);
	}	
}


void destroy_BinaryTreeBFSIter(BinaryTreeBFSIter* iter) {
	if(iter) {
		destruct(QueueList,&iter->queue);
		free(iter);
	}
}

int8_t assign_BinaryTreeBFSIter(BinaryTreeBFSIter* iter, BinaryTree* obj) {
	CHECK_VARN(iter,EINVAL);
	CHECK_VARN(obj,EINVAL);
	CHECK_VARN(H(obj),EINVAL);
	iter->parent = obj;
	iter->ptr = H(obj);
	memset(&iter->queue,0,sizeof iter->queue);
	construct(QueueList,&iter->queue,sizeof *H(obj),NOFREE);
	push(QueueList,&iter->queue,iter->ptr->ptr[LEFT],DYNAMIC);
	push(QueueList,&iter->queue,iter->ptr->ptr[RIGHT],DYNAMIC);
	return SUCCESS;
}

int8_t assign_BinaryTreeIter(BinaryTreeIter* iter, BinaryTree* obj) {
	CHECK_VARN(iter,EINVAL);
	CHECK_VARN(obj,EINVAL);
	CHECK_VARN(H(obj),EINVAL);
	iter->parent = obj;
	iter->ptr = H(obj);
	while(L(iter->ptr)) {
		iter->ptr = L(iter->ptr);
	}
	return SUCCESS;
}
int8_t assign_BinaryTreeDFSIter(BinaryTreeDFSIter* iter, BinaryTree* obj) {
	CHECK_VARN(iter,EINVAL);
	CHECK_VARN(obj,EINVAL);
	iter->parent = obj;
	iter->ptr =H(obj);
	memset(&iter->stack,0,sizeof iter->stack);
	construct(StackList,&iter->stack,sizeof *H(obj),NOFREE);
	push(StackList,&iter->stack,iter->ptr->ptr[RIGHT],DYNAMIC);
	push(StackList,&iter->stack,iter->ptr->ptr[LEFT],DYNAMIC);
	return 0;
}
BinaryTreeDFSIter* create_BinaryTreeDFSIter(BinaryTree* obj) {
	BinaryTreeDFSIter* iter;
	CHECK_VARN(obj,NULL);
	CHECK_VARE(S(obj),NULL);
	CHECK_VARA((iter = malloc(sizeof *iter)), NULL);
	iter->ptr = H(obj);
	iter->parent = obj;
	memset(&iter->stack,0,sizeof iter->stack);
	construct(StackList,&iter->stack,sizeof *H(obj),NOFREE);
	push(StackList,&iter->stack,iter->ptr->ptr[RIGHT],DYNAMIC);
	push(StackList,&iter->stack,iter->ptr->ptr[LEFT],DYNAMIC);
	return iter;
}
BinaryTreeIter* create_BinaryTreeIter(BinaryTree* obj) {
	BinaryTreeIter* iter;
	CHECK_VARN(obj,NULL);
	CHECK_VARE(S(obj),NULL);
	CHECK_VARA((iter = malloc(sizeof *iter)),NULL);
	iter->ptr = H(obj);
	while(L(iter->ptr)) {
		iter->ptr = L(iter->ptr);
	}
	iter->parent = obj;
	return iter;
}
BinaryTreeBFSIter* create_BinaryTreeBFSIter(BinaryTree* obj) {
	BinaryTreeBFSIter* iter;
	CHECK_VARN(obj,NULL);
	CHECK_VARE(S(obj),NULL);
	CHECK_VARA((iter = malloc(sizeof *iter)),NULL);
	iter->parent = obj;
	iter->ptr = H(obj);
	memset(&iter->queue,0,sizeof iter->queue);
	construct(QueueList,&iter->queue,sizeof *H(obj),NOFREE);
	push(QueueList,&iter->queue,iter->ptr->ptr[LEFT],DYNAMIC);
	push(QueueList,&iter->queue,iter->ptr->ptr[RIGHT],DYNAMIC);
	return iter;
}

void* retrieve_BinaryTreeBFSIter(BinaryTreeBFSIter* iter) {
	CHECK_VARN(iter,NULL);
	CHECK_VARN(iter->ptr,NULL);
	return iter->ptr->objptr;
}

void* retrieve_BinaryTreeDFSIter(BinaryTreeDFSIter* iter) {
	CHECK_VARN(iter,NULL);
	CHECK_VARN(iter->ptr,NULL);
	return iter->ptr->objptr;
}
void* retrieve_BinaryTreeIter(BinaryTreeIter* iter) {
	CHECK_VARN(iter,NULL);
	CHECK_VARN(iter->ptr,NULL);
	return iter->ptr->objptr;
}
/*
 * How do we do prev operations for Queue-based BFS & Stack-based DFS?
int8_t prev_BinaryTreeBFSIter(BinaryTreeBFSIter* iter) {
	CHECK_VARN(iter,EINVAL);
	CHECK_VARN(iter->parent,EINVAL);
	return 0;
}
int8_t prev_BinaryTreeDFSIter(BinaryTreeDFSIter* iter) {
	CHECK_VARN(iter,EINVAL);
	CHECK_VARN(iter->parent,EINVAL);
	return 0;
}*/
int8_t prev_BinaryTreeIter(BinaryTreeIter *iter) {
	CHECK_VARN(iter,EINVAL);
	CHECK_VARN(iter->parent,EINVAL);
	/*printf("at %p L %p R %p\n",iter->ptr,L(iter->ptr),R(iter->ptr));*/
	if(L(iter->ptr)) {
		iter->ptr = L(iter->ptr);
		while(R(iter->ptr)) {
			iter->ptr = R(iter->ptr);
		}
	} else {
		if(iter->ptr == H(iter->parent)) {
			return 0;
		} else if(!iter->ptr) {
			iter->ptr = H(iter->parent);
			return -1;
		} else {
			/*printf("Checking %p against %p h %p\n",iter->ptr,iter->ptr->ptr[PARENT]->ptr[LEFT],H(iter->parent));*/
			while(iter->ptr == iter->ptr->ptr[PARENT]->ptr[LEFT]) {
				iter->ptr = iter->ptr->ptr[PARENT];
				if(iter->ptr == H(iter->parent)) {
					return -1;
				}
			}
			iter->ptr = iter->ptr->ptr[PARENT];
		}
	}
	return 0;
}


int8_t next_BinaryTreeIter(BinaryTreeIter* iter) {
	CHECK_VARN(iter,EINVAL);
	CHECK_VARN(iter->parent,EINVAL);
	/*printf("at %p L %p R %p\n",iter->ptr,L(iter->ptr),R(iter->ptr));*/
	if(R(iter->ptr)) {
		iter->ptr = R(iter->ptr);
		while(L(iter->ptr)) {
			iter->ptr = L(iter->ptr);
		}
	} else {
		if(iter->ptr == H(iter->parent)) {
			return SUCCESS;
		} else if(!iter->ptr) {
			iter->ptr = H(iter->parent);
			return EINVAL;
		} else {
			/*printf("Checking %p against %p h %p\n",iter->ptr,iter->ptr->ptr[PARENT]->ptr[RIGHT],H(iter->parent));*/
			while(iter->ptr == iter->ptr->ptr[PARENT]->ptr[RIGHT]) {
				iter->ptr = iter->ptr->ptr[PARENT];
				if(iter->ptr == H(iter->parent)) {
					return EINVAL;
				}
			}
			iter->ptr = iter->ptr->ptr[PARENT];
		}
	}
	return SUCCESS;
}
int8_t next_BinaryTreeBFSIter(BinaryTreeBFSIter* iter) {
	CHECK_VARN(iter,EINVAL);
	CHECK_VARN(iter->parent,EINVAL);
	iter->ptr = front(QueueList,&iter->queue);
	if(!pop(QueueList,&iter->queue)) {
		push(QueueList,&iter->queue,iter->ptr->ptr[LEFT],DYNAMIC);
		push(QueueList,&iter->queue,iter->ptr->ptr[RIGHT],DYNAMIC);
		return SUCCESS;
	} else {
		return EINVAL;
	}
}

int8_t next_BinaryTreeDFSIter(BinaryTreeDFSIter *iter) {
	CHECK_VARN(iter,EINVAL);
	CHECK_VARN(iter->parent,EINVAL);
	iter->ptr = top(StackList,&iter->stack);
	if(!pop(StackList,&iter->stack)) {
		push(StackList,&iter->stack,iter->ptr->ptr[RIGHT],DYNAMIC);
		push(StackList,&iter->stack,iter->ptr->ptr[LEFT],DYNAMIC);
		return SUCCESS;
	} else {
		return EINVAL;
	}
}
int8_t head_BinaryTreeBFSIter(BinaryTreeBFSIter* iter) {
	CHECK_VARN(iter,EINVAL);
	CHECK_VARN(iter->parent,EINVAL);
	CHECK_VARN(H(iter->parent),EINVAL);
	clear(QueueList,&iter->queue);
	iter->ptr = H(iter->parent);
	push(QueueList,&iter->queue,iter->ptr->ptr[LEFT],DYNAMIC);
	push(QueueList,&iter->queue,iter->ptr->ptr[RIGHT],DYNAMIC);
	return SUCCESS;
}

int8_t head_BinaryTreeDFSIter(BinaryTreeDFSIter* iter) {
	CHECK_VARN(iter,EINVAL);
	CHECK_VARN(iter->parent,EINVAL);
	CHECK_VARN(H(iter->parent),EINVAL);
	clear(StackList,&iter->stack);
	iter->ptr = H(iter->parent);
	push(StackList,&iter->stack,iter->ptr->ptr[RIGHT],DYNAMIC);
	push(StackList,&iter->stack,iter->ptr->ptr[LEFT],DYNAMIC);
	return SUCCESS;
}

int8_t head_BinaryTreeIter(BinaryTreeIter* iter) {
	CHECK_VARN(iter,EINVAL);
	CHECK_VARN(iter->parent,EINVAL);
	iter->ptr = H(iter->parent);
	while(L(iter->ptr)) {
		iter->ptr = L(iter->ptr);
	}
	return SUCCESS;
}

int8_t tail_BinaryTreeBFSIter(BinaryTreeBFSIter* iter) {
	CHECK_VARN(iter,EINVAL);
	CHECK_VARN(iter->parent,EINVAL);
	clear(QueueList,&iter->queue);
	iter->ptr = T(iter->parent);
	return SUCCESS;
}

int8_t tail_BinaryTreeIter(BinaryTreeIter* iter) {
	CHECK_VARN(iter,EINVAL);
	CHECK_VARN(iter->parent,EINVAL);
	iter->ptr = H(iter->parent);
	while(R(iter->ptr)) {
		iter->ptr = R(iter->ptr);
	}
	return SUCCESS;
}
generic_iter_func(Ptr_Based,copy,BinaryTree)
generic_iter_func(Ptr_Based,swap,BinaryTree)

