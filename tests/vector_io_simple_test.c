/*
gcc -o vector_io_simple_test ./vector_io_simple_test.c ../src/serialize.c ../src/base64.c ../lib/libcgen.a -I../libcgeneric
*/


#include <stdio.h>
#include <stdlib.h>

#include "libcgeneric.h"
#include "serialize.h"

const char* filepath = "vector_io_simple_test.cbe";
const unsigned int TURNS = 1000;

void printer(const void* number) {
  printf("%u\n", *(unsigned int*)number);
}

FUNC_PRINT(Vector)

int main(void) {
  unsigned int x;
  Vector* masterObject = (Vector*)malloc(sizeof(Vector));
  
  memset(masterObject, 0, sizeof(Vector));
  construct(Vector, masterObject,sizeof(int),FREEOBJ);
  
  printf("Construct content\n");
  
  for(x = 0; x < TURNS; x++) {
	unsigned int* val=malloc(sizeof(x));
	*val = x;
    push_back(Vector, masterObject, val, DYNAMIC);
  }
  
  printf("Print content\n");
  
  set_print(Vector, masterObject, printer);
  print_all(Vector, masterObject);
  
  
  printf("Write content\n");
  
  FILE* f;
  
  Coder* coder = createBase64Coder();
  coder->subcoder = createBase64Coder();
  
  
  /*
  Coder* coder = createXMLCoder();
  coder->subcoder = createXMLCoder();
  coder->writeContainerElement = encodeElements(Vector);
  */
  
  if(f = fopen(filepath, "w")) {
  	/* encode the vector as base64 in a file */
  	if(encode(Vector, masterObject, f, coder) != SUCCESS)
  		printf("There was an error during encoding!\n");
  	fclose(f);
  }else
    printf("Could not create or edit the file!\n");
  
  
  for(x = 0; x < 10; x++) {
  	int* obj = return_at_Vector(masterObject, x);
    //free(obj);
  }
  
  destruct(Vector, masterObject);
  free(masterObject);
  
  printf("Read content!\n");
  if(f = fopen(filepath, "r")) {
    masterObject = decode(Vector, f, coder);
    
    if(masterObject) {
    	 printf("Print the content of the decoded data in a loop\n");
    	 
    	 set_print(Vector, masterObject, printer);
  		 print_all(Vector, masterObject);
  		 /*printf("%lu   <<<-----\n", size_of(Vector, masterObject));
    	 /*VectorIter *ptr;
		 ptr = create(VectorIter, masterObject);
		 
		 head(VectorIter,ptr);
		 do {
		   //intprint(retrieve(VectorIter, ptr));
	     }while (!next(VectorIter, ptr));
			  
		 destroy(VectorIter,ptr);*/
		 destruct(Vector, masterObject);
    }else
      printf("There was an problem during the decoding\n");
    
  }else
    printf("Could not read the file!\n");
  
  
  
  /* you've to release it yourself */
  free(coder);
  
  return EXIT_SUCCESS;
}
