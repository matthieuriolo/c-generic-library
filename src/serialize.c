#include "serialize.h"

/*

TODO:

- think about the point to insert the coder into the API and and remove the CODER parameter in the encoding functions
- proper FUNC, PROTO ec. declarations
- change the name formatter to coder
- make the coder simpler
	coder {
		push_begin(obj, size(obj), &length)// obj is passed for the case that you want to insert more information
		push_end(obj, size(obj), &length)
		
		coder* element_coder //pointer to the same type of structure but with different functions
	}



- create the decode AKA read function
*/




//predefined formatter
Coder* createBase64Coder() {
	Coder* coder = (Coder*)malloc(sizeof(Coder));
	/*
	coder->spush=push_base64_start;
	coder->epush=push_base64_end;
	
	coder->sread=read_base64_start;
	coder->eread=read_base64_end;
	*/
	return coder;
}




/*
int serializeArrayToFile(_array_struct* obj, Coder* form, char* path) {
	FILE* f = fopen(path, "w+");
	void* data;
	size_t length;
	
	data = form->spush(obj, size(obj), obj, &length);
	fwrite(data, 1, length, f);
	free(data);
	
	print_func func = API(obj)->print;
	API(obj)->print = form->print;
	print(type, obj);
	
	data = form->epush(obj, size(obj), &length);
	fwrite(data, 1, length, f);
	free(data);
	
	API(obj)->print = func;
	
	return SUCCESS;
}

int serializeListToFile(_array_struct* obj, SerializeFormatter* form, char* path) {
	
}

int unserializeArrayFromFile(_array_struct* obj, SerializeFormatter* form, char* path) {}

int serializeListFromFile(_array_struct* obj, SerializeFormatter* form, char* path) {}
*/