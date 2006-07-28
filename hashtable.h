/**
 * Copyright 2006, All Rights Reserved, Micah Villmow
 * @file hashtable.h
 * @brief Various implementations of hash tables
 */
#ifndef HASHTABLE_H_
#define HASHTABLE_H_
/* Open hash table */
typedef struct _open_hash_table OHTable;
struct _open_hash_table {
	size_t capacity;
	size_t cur_size;
	int8_t flag;
	Node **nodes;
	int32_t (*hash)(void *,size_t);
};
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
int8_t insert_key_OHTable(OHTable *table, void *key, size_t keysize, void *element, size_t elesize);
int8_t delete_key_OHTable(OHTable *table, void *key, size_t keysize);
void* find_key_OHTable(OHTable *table, void *key, size_t keysize);
int8_t set_hash_OHTable(OHTable *table, int (*hash)(void *,size_t));

/* Closed hash table */
typedef struct _closed_hash_table CHTable;
struct _closed_hash_table {
	size_t capacity;
	size_t cur_size;
	int8_t flag;
	int32_t (*hash)(void *,size_t);
	int32_t (*prob)(int32_t);
};

int8_t construct_CHTable(CHTable *table, size_t init_capacity,int8_t flag);
void destruct_CHTable(CHTable *table);
int8_t insert_key_CHTable(CHTable *table, void *key, size_t keysize, void *element, size_t elesize);
int8_t delete_key_CHTable(CHTable *table, void *key, size_t keysize);
void* find_key_CHTable(CHTable *table, void *key, size_t keysize);
int8_t set_hash_CHTable(CHTable *table, int32_t (*hash)(void *,size_t));
int8_t set_probe_CHTable(CHTable *table, int32_t (*prob)(int32_t));
/* Extensible hash table */
typedef struct _extensible_hash_table EHTable;
struct _extended_hash_table {
	size_t capacity;
	size_t cur_size;
	int8_t flag;
	int32_t (*hash)(void *,size_t);
	int32_t (*prob)(int32_t);
};

int8_t construct_EHTable(EHTable *table, size_t init_capacity, int8_t flag);
void destruct_EHTable(EHTable *table);
int8_t insert_key_EHTable(EHTable *table, void *key, size_t keysize, void *element, size_t elesize);
int8_t delete_key_EHTable(EHTable *table, void *key, size_t keysize);
void *find_key_EHTable(EHTable *table, void *key, size_t keysize);
int8_t set_hash_EHTable(EHTable *table, int32_t (*hash)(void *,size_t));
int8_t set_probe_EHTable(EHTable *table, int32_t (*prob)(int32_t));

/* Generic hashing techinques */
int32_t char_hash(void *key, size_t len);
int32_t alpha_hash(void *key, size_t len);
/* Generic probing techniques */
int32_t linear_probing(int32_t num);
int32_t quadratic_probing(int32_t num);
#endif
