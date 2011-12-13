#include "base64.h"

#ifndef __SERIALIZE_H__
#define __SERIALIZE_H__

/*
 *
 * Coder Structure
 * The encode/decode method uses this structures to create the correct format
 */
typedef struct {
	void (*writeContainerBegin)(FILE* file, const void*  obj, size_t size, size_t obj_size);
	void (*writeContainerEnd)(FILE* file, const void* obj, size_t size, size_t obj_size);
	void (*writeContainerElement)(FILE* file, const void* elem);
	
	/*readContainerBegin
	readContainerEnd
	readContainerElement*/
} Coder;





//predefined formatter
Coder* createBase64Coder();



// -- shortcuts -- 
//std serializer that writes everything to a FILE pointer (can be used for sockets to)
#define encode(TYPE, STRUCT, FILEPTR, CODER) encode_##TYPE(STRUCT, FILEPTR, CODER)
//serializer that writes everything to a specific file
#define encodeToFile(TYPE, STRUCT, FILEPATH, CODER) encodeToFile_##TYPE(STRUCT, FILEPATH, CODER)
//serializer that writes everything to memory
#define encodeToMemory(TYPE, STRUCT, LENGTH, CODER) encodeToFile_##TYPE(STRUCT, LENGTH, CODER)



// -- function declaration -- 
//signature for encode
#define F_ENCODE(TYPE) int encode_##TYPE(TYPE* STRUCT, FILE* FILEPTR, Coder* CODER)



//definition of the content
#define FUNC_ENCODE(TYPE) { \
CODER->writeContainerBegin(fileptr, obj, size(TYPE, STRUCT), O(STRUCT)); \
\
\
\
TYPE##Iter* ptr = create(TYPE##Iter, STRUCT); \
head(TYPE##Iter, ptr); \
do { \
	CODER->writeContainerElement(file, retrieve(TYPE##Iter, ptr)); \
}while(!next(BinaryTreeIter, ptr)); \
\
CODER->writeContainerEnd(fileptr, obj, size(TYPE, STRUCT), O(STRUCT)); \
}





// -- declaration of the existing encode method -- 

F_ENCODE(Vector);

#endif