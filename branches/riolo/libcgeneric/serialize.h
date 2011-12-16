#include <string.h>
#include "base64.h"
#include "vector.h"

#include "gen/error_macros.h"

#ifndef __SERIALIZE_H__
#define __SERIALIZE_H__

/* belongs to error_macros */
#define ECODERWRITE 0x40
#define ECODERREAD 0x50


/*
 *
 * Coder Structure
 * The encode/decode method uses this structures to create the correct format
 */
typedef struct {
	int (*writeContainerBegin)(FILE* file, const void*  obj, size_t size, size_t obj_size);
	int (*writeContainerEnd)(FILE* file, const void* obj, size_t size, size_t obj_size);
	int (*writeContainerElement)(FILE* file, const void* elem, size_t size);
	
	/*readContainerBegin
	readContainerEnd
	readContainerElement*/
} Coder;





//predefined formatter
Coder* createBase64Coder();
Coder* createXMLCoder();

int base64_WriteContainerBegin(FILE* file, const void* obj, size_t size, size_t obj_size);
int base64_WriteContainerEnd(FILE* file, const void* obj, size_t size, size_t obj_size);
int base64_WriteContainerElement(FILE* file, const void* elem, size_t size);


int xml_WriteContainerBegin(FILE* file, const void* obj, size_t size, size_t obj_size);
int xml_WriteContainerEnd(FILE* file, const void* obj, size_t size, size_t obj_size);
int xml_WriteContainerElement(FILE* file, const void* elem, size_t size);

// -- shortcuts -- 
//std serializer that writes everything to a FILE pointer (can be used for sockets to)
#define encode(TYPE, STRUCT, FILEPTR, CODER) encode_##TYPE(STRUCT, FILEPTR, CODER)
//serializer that writes everything to a specific file
#define encodeToFile(TYPE, STRUCT, FILEPATH, CODER) encodeToFile_##TYPE(STRUCT, FILEPATH, CODER)
//serializer that writes everything to memory
#define encodeToMemory(TYPE, STRUCT, LENGTH, CODER) encodeToFile_##TYPE(STRUCT, LENGTH, CODER)



// -- function declaration -- 
//signature for encode
#define F_ENCODE(TYPE) \
int encode_##TYPE(TYPE* obj, FILE* fileptr, Coder* coder)



//definition of the content
#define FUNC_ENCODE(TYPE) F_ENCODE(TYPE) { \
size_t obj_size = O(obj); \
coder->writeContainerBegin(fileptr, obj, size_of(TYPE, obj), obj_size); \
\
\
\
TYPE##Iter* ptr = create(TYPE##Iter, obj); \
head(TYPE##Iter, ptr); \
do { \
	coder->writeContainerElement(fileptr, retrieve(TYPE##Iter, ptr), obj_size); \
}while(!next(TYPE##Iter, ptr)); \
\
destroy(TYPE##Iter, ptr); \
coder->writeContainerEnd(fileptr, obj, size_of(TYPE, obj), obj_size); \
return SUCCESS; \
}



// -- declaration of the existing encode method -- 

F_ENCODE(Vector);

#endif