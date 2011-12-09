#include "serialize.h"

typedef struct {
	(int*)spush(SerializeFormatter* form);
	(int*)epush(SerializeFormatter* form);
	(int*)print(SerializeFormatter* form);
	(int*)sread();
	(int*)eread();
} SerializeFormatter;


//predefined formatter
SerializeFormatter* create_SerializerFormatter_base64() {
	SerializeFormatter* form = (SerializeFormatter*)malloc(sizeof(SerializeFormatter));
	
	form->spush=push_base64_start;
	form->epush=push_base64_end;
	
	form->sread=read_base64_start;
	form->eread=read_base64_end;
	
	return form;
}

int push_base64_start(SerializeFormatter* form) {
	
}

int push_base64_end(SerializeFormatter* form);
int read_base64_start(SerializeFormatter* form);
int read_base64_end(SerializeFormatter* form);

int serializeArrayToFile(_array_struct* obj, SerializeFormatter* form, char* path) {
	FILE* f = fopen(path, "w+");
	void* data;
	size_t length;
	
	data = form->spush(obj, size(obj), obj, &length);
	fwrite(data, 1, length, f);
	free(data);
	
	print_func func = API(obj)->print;
	API(obj)->print = form->print;
	print(type, obj);
	
	data = form->epush(obj, &length);
	fwrite(data, 1, length, f);
	free(data);
	
	API(obj)->print = func;
	
	return SUCCESS;
}

int serializeListToFile(_array_struct* obj, SerializeFormatter* form, char* path) {
	
}

int unserializeArrayFromFile(_array_struct* obj, SerializeFormatter* form, char* path) {}

int serializeListFromFile(_array_struct* obj, SerializeFormatter* form, char* path) {}

#endif