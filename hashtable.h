/**
 * Copyright 2006, All Rights Reserved, Micah Villmow
 * @file hashtable.h
 * @brief Various implementations of hash tables
 */
#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include "gen/data_types.h"
#include "gen/gen_macros.h"


typedef struct _Hash_List_Node HashListNode;
/* Open hash table */
typedef struct _open_hash_table {
	size_t capacity;
	size_t cur_size;
	size_t num_elem;
	int8_t objfree;
	HashListNode *nodes;
	HashListNode *free_list;
	Functor_API API;
	uint32_t (*hash)(void *,size_t);
} OHTable;
/**
 * @fn int8_t construct_OHTable(OHTable *table,size_t, int8_t flag)
 * @param table the table to construct the hash table of
 * @param init_capacity the initial capacity of the hash table
 * @param flag flag to know whether to automatically free objects or not
 * @return 0 on success, non-zero on failure
 * @brief Setup and construct a open addressing hash table
 *
 * Construct and setup an open hash table of init_capacity size.
 * The possible flag options are FREEOBJ to free DYNAMIC objects at the end
 * of the tables life or NOFREE to not free DYNAMIC objects
 * @sa construct_CHTable, construct_EHTable
 */
int8_t construct_OHTable(OHTable *table,size_t init_capacity,int8_t flag);
void destruct_OHTable(OHTable *table);
int8_t insert_OHTable(OHTable *table, void *element, size_t elesize,int8_t flag);
int8_t delete_OHTable(OHTable *table, void *element, size_t elesize);
void *find_OHTable(OHTable *table, void *element, size_t elesize);
int8_t set_hash_OHTable(OHTable *table, int (*hash)(void *,size_t));
int8_t clear_OHTable(OHTable* table);
void print_hash_OHTable(OHTable *table);

prototype(set_compare,OHTable);
prototype(set_rcompare,OHTable);
prototype(set_print,OHTable);
prototype(set_alloc,OHTable);
prototype(set_dealloc,OHTable);
prototype(set_copy,OHTable);

typedef struct _Hash_Node HashNode;

/* Closed hash table */
typedef struct _closed_hash_table CHTable;
struct _closed_hash_table {
	size_t capacity;
	size_t cur_size;
	int8_t objfree;
	HashNode *data;
	uint32_t (*hash)(void *,size_t);
	uint32_t (*prob)(uint32_t);
	Functor_API API;
};

int8_t construct_CHTable(CHTable *table, size_t init_capacity,int8_t flag);
void destruct_CHTable(CHTable *table);
int8_t insert_CHTable(CHTable *table, void *element, size_t elesize,int8_t flag);
int8_t delete_CHTable(CHTable *table, void *element, size_t elesize);
void *find_CHTable(CHTable *table, void *element, size_t elesize);
int8_t set_hash_CHTable(CHTable *table, int32_t (*hash)(void *,size_t));
int8_t set_probe_CHTable(CHTable *table, uint32_t (*prob)(uint32_t));
int8_t clear_CHTable(CHTable* table);
int8_t print_hash_CHTable(CHTable *table);

prototype(set_compare,CHTable);
prototype(set_rcompare,CHTable);
prototype(set_print,CHTable);
prototype(set_alloc,CHTable);
prototype(set_dealloc,CHTable);
prototype(set_copy,CHTable);

/* Extensible hash table */
/*
typedef struct _extensible_hash_table EHTable;
struct _extended_hash_table {
	size_t capacity;
	size_t cur_size;
	int8_t objfree;
	HashNode *data;
	Functor_API API;
	uint32_t (*hash)(void *,size_t);
	uint32_t (*prob)(int32_t);
};

int8_t construct_EHTable(EHTable *table, size_t init_capacity, int8_t flag);
void destruct_EHTable(EHTable *table);
int8_t insert_EHTable(EHTable *table, void *element, size_t elesize,int8_t flag);
int8_t delete_key_EHTable(EHTable *table, void *element, size_t elesize);
void *find_key_EHTable(EHTable *table, void *element, size_t elesize);
int8_t set_hash_EHTable(EHTable *table, int32_t (*hash)(void *,size_t));
int8_t set_probe_EHTable(EHTable *table, int32_t (*prob)(int32_t));

prototype(set_compare,EHTable);
prototype(set_rcompare,EHTable);
prototype(set_print,EHTable);
prototype(set_alloc,EHTable);
prototype(set_dealloc,EHTable);
prototype(set_copy,EHTable);
*/
/* Generic hashing techinques */
uint32_t char_hash(void *key, size_t len);
uint32_t num_hash(void *key, size_t len);
/* Generic probing techniques */
uint32_t linear_probing(uint32_t num);
uint32_t quadratic_probing(uint32_t num);


#endif
