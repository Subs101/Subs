#include "A4.h"

Floor::Floor()
{
	

}

void Floor::findLadders()
{
	
	
		for (int i = 0; i< 20; i++)
	{
		
		for (int j = 0; j < 30 ; j++)
		{
			if (grid[i][j] == 'A')
			{
				
				ladderA.y = i;
				ladderA.x = j;
				
			}
			else if (grid[i][j] == 'B')
			{
				
				ladderB.y = i;
				ladderB.x = j;
				
			}
			
		}
		
	}
	
	
	
	
}
void Floor::findEntrance()
{

		for (int i = 0; i< 20; i++)
	{
		
		for (int j = 0; j < 30 ; j++)
		{
			if (grid[i][j] == 'E')
			{
				
				entrance.y = i;
				entrance.x = j;
				
			}

		}
		
	}

}
void Floor::findExit()
{

		for (int i = 0; i< 20; i++)
	{
		
		for (int j = 0; j < 30 ; j++)
		{
			if (grid[i][j] == 'X')
			{
				
				exit.y = i;
				exit.x = j;
				
			}

		}
		
	}

}



/*
void Floor::Print()
{
	
	for (int i = 0; i< 20; i++)
	{
		
		for (int j = 0; j < 30 ; j++)
		{
			
			cout<<grid[i][j];
			
			
		}
		cout<<endl;
	}
	
	
}
*/
void Floor::Print()
{
	
	for (int i = 0; i< 20; i++)
	{
		
		for (int j = 0; j < 30 ; j++)
		{
			if (visibility[i][j] == 2)
			{
				cout<<grid[i][j];
			}
			else 
			{
				cout<<" ";
			}
			
			
		}
		cout<<endl;
	}
	
	
}

