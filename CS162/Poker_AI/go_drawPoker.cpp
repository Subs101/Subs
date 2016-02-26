#include "A3.h"

using namespace std;

void go_drawPoker::play()
{
	int eval, n, round, winner, overallwinner;
	bool w;
	string winning_hand;
	
	cout<<"Number of players?:"<<endl;
	cin>> n;
	numPlayers = n;
	
	numRounds = 2;
	
	
	cout<<"Number of Games?:";
	cin>>n;
	
	numGames = n;
	
	
	Player StudPlayer[numPlayers];
	
	
	
	for (int games = 0; games < numGames ; games++)
	{
		usleep(600000);
		
		cout<<"===========New Game============\n";
		for (int i = 0 ;i < numPlayers; i++ )
		{
			cout<<"Player "<<i+1<<" money = "<<StudPlayer[i].getMoney()<<endl;
			
		}
		cout<<"================================\n";
		
		usleep(600000);
		
		Pot = 0;
		
		
		
		for(int i = 0; i < numPlayers; i++)
			
			StudPlayer[i].setStatus(true);
		
		
		w = false;
		
		deck1.shuffle();
		
		
		for (int i = 1; i <= numRounds ; i++)
		{
			
		w = PlayRound(StudPlayer,i);
		
		if (w == true)						//someone won, no more rounds needed
		
			break;
		
		}
		
		//reveal cards to everyone
		
		for (int i = 0; i < numPlayers; i++)
		{
			cout<<"Player "<<i+1<<": ";
			
			StudPlayer[i].PrintHand(5);

			
			cout<<endl;
			
		}
		
		
		
		winner = CheckWin(StudPlayer);
		
		winning_hand = HandType(StudPlayer,winner);
		usleep(500000);
		
		cout<<"Pot = "<<Pot<<endl<<endl;
		
		if (w == false)
		cout<<"Player "<<winner + 1<<" wins "<<winning_hand<<endl<<endl;
		else
		cout<<"Player "<<winner + 1<<" wins by being the last man standing."<<endl<<endl;

	
		StudPlayer[winner].setMoney(Pot + StudPlayer[winner].getMoney() );//payout each game
		
	}
	
	overallwinner = OverallWinner(StudPlayer);
	
	usleep(500000);
	
	cout<<endl;
	cout<<"Player "<<overallwinner<<" is the overall winner with "<<StudPlayer[overallwinner - 1].getMoney()<<" points.";
	cout<<endl<<endl;
	
	
	
	
	
	
	
	
}

void go_drawPoker::exchangeCards(Player StudPlayer[])
{
	int numReplace, x, a, b, c, d;
	
	
	for (int i = 0 ; i < numPlayers ; i++)
	{
		if ( StudPlayer[i].getStatus() == true)
		{
			cout<<"Player "<<i + 1<<":"<<endl;
			
			
			
			if ( i == 0)
			{
				cout<<"How many cards do you want replaced (max of 4)?: ";
				cin>>numReplace;
				cout<<endl;
				
			
			}
			else
			{
				numReplace = (rand() + time(0)+ i) % 5;
				
				cout<<"-> replaced "<<numReplace<<" card(s).";
				usleep(900000);
				cout<<endl;
				
			}
			
			
			if (numReplace > 0 && i == 0)	
			cout<<"Enter in positions of up to 4 cards you want replaced: <1 - 5>: ";
			
			
			
			for(int j = 0; j < numReplace ;j++)
			{
				
				if (i == 0)
				{
					cin>> x;
					StudPlayer[i].setHand(x - 1 , deck1.dealCard());
				}
				else
				{
					
					numReplace = (rand() + time(0)+ j) % 5;
					StudPlayer[i].setHand(x - 1 , deck1.dealCard());
					
				}
				
			}
			cout<<endl;
		}
	}
	
	
}



bool go_drawPoker::PlayRound(Player StudPlayer[], int round)
{
	int b;
	bool w;
	
	if (round == 1)
		dealRound(StudPlayer, round);
	else 
	{
		
		
		exchangeCards(StudPlayer);
	
		
	}
		
	
	
	
	cout<<"Round: "<<round<<endl<<endl;
	usleep(900000);
	
	//print player 1's hand out each round

		if (StudPlayer[0].getStatus() == 1)
		{
				cout<<"Player 1: ";
				StudPlayer[0].PrintHand(5);
				cout<<endl;
			
		}
	
	
	cout<<endl;
	
	usleep(900000);
	//start betting
	
	for (int i = 0; i < numPlayers; i ++)
	{
		if (StudPlayer[i].getStatus() == 1)
		{
			if(i == 0)
			{
				cout<<"Player "<<i + 1<<" turn to bet."<<endl;
				cin>>b;
				Pot = Pot + StudPlayer[i].Bet(b);
			}
			else
			{
				int var;
				
				cout<<"Player "<<i + 1<<" turn to bet."<<endl;
				var = StudPlayer[i].AIBet(round);
				Pot = Pot + var;
				
				usleep(500000);
				cout<<"-> bet "<<var<<endl<<endl;
				
			}
			
			
		}
	
		//if only one player is still alive they win and get the pot.
		
			w = CheckForfeit(StudPlayer);
		
			if( w == true )						// someone won this round
				return true;
			
	
	}
	
	
	usleep(900000);
	//print out current pot
	cout<<"Current Pot:"<<Pot<<endl<<endl;
	
	return false;
	
	
	
}
	
	

void go_drawPoker::dealRound(Player StudPlayer[],int round)
{
	// deal 5 cards to each player the first round 
	
	for (int i = 0; i < numPlayers; i++)
	{
		if (StudPlayer[i].getStatus() == 1)
			
			for(int j = 0; j < 5; j++)
			StudPlayer[i].setHand(j, deck1.dealCard());
		
		
	}
	
	
	
	
}