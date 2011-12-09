#include "base64.h"

#ifndef __SERIALIZE_H__
#define __SERIALIZE_H__

//shall ends up in the functions

int encode(TYPE, STRUCT, FILEPTR, CODER)
int encodeToFile(TYPE, STRUCT, FILEPTR, CODER)
int encodeToMemory(TYPE, STRUCT, FILEPTR, CODER)

//pushes and fetches data in the correct form
struct Coder {
	writeContainerBegin(file, obj, size, obj_size)
	writeContainerEnd(file, obj, size, obj_size)
	writeContainerElement(file, elem)
	
	readContainerBegin
	readContainerEnd
	readContainerElement
}

//shortcut
#define encode(TYPE, STRUCT, FILEPTR, CODER) encode_##TYPE##(STRUCT, FILEPTR, CODER)

//function declaration

#define F_ENCODE(TYPE, STRUCT, FILEPTR, CODER) encode_##TYPE##(TYPE* STRUCT, FILE* FILEPTR, Coder* CODER)

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


//shortcut for accessing the encoded data directly - this is quit slow and dangerous ... don't use it
void* serializeToMemory(TYPE, STRUCT, coder, size_t* length) {
	
}



#endif