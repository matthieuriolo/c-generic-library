/**
 * Copyright 2006, All Rights Reserved, Micah Villmow
 * @file libcgeneric.h
 * @brief Includes the whole libgenc
 *
 */

#ifndef GENC_H_
#define GENC_H_

#ifdef __cplusplus
extern "C" {
#endif
 
#include "gen/access_macros.h"
#include "gen/control_arr_macros.h"
#include "gen/control_macros.h"
#include "gen/data_types.h"
#include "gen/error_macros.h"
#include "gen/function_macros.h"
#include "gen/function_signatures.h"
#include "gen/gen_macros.h"
#include "gen/stdint.h"

#include "binary_tree.h"
#include "comparisons.h"
#include "deque.h"
#include "hashtable.h"
#include "heap.h"
#include "list.h"
#include "node.h"
#include "priority_queue.h"
#include "queue.h"
#include "stack.h"
#include "vector.h"


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //GENC_H_
