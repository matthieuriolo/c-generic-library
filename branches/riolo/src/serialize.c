#include "serialize.h"

/*

TODO:

- think about the point to insert the coder into the API and remove the CODER parameter in the encoding functions
- create the decode AKA read function
- rewrite default coder in following matter:
	Coder* coder = createCoderFormatLineSeparated();//subcoder points to NULL
	initializeCoderForBase64(coder);//initialize the subcoder
	//those functions creates a coder with a subcoder.
	//the maincoder contains as BEGIN and END function the line separating functions.
	//the subcoder contains an empty BEGIN and END function. The
	
- add format Line Separated, XML and JSON
- add value coding Base64, Base85, HEX, ASCII, Point-Line-Coding (if Bit(x)=0 then print "."; if Bit(x)=1 then print "-"; I guess that this is useful if you're using this library with microcontrollers)



- add length calculation function (may not supported by all codings)

- think about iconv and openssl
	+ support for more encryptions
	+ perfomance / library size
	- won't work without them


- write a detection function that helps to recognize what kind of data the developer want to safe.
  this helps to store the data more "human" like

- create better documentation
*/
	
	
//predefined formatter
Coder* createBase64Coder() {
	Coder* coder = (Coder*)malloc(sizeof(Coder));
	
	coder->writeContainerBegin = base64_WriteContainerBegin;
	coder->writeContainerEnd = base64_WriteContainerEnd;
	coder->writeContainerElement = base64_WriteContainerElement;
	
	//coder->subcoder = (Coder*)malloc(sizeof(Coder));
	
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

int base64_WriteContainerElement(FILE* file, const void* elem, size_t size, struct coder_t* coder) {
	char* tmp = base64_encode(elem, size);
	size_t ret = fwrite(tmp, strlen(tmp), 1, file);
	free(tmp);
	
	if(ret < 1)
		return ECODERWRITE;
	
	if(fwrite("\n", 1, 1, file) < 1)
		return ECODERWRITE;
	
	return SUCCESS;
}


int base64_ReadContainerBegin(FILE* file, const void*  obj, size_t size, size_t obj_size) {
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


int base64_ReadContainerEnd(FILE* file, const void* obj, size_t size, size_t obj_size) {
	return SUCCESS;
}

int base64_ReadContainerElement(FILE* file, const void* elem, size_t size) {
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
int xml_WriteContainerElement(FILE* file, const void* elem, size_t size, struct coder_t* coder) {
	char* tmp = base64_encode(elem, size);
	size_t ret = fprintf(file, "\t<item>%s</item>\n", tmp);
	free(tmp);
	
	if(ret == 0)
		return ECODERWRITE;
	
	return SUCCESS;
}



// -- datatypes --

F_ENCODE(Vector)
F_ENCODEELEMENTS(Vector)

/*
F_ENCODE(BinaryTree)
F_ENCODE(Queue)
...
*/