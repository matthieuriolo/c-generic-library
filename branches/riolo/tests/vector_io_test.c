#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "gen/error_macros.h"
#include "serialize.h"


const char* filepath = "vector_io_test.txt";

int main(void) {
  
  
  fprintf(stderr, "Create a vector with the numbers 1 to 10\n");
  
  Vector  object;
  unsigned int x, y;
  memset(&object, 0, sizeof (object));
  construct(Vector, &object,sizeof(x),FREEOBJ);
  
  for (x = 0; x < 10; x++) {
    push_back(Vector,  &object, &x, DYNAMIC);
  }
  
  fprintf(stderr, "Write the vector down!\n");
  
  FILE* f;
  
  if(f = fopen(filepath, "w")) {
  	/* you can change the coder the way you want to */
  	SerializeFormatter* coder = create_SerializerFormatter_base64();
  	/* encode the vector as base64 in file vector_io_test.txt */
  	encode(Vector, &object, f, coder);
  	/* you've to release yourself */
  	free(coder);
  	fclose(f);
  }else
    fprintf(stderr, "Could not create or edit the file!\n");
  
  if() {
  
  }else
    
  
  
  VectorIter *ptr;
  ptr = create(VectorIter,  &object);
  
  head(VectorIter,ptr);
  do {
    value = *(unsigned int *) retrieve(VectorIter, ptr);
	/*printf("%d ",value);*/
  }
  while (!next(VectorIter, ptr));
  
  destroy(VectorIter,ptr);
  destruct(Vector,&object);
  
  return EXIT_SUCCESS;
}
