#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "change_alg.h"

char* myStrcat( char* s1, char* s2)
{
	int i = 0;
	int j = 0;
	char* s3 = malloc(sizeof(char)*100);
	while( s1[i] != '\0' && s1[i] != '.')
	{
		
		s3[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while( s2[i] != '\0' && s2[i] != '.')
	{
		s3[j] = s2[i];
		i++;
		j++;
	}
	
	
	s3[j] = '.';
	s3[j+1] ='t';
	s3[j+2] = 'x';
	s3[j+3] = 't';
	s3[j+4] = '\0';
	
	return s3;
}

struct Arr* createArr(int cap)
{
	int i;
	struct Arr* A = malloc(sizeof(struct Arr));
	A->size = 0;
	A->cap = cap;
	A->array = malloc(sizeof(int)*cap);
	
	for(i = 0; i < cap; i++)
		A->array[i] = 0;
	
	return A;
}

void deleteArr(struct Arr* A)
{
	free(A->array);
	free(A);
}



void writeArray(FILE* filePtr, char* filename, struct Arr* A)
{
	int i;
	filePtr = fopen(filename,"a+");
	
	
	if (A->size > 1)
	{
		fprintf(filePtr, "[");
		
		for ( i = 0; i < A->size; i++)
		{	
		if ( i == A->size - 1)
			fprintf(filePtr, "%d",A->array[i] );
		else 
			fprintf(filePtr, "%d, ",A->array[i] );

		

		}
		fprintf(filePtr, "]\n");
	}
	else
		fprintf(filePtr, "%d\n",A->array[0]);
	
	fclose(filePtr);
}

void writeMinCoins(FILE* filePtr, char* filename, struct mincoins m,int size)
{
	int i;
	filePtr = fopen(filename,"a+");

	fprintf(filePtr, "[");
		
	for ( i = 0; i < size; i++)
	{	
		if ( i == size - 1)
			fprintf(filePtr, "%d",m.coins[i] );
		else 
			fprintf(filePtr, "%d, ",m.coins[i] );

		

	}
	fprintf(filePtr, "]\n");
	
	fprintf(filePtr, "%d\n",m.num );
	
	fclose(filePtr);
	
	
	
}



struct Arr* getArray(FILE *filePtr, char* filename, int lineNum)
{
  int j;
  struct Arr* A = createArr(100);
  char line[200];  /* Assume lines < 200 */
  
  filePtr = fopen(filename,"r");
  if (filePtr == NULL)
	return NULL;
  
  if (lineNum == 0)
	  return NULL;
  
  
  for(j = 0; j < lineNum; j++)
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
		A->array[i] = atoi(token);
		i++;
		  
	  }

      token = strtok(NULL, comma);

   }
   
   
   fclose(filePtr);
   
   A->size = i;
   
  
   
   return A;
   
   
}