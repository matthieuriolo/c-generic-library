#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "gen/error_macros.h"

#define RUNS 10000
#define BOUND 10000
#define NUMCASES 3
#define CAPACITY 1000000

uint32_t inthash(void *,size_t);
void print_hash(const void *a);
int main(void)
{
        CHTable hashtable, *dupe;
        CHTableIter *hiter;
        int item;
        int x = RUNS, y;

        memset(&hashtable,0,sizeof(hashtable));
        construct(CHTable,&hashtable,CAPACITY,FREEOBJ);
        set_hash_CHTable(&hashtable,num_hash);
        set_print(CHTable,&hashtable,print_hash);
        for(y = 0; y < x; y++) {
                srand((unsigned int)((x * y) / (x - y) + (x + y / x)));
                switch(rand() % NUMCASES) {
					default:
                case 0:
                        item = rand() % CAPACITY;
                        /*printf("Inserting %d\n",item);*/
                        insert(CHTable,&hashtable,&item,STATIC);
                        break;
                case 1:
                        item = rand() % CAPACITY;
                        if(find(CHTable,&hashtable,&item)) {
                                /*printf("%d found\n",item);*/
                        } else {
                                /*printf("%d not found\n",item);*/
                        }
                        break;
                case 2:
                        item = rand() % CAPACITY;
                        if(delete(CHTable,&hashtable,&item)) {
                                /*printf("%d not deleted\n",item);*/
                        } else {
                                /*printf("%d deleted\n",item);*/
                        }
                        break;
                };
        }
        print_all(CHTable,&hashtable);
        printf("Now testing the iterators\n");
        hiter = create(CHTableIter,&hashtable);
        head(CHTableIter,hiter);
        do {
                item = *(int *)retrieve(CHTableIter,hiter);
        } while(!next(CHTableIter,hiter));
        assign(CHTableIter,hiter,&hashtable);
        tail(CHTableIter,hiter);
        do {
                item = *(int *)retrieve(CHTableIter,hiter);
        } while(!prev(CHTableIter,hiter));
        destroy(CHTableIter,hiter);
        dupe = duplicate(CHTable,&hashtable);
        hiter = create(CHTableIter,dupe);
        head(CHTableIter,hiter);
        do {
                item = *(int *)retrieve(CHTableIter,hiter);
        } while(!next(CHTableIter,hiter));
        assign(CHTableIter,hiter,dupe);
        tail(CHTableIter,hiter);
        do {
                item = *(int *)retrieve(CHTableIter,hiter);
        } while(!prev(CHTableIter,hiter));
        destroy(CHTableIter,hiter);
        destruct(CHTable,&hashtable);
        destruct(CHTable,dupe);
        free(dupe);
	return EXIT_SUCCESS;
}

uint32_t inthash(void *a, size_t len)
{
        uint32_t h_index = 0;
        char *ptr = (char *)a;
        while(len--) {
                h_index += (ptr[len]  *  13);
                h_index +=  ptr[len]<< 7;
                h_index +=  (h_index >> 3);
        }
        return h_index;
}

void print_hash(const void *a)
{
        printf("%d ",*(int32_t *)a);
}
