/*
gcc -o vector_io_test ./vector_io_test.c ../src/serialize.c ../src/base64.c ../lib/libcgen.a -I../libcgeneric
*/


#include <stdio.h>
#include <stdlib.h>

#include "libcgeneric.h"
#include "serialize.h"

/*
cbe stands for Container as Base64 Encoded

for remembering what kind of container was used to manage the elements you should replace the C through the
first letter of the containername

Suggestion =>
Vector: .vbe
Queue: .qbe
Dequeue: .dbe
Heap: .hbe
BinaryTree: .bbe
List: .lbe
PriorityList: .pbe

OpenHashTable: .obe
ClosedHashTable: .cbe

StackList: .tbe (last letter in this case here)
StackVector: .rbe
*/
const char* filepath = "vector_io_test.cbe";


void intprint(const void* number) {
  printf("%u\n", *(unsigned int*)number);
}

void printer(const void* obj) {
  Vector* vec = (Vector*)obj;
  set_print(Vector, vec, intprint);
  print_all(Vector, vec);
  printf("\n");
}

FUNC_PRINT(Vector)

int main(void) {
  unsigned int x, y;
  Vector* masterObject = (Vector*)malloc(sizeof(Vector));
  
  memset(masterObject, 0, sizeof(Vector));
  construct(Vector, masterObject,sizeof(Vector),FREEOBJ);
  
  fprintf(stderr, "Construct content\n");
  
  for(x = 0; x < 10; x++) {
	Vector* object = (Vector*)malloc(sizeof(Vector));
	memset(object, 0, sizeof(Vector));
	construct(Vector, object,sizeof(x),FREEOBJ);
	
	for(y = 0; y < 3; y++) {
	  unsigned int t = y+x;
	  
      push_back(Vector, object, &t, STATIC);
    }
    push_back(Vector, masterObject, object, DYNAMIC);
  }
  
  fprintf(stderr, "Print content\n");
  
  set_print(Vector, masterObject, printer);
  print_all(Vector, masterObject);
  
  
  fprintf(stderr, "Write content\n");
  
  FILE* f;
  
  Coder* coder = createBase64Coder();
  coder->subcoder = createBase64Coder();
  coder->writeContainerElement = encodeElements(Vector);
  
  /*
  Coder* coder = createXMLCoder();
  coder->subcoder = createXMLCoder();
  coder->writeContainerElement = encodeElements(Vector);
  */
  if(f = fopen(filepath, "w")) {
  	/* encode the vector as base64 in a file */
  	if(encode(Vector, masterObject, f, coder) != SUCCESS)
  		fprintf(stderr, "There was an error during encoding!\n");
  	fclose(f);
  }else
    fprintf(stderr, "Could not create or edit the file!\n");
  
  
  for(x = 0; x < 10; x++) {
  	Vector* obj = return_at_Vector(masterObject, x);
    destruct(Vector, obj);
    //free(obj);
  }
  
  destruct(Vector, masterObject);
  free(masterObject);
  
  /*fprintf(stderr, "Read content!\n");
  if(f = fopen(filepath, "r")) {
    object = decode(Vector, f, coder);
    
    if(object) {
    	 fprintf(stderr, "Print the content of the decoded data in a loop\n");
    	 
    	 VectorIter *ptr;
		 ptr = create(VectorIter,  object);
		 
		 head(VectorIter,ptr);
		 do {
		   intprint(retrieve(VectorIter, ptr));
	     }while (!next(VectorIter, ptr));
			  
		 destroy(VectorIter,ptr);
		 destruct(Vector,object);
    }else
      fprintf(stderr, "There was an problem during the decoding\n");
    
  }else
    fprintf(stderr, "Could not read the file!\n");
  
  
  
  /* you've to release it yourself */
  free(coder->subcoder);
  free(coder);
  
  return EXIT_SUCCESS;
}
