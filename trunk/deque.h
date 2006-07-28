
/**
 * @file deque.h
 * @author Micah Villmow
 * @brief a resuable deque class that takes any object
 *
 */
#ifndef QUEUE_H_
#    define QUEUE_H_
#include "gen/data_types.h"
#include "gen/gen_macros.h"
#include "gen/function_macros.h"


/**
 * @struct DequeList
 * @brief the deque object that handles the objects
 * and is based on a generic list data structure
 */
#ifndef DEQUELIST_DEFINED
#define DEQUELIST_DEFINED	
typedef struct _ptr_struct DequeList;
#endif

/**
 * @brief the iterator object that helps
 * traverse the deque
 */
#ifndef DEQUELIST_ITER_DEFINED
#define DEQUELIST_ITER_DEFINED
typedef struct _ptr_iter ITER(DequeList);
#endif

/**
 * @fn int8_t construct_DequeList(DequeList *deque)
 * @param deque the deque object to initialize
 * @return 0 on success, non-zero on failure
 *
 * @warning clear out the memory of the object before
 * calling this function using memset or bzero
 * */
 int8_t construct_DequeList(DequeList * deque,size_t objsize, int flag);

/** 
 * @fn int8_t construct_func_DequeList()
 * @param deque the deque object to initialize
 * @param alloc the allocation functor
 * @param dealloc the deallocation functor
 * @param cmp the comparison functor
 * @param rcmp the reverse comparison functor
 * @param print the print functor
 * @param copy the copy functor
 * @return 0 on success, non-zero on failure
 *
 * @brief Zero's out the deque and assigns all the
 * function pointers in one function call
 */
 int8_t construct_func_DequeList(DequeList * deque,size_t objsize, int flag,
                                   void *(*alloc) (size_t),
                                   void (*dealloc) (void *),
                                   int (*cmp) (const void *, const void *),
                                   int (*rcmp) (const void *, const void *),
                                   void (*print) (const void *),
                                   void *(*copy) (void *, const void *,
                                                  size_t));

/**
 * @fn int8_t destruct_DequeList(DequeList* deque)
 * @param deque the deque object to destroy
 * @return 0 on success, non-zero on failure
 */
 int8_t destruct_DequeList(DequeList * deque);

/**
 * @fn int8_t pop_front_DequeList()
 * @param deque the deque to remove the front item from
 * @return 0 on success, non-zero on failure
 * @brief removes the front item from the deque
 */
 int8_t pop_front_DequeList(DequeList * deque);
/**
 * @fn int8_t pop_back_DequeList()
 * @param deque the deque to remove the front item from
 * @return 0 on success, non-zero on failure
 * @brief removes the front item from the deque
 */
 int8_t pop_back_DequeList(DequeList * deque);

/**
 * @fn int8_t clear_DequeList()
 * @param deque the deque to clear
 * @return 0 on success, non-zero on failure
 * @brief removes all items from the deque
 */
 int8_t clear_DequeList(DequeList *deque);

/**
 * @fn void* front_DequeList()
 * @param deque the deque to get the first item of
 * @return a pointer to the front object in the stack or NULL on failure
 * @brief returns a pointer to the front object so that it can be
 * easily referenced
 */
 void *front_DequeList(DequeList * deque);

 /**
  * @fn void* back_DequeList()
  * @param deque the deque to get the last item of
  * @return a pointer to the last object in the deque or NULL on failure
  * @brief returns a pointer to the last object so that it can be
  * be easily referenced
  */
 void *back_DequeList(DequeList *deque);

/**
 * @fn int8_t push_back_DequeList()
 * @param deque the deque to push an item into
 * @param obj the object to add to the deque
 * @param objsize the size of the object to add
 * @param flag the flag for the object
 * @return 0 on success, non-zero on error
 *
 * @brief pushes an item onto the end of a deque
 */
 int8_t push_back_DequeList(DequeList * deque, void *obj, size_t objsize,
                         int flag);
int8_t convert_DequeList(DequeList *deque, void *obj, size_t objsize, int flag);
/**
 * @fn int8_t push_front_DequeList()
 * @param deque the deque to push an item into
 * @param obj the object to add to the deque
 * @param objsize the size of the object to add
 * @param flag the flag for the object
 * @return 0 on success, non-zero on error
 *
 * @brief pushes an item onto the end of a deque
 */
 int8_t push_front_DequeList(DequeList * deque, void *obj, size_t objsize,
                         int flag);



prototype(size_of, DequeList);
prototype(set_compare, DequeList);
prototype(set_rcompare, DequeList);
prototype(set_print, DequeList);
prototype(set_alloc, DequeList);
prototype(set_dealloc, DequeList);
prototype(set_copy, DequeList);
create_iter_prototypes(DequeList)

/* beginning of vector based deque functions */
#ifndef DEQUEVECTOR_DEFINED
#define DEQUEVECTOR_DEFINED
typedef struct _array_struct DequeVector;
#endif

#ifndef DEQUEVECTOR_ITER_DEFINED
#define DEQUEVECTOR_ITER_DEFINED
typedef struct _array_iter ITER(DequeVector);
#endif

int8_t construct_DequeVector(DequeVector *deque,size_t objsize, int flag);
int8_t construct_func_DequeVector(DequeVector *deque,size_t objsize, int flag,
                                       void *(*alloc) (size_t),
                                       void (*dealloc) (void *),
                                       int (*cmp) (const void *,
                                                   const void *),
                                       int (*rcmp) (const void *,
                                                    const void *),
                                       void (*print) (const void *),
                                       void *(*copy) (void *, const void *,
                                                      size_t));

int8_t destruct_DequeVector(DequeVector *deque);
int8_t pop_front_DequeVector(DequeVector *deque);
int8_t pop_back_DequeVector(DequeVector *deque);
void * front_DequeVector(DequeVector *deque);
void * back_DequeVector(DequeVector *deque);
int8_t clear_DequeVector(DequeVector *deque);
int8_t push_front_DequeVector(DequeVector *deque, void *obj, size_t objsize, int flag);
int8_t push_back_DequeVector(DequeVector *deque, void *obj, size_t objsize, int flag);
int8_t resize_DequeVector(DequeVector *deque,size_t size);

#define convert_DequeVector(A,B,C,D)	push_DequeVector((A),(B),(C),(D))

prototype(size_of, DequeVector);
prototype(set_compare, DequeVector);
prototype(set_rcompare, DequeVector);
prototype(set_print, DequeVector);
prototype(set_alloc, DequeVector);
prototype(set_dealloc, DequeVector);
prototype(set_copy, DequeVector);

create_iter_prototypes(DequeVector)

#endif
