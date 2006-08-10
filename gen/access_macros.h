
/**
 * Copyright 2006, All Rights Reserved, Micah Villmow
 * @file access_macros.h
 * @author Micah Villmow
 * @brief a bunch of macros that help with access into
 * a structure
 */
#ifndef ACCESS_MACROS_H_
#    define ACCESS_MACROS_H_
/**
 * @brief flag to pass in if the data to be stored
 * is statically allocated.
 *
 * If the data passed in to a function is statically
 * allocated, then the function will make a copy of
 * the data and store that data instead.
 */
#    ifndef STATIC
#        define STATIC  (0x2)
#    endif

/**
 * @brief flag to pass in if the data to be stored
 * is dynamically allocated.
 *
 * If the data passed in to a function is created dynamically,
 * then the function will not make a copy and instead just
 * point to the dynamically allocated memory.
 */
#    ifndef DYNAMIC
#        define DYNAMIC (0x01)
#    endif
#    ifndef INITIAL_SIZE
#        define INITIAL_SIZE 256
#    endif
#    ifndef FREEOBJ
#        define FREEOBJ 0x1
#    endif
#    ifndef NOFREE
#        define NOFREE	0x2
#    endif
#    ifndef T
#        define T(X)	((X)->tail)
#    endif

#    ifndef H
#        define H(X)	((X)->head)
#    endif

#    define LEFT 	0x00
#    define RIGHT   0x01


#    ifndef P
#        define P(X)	L(X)
#    endif
#    ifndef L
#        define L(X)	((X)->ptr[LEFT])
#    endif
#define flag(X)	((X)->flags)


#    ifndef N
#        define N(X)	R(X)
#    endif
#    ifndef R
#        define R(X)	((X)->ptr[RIGHT])
#    endif

#    ifndef B
#        define B(X)	((X)->base)
#    endif

#    ifndef S
#        define S(X)	((X)->size)
#    endif

#    ifndef C
#        define C(X)	((X)->capacity)
#    endif

#    ifndef O
#        define O(X)	((X)->objsize)
#    endif

#ifndef M
#define M(X)		((X)->mem)
#endif
#    ifndef FL
#        define FL(X)	((X)->free_list)
#    endif
#    ifndef CHECK
#        ifdef USE_NULL_POINTERS
#            define CHECK(X)	(NULL)
#        else
#            define CHECK(X)	(X)
#        endif
#    endif

#    define ITERLIST_OBJ(X)  	((X)->ptr->objptr)
#    define ITERLIST_NEXT(X) 	((X)->ptr = R((X)->ptr))
#    define ITERLIST_PREV(X) 	((X)->ptr = L((X)->ptr))
#define ITERARRAY_OBJ(X)	((X)->ptr)
#define ITERARRAY_NEXT(X)	((X)->ptr = (((char*)(X)->ptr) + O((X)->parent)))
#define ITERARRAY_PREV(X)	((X)->ptr = (((char*)(X)->ptr) - O((X)->parent)))
#    define ITER_HEAD(X)	((X)->ptr = H((X)->parent))
#    define ITER_TAIL(X)	((X)->ptr = T((X)->parent))


#endif
