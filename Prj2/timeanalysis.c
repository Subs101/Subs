#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "change_alg.h"
#define BILLION 1000000000L

int main()
{
	int i,j,l;
	int n = 4;
	int A = 5;
	int* K = malloc(sizeof(int)*n);
	struct Arr* k = createArr(n);
	int R[4] = {1,3,7,12};
	char* fn = "timeslow.txt";
	char* fn1 = "timedp.txt";
	char* fn2 = "timegreedy.txt";
	double d;
	uint64_t diff;
	FILE* fp = fopen(fn1,"w+");
	K = R;
	k->array[0] = 1;
	k->array[1] = 3;
	k->array[2] = 7;
	k->array[3] = 12;
	k->size = n;
	struct mincoins m,m1,m2,r; 
	
	struct timespec s,e;
	
	//r = changeslow(A,K,n);
	
	//m = changedp(A,k);
	
	for(A = 1000; A <= 30000; A = A + 100)
	{
		clock_gettime(CLOCK_MONOTONIC,&s);
		//r = changedp(A,k);
		for(i = 1; i < A; i++)
					1+1;
			
		clock_gettime(CLOCK_MONOTONIC ,&e);
		
		diff = BILLION * (e.tv_sec - s.tv_sec) + e.tv_nsec - s.tv_nsec;
		
		printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
		
		
		fprintf(fp,"%llu, %d\n",diff,A);
		
	
	}
	fclose(fp);
	fp = fopen(fn2,"w+");
	/*
	for(A = 1; A < 100000; A = A + 1000)
	{
		clock_gettime(CLOCK_MONOTONIC,&s);
		r = changegreedy(A,k);
		clock_gettime(CLOCK_MONOTONIC ,&e);
		
		diff = BILLION * (e.tv_sec - s.tv_sec) + e.tv_nsec - s.tv_nsec;
		
		printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
		
		
		fprintf(fp,"%llu, %d\n",diff,A);
	}
	fclose(fp);
	fp = fopen(fn,"w+");
		for(A = 1; A < 20 ; A++)
	{
		clock_gettime(CLOCK_MONOTONIC,&s);
		r = changeslow(A,k);
		clock_gettime(CLOCK_MONOTONIC ,&e);
		
		diff = BILLION * (e.tv_sec - s.tv_sec) + e.tv_nsec - s.tv_nsec;
		
		printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
		
		
		fprintf(fp,"%llu, %d\n",diff,A);
	
	}
	
	
	fclose(fp);
	*/
	deleteArr(k);
	
	return 0;
}
