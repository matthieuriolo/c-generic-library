
/**
 * @file stack.h
 * @author Micah Villmow
 * @brief a reuseable stack class that takes any object
 *
 * the stack class offers two flavors, a stacklist and
 * a stackvector, depending on which underlying structure
 * the programmer prefers
 */
#ifndef STACK_H_
#    define STACK_H_
#include "gen/data_types.h"
#include "gen/gen_macros.h"
#include "gen/function_macros.h"

/**
 * @struct StackList
 * @brief The stack object that handles the objects
 * and is based on a list generic data structure
 */
#ifndef STACKLIST_DEFINED
#define STACKLIST_DEFINED
typedef struct _stack_list StackList;
#endif

/**
 * @brief the iterator object that helps
 * traverse the stack
 */
#ifndef STACKLIST_ITER_DEFINED
#define STACKLIST_ITER_DEFINED
typedef struct _ptr_iter ITER(StackList);
#endif

/**
 * @fn int8_t push_StackList(StackList*, void*, size_t, int8_t)
 * @param stack the stack to push an item onto
 * @param obj the obj to push onto the stack
 * @param objsize the size of the object
 * @param flag the flag for this specific push
 * @return 0 on success, non-zero on error
 *
 * @brief pushes an item onto the stack
 */
int8_t push_StackList(StackList * stack, void *obj, size_t objsize,
                             int8_t flag);

#define convert_StackList(A,B,C,D) push_StackList((A),(B),(C),(D))

/**
 * @fn int8_t pop_StackList(StackList*)
 * @param stack the stack to remove the top item from
 * @return 0 on success, non-zero on failure
 *
 * @brief pops the first item off the stack
 */
int8_t pop_StackList(StackList * stack);

/**
 * @fn void *top_StackList(StackList*)
 * @param stack the stack to return the top object from
 * @return the object on success, NULL on failure
 *
 * @brief returns a pointer to the top of the stack so it
 * can be easily referenced
 */
void *top_StackList(StackList * stack);

/**
 * @fn int8_t clear_StackList(StackList* stack)
 * @param stack the stack to clear
 * @return 0 on success, non-zero on failure
 * @brief removes all items from the stack
 */
int8_t clear_StackList(StackList *stack);
/**
 * @fn int8_t construct_StackList(StackList* stack)
 * @param stack the stack to initalize
 * @return 0 on success, non-zero on failure
 *
 * @warning clear out the memory of the object before
 * calling this function using memset or bzer
 */
int8_t construct_StackList(StackList * stack,size_t objsize, int flag);

/**
 * @fn int8_t construct_func_StackList(StackList*,void*,void,int,int,void,void*)
 * @param stack the stack to initialize
 * @param alloc the allocation functor
 * @param dealloc the deallocation functor
 * @param cmp the comparison functor
 * @param rcmp the reverse comparison functor
 * @param print the print functor
 * @param copy the copy functor
 * @return 0 on success, non-zero on failure
 *
 * @brief Zero's out the stack and assigns all the
 * function pointers in one function call
 */
int8_t construct_func_StackList(StackList * stack,size_t objsize, int flag,
                                       void *(*alloc) (size_t),
                                       void (*dealloc) (void *),
                                       int (*cmp) (const void *,
                                                   const void *),
                                       int (*rcmp) (const void *,
                                                    const void *),
                                       void (*print) (const void *),
                                       void *(*copy) (void *, const void *,
                                                      size_t));

/**
 * @fn int8_t destruct_StackList(StackList *stack)
 * @param stack the stack to destroy
 * @return 0 on success, non-zero on failure
 */
int8_t destruct_StackList(StackList * stack);

prototype(size_of, StackList);
prototype(set_compare, StackList);
prototype(set_rcompare, StackList);
prototype(set_print, StackList);
prototype(set_alloc, StackList);
prototype(set_dealloc, StackList);
prototype(set_copy, StackList);

create_iter_prototypes(StackList)


/* beginning of vector based deque functions */
#ifndef STACKVECTOR_DEFINED
#define STACKVECTOR_DEFINED
typedef struct _array_struct StackVector;
#endif

#ifndef STACKVECTOR_ITER_DEFINED
#define STACKVECTOR_ITER_DEFINED
typedef struct _array_iter ITER(StackVector);
#endif

int8_t construct_StackVector(StackVector *stack,size_t objsize, int flag);
int8_t construct_func_StackVector(StackVector *stack, size_t objsize, int flag,
                                       void *(*alloc) (size_t),
                                       void (*dealloc) (void *),
                                       int (*cmp) (const void *,
                                                   const void *),
                                       int (*rcmp) (const void *,
                                                    const void *),
                                       void (*print) (const void *),
                                       void *(*copy) (void *, const void *,
                                                      size_t));

int8_t destruct_StackVector(StackVector *stack);
int8_t pop_StackVector(StackVector *stack);
void * top_StackVector(StackVector *stack);
int8_t clear_StackVector(StackVector *stack);
int8_t push_StackVector(StackVector *stack, void *obj, size_t objsize, int flag);
int8_t resize_StackVector(StackVector *stack,size_t size);

#define convert_StackVector(A,B,C,D)	push_StackVector((A),(B),(C),(D))

prototype(size_of, StackVector);
prototype(set_compare, StackVector);
prototype(set_rcompare, StackVector);
prototype(set_print, StackVector);
prototype(set_alloc, StackVector);
prototype(set_dealloc, StackVector);
prototype(set_copy, StackVector);

create_iter_prototypes(StackVector)
#endif
