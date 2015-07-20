#include "change_alg.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[])
{
	struct Arr* A ,*B;
	struct mincoins m;
	int n;
	int i;
	FILE* fp;
	char* fn = argv[1];
	char* fn1 = "change";
	

	char* s3 = myStrcat(fn,fn1);
	printf(" + %s\n",s3);
	i = 1;
	
	while (1)
	{
		A = getArray(fp,fn,i);
		B = getArray(fp,fn,i+1);	

		if(B == NULL || A == NULL)
			break;
		
		n = A->size;
		m = changegreedy(B->array[0],A);
		writeMinCoins(fp,s3,m,n);
		
		deleteArr(A);
		deleteArr(B);	
		i =  i + 2;
	}

	return 0;
}