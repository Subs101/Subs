#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "change_alg.h"

int min(int a, int b)
{
	return (a < b)? a : b;
	
}
	

		
struct mincoins changeslow(int A, struct Arr* K)
{
	int i,k,j;
	int T;
	struct mincoins m,m1,m2;
	
	for (k = 0; k < K->size ; k++)
		m.coins[k] = 0;
	
	if (A == 0)
	{
		m.num = 0;
		for (k = 0; k<K->size ; k++)
			m.coins[k] = 0;
		
		return m;
	}
	for(i = 0; i < K->size; i++)
	{
		if(K->array[i] == A)
		{
			m.num = 1;
			m.coins[i] += 1;
			return m;
		}
			
	}
	
	m.num = BIG_NUMBER;
	
	for(i = 1; i < A; i++)
	{
		m1 = changeslow(i,K);
		m2 = changeslow(A-i,K);
		
		T = m1.num + m2.num;
		if (T < m.num)
		{
			m.num = T;
			
			for(j = 0; j < K->size; j++)
			{
				m.coins[j] = m1.coins[j] + m2.coins[j];
			}
		}	
	}
	
	return m;	
}
	
	
	
	
	
	
struct mincoins changedp(int A, struct Arr* K)
{
	int* C = malloc(sizeof(int)*A);
	int* S = malloc(sizeof(int)*A);
	int p, i,j, minval,coin,idx;
	struct mincoins m;
	
	m.num = 0;
	
	for(j = 0; j < K->size; j++)
	{
		m.coins[j] = 0;
	}
	
	for(j = 0; j < A; j++ )
	{
		C[j] = S[j] = 0;
	}
	
	for(p =1; p <= A; p++)
	{
		minval = BIG_NUMBER;
		
		for(i =0; i < K->size; i++)
		{
			if (K->array[i] <= p)
			{
				idx = p - K->array[i];
				
				if(idx < 0)
					idx = 0;
				
				if( 1 + C[idx] < minval)
				{
					
					
					minval = 1 + C[idx];
					coin = i;
					
				}
				
				
			}
			
		}
		
		C[p] = minval;
		S[p] = coin;
		
		
	}
	
	
	int a = A;
    while (a > 0)
    {
	   m.coins[S[a]]++;
	   a = a - K->array[S[a]];
    }
	
	for(i = 0; i < K->size; i++)
		m.num += m.coins[i];
	
	free(C);
	free(S);
	
	return m;
	
}
	



/*precondition: Array K in sorted order*/
struct mincoins changegreedy(int A, struct Arr* K)
{
	int i;
	int change;
	struct mincoins m;
	m.num = 0;
	
	for (i = 0; i < K->size; i++)
		 m.coins[i] = 0;
	
	change = A;
		
	for(i = K->size - 1; i >= 0; i--)
	{
		
		if( change >= K->array[i]);
		{
			m.coins[i] = change / K->array[i];
			change = change - (change / K->array[i])*K->array[i];
			
		}
			
		
		
	}
	
	for (i = 0; i < K->size; i++)
		m.num += m.coins[i];
	
	
	
	return m;
}


