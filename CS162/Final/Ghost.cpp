#include "A4.h"
using namespace std;

Ghost::Ghost()
{
	
	symbol = 'G';
	
}

void Ghost::move(char c, Floor& Level)
{
	point temp;
	
	if (c == 'w')
	{
		temp.y = y - 1;
		temp.x = x;
		if (Level.getGrid(temp.y,temp.x) != '#' &&  Level.getGrid(temp.y,temp.x) != 'D')
			y--;
		
	}
	else if(c == 'a')
	{
		
		temp.y = y;
		temp.x = x - 1;
		if (Level.getGrid(temp.y,temp.x) != '#' &&  Level.getGrid(temp.y,temp.x) != 'D')
			x--;
	}
	else if (c == 's')
	{
		temp.y = y+1;
		temp.x = x ;
		if (Level.getGrid(temp.y,temp.x) != '#' &&  Level.getGrid(temp.y,temp.x) != 'D')
			y++;
	}
	else if(c == 'd')
	{
		temp.y = y;
		temp.x = x + 1;
		if (Level.getGrid(temp.y,temp.x) != '#' &&  Level.getGrid(temp.y,temp.x) != 'D')
			x++;
		
	}
	

	
	
	
}

/*
void Ghost::AImove(int Level, int frame)
{
	Floor a;
	// each level will have 10 frames that will loop
	if (Level == 0 )
	{
		if (frame <= 5)
		move('d',a);
	else
		move('a',a);
	}
	else if (Level == 1)
	{
		if (frame <=3)
			move('a');
		else if (frame == 4)
			move('s');
		else if (frame <=7)
			move('d');
		else if (frame == 10)
			move('w');
	}
	
	
	
	
}
*/

void Ghost::moveToPlayer(Player P1, int(&bestmoves)[5])
{
	int distance[5];// 4 moves + 1 base case 
	int w, a, s ,d, base;
	int array[5];
	
	//base case without moving
	distance[0] = pow(P1.getx() - x,2) + pow(P1.gety() - y,2);// base
	distance[1] = pow(P1.getx() - (x+1),2 )+ pow(P1.gety() - y,2); // d
	distance[2] = pow(P1.getx() - (x-1),2) + pow(P1.gety() - y,2); // a
	distance[3] = pow(P1.getx()  - x,2) + pow(P1.gety() - (y+1),2); // s
	distance[4] = pow(P1.getx() - x,2) + pow(P1.gety() - (y-1),2); // w
	// base d a s w
	for (int i = 0; i<5; i++)
	{
		array[i] = distance[i];
		
	}
	 sort(distance, distance + 5);
	for (int i = 0; i < 5 ; i++)
	{
		if ( array[i] ==  distance[0])
		{
			bestmoves[0] = i;
			
		}			
		else if (array[i] ==  distance[1] )
			bestmoves[1] = i;
		else if (array[i] ==  distance[2] )
			bestmoves[2] = i;
		else if (array[i] ==  distance[3] )
			bestmoves[3] = i;
		else if (array[i] ==  distance[4] )
			bestmoves[4] = i;
		
	}
	 
	

	
	
	
	
	
	
}

bool Ghost::chase(Player P1)
{
	float d;
	d = sqrt(pow(P1.getx() - x,2) + pow(P1.gety() - y,2));
	if (d <= 16)
		return true;
	
	return false;
	
	
}



void Ghost::locateGhost(Floor Level)
{
	
	for (int i = 0; i< 20; i++)
	{
		
		for (int j = 0; j < 30 ; j++)
		{
			if (Level.getGrid(i,j) == 'G')
			{
				
				y = i;
				x = j;
				
				
			}
			
		}
		
	}
	
	
	

}