#ifndef _A
#define _A

#include <stdlib.h>
#include <stdio.h>


# endif

struct mincoins;

struct Arr
{
	int* array;
	int size;
	int cap;
		
};

/*basic ARR constructor / destructor*/
struct Arr* createArr(int cap);

void deleteArr(struct Arr* A);



void writeArray(FILE* f , char* fn,struct Arr*);

void writeMinCoins(FILE* f ,char* fn ,struct mincoins m,int);

struct Arr* getArray(FILE *filePtr, char* filename, int lineNum);
