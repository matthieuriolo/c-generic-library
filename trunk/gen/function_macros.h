
/**
 * Copyright 2006, Micah Villmow, All Rights Reserved
 * @file function_macros.h
 * @author Micah Villmow
 * @brief function macros that expand to the actual functions
 */
#include "access_macros.h"
#ifndef FUNCTION_MACROS_H_
#    define FUNCTION_MACROS_H_

/*
 * TYPE is the type of the object(i.e. List, Node, Binary_Tree, etc...)
 * STRUCT is the actual struct to be modified
 * OBJ is the object to find/add/remove from the struct
 * FLAG is flags tobe passed to the function
 */

#    define construct(TYPE,STRUCT,OBJSIZE,FLAG)\
	construct_##TYPE((STRUCT),OBJSIZE,FLAG)

#    define construct_func(TYPE,STRUCT,OBJSIZE,FLAG,ALLOC,DEALLOC,CMP,RCMP,PRINT,COPY) \
	construct_func_##TYPE(STRUCT,OBJSIZE,FLAG,ALLOC,DEALLOC,CMP,RCMP,PRINT,COPY)

#    define destruct(TYPE,STRUCT)\
	destruct_##TYPE((STRUCT))

#    define clear(TYPE,STRUCT)\
	clear_##TYPE((STRUCT))

#define pop(TYPE,STRUCT)\
	pop_##TYPE((STRUCT))

#    define pop_back(TYPE,STRUCT) \
	pop_back_##TYPE((STRUCT))

#    define pop_front(TYPE,STRUCT) \
	pop_front_##TYPE((STRUCT))

#    define front(TYPE,STRUCT) \
	front_##TYPE((STRUCT))

#define top(TYPE,STRUCT) \
	top_##TYPE((STRUCT))

#    define back(TYPE,STRUCT) \
	back_##TYPE((STRUCT))

#define push(TYPE,STRUCT,OBJ,FLAG)\
	push_##TYPE((STRUCT),(OBJ),sizeof *(OBJ),(FLAG))

#    define push_back(TYPE,STRUCT,OBJ,FLAG)\
	push_back_##TYPE((STRUCT),(OBJ),sizeof *(OBJ),(FLAG))

#    define push_front(TYPE,STRUCT,OBJ,FLAG)\
	push_front_##TYPE((STRUCT),(OBJ),sizeof *(OBJ),(FLAG))

#    define delete(TYPE,STRUCT,OBJ)\
	delete_##TYPE((STRUCT),(OBJ),sizeof *(OBJ))

#    define insert(TYPE,STRUCT,OBJ,FLAG)\
	insert_##TYPE((STRUCT),(OBJ),sizeof *(OBJ),(FLAG))

#define convert(TYPE,STRUCT,OBJ,SIZE,FLAG) \
	convert_##TYPE((STRUCT),(OBJ),(SIZE),(FLAG))

#    define find(TYPE,STRUCT,OBJ)\
	find_##TYPE((STRUCT),(OBJ),sizeof *(OBJ))

#define resize(TYPE,STRUCT,SIZE)\
	resize_##TYPE((STRUCT),(SIZE))

#    define sort(TYPE,STRUCT) \
	sort_##TYPE((STRUCT),O(STRUCT))

#    define rsort(TYPE,STRUCT) \
	rsort_##TYPE((STRUCT),O(STRUCT))

#    define set_free_objects(TYPE,STRUCT,OBJ)\
	set_free_objects_##TYPE((STRUCT),(OBJ))

#define dump(TYPE,STRUCT)\
	dump_##TYPE((STRUCT))

#    define set_object_size(TYPE,STRUCT,OBJ)\
	set_object_size_##TYPE((STRUCT),(OBJ))

#    define size_of(TYPE,STRUCT)\
	size_of_##TYPE((STRUCT))

#define size(TYPE,STRUCT)\
	size_##TYPE((STRUCT))

#define empty(TYPE,STRUCT)\
	empty_##TYPE((STRUCT))


#    define set_compare(TYPE,STRUCT,OBJ)\
	set_compare_##TYPE((STRUCT),(OBJ))

#    define set_rcompare(TYPE,STRUCT,OBJ)\
	set_rcompare_##TYPE((STRUCT),(OBJ))

#    define set_print(TYPE,STRUCT,OBJ)\
	set_print_##TYPE((STRUCT),(OBJ))

#    define set_copy(TYPE,STRUCT,OBJ)\
	set_copy_##TYPE((STRUCT),(OBJ))

#    define set_alloc(TYPE,STRUCT,OBJ)\
	set_alloc_##TYPE((STRUCT),(OBJ))

#    define set_dealloc(TYPE,STRUCT,OBJ)\
	set_dealloc_##TYPE((STRUCT),(OBJ))


/*
 * Iterator based macro functions
 */
#define ITER(X)	X##Iter
#    define tail(TYPE,ITER) \
	tail_##TYPE((ITER))

#    define head(TYPE,ITER) \
	head_##TYPE((ITER))

#    define retrieve(TYPE,ITER) \
	retrieve_##TYPE((ITER))

#    define next(TYPE,ITER) \
	next_##TYPE((ITER))

#    define prev(TYPE,ITER) \
	prev_##TYPE((ITER))

#    define extract(TYPE,ITER) \
	extract_##TYPE((ITER))

#    define assign(TYPE,ITER,PARENT) \
	assign_##TYPE((ITER),(PARENT))

#    define destroy(TYPE,ITER) \
	destroy_##TYPE((ITER))

#    define create(TYPE,PARENT) \
	create_##TYPE((PARENT))

#    define CHECK_FLAG(X,Y)	(((X) & (Y)) == (Y))
#endif
