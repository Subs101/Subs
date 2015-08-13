#ifndef _A
#define _A

#include <stdlib.h>
#include <stdio.h>
#define BUFFER 200
#define MAX_INT 3000000
#define BIG_NUM 3000000000
#define SOLVE_TIME 20


enum data
{
	CITY,
	X,
	Y,
	ORDER,
};




struct Arr
{
	int* array;
	int size;
	int cap;
		
};


struct Arr2D
{
	int** array;
	int *size;
	int cap_row;
	int cap_col;
	double dist;
};



/*basic ARR constructor / destructor*/
struct Arr* createArr(int cap);
void deleteArr(struct Arr* A);

struct Arr2D* create2DArr(int cap_row,int cap_col);
void delete2DArr(struct Arr2D* A);


void writeArray(FILE* f , char* fn,struct Arr*);
struct Arr* getArray(FILE *filePtr, char* filename, int lineNum);
# endif