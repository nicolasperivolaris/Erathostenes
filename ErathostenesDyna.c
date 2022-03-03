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
        /*ShowPrimes(&listPrimes);*/
        DestroyTListPrimes(&listPrimes);
    } while(!Stop());
    return EXIT_SUCCESS;
}

typedef unsigned int uint32;
typedef unsigned long int ulong64;
#define setbitarray(pba, i) (pba[i >> 5] |= (0x00000001 << (i & 0x0000001F)))
#define unsetbitarray(pba, i) (pba[i >> 5] &= ~(0x00000001 << (i & 0x0000001F)))
#define issetbitarray(pba, i) (pba[i >> 5] & (0x00000001 << (i & 0x0000001F)))

void InitializeTListPrimes(ListPrimes *list){
	list->cPrimes = 0;
	list->pPrimes = NULL;
	list->maximum = 0;
}

void toIntArray(uint32* tab, ListPrimes *list){	
	uint32 nbByte = sizeof(int)*list->cPrimes;
	int* result = malloc(nbByte);
	int i, j = 0;
	
	result[j++] = 2;
	for(i=3; (j<list->cPrimes) && (i<list->maximum); i+= 2){
		if(!issetbitarray(tab, i)){ 
			result[j] = i;
			j++;
		}
	}
	list->pPrimes = result;
}

void fillArrayWith(uint32 *tab, int size, int value){
	int i;
	for(i = 0; i<size; i++){
		tab[i]=value;
	}
}

void Erathostenes(ListPrimes *list){
	ulong64 i;
	long nbInt = (list->maximum-1)/sizeof(uint32)+1;
	uint32 *tab = calloc(nbInt, sizeof(uint32));
	/*if prime -> 0, if not -> 1*/
	setbitarray(tab, 0); 
	setbitarray(tab, 1);
	
	for(i=3; i*i<=list->maximum; i+=2){/*read the tab until limit*/
		if(!issetbitarray(tab, i)){/*if not already checked*/
			ulong64 j;
			for(j = i*i; j<=list->maximum; j+=2*i){
					setbitarray(tab,j);
			}
		} 
	}
	list->cPrimes++;
	
	for(i = 3; i<=list->maximum; i+=2){
		if(!issetbitarray(tab, i)){
			list->cPrimes++;
		}
	}
	toIntArray(tab, list);
}

void ShowPrimes(ListPrimes *list){
	int i;
	printf("Il y a %d nombres premiers inferieurs a %d\n", list->cPrimes, list->maximum);	for(i=0; i<list->cPrimes; i++){
		printf("Nombre premier n%d: %d\n",i, list->pPrimes[i]);
	}
	Stop();
}

void DestroyTListPrimes(ListPrimes *list){
	free(list->pPrimes);
	free(list);
}
