# Tutorial

## Introduction

This tutorial should be read be everyone who wants to know how the code would feel like, what the basic functions are and, briefly, how they work.

However, we will create a little dummy applications that does collect an unlimited amount of positive numbers. If the number 0 is entered then the application will print out twice the numbers in the given order and once in ascending order. After printing the list the application will terminated himself.

## Compilation

The C Generic Library uses the build system http://en.wikipedia.org/wiki/GNU_build_system from GNU. Read the article https://github.com/matthieuriolo/c-generic-library/blob/master/COMPILE.md if you want to know how to compile the library.


You can use the below statements for compiling the tutorial sourcecode or any other simple application that uses the c generic library.

### Library installed

```
gcc -lcgeneric tutorial.c -o tutorial
```

### Library uninstalled

```
gcc -i<pathToLibcgeneric> <pathToLibcgeneric>/libs/libcgen.a tutorial.c -o tutorial
```


The explanation of the command line _gcc_ does not belong to the topics of this tutorial. If you need to know more about gcc then visit the page [http://linux.die.net/man/1/gcc GCC's manpage].



## Our First step

Create a new file and write into it the skeleton of a C file. Extend your code be including the needed header files. Like the most linux libraries the c generic library  provides a "main headerfile" that is called libcgeneric.h. Actually the headerfile does nothing else than including all other libcgeneric header files.

```
//all headers of the library are bundled in the directory libcgeneric
#include "libcgeneric/libcgeneric.h"

//memset is defined in string.h
#include <string.h>
//printf scanf is defined in stdio.h
#include <stdio.h>
//malloc etc is defined in stdlib.h
#include <stdlib.h>
```

If you use this code above with the installed version of the library then it is necessary that you use angle brackets.


Then create a new variable with the type "List" and call it container. Mind that the construction functions of libcgeneric expects that all fields of the datatype is set to NULL.

```
List container;
memset(&container, 0, sizeof(container));
```


The most easiest way to find out which datatypes are possible is to look into the including directory of libcgeneric. There exists for each datatypes a headerfile. If you've installed the library then you can access the description over the manpage. To do this just search for the datatype (the first letter must be capital).

```
man List
```

Now we need to initialize the container. All datatypes have a function called construct{{{_<}}}datatype>. To find out which generic functions exists look into the file <libcgenericIncludingPath>/gen/function_macros.h. You can also use the _man_ command (passing the filename) for displaying a description.

```
man list.h
```

For initializing you just need to call the _construct_ function.

```
construct(List, &container, sizeof(unsigned int), FREEOBJ);
```

All generic functions have at least two parameters. The construct functions takes following four:

- List: The datatype you're using
- container: the object that contains the data
- sizeof(unsigned int): Declare how big the data is that you want to store in the container
- FREEOBJ: Declares if the container should giove the free the memory that it is used to store the values. Use the "NOFREE" flag if you still use those objects (ex. pointing at them).



## Using c generic library

The next step in our dummy application is to read in the data and to store them in the list. Depending the type of your container you have to use a different insertion function. You can get more information in the datatype specific header files and manpages.


```
while(1) {
	//alloc the data
	unsigned int* t = (unsigned int*)malloc(sizeof(unsigned int));
	//read it in
	scanf("%u", t);
	
	//push the data
	//we're handling the memory of the element, so just pass the pointer)
	push(List, &container, t, DYNAMIC);
	
	//if the user entered 0 then break the loop
	if(*t==0)
		break;
}
```


The insertion functions take usually following parameters:
- List: The datatype
- List: The container
- t: A pointer to the value we want to store
- DYNAMIC: A flag that indicates if the value should be copied or if the developer is managing the memory. DYNAMIC means that the developer it does (see the parameter FREEOBJ in construct).


## API functions


If you just want to have simple dump of your container then you should use the api functions of the c generic library. All the datatypes defines an own abstraction layer that allows to interact with the managment of the elements in the container. Currently following possibilites exists to manage the elements:
	

name | default | description
---------------------
alloc | malloc | Used to alloc new memory
dealloc - free | Used to dealloc memory
cmp | memcmp | This functions is called if the container is comparing two elements
copy | memcpy | Used to copy an element
print | NULL | This functions is used to print the elements


Write following code above your main function: 

```
void myPrintFunction(const void *element) {
	//cast it to the right type and format the output string
	printf("%u\n", (*(const unsigned int *) element));
}
```

The container works with pointers and does not know (neither care) what kind of data you're storing. This is the reason why you have define a "print" function that convert the data into the right format.

For making the container use this functions you need to call the bellow function after the construct function:

```
set_print(List, &container, myPrintFunction);
```


For printing the content of the container we only need to call the print_all functions.

```
print_all(List, &container);
```



## Iterating

The function print_all does actually nothing else the iterating through the container. For iterating through the list we need to create at first an iterator the is bound against our container.

```
ListIter* iterator = create(ListIter, &container); 
```

The function "create" alloces an iterater that is bound to our object container. That means that *i* is always pointing at an element from *container*.

You can use the generic functions retrieve, next, previous and head for reseting the iteratorposition. There exists also a function called empty which checks if there is any element inside the container.

```
if(!empty(List, iterator)){
	head(ListIter, iterator);
	do {
		printf("%u\n", *((unsigned int*)retrieve(ListIter, iterator)));
	}while(!next(ListIter, iterator));
}
``` 


## Sorting

The most datatype contains a function for sorting. As already said the container does not know what it is storing. if we want to sort them in ascending order we have to set the correct comparison function in the containers API:

```
int unintcmp(const void* a, const void* b, size_t x UNUSED) {
	return (*((unsigned int*)a)>*((unsigned int*)b))-(*((unsigned int*)a)<*((unsigned int*)b));
}
```


The parameter x with the flag "UNUSED" is an optional parameter. You can use the print function again to display the content in the terminal.


## Destruct

The container has alloced memory for storing the elementspointer and the iterator is automatically alloced. So how to give free those memories? Like all the functions we have used till yet there exists also a macro that expands to the correct sub-function.


```
destroy(ListIter, i);
destruct(List, &container);
```

## Source
The whole code for this small project is available at https://github.com/matthieuriolo/c-generic-library/blob/master/tutorial.c



We hope you'll enjoy it!
