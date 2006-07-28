
/** 
 * Copyright 2006, Micah Villmow, All Rights Reserved
 * @file tree.h
 * @author Micah Villmow(villmow at cs dot fsu dot edu)
 * @brief a resuable tree class that takes any object
 */
#ifndef BASE_TREE_H_
#    define BASE_TREE_H_
#include "gen/data_types.h"
#include "gen/gen_macros.h"
#include "gen/function_macros.h"

/**
 * @struct BinaryTree
 * @brief flag to pass in if the data to be stored
 * is dynamically allocated.
 *
 * If the data passed in to a function is created dynamically,
 * then the function will not make a copy and instead just
 * point to the dynamically allocated memory.
 */
#ifndef BINARYTREE_DEFINED
#define BINARYTREE_DEFINED
typedef struct _ptr_struct BinaryTree;
#endif
/*
#ifndef BINARYTREE_DFS_ITER_DEFINED
#define BINARYTREE_DFS_ITER_DEFINED
typedef struct _ptr_iter BinaryTreeDFSIter;
#endif

#ifndef BINARYTREE_BFS_ITER_DEFINED
#define BINARYTREE_BFS_ITER_DEFINED
typedef struct _ptr_iter BinaryTreeBFSIter;
#endif
*/
/**
 * @fn int8_t construct_BinaryTree()
 * @param tree pointer to the tree to construc
 * @return 0 on success, non-zero on failure
 *
 * @warning memory should be cleared out before calling
 * this function. 
 * @sa BinaryTree_construct_func
 */
int8_t construct_BinaryTree(BinaryTree * tree,size_t objsize, int flag);

/**
 * @fn int8_t construct_func_BinaryTree()
 * @param tree the tree to initialize
 * @param alloc the allocation function to use
 * @param dealloc the deallocation function to use
 * @param cmp the comparison function to use
 * @param rcmp the reverse comparison function to use
 * @param print the print function to use
 * @param copy the copy function to use 
 * @return 0 on success, non-zero on failure
 *
 * @brief Zero's out the BinaryTree and assigns all
 * the function pointers in once function call
 */
int8_t construct_func_BinaryTree(BinaryTree * tree,size_t objsize, int flag,
                                  void *(*alloc) (size_t),
                                  void (*dealloc) (void *),
                                  int (*cmp) (const void *, const void *),
                                  int (*rcmp) (const void *, const void *),
                                  void (*print) (const void *),
                                  void *(*copy) (void *, const void *,
                                                 size_t));

/**
 * @fn int8_t BinaryTree_destruct(BinaryTree*)
 * @param tree the tree to destroy
 * @return 0 on success, non-zero on failure
 */
int8_t destruct_BinaryTree(BinaryTree * tree);

/**
 * @fn int8_t clear_BinaryTree(BinaryTree*)
 * @param tree the tree to clear nodes from
 * @return 0 on success, non-zero on failure
 *
 * @brief removes all the nodes from the tree
 * without destroying the tree
 */
int8_t clear_BinaryTree(BinaryTree *);

/**
 * @fn int8_t insert_BinaryTree()
 * @param tree the tree to insert object into
 * @param obj the object to insert into the tree
 * @param objsize the size of the object to insert
 * @param flag dynamic or static flag
 * @return pointer to node on success, pointer to
 * error node/NULL on failure
 */
void* insert_BinaryTree(BinaryTree * tree, void *obj, size_t objsize, int flag);
#define convert_BinaryTree(A,B,C,D)	insert_BinaryTree((A),(B),(C),(D))

/**
 * @fn int8_t delete_BinaryTree()
 * @param tree the tree to remove object from
 * @param obj the object to remove
 * @param objsize the size of the object to remove
 * @return 0 on success, non-zero on failure
 */
int8_t delete_BinaryTree(BinaryTree * tree, void *obj, size_t objsize);

/**
 * @fn void* find_BinaryTree()
 * @param tree the tree to search object for
 * @param obj the object to search for
 * @param objsize the size of the object
 * @return pointer to object on success, NULL on
 * not found
 */
void *find_BinaryTree(BinaryTree * tree, void *obj, size_t objsize);

/**
 * @fn void* max_BinaryTree()
 * @param tree the tree to search for the max value of
 * @return pointer to max value or NULL on error
 */
void *max_BinaryTree(BinaryTree* tree);

/**
 * @fn void* min_BinaryTree()
 * @param tree the tree to search for the min value of
 * @return pointer to min value or NULL on error
 */
void* min_BinaryTree(BinaryTree* tree);

/**
 * @fn void dump_BinaryTree()
 * @param tree the tree to dump the structure of
 */
void dump_BinaryTree(BinaryTree *tree);

prototype(size_of, BinaryTree);
prototype(set_compare, BinaryTree);
prototype(set_rcompare, BinaryTree);
prototype(set_print, BinaryTree);
prototype(set_alloc, BinaryTree);
prototype(set_dealloc, BinaryTree);
prototype(set_copy, BinaryTree);
/*
iter_proto(prev,BinaryTreeDFS);
iter_proto(next,BinaryTreeDFS);
iter_proto(destroy,BinaryTreeDFS);
iter_proto(head,BinaryTreeDFS);
iter_proto(tail,BinaryTreeDFS);
iter_proto(retrieve,BinaryTreeDFS);
iter_proto(prev,BinaryTreeBFS);
iter_proto(next,BinaryTreeBFS);
iter_proto(destroy,BinaryTreeBFS);
iter_proto(head,BinaryTreeBFS);
iter_proto(tail,BinaryTreeBFS);
iter_proto(retrieve,BinaryTreeBFS);
int8_t assign_BinaryTreeDFSIter(BinaryTreeDFSIter* iter, BinaryTree* obj);
int8_t assign_BinaryTreeBFSIter(BinaryTreeBFSIter* iter, BinaryTree* obj);
BinaryTreeBFSIter* create_BinaryTreeBFSIter(BinaryTree* obj);
BinaryTreeDFSIter* create_BinaryTreeDFSIter(BinaryTree* obj);*/

create_iter_prototypes(BinaryTree)

#endif
