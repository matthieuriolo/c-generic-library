/**
 * Copyright 2006, All Rights Reserved, Micah Villmow
 * @file comparisons.h
 * @brief File containing generic comparison functions
 * for most of the built in data types for C
 */

/**
 * @brief macro to expand to the comparison function
 * prototype
 */
 
#ifndef COMPARISONS_H_
#define COMPARISONS_H_

#include "stdint.h"
#include <stdlib.h>

#define CMPFUNC_PROTO(TYPE) int TYPE##cmp(void * first, void * second, size_t size)
#define CMPFUNC_IMPL(TYPE) \
	int TYPE##cmp(void *first, void *second, size_t size) {\
		return (*(const TYPE *)first) - (*(const TYPE *)second);\
	}


CMPFUNC_PROTO(char);
CMPFUNC_PROTO(float);
CMPFUNC_PROTO(double);
CMPFUNC_PROTO(int8_t);
CMPFUNC_PROTO(int16_t);
CMPFUNC_PROTO(int32_t);
CMPFUNC_PROTO(int64_t);
CMPFUNC_PROTO(uint8_t);
CMPFUNC_PROTO(uint16_t);
CMPFUNC_PROTO(uint32_t);
CMPFUNC_PROTO(uint64_t);

#endif

