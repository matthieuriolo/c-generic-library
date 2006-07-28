
/**
 * Copyright 2006, Micah Villmow, All Rights Reserved
 * @file gen_macros.h
 * @author Micah Villmow
 * @brief macro functions that apply to all data structures
 *
 * Some functions are very repetetive and are simple, so they can
 * easily be macro'd and generalized. All functions that have this
 * ability will be put in this file and be used throughout the code
 */

#ifndef GEN_MACROS_H_
#    define GEN_MACROS_H_
#include <stddef.h>

#    define prototype(FUNC,TYPE)	proto_##FUNC(TYPE)
#    define function(FUNC,TYPE)	func_##FUNC(TYPE)

/**
 * Beginning of macro definitions for function prototypes 
 */
#    define proto_set_compare(X) \
/**
 * @param obj the obj to set the compare function of
 * @param cmp the function pointer to the comparison function
 * @return 0 on success, non-zero on error
 */\
	int8_t set_compare_##X(X* obj,\
			int (*cmp)(const void*, const void*))

#    define proto_set_rcompare(X)\
/** 
 * @param obj the obj to set the reverse comparison function of
 * @param rcmp the function pointer to the reverse comparison function
 * @return 0 on success, non-zero on error
 */\
	int8_t set_rcompare_##X(X* obj,\
			int (*rcmp)(const void*, const void*))

#    define proto_set_print(X)\
/**
 * @param obj the obj to set the print function of
 * @param print the function pointer to the print function
 * @return 0 on success, non-zero on error
 */\
	int8_t set_print_##X(X* obj, \
			void (*print)(const void *))

#    define proto_set_copy(X)\
/**
 * @param obj the object to set the copy function for
 * @param copy the function pointer to the copy function
 * @return 0 on success, non-zero on error
 */\
	int8_t set_copy_ ##X(X* obj, \
			void* (*copy)(void*, const void*, size_t))

#    define proto_set_alloc(X)\
/**
 * @param obj the obj to set the alloc funtion for
 * @param alloc the function pointer to the alloc function
 * @return 0 on success, non-zero on error
 */\
	int8_t set_alloc_##X(X* obj, \
			void* (*alloc)(size_t))

#    define proto_set_dealloc(X)\
/**
 * @param ptr the obj to set the dealloc function for
 * @param dealloc the function pointer to the dealloc function
 * @return 0 on success, non-zero on error
 */\
	int8_t set_dealloc_##X(X* obj, \
			void (*dealloc)(void *))

#    define proto_size_of(X) \
	/**
	 * @param obj the tree to get the size of
	 * @return size of tree or 0 on error
	 */\
	size_t size_of_##X( X* obj)

/** Beginning of macro definitions for function implementations */


#    define func_set_compare(X) \
	int8_t set_compare_##X (X* obj,\
			int (*cmp)(const void*,const void*)) {\
		CHECK_VARN(obj,EINVAL);\
		CHECK_VARN(cmp,EINVAL);\
		obj->API.cmp = cmp;\
		return 0;\
	}

#    define func_set_rcompare(X) \
	int8_t set_rcompare_##X(X* obj,\
			int (*rcmp)(const void*,const void*)) {\
		CHECK_VARN(obj,EINVAL);\
		CHECK_VARN(rcmp,EINVAL);\
		obj->API.rcmp = rcmp;\
		return 0;\
	}

#    define func_set_print(X) \
	int8_t set_print_##X(X* obj,\
			void (*print)(const void *)) {\
		CHECK_VARN(obj,EINVAL);\
		CHECK_VARN(print,EINVAL);\
		obj->API.print = print;\
		return SUCCESS;\
	}

#    define func_set_copy(X) \
	int8_t set_copy_##X(X* obj, \
			void* (*copy)(void*, const void*,size_t)) {\
		CHECK_VARN(obj,EINVAL);\
		CHECK_VARN(copy,EINVAL);\
		obj->API.copy = copy;\
		return SUCCESS;\
	}

#    define func_set_alloc(X) \
	int8_t set_alloc_##X(X* obj,\
			void* (*alloc)(size_t)){\
		CHECK_VARN(obj,EINVAL);\
		CHECK_VARN(alloc,EINVAL);\
		obj->API.alloc = alloc;\
		return SUCCESS;\
	}

#    define func_set_dealloc(X) \
	int8_t set_dealloc_##X(X* obj,\
			void (*dealloc)(void *)){\
		CHECK_VARN(obj,EINVAL);\
		CHECK_VARN(dealloc,EINVAL);\
		obj->API.dealloc = dealloc;\
		return SUCCESS;\
	}


#    define func_size_of(X) \
	size_t size_of_##X( X* obj) {\
		CHECK_VARN(obj,0);\
		return S(obj);\
	}

#    define func_set_object_size(X) \
	void set_object_size_##X( X *obj, size_t objsize) {\
		char *ptr;\
		O(obj) = objsize;\
		if(!E(obj)) {\
			if(!(E(obj) = malloc(objsize))) {\
				return;\
			}\
			for(ptr = E(obj); ptr < ((char *)E(obj) + objsize); ptr++) {\
			    /*
			     * This assigns the bit mask: 1010(B) 0101(5)
			     * * to each byte that the pointer points to 
			     */\
				*ptr = (char)0xB5;\
			}\
		}\
	}

#define func_set_arr_object_size(X) \
	void set_object_size_##X(X *obj,size_t objsize) {\
		O(obj) = objsize;\
	}

#    define func_set_free_objects(X)\
	void set_free_objects_##X( X* obj, int flag) {\
		obj->objfree = flag;\
	}

/*
 * Iterator based generic functions
 */
#define create_iter_prototypes(TYPE) \
	iter_proto(prev,TYPE);\
	iter_proto(next,TYPE);\
	iter_proto(assign,TYPE);\
	iter_proto(destroy,TYPE);\
	iter_proto(head,TYPE);\
	iter_proto(tail,TYPE);\
	iter_proto(create,TYPE);\
	iter_proto(retrieve,TYPE);

#define iter_proto(FUNC,TYPE) proto_##FUNC(TYPE)

#define proto_prev(TYPE)\
/**
 * @param iter the iter to move to the prev element
 * @return 0 on success, non-zero on error
 * @brief moves the iterator to the prev element in the
 * obj
 */\
	int8_t prev_##TYPE##Iter(TYPE##Iter* iter)

#define proto_next(TYPE)\
/**
 * @param iter the iter to move to the next element
 * @return 0 on success, non-zero on error
 * @brief moves the iterator to the next element in the
 * obj
 */\
	int8_t next_##TYPE##Iter(TYPE##Iter* iter)

#define proto_head(TYPE)\
/**
 * @param iter the iterator to move to the head
 * @return 0 on success, non-zero on error
 * @brief moves the iterator to the head of the obj
 * it has been assigned to
 */\
	int8_t head_##TYPE##Iter(TYPE##Iter* iter)

#define proto_tail(TYPE)\
/**
 * @param iter the iterator to move to the tail
 * @return 0 on success, non-zero on error
 * @brief moves the iterator to the tail of the
 * obj it has been assigned to
 */\
	int8_t tail_##TYPE##Iter(TYPE##Iter* iter)

#define proto_assign(TYPE)\
/**
 * @param iter the iterator to assign to the obj
 * @param obj the obj to point the iterator to
 * @return 0 on success, non-zero on error
 * @brief assign statically created iterator to the obj
 */\
	int8_t assign_##TYPE##Iter(TYPE##Iter* iter, TYPE* obj)


#define proto_retrieve(TYPE)\
/**
 * @param iter the iterator to retrieve the object from
 * @return object on success, NULL on error
 * @brief returns a void poitner to the object that
 * the iterator points to
 */\
	void* retrieve_##TYPE##Iter(TYPE##Iter* iter)

#define proto_destroy(TYPE)\
	/**
	 * @param iter the iterator to destroy
	 * @warning only use this in conjunction with create
	 */\
	void destroy_##TYPE##Iter(TYPE##Iter* iter)

#define proto_create(TYPE)\
/**
 * @param obj the obj to create iterator for
 * @return returns an iterator to the obj on success
 * or NULL on error
 * @brief creates and iterator and assigns it to the obj
 */\
	TYPE##Iter *create_##TYPE##Iter(TYPE *obj)

#define create_iter_func(PTR,TYPE) \
	generic_iter_func(PTR,prev,TYPE)\
	generic_iter_func(PTR,next,TYPE)\
	generic_iter_func(PTR,head,TYPE)\
	generic_iter_func(PTR,tail,TYPE)\
	generic_iter_func(PTR,assign,TYPE)\
	generic_iter_func(PTR,create,TYPE)\
	generic_iter_func(PTR,destroy,TYPE)\
	generic_iter_func(PTR,retrieve,TYPE)

#define generic_iter_func(PTR,FUNC,TYPE) gen_##PTR##_iter_##FUNC(TYPE)

#define gen_Ptr_Based_iter_create(TYPE) \
		TYPE##Iter* create_##TYPE##Iter(TYPE *obj) {\
			ITER(TYPE) *iter;\
			if(!obj) {\
				return NULL;\
			}\
			if(!S(obj)) {\
				return NULL;\
			}\
			CHECK_VARA((iter = malloc(sizeof *iter)),NULL);\
			iter->ptr = H(obj);\
			iter->parent = obj;\
			return iter;\
		}

#define gen_Arr_Based_iter_create(TYPE) gen_Ptr_Based_iter_create(TYPE)

#define gen_Ptr_Based_iter_assign(TYPE) \
		int8_t assign_##TYPE## Iter(ITER(TYPE)* iter,TYPE *obj) {\
			CHECK_VARN(iter,-1);\
			CHECK_VARN(obj,-1);\
			iter->ptr = H(obj);\
			iter->parent = obj;\
			return 0;\
		}

#define gen_Arr_Based_iter_assign(TYPE) gen_Ptr_Based_iter_assign(TYPE)


#define gen_Ptr_Based_iter_destroy(TYPE)\
		void destroy_##TYPE## Iter(ITER(TYPE)*iter) {\
			if(iter) {\
				free(iter);\
			}\
		}
#define gen_Arr_Based_iter_destroy(TYPE) gen_Ptr_Based_iter_destroy(TYPE)
	
#define gen_Ptr_Based_iter_next(TYPE) \
		int8_t next_##TYPE##Iter(TYPE##Iter *iter) {\
			CHECK_VARN(iter,-1);\
			CHECK_VARN(iter->ptr,-1);\
			CHECK_VARN(N(iter->ptr),-1);\
			ITERLIST_NEXT(iter);\
			return 0;\
		}

#define gen_Arr_Based_iter_next(TYPE) \
		int8_t next_##TYPE##Iter(ITER(TYPE) *iter) {\
			CHECK_VARN(iter,EINVAL);\
			CHECK_VARN(iter->ptr,EINVAL);\
			if(iter->ptr == T(iter->parent) - O(iter->parent)) {\
				return EINVAL;\
			}\
			if((char *)H(iter->parent) < (char *)T(iter->parent)) {\
				/* no wraparound */ \
				ITERARRAY_NEXT(iter);\
			} else if((char *)iter->ptr == ((char *)iter->parent->end - O(iter->parent))) {\
				iter->ptr = M(iter->parent);\
			} else {\
				ITERARRAY_NEXT(iter);\
			}\
			return 0;\
		}


#define gen_Ptr_Based_iter_prev(TYPE) \
		int8_t prev_##TYPE##Iter(ITER(TYPE)* iter) {\
			CHECK_VARN(iter,-1);\
			CHECK_VARN(iter->ptr,-1);\
			CHECK_VARN(P(iter->ptr),-1);\
			ITERLIST_PREV(iter);\
			return 0;\
		}

#define gen_Arr_Based_iter_prev(TYPE) \
		int8_t prev_##TYPE##Iter(ITER(TYPE) *iter) {\
			CHECK_VARN(iter,EINVAL);\
			CHECK_VARN(iter->ptr,EINVAL);\
			if(iter->ptr == H(iter->parent)) {\
				return EINVAL;\
			}\
			if(H(iter->parent) > T(iter->parent)) {\
				/* no wraparound */ \
				ITERARRAY_PREV(iter);\
			} else if(iter->ptr == M(iter->parent)) {\
				iter->ptr = iter->parent->end;\
			} else {\
				ITERARRAY_PREV(iter);\
			}\
			return 0;\
		}

#define gen_Ptr_Based_iter_head(TYPE) \
		int8_t head_##TYPE## Iter(ITER(TYPE) *iter) {\
			CHECK_VARN(iter,-1);\
			CHECK_VARN(iter->parent,-1);\
			ITER_HEAD(iter);\
			return 0;\
		}

#define gen_Arr_Based_iter_head(TYPE) gen_Ptr_Based_iter_head(TYPE)

#define gen_Ptr_Based_iter_tail(TYPE) \
		int8_t tail_##TYPE## Iter(ITER(TYPE) *iter) {\
			CHECK_VARN(iter,-1);\
			CHECK_VARN(iter->parent,-1);\
			ITER_TAIL(iter);\
			return 0;\
		}

#define gen_Arr_Based_iter_tail(TYPE)\
		int8_t tail_##TYPE## Iter(ITER(TYPE) *iter) { \
			CHECK_VARN(iter,EINVAL);\
			CHECK_VARN(iter->parent,EINVAL);\
			iter->ptr = iter->parent->tail - O(iter->parent);\
			return 0;\
		}

#define gen_Ptr_Based_iter_retrieve(TYPE) \
		void* retrieve_##TYPE## Iter(ITER(TYPE) *iter) {\
			CHECK_VARN(iter,CHECK(E(iter->parent)));\
			CHECK_VARN(iter->ptr,CHECK(E(iter->parent)));\
			CHECK_VARN(iter->ptr->objptr,CHECK(E(iter->parent)));\
			return ITERLIST_OBJ(iter);\
		}

#define gen_Arr_Based_iter_retrieve(TYPE) \
		void* retrieve_##TYPE## Iter(ITER(TYPE) *iter) {\
			CHECK_VARN(iter,CHECK(E(iter->parent)));\
			CHECK_VARN(iter->ptr,CHECK(E(iter->parent)));\
			return ITERARRAY_OBJ(iter);\
		}

#define ptr_clear(TYPE,OBJ) \
do {\
	Node *iter, *iter2;\
	\
	CHECK_VARN((OBJ),EINVAL);\
	for(iter = H((OBJ));iter;iter = iter2) {\
		iter2 = N(iter);\
		REMOVE_NODE(iter,(OBJ));\
		DELETE_OBJPTR((OBJ),iter);\
		ADD_FREE_NODE((OBJ),iter);\
	}\
	H((OBJ)) = T((OBJ)) = NULL;\
	S((OBJ)) = 0;\
}while(0)

#define arr_construct(TYPE,OBJ,OBJSIZE,FLAG) \
do{\
	if(S((OBJ)) > 0) {\
		destruct(TYPE,(OBJ));\
	}\
	S((OBJ)) = 0;\
	C((OBJ)) = 0;\
	(OBJ)->end = M((OBJ)) = H((OBJ)) = T((OBJ)) = NULL;\
	(OBJ)->API.alloc = malloc;\
	(OBJ)->API.dealloc = free;\
	(OBJ)->API.copy = memcpy;\
	(OBJ)->API.cmp = NULL;\
	(OBJ)->API.rcmp = NULL;\
	(OBJ)->API.print = NULL;\
	(OBJ)->objsize = (OBJSIZE);\
	(OBJ)->objfree = (FLAG);\
}while(0)

#define arr_pop_back(TYPE,OBJ) \
do{\
	if(T((OBJ)) == M((OBJ))) {\
		T((OBJ)) = (OBJ)->end;\
	} else {\
		T((OBJ)) = ((char *)T((OBJ))) - O((OBJ));\
	}\
	S((OBJ))--;\
}while(0)

#define arr_pop_front(TYPE,OBJ) \
do {\
	if(H((OBJ)) >= (OBJ)->end) {\
		H((OBJ)) = M((OBJ));\
	} else { \
		H((OBJ)) = ((char *)H((OBJ))) + O((OBJ));\
	}\
	S((OBJ))--;\
}while(0)

#define arr_clear(TYPE,OBJ) \
do{ \
	H((OBJ)) = M((OBJ));\
	T((OBJ)) = ((char *)H((OBJ)) + O((OBJ)));\
	E((OBJ)) = (char *)H((OBJ)) + (O((OBJ)) * C((OBJ)));\
	S((OBJ)) = 0;\
}while(0)

#define arr_push_back(TYPE,OBJ,ITEM,ITEMSIZE) \
do{ \
	if(S((OBJ)) == C((OBJ))) {\
		if(C((OBJ))) {\
			resize(TYPE,(OBJ),C((OBJ)) << 1);\
		} else {\
			CHECK_VARA(M((OBJ)) = malloc(O((OBJ)) * INITIAL_SIZE),EALLOCF);\
			H((OBJ)) = T((OBJ)) = M((OBJ));\
			C((OBJ)) = INITIAL_SIZE;\
			S((OBJ)) = 0;\
			(OBJ)->end = (char *)M((OBJ)) + (O((OBJ)) * C((OBJ)));\
		 }\
	}\
	if(T((OBJ)) >= (OBJ)->end) {\
		T((OBJ)) = M((OBJ));\
	}\
	(OBJ)->API.copy(T((OBJ)),(ITEM),(ITEMSIZE));\
	S((OBJ))++;\
	T((OBJ)) = ((char *)T((OBJ))) + O((OBJ));\
}while(0)

#define arr_push_front(TYPE,OBJ,ITEM,ITEMSIZE) \
do{ \
	if(S((OBJ)) == C((OBJ))) {\
		if(C((OBJ))) {\
			resize(TYPE,(OBJ),C((OBJ)) << 1);\
		} else {\
			CHECK_VARA(M((OBJ)) = malloc(O((OBJ)) * INITIAL_SIZE),EALLOCF);\
			H((OBJ)) = T((OBJ)) = M((OBJ));\
			C((OBJ)) = INITIAL_SIZE;\
			S((OBJ)) = 0;\
			(OBJ)->end = (char *)M((OBJ)) + (O((OBJ)) * C((OBJ)));\
		 }\
	}\
	S((OBJ))++;\
	if(H((OBJ)) == M((OBJ))) {\
		H((OBJ)) = ((char *)(OBJ)->end) - O((OBJ));\
	} else {\
		H((OBJ)) = ((char *)H((OBJ))) - O((OBJ));\
	}\
    (OBJ)->API.copy(H((OBJ)),(ITEM),(ITEMSIZE));\
}while(0)

#define arr_copy_wrap(TYPE,DST,SRC,SIZE) \
do {\
	if(M((SRC))) {\
	size_t off = S((SRC)) * O((SRC));\
	if(S((SRC)) == 0) {\
		/* header and tail are same, no need to copy */\
	} else if(H((SRC)) < T((SRC))) {\
		/* No wraparound */ \
		memcpy((DST),H((SRC)),((char *)T((SRC)) - (char *)H((SRC)))/sizeof(char *));\
	} else if((void *)((char *)(H((SRC))) + off) < (SRC)->end) {\
		/* wraparound exists, but the new size fits between
		 * the current head and the end of the memarray*/\
		memcpy((DST),H((SRC)),off);\
	} else {\
		/* wraparound exists, and the new size
		 * overruns into the beginning, need to
		 * do a double copy
		 */\
		ptrdiff_t spaces = ((char *)(SRC)->end - (char *)H((SRC)));\
		memcpy((DST),H((SRC)),(size_t)spaces);\
		memcpy((char *)(DST) + spaces,M((SRC)),((O((SRC)) * (S((SRC))) - spaces/O((SRC)))));\
	}\
	free(M((SRC)));\
	}\
}while(0)
		

#define arr_setup_pointers(TYPE,DST,SRC,SIZE) \
do{\
	M((SRC)) = H((SRC)) = (DST);\
	C((SRC)) = SIZE;\
	(SRC)->end = (char *)M((SRC)) + (O((SRC)) * C((SRC)));\
	if(S((SRC)) > C((SRC))) {\
	  S((SRC)) = C((SRC));\
	}\
	T((SRC)) = (char *)H((SRC)) + (S((SRC)) * O((SRC)));\
	if(T((SRC)) == H((SRC))) {\
		T((SRC)) == (char *)H((SRC)) + O((SRC));\
	}\
}while(0)

#endif
