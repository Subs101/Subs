#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#ifndef max
	#define maxfun( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
struct Idx
{
	int s;
	int e;
};

int* getArray(FILE *filePtr, int* size )
{
  
  int Array[50];
  char line[200];  /* Assume lines < 100 */
  fgets(line, sizeof(line), filePtr) ;
  
  if (line[0] == '\r' || line[0] == '\n')
  {
	 
	  return NULL;
	 
  }
 
 
   const char comma[2] = ",";
   const char Lbracket[2] = "[";
   const char Rbracket[2] = "]";
   const char space[2] = " ";
   char *token;
   
 
   token = strtok(line,Rbracket);
   token = strtok(token,Lbracket);
   token = strtok(token,comma);
   

 
   /* walk through other tokens */
   int i = 0;
   while( token != NULL) 
   {
      
	  
	  if(token != NULL) 
	  {
		Array[i] = atoi(token);
		i++;
		  
	  }

      token = strtok(NULL, comma);

   }
   
   *size = i;
   int* A = malloc(sizeof(int)*(i+1))
   ;
	for(int j = 0; j < i; j++)
		A[j] = Array[j];
   
   return A;
   
}



int MAXSUBARRAY_BestEnum(int* A, int size)
{
	int sum, max;
	max = sum = 0;
	
	if (size == 1)
		return A[0];
	
		for(int i = 0; i < size; i++)
		{
			for(int j = i; j < size; j++)
			{
				sum += A[j];
				
				if (sum > max)
					max = sum;
			}
			
			sum = 0;	
			
		}
		
	return max;
}


int MAXSUBARRAY_Enum(int* A, int size)
{
	int sum, max;
	max = sum = 0;
	
	if (size == 1)
		return A[0];
	
	for(int i = 0; i < size; i++ )
	{
		for(int j = 0; j < size; j++)
		{
			for(int k = i; k <= j; k++)
				sum += A[k];
		
			if (sum > max)
				max = sum;
			
			sum = 0;	
			
		}
		
	}
		
	return max;
}

int MAXSUBARRAY_Div(int* A, int low, int high)
{
	int mid, sum, maxLeft, maxRight,max;
	mid = (low + high)/2;
	
	if (low > high)
		return 0;
	if (high == low)
		return A[low];
	//short circuit single element
	
	//max on left side
     maxLeft = sum = 0;
	 
     for (int i = mid; i >= low; i--) {
        sum += A[i];
		
        if (sum > maxLeft)
            maxLeft = sum;
     }
    
     //max on right side
     maxRight = sum = 0;
     for (int i = mid+1; i <= high; i++) {
        sum += A[i];
        if (sum > maxRight)
            maxRight = sum;
     }
	max = maxRight+maxLeft;
	
	return maxfun(max, maxfun(MAXSUBARRAY_Div(A,low, mid),MAXSUBARRAY_Div(A,mid+1,high))) ;
	 
	
	
}

int MAXSUBARRAY_Linear(int* A,int size)
{
	int max, temp_max;
	max = temp_max = 0;
	
	if(size == 1)
		return A[0];
	
	for(int i = 0; i < size; i++)
	{
		temp_max = maxfun(temp_max + A[i], 0);
		max = maxfun(temp_max, max);
		
	}
	
	return max;
	
	
}

struct Idx MAXSUBARRAY_Linear_A(int* A,int size)
{
	int maxSum, curSum, curStartIdx, maxStartIdx, maxEndIdx, curEndIdx;
	maxSum = curSum = maxStartIdx = maxEndIdx = 0;
	struct Idx I;
	curStartIdx = 0;
	for (curEndIdx = 0; curEndIdx < size; curEndIdx++ )
	{
		curSum += A[curEndIdx];
		
		if(curSum > maxSum)
		{
			maxSum = curSum;
			maxStartIdx = curStartIdx;
			maxEndIdx = curEndIdx;
		}
		else if (curSum < 0)
		{
			curSum = 0;
			curStartIdx = curEndIdx + 1;
		}
	}
	
	
	I.e = maxEndIdx;
	I.s = maxStartIdx;
	return I;
	
}

void timeTest_BestEnum(int size)
{
	int A[size];
	int w;
	clock_t start, end;
	float seconds;
	
	for(int i = 0; i< size; i++)
	{
		if (rand()%100 > 50)
			A[i] = rand() % 100;
		else 
			A[i] = (rand()% 100)*-1;
		
	}
	start = clock();
	w = MAXSUBARRAY_BestEnum(A,size);
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("BestEnum: size: %d Time: %0.2f sec\n",size,seconds);
	
}

timeTest_Enum(int size)
{
	int A[size];
	int w;
	clock_t start, end;
	float seconds;
	
	for(int i = 0; i< size; i++)
	{
		if (rand()%100 > 50)
			A[i] = rand() % 100;
		else 
			A[i] = (rand()% 100)*-1;
		
	}
	start = clock();
	w = MAXSUBARRAY_Enum(A,size);
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("Enum: size: %d Time: %0.2f sec\n",size,seconds);
	
	
}
timeTest_Linear(int size)
{
	int A[size];
	int w;
	clock_t start, end;
	float seconds;
	
	for(int i = 0; i< size; i++)
	{
		if (rand()%100 > 50)
			A[i] = rand() % 100;
		else 
			A[i] = (rand()% 100)*-1;
		
	}
	start = clock();
	w = MAXSUBARRAY_Linear(A,size);
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("Linear: size: %d Time: %0.2f sec\n",size,seconds);
	
	
}

timeTest_Div(int size)
{
	int A[size];
	int w;
	clock_t start, end;
	float seconds;
	
	for(int i = 0; i< size; i++)
	{
		if (rand()%100 > 50)
			A[i] = rand() % 100;
		else 
			A[i] = (rand()% 100)*-1;
		
	}
	start = clock();
	w = MAXSUBARRAY_Div(A,0,size-1);
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("Div: size: %d Time: %0.2f sec\n",size,seconds);
	
	
}
void timeAnalysis()
{
	for (int i = 100; i <=200000; i = i *3)
		timeTest_Div(i);
	
	for (int i = 100; i <=200000; i = i * 3)
		timeTest_BestEnum(i);
	
	for (int i = 100; i <= 1000000; i = i *3)
		timeTest_Linear(i);
	
	for (int i = 100; i <=200000; i = i *3)
		timeTest_Enum(i);
	
	

	//w = MAXSUBARRAY_BestEnum(A,100);
	
	//w = MAXSUBARRAY_BestEnum(B,1000);
	
	//w = MAXSUBARRAY_BestEnum(C,10000);
	
	

	
	
	//x = MAXSUBARRAY_Enum(A,100);
	//y = MAXSUBARRAY_Div(C,0,100-1);
	//z = MAXSUBARRAY_Linear(C,100);
	
	
}

int main()
{
	FILE* filePointer2;
	char* filename2 = "MSS_Results.txt";
	int w,x,y,z,size;
	int* sizes;
	struct Idx I;
	int k;
	size = 10;
	int* C;
	int* A = malloc(sizeof(int)*size);
	int B[] = {31,-41,59,26,-53,58,97,-93,-23,84};
	A = B;
	
	FILE* filePointer;
	
	
	char* filename = "MSS_Problems.txt";
	
	
	filePointer = fopen(filename, "r");
	if( filePointer == NULL ) 
	{
		fprintf(stderr, "Unable to open %s\n", filename);
			
	}
	filePointer2= fopen(filename2, "w+");
			

	//Part 1: Generating answers to MSS_Problems.txt in an output file 
	// MSS_Results.txt
	
	while(1)
	{
		C = getArray(filePointer, sizes);
		
		if (C == NULL)
			break;
		
		I = MAXSUBARRAY_Linear_A(C,*sizes); //output: start and end index of max subarray
		printf("%d %d \n",I.s,I.e);
		w = MAXSUBARRAY_BestEnum(C,*sizes);	
		x = MAXSUBARRAY_Enum(C,*sizes);
		y = MAXSUBARRAY_Div(C,0,*sizes - 1);
		z = MAXSUBARRAY_Linear(C,*sizes);
	
		
		fprintf(filePointer2, "[");
		for(k = I.s; k <= I.e; k++)
		{
			if ( k == I.e)
				fprintf(filePointer2, "%d",C[k] );
			else 
				fprintf(filePointer2, "%d, ",C[k] );
		}

		fprintf(filePointer2, "]\n");
		fprintf(filePointer2, "Sum: %d\n\n",x);
		
		
	
		printf("Best Enum %d\nEnum %d\nDiv %d\nLinear %d\n\n",w,x,y,z);
	}

	
	
	fclose(filePointer);
	fclose(filePointer2);
	
	
	timeAnalysis();
	
	
	
	return 0;
}