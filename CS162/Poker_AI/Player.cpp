#include "A3.h"

using namespace std;

Player::Player()
{
	
	Money = 200;
	
	Status = 1;
	
	Hand = new Card[5];
}



int Player::evaluateHand(){
	
            qsort( Hand , 5 , sizeof(Card),compareCards);
			
            int straight, flush, three, four, full, pairs;
			
            int k;

            straight = flush = three = four = full = pairs = 0;
			
            k = 0;

            /*checks for flush*/
			
            while (k < 4 && Hand[k].getSuit().value == Hand[k+1].getSuit().value)
                k++;
            if (k==4) 
				
                flush = 1;

				
            /* checks for straight*/
			
            k=0;
			
            while ( k < 4 && Hand[k].getFace().value == Hand[k+1].getFace().value - 1 )
				
                k++;
				
            if (k == 4)
				
                straight = 1;

            /* checks for fours */
            for ( int i = 0; i < 2; i++)
			{
                k = i;
				
                while (k < i + 3 && Hand[k].getFace().value == Hand[k+1].getFace().value)
					
                    k++;
					
                if (k == i + 3 )
					
                    four = 1;
            }

            /*checks for threes and full house*/
            if (!four)
			{
                for (int i=0;i<3;i++)
				{
                    k = i;
					
                    while (k<i+2&&Hand[k].getFace().value==Hand[k+1].getFace().value)
						
                        k++;
						
                    if (k==i+2)
					{
                        three = 1;
						
                        if (i==0)
						{
                            if (Hand[3].getFace().value==Hand[4].getFace().value)
								
                                full=1;
                        }
                        else if(i==1)
						{
                            if (Hand[0].getFace().value==Hand[4].getFace().value)
								
                                full=1;
                        }
                        else
						{
                            if (Hand[0].getFace().value==Hand[1].getFace().value)
								
                                full=1;
                        }
                    }
                }
            }

            if (straight&&flush)
				
                return 9;
				
            else if(four)
				
                return 8;
				
            else if(full)
				
                return 7;
				
            else if(flush)
				
                return 6;
				
            else if(straight)
				
                return 5;
				
            else if(three)
				
                return 4;

            /* checks for pairs*/
            for (k = 0; k < 4; k++)
				
                if (Hand[k].getFace().value == Hand[k+1].getFace().value)
					
                    pairs++;

            if (pairs == 2)
				
                return 3;
				
            else if(pairs)
				
                return 2;
				
            else
				
                return 1;
}


void Player::PrintHand(int round)
{
	
			
			for (int j = 0; j < round ; j++)
				
				cout<<this->Hand[j].print();
			
			
}


int Player::Bet(int bet)
{							// Player folds for this game
	if ( bet == 0)
	{
		Status = 0;
		return 0;
	}	

	if (bet < 0)
	{
		cout<<"Surely you meant to bet positive "<<(-bet)<<"."<<endl;
		
		Money = Money + bet;
		return (-bet);
		
		
	}
	
	Money = Money - bet;	
	return bet;
	
	
	
	
}
	




int Player::AIBet(int round)
{
	//initialize random betting for rounds 1 - 4
	
	int j = ((rand() + time(0) ) % 10 );
	int x, n;
	x = 50;
	if (round != 5)
	{
		if (j < 1)
		{
			Status = 0;
			return 0;
			
		}
		else if (j < 6)
		{
			Money = Money - x;
			return x;
			
		}
		else if (j <= 7)
		{
			Money = Money - 2*x;
			return 2*x;
		}
		else if (j == 8)
		{
			Money = Money - 4*x;
			return 4*x;
			
		}
		else if (j == 9)
		{
			Money = Money - 8*x;
			return 8*x;
			
		}
	}
	else
	{
		n = this -> evaluateHand();
		
		switch(n)
		{
			case 1: return 	50; 											//bet 50 on high card
			
			case 2: return ((((rand() + time(0) ) % 2 ) + 1 ) * x);			//bet 100 or 50 on pair
			
			case 3: return ((((rand() + time(0) ) % 2 ) + 1 ) * 2*x);		//bet 100 or 200 on 2 pair	
			
			case 4: return ((((rand() + time(0) ) % 2 ) + 1 ) * 8*x);		//bet 400 or 800 on trips
			
			case 5: return ((((rand() + time(0) ) % 2 ) + 1 ) * 8*x);		//bet 400 or 800 on straight
			
			case 6: return ((((rand() + time(0) ) % 2 ) + 1 ) * 10*x);		//bet 500 or 1000 on flush	
			
			case 7: return ((((rand() + time(0) ) % 2 ) + 1 ) * 12*x);		//bet 600 or 1200 on full house	
			
			case 8: return ((((rand() + time(0) ) % 2 ) + 1 ) * 50*x);		//bet 2500 or 5000 on quads	
			
			case 9: return (100*x);											//bet 5000 on straight flush
			
			default: return 1;
		}
		
		
		
	}		
	
	
}