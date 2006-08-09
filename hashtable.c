/**
 * Copyright 2006, All Rights Reserved, Micah Villmow
 * @file hashtable.c
 * @brief implementation of three generic hash tables
 * and some basic hashing functions
 */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "hashtable.h"
#include "gen/data_types.h"
#include "gen/error_macros.h"
#include "gen/control_macros.h"

int8_t construct_OHTable(OHTable *table, size_t init_capacity, int8_t flag) {
	CHECK_VARN(table,EINVAL);
	if(table->capacity > 0) {
		destruct(OHTable,table);
	}
	table->capacity = init_capacity;
	table->cur_size = 0;
	table->num_elem = 0;
	table->objfree = flag;
	table->hash = num_hash;
	table->API.copy = memcpy;
	table->API.alloc = malloc;
	table->API.dealloc = free;
	table->API.cmp = memcmp;
	table->API.rcmp = NULL;
	table->API.print = NULL;
	table->nodes = malloc(sizeof *table->nodes * init_capacity);
	memset(table->nodes,0,sizeof *table->nodes * init_capacity);
	return SUCCESS;
}


void destruct_OHTable(OHTable *table) {
	HashListNode *ptr, *tmp;
	clear(OHTable,table);
	for(ptr = table->free_list;ptr; ptr = tmp) {
		tmp = ptr->next;
		free(ptr);
	}
	table->capacity = 0;
	table->cur_size = 0;
	table->num_elem = 0;
	table->objfree = 0;
	table->hash = NULL;
	free(table->nodes);
}

int8_t clear_OHTable(OHTable *table) {
	HashListNode *ptr, *iter;
	size_t x = 0;
	CHECK_VARN(table,EINVAL);
	for(x = 0; x < table->capacity; x++) {
		if(table->nodes[x].objptr) {
			ptr = &table->nodes[x];
			DELETE_OBJPTR(table,ptr);
			iter = ptr->next;
			while(iter) {
				DELETE_OBJPTR(table,iter);
				iter->objptr = NULL;
				iter->objsize = 0;
				iter->flags = 0;
				ptr = iter->next;
				iter->next = FL(table);
				FL(table) = iter;
				iter = ptr;
			}
		}
	}
	return SUCCESS;
}

int8_t insert_OHTable(OHTable *table, void *element, size_t elesize,int8_t flag) {
	int32_t h_index;
	HashListNode *ptr;
	CHECK_VARN(table,EINVAL);
	CHECK_VARN(element,EINVAL);
	h_index = table->hash(element,elesize) % table->capacity;
	if(table->nodes[h_index].objptr) {
		HashListNode *iter;
		iter = &table->nodes[h_index];
		while(1) {
			if(table->API.cmp(iter->objptr,element,elesize) == 0) {
				return SUCCESS;
			}
			if(iter->next) {
				iter = iter->next;
			} else {
				break;
			}
		}
		if(FL(table)) {
			ptr = table->free_list;
			table->free_list = ptr->next;
		} else if(!(ptr = malloc(sizeof *ptr))) {
			return EALLOCF;
		}
		ptr->next = NULL;
		iter->next = ptr;
	} else {
		ptr = &table->nodes[h_index];
		table->cur_size++;
	}
	ptr->objsize = elesize;
	ptr->flags = flag;
	if(flag == DYNAMIC) {
		ptr->objptr = element;
	} else if((ptr->objptr = table->API.alloc(elesize))) {
		table->API.copy(ptr->objptr,element,elesize);
	} else {
		return EALLOCF;
	}
	table->num_elem++;
	return SUCCESS;
}

int8_t delete_OHTable(OHTable *table, void *element, size_t elesize) {
	int32_t h_index;
	CHECK_VARN(table,EINVAL);
	CHECK_VARN(element,EINVAL);
	h_index = table->hash(element,elesize) % table->capacity;
	if(table->nodes[h_index].objptr) {
		HashListNode *iter,*prev;
		iter = &table->nodes[h_index];
		prev = NULL;
		while(1) {
			if(table->API.cmp(iter->objptr,element,elesize) == 0) {
				if(!prev) {
					prev = iter->next;
					DELETE_OBJPTR(table,iter);
					if(prev) {
						iter->next = prev->next;
						iter->objptr = prev->objptr;
						iter->flags = prev->flags;
						iter->objsize = prev->objsize;
						prev->objptr = NULL;
						prev->flags = 0;
						prev->objsize = 0;
						prev->next = FL(table);
						FL(table) = prev;
					} else {
						iter->next = NULL;
						iter->objptr = 0;
						iter->flags = 0;
						iter->objsize = 0;
						table->cur_size--;
					}
				} else {
					prev->next = iter->next;
					DELETE_OBJPTR(table,iter);			
					iter->objptr = NULL;
					iter->flags = 0;
					iter->objsize = 0;
					iter->next = FL(table);
					FL(table) = iter;
				}
				table->num_elem--;
				return SUCCESS;
			}
			if(iter->next) {
				prev = iter;
				iter = iter->next;
			} else {
				break;
			}
		}
	}
	return ENOVAL;
}

void *find_OHTable(OHTable *table, void *element, size_t elesize) {
	int32_t h_index;
	CHECK_VARN(table,NULL);
	CHECK_VARN(element,NULL);
	h_index = table->hash(element,elesize) % table->capacity;
	if(table->nodes[h_index].objptr) {
		HashListNode *iter;
		iter = &table->nodes[h_index];
		while(1) {
			if(table->API.cmp(iter->objptr,element,elesize) == 0) {
				return iter->objptr;
			}
			if(iter->next) {
				iter = iter->next;
			} else {
				break;
			}
		}
	}
	return NULL;
}

void print_hash_OHTable(OHTable *table) {
	size_t x;
	HashListNode *ptr;
	printf("Open Hash Table: %p Capacity: %d Size: %d\n",table,table->capacity,table->cur_size);
	printf("Flags: %d Hash_Function: %p Element: %d\n",table->objfree,table->hash,table->num_elem);
	/*printf("Current nodes:\n");
	for(x = 0; x < table->capacity; x++) {
		ptr = &table->nodes[x];
		printf("%d) ",x);
		do{
			if(ptr->objptr) {
				table->API.print(ptr->objptr);
			}
			ptr = ptr->next;
		}while(ptr);
		printf("\n");
	}*/
	printf("\n");
}

int8_t set_hash_OHTable(OHTable *table, int (*hash)(void *,size_t)) {
	CHECK_VARN(table,EINVAL);
	CHECK_VARN(hash,EINVAL);
	table->hash = hash;
	return SUCCESS;
}

function(set_compare,OHTable)
function(set_rcompare,OHTable)
function(set_print,OHTable)
function(set_copy,OHTable)
function(set_alloc,OHTable)
function(set_dealloc,OHTable)

int8_t construct_CHTable(CHTable *table, size_t init_capacity, int8_t flag) {
	CHECK_VARN(table,EINVAL);
	if(table->capacity > 0) {
		destruct(CHTable,table);
	}
	table->capacity = init_capacity;
	table->cur_size = 0;
	table->objfree = flag;
	table->hash = num_hash;
	table->prob = linear_probing;
	table->API.alloc = malloc;
	table->API.dealloc = free;
	table->API.copy = memcpy;
	table->API.cmp = memcmp;
	table->API.rcmp = NULL;
	table->API.print = NULL;
	if(!(table->data = malloc(sizeof *table->data * init_capacity))) {
		return EALLOCF;
	}
	memset(table->data,0,sizeof *table->data * init_capacity);
	return SUCCESS;
}
void destruct_CHTable(CHTable *table) {
	if(table) {
		clear(CHTable,table);
		table->capacity = 0;
		table->cur_size = 0;
		table->objfree = 0;
		table->hash = NULL;
		table->prob = NULL;
		free(table->data);
		table->data = NULL;
	}
}
int8_t clear_CHTable(CHTable *table) {
	HashNode *iter;
	CHECK_VARN(table,EINVAL);
	for(iter = table->data; 
		iter < &table->data[table->capacity]; iter++) {
		if(iter->objptr) {
			if((iter->flags == STATIC) || 
			   (iter->flags == DYNAMIC && table->objfree == FREEOBJ)) {
				table->API.dealloc(iter->objptr);
			}
		}
	}
	return SUCCESS;
}
int8_t insert_CHTable(CHTable *table, void *element, size_t elesize, int8_t flag) {
	uint32_t h_index,start;
	uint16_t x = 0;
	CHECK_VARN(table,EINVAL);
	CHECK_VARN(element,EINVAL);
	start = h_index = table->hash(element,elesize) % table->capacity;
	while(table->data[h_index].objptr) {
		if(table->API.cmp(table->data[h_index].objptr,element,elesize) == 0) {
			return SUCCESS;
		}
		x++;
		h_index = table->prob(h_index) % table->capacity;
		if(h_index == start) {
			return EINVAL;
		}
	}
	if(x > table->max_jumps) {
		table->max_jumps = x;
	}
	table->data[h_index].flags = flag;
	table->data[h_index].objsize = elesize;
	if(flag == DYNAMIC) {
		table->data[h_index].objptr = element;
	} else if((table->data[h_index].objptr = table->API.alloc(elesize))) {
		table->API.copy(table->data[h_index].objptr,element,elesize);
	} else {
		return EALLOCF;
	}
	table->cur_size++;
	return SUCCESS;
}
int8_t delete_CHTable(CHTable *table, void *element, size_t elesize) {
	uint32_t h_index, start;
	uint16_t x;
	CHECK_VARN(table,EINVAL);
	CHECK_VARN(element,EINVAL);
	start = h_index = table->hash(element,elesize) % table->capacity;
	for(x = 0; x <= table->max_jumps; x++) {
		if(table->data[h_index].objptr) {
			if(table->API.cmp(table->data[h_index].objptr,element,elesize) == 0) {
				if((table->data[h_index].flags == STATIC) || 
				   (table->data[h_index].flags == DYNAMIC && table->objfree == FREEOBJ)) {
					table->API.dealloc(table->data[h_index].objptr);
				}
				table->data[h_index].objptr = NULL;
				table->data[h_index].objsize = 0;
				table->data[h_index].flags = 0;
				table->cur_size--;
				return SUCCESS;
			}
		}
		h_index = table->prob(h_index) % table->capacity;
		if(h_index == start) {
			break;
		}
	}
	return ENOVAL;
}
void *find_CHTable(CHTable *table, void* element, size_t elesize) {
	uint32_t h_index, start;
	uint16_t x;
	CHECK_VARN(table,NULL);
	CHECK_VARN(element,NULL);
	start = h_index = table->hash(element,elesize) % table->capacity;
	for(x = 0; x <= table->max_jumps; x++) {
		if(table->data[h_index].objptr) {
			if(table->API.cmp(table->data[h_index].objptr,element,elesize) == 0) {
				return table->data[h_index].objptr;
			} 
		}
		h_index = table->prob(h_index) % table->capacity;
		if(h_index == start) {
			break;
		}
	}
	return NULL;
}

int8_t set_hash_CHTable(CHTable *table, int32_t (*hash)(void *,size_t)) {
	CHECK_VARN(table,EINVAL);
	CHECK_VARN(hash,EINVAL);
	table->hash = hash;
	return SUCCESS;
}

int8_t set_probe_CHTable(CHTable *table, uint32_t (*prob)(uint32_t)) {
	CHECK_VARN(table,EINVAL);
	CHECK_VARN(prob,EINVAL);
	table->prob = prob;
	return SUCCESS;
}

int8_t print_hash_CHTable(CHTable *table) {
	size_t x;
	CHECK_VARN(table,EINVAL);
	printf("Open Hash Table: %p Capacity: %d Size: %d\n",table,table->capacity,table->cur_size);
	printf("Flags: %d Hash_Function: %p Prob_Function: %p\n",table->objfree,table->hash,table->prob);
	/*for(x = 0; x < table->capacity; x++) {
		printf("%d) ",x);
		if((table->data[x].objptr) && (table->API.print)) {
			table->API.print(table->data[x].objptr);
		}
		if(!((x+1) % 5)) {
			printf("\n");
		} else {
			printf("  ");
		}
	}*/
	return SUCCESS;
}
function(set_compare,CHTable)
function(set_rcompare,CHTable)
function(set_print,CHTable)
function(set_copy,CHTable)
function(set_alloc,CHTable)
function(set_dealloc,CHTable)



uint32_t char_hash(void *key, size_t len) {
	uint32_t val = 0;
	while(len--) {
		val = (val << 5) + tolower(*(char *)(key++));
	}
	return val;
}

uint32_t num_hash(void *key, size_t len) {
	uint32_t val =0;
	while(len--) {
		val = (val << 5) + *(char *)(key++);
	}
	return val;
}

uint32_t linear_probing(uint32_t num) {
	return ++num;
}

uint32_t quadratic_probing(uint32_t num) {
	return num * num;
}
