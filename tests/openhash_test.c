#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "gen/error_macros.h"

#define RUNS 10000
#define BOUND 10000
#define NUMCASES 3
#define CAPACITY 1000000

int32_t inthash(void *,size_t);
void print_hash(const void *a);
int main(void)
{
        OHTable hashtable,*dupe;
        OHTableIter *hiter;
        int item;
        int x = RUNS, y;

        memset(&hashtable,0,sizeof(hashtable));
        construct(OHTable,&hashtable,CAPACITY,FREEOBJ);
        set_hash_OHTable(&hashtable,num_hash);
        set_print(OHTable,&hashtable,print_hash);
        for(y = 0; y < x; y++) {
                srand((x * y) / (x - y) + (x + y / x));
                switch(rand() % NUMCASES) {
					default:
                case 0:
                        item = rand() % CAPACITY;
                        /*printf("Inserting %d\n",item);*/
                        insert(OHTable,&hashtable,&item,STATIC);
                        break;
                case 1:
                        item = rand() % CAPACITY;
                        if(find(OHTable,&hashtable,&item)) {
                                /*printf("%d found\n",item);*/
                        } else {
                                /*printf("%d not found\n",item);*/
                        }
                        break;
                case 2:
                        item = rand() % CAPACITY;
                        if(delete(OHTable,&hashtable,&item)) {
                                /*	printf("%d not deleted\n",item);*/
                        } else {
                                /*printf("%d deleted\n",item);*/
                        }
                        break;
                };
        }
        print_all(OHTable,&hashtable);
        printf("Now testing the iterators!\n");
        hiter = create(OHTableIter,&hashtable);
        head(OHTableIter,hiter);
        do {
                item = *(int*)retrieve(OHTableIter,hiter);
        } while(!next(OHTableIter,hiter));
        assign(OHTableIter,hiter,&hashtable);
        tail(OHTableIter,hiter);
        do {
                item = *(int*)retrieve(OHTableIter,hiter);
        } while(!prev(OHTableIter,hiter));
        destroy(OHTableIter,hiter);
        dupe = duplicate(OHTable,&hashtable);
        hiter = create(OHTableIter,dupe);
        head(OHTableIter,hiter);
        do {
                item = *(int*)retrieve(OHTableIter,hiter);
        } while(!next(OHTableIter,hiter));
        assign(OHTableIter,hiter,dupe);
        tail(OHTableIter,hiter);
        do {
                item = *(int*)retrieve(OHTableIter,hiter);
        } while(!prev(OHTableIter,hiter));
        destroy(OHTableIter,hiter);
        destruct(OHTable,&hashtable);
        destruct(OHTable,dupe);
        free(dupe);
	return EXIT_SUCCESS;
}

int32_t inthash(void *a, size_t len)
{
        int32_t h_index = 0;
        char *ptr = (char *)a;
        size_t x;
        for(x = 0; x < len; x++) {
                h_index += (ptr[x]  *  13);
                h_index +=  ptr[x]<< 7;
                h_index +=  (h_index >> 3);
        }
        return h_index;
}

void print_hash(const void *a)
{
        printf("%d ",*(int32_t *)a);
}
