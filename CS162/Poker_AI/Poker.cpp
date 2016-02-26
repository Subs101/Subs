#include "A3.h"

using namespace std;

int Poker::OverallWinner(Player StudPlayer[])
{
	int max_money = 0;
	int winner = 0;
	
	for(int i = 0; i < numPlayers; i++)
	{
		if (StudPlayer[i].getMoney() > max_money)
		{
			max_money = StudPlayer[i].getMoney();
			winner = i+1;
		}
		
		
		
	}
	
	return winner;
	
	
	
}
int Poker::CheckWin(Player StudPlayer[])
{
	
	int win_type, win_player, a ,counter;
	bool type_tie = false;
	
	double sum = 0;
	double win_sum = 0;

	win_type = 0;
	
	
	
	for (int i = 0; i < numPlayers; i++)				//loop to figure out the highest hand of the round
	{
		if ( StudPlayer[i].getStatus() == 1)
		{
			a = StudPlayer[i].evaluateHand();
			if (a > win_type)
			{
				win_type = a;
			}
			
			
		}
	
	}
	counter = 0;
	for (int i = 0; i < numPlayers; i++)
	{
		if (StudPlayer[i].getStatus() == 1)
		{
			
			if (StudPlayer[i].evaluateHand() == win_type)
			{
				counter++;
				
				if (counter > 1)
				{
					type_tie = true;
				}
				else if (counter == 1)
				{
					win_player = i;
				}
			
			}
		
		}
		
	}
	
	if (type_tie == false)
	{
		
		return win_player;
		
		
	}
	
	//if 2 or more players have the same type of hand the sum of their hand will decide who wins
	// for 4 of a kind, straight , flush , full house, flush, straight. This isn't always true but 
	//this condition is most likely to be true.
	
	
	if (win_type >= 5)
	{
		for(int i = 0 ; i < numPlayers; i++)
		{
			if ( StudPlayer[i].getStatus() == 1)
			{
				sum = 0;
				
				if (StudPlayer[i].evaluateHand() == win_type)
				{
					for(int j = 0 ; j < 5; j++)
						sum = StudPlayer[i].getHand(j).getFace().value + sum;
					
					if(sum > win_sum)
					{
						win_sum = sum;
						win_player = i;
					}
				}
			}
		}
		
		return win_player;
	}
	//resolve triple ties: if the hand is ordered the 3rd card in the hand must be part of the triple.
	//direct comparison of this card will correct for ties.
	if (win_type == 4)
	{
		for(int i = 0 ; i < numPlayers; i++)
		{
			if ( StudPlayer[i].getStatus() == 1)
			{
				sum = 0;
				
				if (StudPlayer[i].evaluateHand() == win_type)
				{
					sum = StudPlayer[i].getHand(2).getFace().value; //3rd card
					
					if(sum > win_sum)
					{
						win_sum = sum;
						win_player = i;
					}
				}
			}
		}
		
		return win_player;
	}
	
	//resolve 2 pair ties
	// if cards are ordered by value then the 2nd and 4th cards of the hand must 
	//be a part of the first and 2nd pair. Therefore we should compare the sum of both 
	//of these cards to determine winner.
	if (win_type == 3)
	{
		for(int i = 0 ; i < numPlayers; i++)
		{
			if ( StudPlayer[i].getStatus() == 1)
			{
				sum = 0;
				
				if (StudPlayer[i].evaluateHand() == win_type)
				{
					// 2nd and 4th cards added together to see who has the highest 2 pair
					sum = StudPlayer[i].getHand(1).getFace().value + StudPlayer[i].getHand(3).getFace().value;
					
					if(sum > win_sum)
					{
						win_sum = sum;
						win_player = i;
					}
				}
			}
		}
		
		return win_player;
	}
	
	//resolve 1 pair ties
	//first find where the pair is located and compare the face value to the other competitors
	//if the value is equal move to suit to determine winner.
	
	
	if (win_type == 2)
	{
		for(int i = 0 ; i < numPlayers; i++)
		{
			if ( StudPlayer[i].getStatus() == 1)
			{
				sum = 0;
				
				if (StudPlayer[i].evaluateHand() == win_type)
				{
					
					for (int j = 0; j < 4; j++)
					{
						if (StudPlayer[i].getHand(j).getFace().value == StudPlayer[i].getHand(j+1).getFace().value)
							
							sum = StudPlayer[i].getHand(j).getFace().value;
							
							
					}
					
					if(sum > win_sum)
					{
						win_sum = sum;
						win_player = i;
					}
										
			
				}
				
				
			}
			
			
		}
		
		return win_player;
	}
	
	//resolve high card ties	
	
	if (win_type == 1)
	{
		for(int i = 0 ; i < numPlayers; i++)
		{
			if ( StudPlayer[i].getStatus() == 1)
			{
				sum = 0;
				
				if (StudPlayer[i].evaluateHand() == win_type)
				{
					
					for (int j = 0; j <= 4; j++)
					{
						
						if(StudPlayer[i].getHand(j).getFace().value > sum)
						{
							sum = StudPlayer[i].getHand(j).getFace().value + double(StudPlayer[i].getHand(j).getSuit().value) / 10;
							
						}	
					}
					
					if(sum > win_sum)
					{
						win_sum = sum;
						win_player = i;
					}
										
			
				}
				
				
			}
			
			
		}
		
		return win_player;
	}
	
	
	
	
	
	
	
}

bool Poker::CheckForfeit(Player StudPlayer[])
{
	int counter;
	counter = 0;
	
	//first check if only one player is in the game using the member Status
	
	// status = 1 ; still in game
	// status = 0 ; not playing
	
	for (int i = 0; i < numPlayers; i++)
	{
		
		counter = StudPlayer[i].getStatus() + counter;
		
	}
	
	if (counter == 1)
		return true;
	
	return false;
	
	
	
	
	
	
}


