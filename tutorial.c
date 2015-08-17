/* 
 * 
 * All codes and statements are licensed equally to the lib-c-generic library.
 * 
 * 
 * 
 * compile with built library:
 * gcc -i<pathToLibcgeneric> <pathToLibcgeneric>/libs/libcgen.a tutorial.c -o tutorial
 * 
 * 
 * compile with installed library:
 * gcc -lcgeneric tutorial.c -o tutorial
 * 
 * 
 */

//include some basic system header files
#include <stdio.h>
#include <limits.h>
#include <string.h>

//include the installed libcgeneric library
//#include <libcgeneric/libcgeneric.h>

//include the built libcgeneric library
#include "libcgeneric/libcgeneric.h"

//declare the output function used by our list
void print(const void *element);

//declaration of the comparison function
int intcmp(const void* a, const void* b, size_t x UNUSED);


//main function
int main() {
	//print out some application instructions
	printf("Enter some numbers that are bigger than 0 and smaller than %u\n", UINT_MAX);
	printf("If you enter the number 0 the applications will print out all given numbers as a sorted list\n\n---- Input --------------\n\n");
	
	
	//declare a c-generic datatype
	List container;
	
	//initialize the list
	memset(&container, 0, sizeof(List));
	construct(List, &container, sizeof(unsigned int), FREEOBJ);
	
	
	
	while(1) {
		//read out an element
		unsigned int* t=malloc(sizeof(unsigned int));
		scanf("%u", t);
		
		//add it to the list
		push_back(List, &container, t, DYNAMIC);
		
		//break if zero is the input
		if(*t==0)
			break;
	}
	
	
	printf("\n\n---- Unsorted --------------\n\n");
	
	//set print functions
	set_print(List, &container, print);
	
	//print all element in our list
	print_all(List, &container);
	
	
	//lets have fun with iterators (instead using print_all)
	printf("\n\n---- Iterators --------------\n\n");
	
	ListIter* i = create(ListIter, &container);
	//check if it is empty - this will never happen
	if(!empty(List, &container)) {
		//place the iterator at the first element
		head(ListIter, i);
		
		do {
			printf("%u\n", *((unsigned int*)retrieve(ListIter, i)));
			
		}while(!next(ListIter, i));
	}
	
	//give the memory free
	destroy(ListIter, i);
	
	
	printf("\n\n---- Sorted ASC --------------\n\n");
	
	//set the sort functions
	set_compare(List, &container, intcmp);
	
	//use the in-place sort
	sort(List, &container);
	
	
	print_all(List, &container);
	
	
	//give the memory free
	destruct(List, &container);
	
	printf("\n\n");
	return 0;
}

//write the print function
void print(const void *element) {
	//cast it to the right type and format the output string
	printf("%u\n", (*(const unsigned int *) element));
}

//write the comparison function
int intcmp(const void* a, const void* b, size_t x UNUSED) {
	/* see note 1*/
	return (*((unsigned int*)a)>*((unsigned int*)b))-(*((unsigned int*)a)<*((unsigned int*)b));
}