/*
gcc -o base64_test -I../libcgeneric/ ../src/base64.c ./base64_test.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "base64.h"



int main() {
	
	char a = 'Z';
	void* b = malloc(3);
	int c = 7564321;
	char* x;
	
	FILE* f = fopen("./base64_output", "w");
	
	x = base64_encode(&a, sizeof(a));
	fwrite(x, strlen(x), 1, f);
	fwrite("\n", 1, 1, f);
	free(x);
	
	x = base64_encode(&c, sizeof(c));
	fwrite(x, strlen(x), 1, f);
	fwrite("\n", 1, 1, f);
	free(x);
	
	memset(b, 111, 3);
	x = base64_encode(&b, sizeof(b));
	printf("%lu\n", strlen(x));
	fwrite(x, strlen(x), 1, f);
	fwrite("\n", 1, 1, f);
	free(x);
	free(b);
	
	x = base64_encode(&b, sizeof(b));
	printf("%lu\n", strlen(x));
	fwrite(x, strlen(x), 1, f);
	fwrite("\n", 1, 1, f);
	free(x);
	
	fclose(f);
	
	size_t t;
	char* strA = "aaaa";
	x = base64_encode(strA, strlen(strA));
	char* strB = (char*)base64_decode(x, &t);
	printf("gives me %s\n", x);
	
	if(t + 1 != strlen(strA))
		printf("different object size during the base64 encode %lu %lu\n", strlen(strA), t);
	if(strcmp(strA, strB) != 0)
		printf("different value %s %s\n", strA, strB);
	
	free(strB);
	
	
	size_t d = 10;
	x = base64_encode(&d, sizeof(d));
	size_t* e = base64_decode(x, &t);
	
	if(t != sizeof(d))
		printf("different object size during the base64 encode %lu %lu\n", sizeof(d), t);
	if(e == NULL)
		printf("failure - points to null\n");
	if(*e != d)
		printf("different value %lu %lu\n", *e, d);
	free(e);
	
	
	//8 388 608
	for(d = 0; d < (size_t) -1; d++) {
		x = base64_encode(&d, sizeof(d));
		size_t* m = base64_decode(x, &t);
		
		if(m == NULL || *m != d) {
			printf("the string '%s' creates an failure when it hits the number %lu\n", x, d);
			return EXIT_SUCCESS;
		}
		
		if(m != NULL)
			free(m);
		free(x);
	}
	
	return EXIT_SUCCESS;
}