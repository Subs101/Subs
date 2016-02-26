#include "A4.h"
using namespace std;

Player::Player()
{
	x = 0;
	y = 15;
	lvl = 0;
	key_counter = 0;
	inv_counter = 0;
	
	//starting location
	
	symbol = 'P';
	
}

void Player::move(char c, Floor& Level)
{
	
	
	if (c == 'w')
	{
		y--;
	}
	else if(c == 'a')
	{
		x--;
	}
	else if (c == 's')
	{
		y++;
	}
	else if(c == 'd')
	{
		x++;
	}
	
	if (inv_counter > 0 )
	{
		inv_counter--;
	}
	
	for (int i = (y - 2); i <= (y + 2) ; i++)
	{
		for (int j = (x-4); j <= (x + 4); j++)
		{
			if ( i >= 0 && i <= 19 && j >= 0 && j<= 29)
			{
				Level.setVis(j,i,2);
				
			}
			
			
			
		}
		
		
		
	}
	
	
	
	
}

