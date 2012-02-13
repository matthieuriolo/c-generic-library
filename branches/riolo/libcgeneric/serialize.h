/* 
todo in common:
- need a proper way to delete dynamic allocated elements + container
- common way to load the data into the container (a new function called add, join, attach or something like that ... a functions that does not care about the sort function)
- create print_all functions for all datatypes
- print_all should be based on the makro bellow

- create dump function for all datatypes
- create better documentation (explanation which datatype is useful for what and what's the runtime of the functions)

- create makro called COMMON_FUNCTIONS which uses the makro bellow to create the default api functions

some missing generic functions - put this into gen/somewhere.h */
#define FUNC_PRINT(TYPE) F_PRINT(TYPE) { \
	if(!empty(TYPE, obj)) { \
		TYPE##Iter* iter = create(TYPE##Iter, obj);\
		head(TYPE##Iter, iter);\
		do { \
			obj->API.print(retrieve(TYPE##Iter, iter)); \
		}while(!next(TYPE##Iter, iter)); \
		destroy(TYPE##Iter, iter); \
	} \
}

/*
#define FUNC_EMPTY_ARR(TYPE) { \
	return !S(obj); \
}

#define FUNC_DUMP(TYPE) { \
}

*/


#include <string.h>
#include <stdio.h>

#include "base64.h"
#include "gen/error_macros.h"

#include "vector.h"


#ifndef __SERIALIZE_H__
#define __SERIALIZE_H__

/* belongs to error_macros (gen/error_macros.h) */
#define ECODERWRITE 0x40
#define ECODERREAD 0x50
#define WCODERINIT 0x60

/*
 *
 * Coder Structure
 * The encode/decode method uses this structures to create the correct format
 */
typedef struct coder_t {
	int (*writeContainerBegin)(FILE* file, const void*  obj, size_t size, size_t obj_size);
	int (*writeContainerEnd)(FILE* file, const void* obj, size_t size, size_t obj_size);
	int (*writeContainerElement)(FILE* file, const void* elem, size_t size, struct coder_t* coder);
	
	struct coder_t* subcoder;
	
	int (*readContainerBegin)(FILE* file, void* obj, size_t* size, size_t* obj_size);
	int (*readContainerEnd)(FILE* file, void* obj, size_t* size, size_t* obj_size);
	int (*readContainerElement)(FILE* file, void* elem, size_t size, struct coder_t* coder);
} Coder;



char* memstr(FILE* file, int character, size_t* len);

//predefined formatter
Coder* createBase64Coder();
Coder* createBinaryCoder();
Coder* createXMLCoder();

int base64_WriteContainerBegin(FILE* file, const void* obj, size_t size, size_t obj_size);
int base64_WriteContainerEnd(FILE* file, const void* obj, size_t size, size_t obj_size);
int base64_WriteContainerElement(FILE* file, const void* elem, size_t size, struct coder_t* coder);

int base64_ReadContainerBegin(FILE* file, void* obj, size_t* size, size_t* obj_size);
int base64_ReadContainerEnd(FILE* file, void* obj, size_t* size, size_t* obj_size);
int base64_ReadContainerElement(FILE* file, void* elem, size_t size, struct coder_t* coder);

int binary_WriteContainerBegin(FILE* file, const void* obj, size_t size, size_t obj_size);
int binary_WriteContainerEnd(FILE* file, const void* obj, size_t size, size_t obj_size);
int binary_WriteContainerElement(FILE* file, const void* elem, size_t size, struct coder_t* coder);

int binary_ReadContainerBegin(FILE* file, void* obj, size_t* size, size_t* obj_size);
int binary_ReadContainerEnd(FILE* file, void* obj, size_t* size, size_t* obj_size);
int binary_ReadContainerElement(FILE* file, void* elem, size_t size, struct coder_t* coder);

int xml_WriteContainerBegin(FILE* file, const void* obj, size_t size, size_t obj_size);
int xml_WriteContainerEnd(FILE* file, const void* obj, size_t size, size_t obj_size);
int xml_WriteContainerElement(FILE* file, const void* elem, size_t size, struct coder_t* coder);

int xml_ReadContainerBegin(FILE* file, void* obj, size_t* size, size_t* obj_size);
int xml_ReadContainerEnd(FILE* file, void* obj, size_t* size, size_t* obj_size);
int xml_ReadContainerElement(FILE* file, void* elem, size_t size, struct coder_t* coder);



// -- shortcuts -- 
//std serializer that writes everything to a FILE pointer (can be used for sockets too) - NON ATOMAR!
#define encode(TYPE, STRUCT, FILEPTR, CODER) encode_##TYPE(STRUCT, FILEPTR, CODER)

//serializer that writes everything to a specific file - shurtcut for lazy programmer - ATOMAR
#define encodeToFile(TYPE, STRUCT, FILEPATH, CODER) encodeToFile_##TYPE(STRUCT, FILEPATH, CODER)

//serializer that writes everything to memory - shurtcut for lazy programmer
#define encodeToMemory(TYPE, STRUCT, LENGTH, CODER) encodeToMemory_##TYPE(STRUCT, LENGTH, CODER)


#define decode(TYPE, FILEPTR, CODER) decode_##TYPE(FILEPTR, CODER)


// -- function declaration -- 
//signature for encode
#define PROTO_ENCODE(TYPE) int encode_##TYPE(TYPE* obj, FILE* fileptr, Coder* coder)
#define PROTO_ENCODETOFILE(TYPE) int encodeToFile_##TYPE(TYPE* obj, const char* path, Coder* coder)
#define PROTO_ENCODETOMEMORY(TYPE) void* encodeToMemory_##TYPE(TYPE* obj, size_t* length, Coder* coder)

#define PROTO_DECODE(TYPE) void* decode_##TYPE(FILE* fileptr, Coder* coder)
//#define PROTO_DECODETOFILE(TYPE) int decodeToFile_##TYPE(TYPE* obj, const char* path, Coder* coder)
//#define PROTO_DECODEFROMMEMORY(TYPE) void* decodeToMemory_##TYPE(TYPE* obj, size_t* length, Coder* coder)


#define encodeElements(TYPE) encode##TYPE##Elements
#define PROTO_ENCODEELEMENTS(TYPE) int encodeElements(TYPE) (FILE* file, const void* elem, size_t size, struct coder_t* coder)
#define F_ENCODEELEMENTS(TYPE) PROTO_ENCODEELEMENTS(TYPE) { \
	return encode(TYPE, (TYPE*)elem, file, coder); \
}

#define decodeElements(TYPE) decode##TYPE##Elements
#define PROTO_DECODEELEMENTS(TYPE) int decodeElements(TYPE) (FILE* file, void* elem, size_t size, struct coder_t* coder)
#define F_DECODEELEMENTS(TYPE) PROTO_DECODEELEMENTS(TYPE) { \
	void* tmp = decode(TYPE, file, coder); \
	if(tmp != NULL) { \
		memcpy(elem, tmp, size); \
		free(tmp); \
		return SUCCESS; \
	} \
	\
	return ECODERREAD; \
}



//definition of the function-content
#define F_ENCODE(TYPE) PROTO_ENCODE(TYPE) { \
	size_t obj_size = O(obj); \
	if(coder->writeContainerBegin(fileptr, obj, size_of(TYPE, obj), obj_size) != SUCCESS) \
		return ECODERWRITE; \
	if(!empty(TYPE, obj)) { \
		TYPE##Iter* ptr = create(TYPE##Iter, obj); \
		head(TYPE##Iter, ptr); \
		do { \
			coder->writeContainerElement(fileptr, retrieve(TYPE##Iter, ptr), obj_size, coder->subcoder); \
		}while(!next(TYPE##Iter, ptr)); \
		destroy(TYPE##Iter, ptr); \
	} \
	\
	if(coder->writeContainerEnd(fileptr, obj, size_of(TYPE, obj), obj_size) != SUCCESS) \
		return ECODERWRITE; \
	return SUCCESS; \
}



#define F_ENCODETOFILE(TYPE) PROTO_ENCODETOFILE(TYPE) { \
	char* p = tmpname(); \
	FILE* f = fopen(p, "w"); \
	if(f!=NULL){ \
		int ret = encode(TYPE, f, coder); \
		fclose(f); \
		if(ret != SUCCESS) \
			return ret; \
		\
		rename(p, path); \
	}else \
		return errno; \
	\
	return SUCCESS; \
}



#define F_ENCODETOMEMORY(TYPE) PROTO_ENCODETOMEMORY(TYPE) { \
	char* path = tmpnam(); \
	if(encodeToFile(TYPE, path, coder, 0)!=SUCCESS) \
		return NULL; \
	\
	FILE* f = fopen(path, "r"); \
	fseek(f, 0, SEEK_END); \
	size_t length = ftell(f); \
	void* data = (void*)malloc(length); \
	frewind(f); \
	fread(data, length, 1, f); \
	fclose(f); \
	remove(path); \
	return data; \
}


#define F_DECODE(TYPE, FUNC) PROTO_DECODE(TYPE) { \
	TYPE* obj = NULL; \
	\
	size_t obj_size, size; \
	int ret = coder->readContainerBegin(fileptr, obj, &size, &obj_size); \
	\
	if(ret == WCODERINIT) { \
		obj = (TYPE*)malloc(sizeof(TYPE)); \
		memset(obj, 0, sizeof(TYPE)); \
		construct(TYPE, obj, obj_size, FREEOBJ); \
	}else \
		if(ret != SUCCESS) \
			return NULL; \
	\
	\
	while(size--) { \
		void* elem = malloc(obj_size); \
		if(coder->readContainerElement(fileptr, elem, obj_size, coder->subcoder) != SUCCESS) { \
			if(!empty(TYPE, obj)) { \
				TYPE##Iter* ptr = create(TYPE##Iter, obj); \
				head(TYPE##Iter, ptr); \
				do { \
					/*free(retrieve(TYPE##Iter, ptr));*/ \
				}while(!next(TYPE##Iter, ptr)); \
				destroy(TYPE##Iter, ptr); \
			} \
			destruct(TYPE, obj); \
			free(obj); \
			free(elem); \
			return NULL; \
		}else { \
			FUNC##TYPE(obj, elem, obj_size, DYNAMIC);/*push_back(TYPE, obj, elem, DYNAMIC); - issue with the obj size*/ \
		} \
	} \
	\
	if(coder->writeContainerEnd(fileptr, obj, size_of(TYPE, obj), obj_size)!=SUCCESS) {\
		if(ret == WCODERINIT) { \
			destruct(TYPE, obj); \
			free(obj); \
		} \
		\
		return NULL; \
	} \
	\
	return obj; \
}



// -- declaration of the existing encode method -- 
PROTO_ENCODE(Vector);
PROTO_ENCODETOFILE(Vector);
PROTO_ENCODETOMEMORY(Vector);

PROTO_ENCODEELEMENTS(Vector);


PROTO_DECODE(Vector);
PROTO_DECODEELEMENTS(Vector);
#endif