#ifndef _ALG
#define _ALG


#define BIG_NUMBER 1000000
#define ARR_SIZE 100

#include <stdlib.h>
#include <stdio.h>

# endif


struct mincoins
{
	int num;
	int coins[ARR_SIZE];
	
};

struct Arr
{
	int* array;
	int size;
	int cap;
		
};

/*basic ARR constructor / destructor*/
struct Arr* createArr(int cap);

void deleteArr(struct Arr* A);


/*file system functions to read and write arrays*/

void writeArray(FILE* f , char* fn,struct Arr*);

void writeMinCoins(FILE* f ,char* fn ,struct mincoins m,int);

struct Arr* getArray(FILE *filePtr, char* filename, int lineNum);

char* myStrcat(char*,char*);


/*basic function to return min of two ints*/
int min(int a, int b);

/*Algorithms to make min change*/
struct mincoins changeslow(int A, struct Arr* K);

struct mincoins changedp(int A,struct Arr* K);

struct mincoins changegreedy(int A, struct Arr* K);