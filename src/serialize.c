#include "serialize.h"

/*

TODO:

- think about the point to insert the coder into the API and remove the CODER parameter in the encoding functions
- make the coder simpler
	coder {
		push_begin(obj, size(obj), &length)// obj is passed for the case that you want to insert more information
		push_end(obj, size(obj), &length)
		
		coder* element_coder //pointer to the same type of structure but with different functions
	}



- create the decode AKA read function
- Create a makro for the standard-coder creators (signatur + prototype)

-rewrite the coder to this structures (rethink about that...):

typedef Coder_t struct {
	writeContainerStart
	writeContainerEnd
	writeContainerValue
	
	Coder_t* subcoder;
} Coder;


this structure is more sophisticated because the programmer
can simpler declare the container typ and the value encoding

- remove the predefined formatter and store them in the files serialize_coder.c / .h
- rewrite default coder in following matter:
	Coder* coder = createCoderFormatLineSeparated();//subcoder points to NULL
	initializeCoderForBase64(coder);//initialize the subcoder
	//those functions creates a coder with a subcoder.
	//the maincoder contains as BEGIN and END function the line separating functions.
	//the subcoder contains an empty BEGIN and END function. The
	
- add format Line Separated, XML and JSON
- add value coding Base64, Base85, HEX, ASCII, Point-Line-Coding (if Bit(x)=0 then print "."; if Bit(x)=1 then print "-"; I guess that this is useful if you're using this library with microcontrollers) 
*/
	
	
//predefined formatter
Coder* createBase64Coder() {
	Coder* coder = (Coder*)malloc(sizeof(Coder));
	
	coder->writeContainerBegin = base64_WriteContainerBegin;
	coder->writeContainerEnd = base64_WriteContainerEnd;
	coder->writeContainerElement = base64_WriteContainerElement;
	
	return coder;
}


int base64_WriteContainerBegin(FILE* file, const void*  obj, size_t size, size_t obj_size) {
	char* tmp = base64_encode(&size, sizeof(size));
	size_t ret = fwrite(tmp, strlen(tmp), 1, file);
	free(tmp);
	
	if(ret < 1)
		return ECODERWRITE;
	
	if(fwrite("\n", 1, 1, file) < 1)
		return ECODERWRITE;
	
	tmp = base64_encode(&obj_size, sizeof(obj_size));
	ret = fwrite(tmp, strlen(tmp), 1, file);
	free(tmp);
	
	if(ret < 1)
		return ECODERWRITE;
	
	if(fwrite("\n", 1, 1, file) < 1)
		return ECODERWRITE;
	
	return SUCCESS;
}


int base64_WriteContainerEnd(FILE* file, const void* obj, size_t size, size_t obj_size) {
	return SUCCESS;
}

int base64_WriteContainerElement(FILE* file, const void* elem, size_t size) {
	char* tmp = base64_encode(elem, size);
	size_t ret = fwrite(tmp, strlen(tmp), 1, file);
	free(tmp);
	
	if(ret < 1)
		return ECODERWRITE;
	
	if(fwrite("\n", 1, 1, file) < 1)
		return ECODERWRITE;
	
	return SUCCESS;
}



Coder* createXMLCoder() {
	Coder* coder = (Coder*)malloc(sizeof(Coder));
	
	coder->writeContainerBegin = xml_WriteContainerBegin;
	coder->writeContainerEnd = xml_WriteContainerEnd;
	coder->writeContainerElement = xml_WriteContainerElement;
	
	return coder;
}


int xml_WriteContainerBegin(FILE* file, const void*  obj, size_t size, size_t obj_size) {
	if(fprintf(file, "<data count=\"%lu\" size=\"%lu\">\n", size, obj_size)==0)
		return ECODERWRITE;
	
	return SUCCESS;
}


int xml_WriteContainerEnd(FILE* file, const void* obj, size_t size, size_t obj_size) {
	if(fprintf(file, "</data>\n")==0)
		return ECODERWRITE;
	
	return SUCCESS;
}

/* You've to overwrite this function for a proper xml representation (with proper is meant that it is readable for human) */
int xml_WriteContainerElement(FILE* file, const void* elem, size_t size) {
	char* tmp = base64_encode(elem, size);
	size_t ret = fprintf(file, "\t<item>%s</item>\n", tmp);
	free(tmp);
	
	if(ret == 0)
		return ECODERWRITE;
	
	return SUCCESS;
}



// -- datatypes --

FUNC_ENCODE(Vector)

/*
FUNC_ENCODE(BinaryTree)
FUNC_ENCODE(Queue)
...
*/