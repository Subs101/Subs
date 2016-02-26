#include "A3.h"

using namespace std;
char choose_game()
{
	char game;
	cout<<endl<<endl;
	cout<<"=========================="<<endl;
	cout<<"|    Welcome to Poker    |"<<endl;
	cout<<"|                        |"<<endl;
	cout<<"| Author: Subhei Shaar   |"<<endl;
	cout<<"=========================="<<endl;
	
	
	cout<<"=========================="<<endl;
	cout<<"|   Choose game type     |"<<endl;
	cout<<"|                        |"<<endl;
	cout<<"| 1. 's' for Stud Poker  |"<<endl;
	cout<<"|                        |"<<endl;
	cout<<"| 2. 'd' for Draw Poker  |"<<endl;
	cout<<"|                        |"<<endl;
	cout<<"=========================="<<endl;
	
	cin>>game;
	
	return game;
	
}



string HandType(Player StudPlayer[], int winner)
{
	switch( StudPlayer[winner].evaluateHand() )
	{
		
		case 1: return ("with a high card...");
		
		case 2: return ("with a pair!");
		
		case 3: return ("with two pairs!");
		
		case 4:	return ("with trips!");
		
		case 5: return ("with a straight!");
		
		case 6: return ("with a flush!");
		
		case 7: return ("with a full house!");
		
		case 8: return ("with quads!");
		
		case 9: return ("with a straight flush!");
		
		default: return (" ");
		
	}
}

int compareCards(const void *card1, const void *card2){
	
    return ( *(Card *)card1).getFace().value - (*(Card *)card2).getFace().value;
}

