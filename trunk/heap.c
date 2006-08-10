/**
 * Copyright 2006, All Rights Reserved, Micah Villmow
 * @file heap.c
 * @brief Implementation of various generic heap functions
 */

#include <string.h>
#include <stddef.h>
#include <stdio.h>

#include "heap.h"
#include "gen/gen_macros.h"
#include "gen/data_types.h"
#include "gen/error_macros.h"
#include "gen/control_macros.h"
#include "gen/function_macros.h"
#include "gen/function_signatures.h"


F_CONSTRUCT(Heap) {
	CHECK_VARN(obj,EINVAL);
	if(S(obj) > 0) {
		destruct(Heap,obj);
	}
	ARR_STRUCT_SETUP(obj,datasize,flag);
	API_DEFAULT_SETUP(obj);
	return SUCCESS;
}


F_CONSTRUCT_FUNC(Heap) {
	CHECK_VARN(obj,EINVAL);
	ARR_STRUCT_SETUP(obj,datasize,flag);
	obj->API.alloc = alloc;
	obj->API.dealloc = dealloc;
	obj->API.cmp = cmp;
	obj->API.print = print;
	obj->API.copy = copy;
	return SUCCESS;
}

F_DESTRUCT(Heap) {
	CHECK_VARN(obj,EINVAL);
	clear(Heap,obj);
	free(M(obj));
	memset(obj,0,sizeof *vec);
}

F_CLEAR(Heap) {
	CHECK_VARN(obj,EINVAL);
	if(!C(obj)) {
		return SUCCESS;
	}
	ARR_CLEAR(Heap,obj);
	return SUCCESS;
}

F_PRINT(Heap) {
}

F_DUMP(Heap) {

}

F_EMPTY(Heap) {
	CHECK_VARN(obj,EINVAL);
	CHECK_VARN(obj->mem,EINVAL);
	if(H(obj) != T(obj)) {
		return SUCCESS;
	} else {
		return EINVAL;
	}
}

F_SIZE(Heap) {
	CHECK_VARN(obj,0);
	CHECK_VARN(obj->mem,0);
	return (char *)T(obj) - (char *)H(obj) / O(obj);
}

function(duplicate_arr_struct,Heap);
