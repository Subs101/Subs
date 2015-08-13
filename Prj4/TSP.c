#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "Arr.h"

/********************************************
Author: Subhei Shaar
Date: 8/13/2015

Description:

Solution to the travelling salesman problem by
doing running the best nearest neighbor approach
or random seed for start vertex if input is too
large. 
Input: text file with 3 columns: City ID,
	   X pos (int), Y pos (int).
	   
Output: .tour file with 1 column displaying
		total distance and city order.

********************************************/

double euclidDist(int,int,int,int);
double addRoundTrip(struct Arr2D* tour);

void clearOrder(struct Arr2D* tour)
{
	int i;
	for(i =0; i<tour->size[CITY];i++)
		tour->array[ORDER][i] = -1;
}

int visitedAll(struct Arr2D* tour)
{
	int i;
	for(i = 0; i < tour->size[CITY]; i++)
	{
		if (tour->array[ORDER][i] == -1)
		{
			return -1;
		}
		
	}
	
	return 0;
	
}

double nearestNeighbor(struct Arr2D* tour,int seed)
{
	int x1,x2,y1,y2,i;
	int a = 0;
	int temp;
	int order_index = 0;
	double distAB = 0.0f;
	double minDistAB;
	double totalDist = 0;
	
	
	clearOrder(tour);
	a = seed;
	tour->array[ORDER][a] = order_index;
	order_index++;
	
	
	while(visitedAll(tour) == -1)
	{
		distAB = BIG_NUM;
		minDistAB = BIG_NUM;
		
		
		
		for (i = 0; i< tour->size[CITY]; i++)
		{	
			if(tour->array[ORDER][i] == -1)
			{
				x1 = tour->array[X][a];
				x2 = tour->array[X][i];
				
				y1 = tour->array[Y][a];
				y2 = tour->array[Y][i];
			
				distAB = euclidDist(x1,x2,y1,y2);
		
				if(distAB < minDistAB)
				{
					minDistAB = distAB;
					
					temp = i;
				}
			}
			else{
				
			}
	
		}
		totalDist += minDistAB;
		tour->array[ORDER][temp] = order_index;
		
		a = temp;
		temp = -1;
		
		order_index++;
		
		
		
	}
	
	//add an edge from last visited to start point
	totalDist+= addRoundTrip(tour);
	
	
	
	return totalDist;
	
}


	
int RepNearestNeighbor(struct Arr2D* tour)
{
	int x1,x2,y1,y2,i,j;
	int seed;
	int a = 0;
	int temp;
	
	int order_index = 0;
	
	double distAB = BIG_NUM;
	double minDistAB = BIG_NUM;
	double totalDist = BIG_NUM;
	double minTotalDist = BIG_NUM;

	
	
	for(j = 0; j < tour->size[CITY];j++)
	{
		a = j;
		order_index = 0;
		totalDist = 0;
		clearOrder(tour);
	
		tour->array[ORDER][a] = order_index;
		order_index++;
	
		while(visitedAll(tour) == -1)
		{
			distAB = BIG_NUM;
			minDistAB = BIG_NUM;
		
			for (i = 0; i< tour->size[CITY]; i++)
			{	
				if(tour->array[ORDER][i] == -1 && i != a)
				{
					x1 = tour->array[X][a];
					x2 = tour->array[X][i];
				
					y1 = tour->array[Y][a];
					y2 = tour->array[Y][i];
			
					distAB = euclidDist(x1,x2,y1,y2);
		
					if(distAB < minDistAB)
					{
						
						minDistAB = distAB;
						
						temp = i;
					}
				}
				else{
				
					}
	
			}
			
			totalDist += minDistAB;
			tour->array[ORDER][temp] = order_index;
			a = temp;
		
			order_index++;
			

		}
	
		//add an edge from last visited to start point
		totalDist+=addRoundTrip(tour);
	
	
		
		if( totalDist < minTotalDist)
		{
			minTotalDist = totalDist;
			seed = j;
			
		}
	
	}
	
	
	
	
	return seed;
	
}

double addRoundTrip(struct Arr2D* tour)
{
	int i,x1,x2,y1,y2;
	for (i = 0; i < tour->size[CITY];i++)
	{
		if (tour->array[ORDER][i] == 0)
		{
			x1 = tour->array[X][i];	
			y1 = tour->array[Y][i];
		
		}
		if (tour->array[ORDER][i] == tour->size[CITY] - 1  )
		{
			x2 = tour->array[X][i];
			y2 = tour->array[Y][i];
		}
	}
	
	return euclidDist(x1,x2,y1,y2);
	
}
	

double euclidDist(int x1,int x2,int y1,int y2)
{
    
 
    double xd = x1 - x2;
    double yd = y1 - y2;
	
    double d = (xd*xd + yd*yd);  
	
	d = sqrt(d);
	
    double d_i = round(d);

    return d_i;
}


int getCityXY(FILE* filePtr, char* filename, struct Arr2D* A)
{
  int i, j;
  char line[BUFFER];  /* Assume lines < 200 */
  
  /*get line of choice*/
  
  filePtr = fopen(filename,"r");
  if (filePtr == NULL)
	return -1;
  

 while (fgets(line, sizeof line, filePtr) != NULL)
 {
   // process buffer
   char *token;
  
  token = strtok(line," ");
  
  A->array[CITY][A->size[CITY]] = atoi(token);
  A->size[CITY]++;
  
  
  token = strtok(NULL," ");
  A->array[X][A->size[X]] = atoi(token);
  A->size[X]++;
  
  token = strtok(NULL," ");
  A->array[Y][A->size[Y]] = atoi(token);
  A->size[Y]++;

  
   
 }
 if (feof(filePtr))
 {
	 return -1;
   // hit end of file
 }
 
  
  

  return 0;
	
}

outPutFile(FILE* fp,char* filename,struct Arr2D* A,double totalDist)
{
	int i,j;
	fp = fopen(filename,"w+");
	
	fprintf(fp,"%0.0f\n",totalDist);
	j = 0;
	i = 0;
	while( i < A->size[CITY])
	{
		if(A->array[ORDER][j] == i)
		{
			fprintf(fp,"%d\n",A->array[CITY][j]);
			i++;
		}
		if( j < A->size[CITY])
		{
			j++;
		}
		else{
			j = 0;
		}
		
	}
	
	fclose(fp);
	
	
}

int main(int argc,char* argv[])
{
	int k;
	clock_t start, end;
	float seconds = 0;
	int r;
	double minDist = BIG_NUM;
	double totalDist;
	int i,seed,storeSeed;
	char* x;
	struct Arr2D* Array = create2DArr(4,40000);
	
	//1 = city//2 = x // 3 = y// 4 = order
	FILE* fp;
	
	
	getCityXY(fp,argv[1],Array);
	
	for(i = 0; i < Array->size[CITY]; i++)
	{
		Array->array[ORDER][i] = -1;
	}
	
	
	
	if (Array->size[CITY] > 1000)
	{
			printf("MAX SOLVE TIME = %d Seconds\n",SOLVE_TIME);
	
		do{
			start = clock();
		
	
			seed = (rand())%(Array->size[CITY]);
		

			totalDist = nearestNeighbor(Array,seed);
			if(totalDist < minDist)
			{
				storeSeed = seed;
				minDist = totalDist;
			}
		
	
			end = clock();
	
			seconds += (float)(end - start) / CLOCKS_PER_SEC;
		
		
		}while(seconds <= SOLVE_TIME);
	
		
	}
	else
	{
		storeSeed = RepNearestNeighbor(Array);
		
	}
	
	minDist = nearestNeighbor(Array,storeSeed);
	
	
	
	x = strcat(argv[1],".tour");
	outPutFile(fp,x,Array,minDist);
	
	
	delete2DArr(Array);
	
	printf("Success!\n");
	
	return 0;
}
