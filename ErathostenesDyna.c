/*
 ============================================================================
 Name        : ErathostenesDyna.c
 Author      : JM Mattens
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "inout.h"

/* typedef short int bool; */
typedef unsigned char bool;
#define false 0
#define true 1

#define MAX 2147483647       /* (2^31-1) */
#define MAX_UINT32 4294967295      

typedef struct TListPrimes {
    int maximum;
    int* pPrimes;
    int cPrimes;
}ListPrimes;

void InitializeTListPrimes(ListPrimes *list);
void Erathostenes(ListPrimes *list);
void ShowPrimes(ListPrimes *list);
void DestroyTListPrimes(ListPrimes *list);

int main(int argc, char* argv[]) {
    clock_t ct1, ct2;
	ListPrimes listPrimes;
    do {
        InitializeTListPrimes(&listPrimes);
        listPrimes.maximum = ReadIntLimited("\nVotre naturel maximum ? ", 0, MAX);
        ct1 = clock();
        Erathostenes(&listPrimes);
        ct2 = clock();
        printf("Duree calculs : %.2f\n", (double)(ct2 - ct1) / CLOCKS_PER_SEC);
        ShowPrimes(&listPrimes);
        DestroyTListPrimes(&listPrimes);
    } while(!Stop());
    return EXIT_SUCCESS;
}

typedef unsigned int uint32;
#define setbitarray(pba, i) (pba[i >> 5] |= (0x00000001 << (i & 0x0000001F)))
#define unsetbitarray(pba, i) (pba[i >> 5] &= ~(0x00000001 << (i & 0x0000001F)))
#define issetbitarray(pba, i) (pba[i >> 5] & (0x00000001 << (i & 0x0000001F)))

void InitializeTListPrimes(ListPrimes *list){
	list->cPrimes = 0;
	list->pPrimes = NULL;
	list->maximum = 0;
}

int* toIntArray(uint32* tab, int size){
	int* result = malloc(sizeof(int)*size);
	int j = 0;
	for(int i=0; i<size; i++){
		if(issetbitarray(tab, i)){
			result[j] = i;
			j++;
		}
	}
	return result;
}

void fillArrayWith(uint32 *tab, int size, int value){
	for(int i = 0; i<size; i++){
		tab[i]=value;
	}
}

void Erathostenes(ListPrimes *list){
	int limit = sqrt(list->maximum);
	uint32 tab[limit/32];
	fillArrayWith(tab, limit/32, MAX); //fill array with 1 bits
	unsetbitarray(tab, 0);
	unsetbitarray(tab, 1);
	for(int i=2; i<limit; i++){//read the tab until limit
		if(issetbitarray(tab, i)){//check next prime
			for(int j = i*i; j<limit; j+=i){//delete multiples
				unsetbitarray(tab,j);
			} 
		}
	}
	
	list->pPrimes = toIntArray(tab, limit);
}

void ShowPrimes(ListPrimes *list){
	printf("Il y a %d nombres premiers inférieurs à %d", list->cPrimes, list->maximum);
	for(int i=0; i<list->maximum; i++){
		printf("Nombre premier n %d: %d\n",i, list->pPrimes[i]);
	}
	Stop();
}

void DestroyTListPrimes(ListPrimes *list){
	free(list->pPrimes);
	free(list);
}
