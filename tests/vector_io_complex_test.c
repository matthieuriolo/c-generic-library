/*
gcc -O3 -o vector_io_complex_test ./vector_io_complex_test.c ../src/serialize.c ../src/base64.c ../lib/libcgen.a -I../libcgeneric
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
const char* filepath = "vector_io_complex_test.cbe";
const unsigned int TURNS = 10000;

void intprint(const void* number) {
  unsigned int* i = (unsigned int*)number;
  printf("%u\n", *i);
}

void printer(const void* obj) {
  Vector* vec = (Vector*)obj;
  set_print(Vector, vec, intprint);
  print_all(Vector, vec);
}

FUNC_PRINT(Vector)

int main(void) {
  clock_t builds, builde, writes, writee, reads, reade;
  
  unsigned int x, y;
  Vector* masterObject = (Vector*)malloc(sizeof(Vector));
  
  memset(masterObject, 0, sizeof(Vector));
  construct(Vector, masterObject,sizeof(Vector),FREEOBJ);
  
  fprintf(stderr, "Construct content\n");
  
  builds = clock();
  
  for(x = 0; x < TURNS; x++) {
	Vector* object = (Vector*)malloc(sizeof(Vector));
	memset(object, 0, sizeof(Vector));
	construct(Vector, object,sizeof(x),FREEOBJ);
	
	for(y = 0; y < sqrt(TURNS); y++) {
	  unsigned int t = y+x;
	  
      push_back(Vector, object, &t, STATIC);
    }
    push_back(Vector, masterObject, object, DYNAMIC);
  }
  
  builde = clock();
  
  /*fprintf(stderr, "Print content\n");
  
  set_print(Vector, masterObject, printer);
  //print_all(Vector, masterObject);
  */
  fprintf(stderr, "Write content\n");
  
  FILE* f;
  Coder* coder = createBinaryCoder();
  coder->subcoder = createBinaryCoder();
  
  /*
  Coder* coder = createBase64Coder();
  coder->subcoder = createBase64Coder();
  */
  coder->writeContainerElement = encodeElements(Vector);
  coder->readContainerElement = decodeElements(Vector);
  
  
  if(f = fopen(filepath, "w")) {
  	/* encode the vector as base64 in a file */
  	writes = clock();
  	if(encode(Vector, masterObject, f, coder) != SUCCESS)
  		fprintf(stderr, "There was an error during encoding!\n");
  	writee = clock();
  	fclose(f);
  }else
    fprintf(stderr, "Could not create or edit the file!\n");
  
  for(x = 0; x < TURNS; x++) {
  	Vector* obj = return_at_Vector(masterObject, x);
    destruct(Vector, obj);
  }
  
  destruct(Vector, masterObject);
  free(masterObject);
  
  fprintf(stderr, "Read content!\n");
  if(f = fopen(filepath, "r")) {
  	reads = clock();
    masterObject = decode(Vector, f, coder);
    reade = clock();
    
    if(masterObject) {
    	 /*fprintf(stderr, "Print the content of the decoded data in a loop\n");
    	 
    	 set_print(Vector, masterObject, printer);
  		 //print_all(Vector, masterObject);
  		 */
		 destruct(Vector, masterObject);
    }else
      fprintf(stderr, "There was an problem during the decoding\n");
    
  }else
    fprintf(stderr, "Could not read the file!\n");
  
  
  
  /* you've to release it yourself */
  free(coder->subcoder);
  free(coder);
  
  printf("======================== Perfomance for datasize %u (microseconds) ========================\n", TURNS);
  
  printf("time usage for building: %lu\n", ((builde - builds)*1000000) / CLOCKS_PER_SEC);
  printf("time usage for writing: %lu\n", ((writee - writes)*1000000) / CLOCKS_PER_SEC);
  printf("time usage for reading: %lu\n", ((reade - reads)*1000000) / CLOCKS_PER_SEC);
  
  return EXIT_SUCCESS;
}
