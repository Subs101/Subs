#include "A3.h"
using namespace std;


/*
Function: Shuffle 

Description:

function sets the current card to be the top of the deck
then randomly generates a position and swaps each card in the deck
with a randomly placed card.


*/


void Deck::shuffle()
{
	currentCard = 0;
	
	for ( int i = 0; i < CARDS_PER_DECK; i++)
	{
		
		int j = (rand() + time(0) ) % CARDS_PER_DECK; 		// pick a random card from the deck
		
		Card temp = deck[ i ];								//hold the current card in for loop
		
		deck [i] = deck [ j ];								// swap random card with the first
		
		deck [j] = temp;
		
		
	}
	
	
}


/*
Function: printDeck 

Description:

Go through all the cards in the deck and print them all out.
Not used in the Poker games but useful to test the deck class.


*/

void Deck::printDeck() const
{
	
	for (int i = 0; i < CARDS_PER_DECK; i++)
	{
		cout<<deck[i].print();
		
		if ((i + 1) % 4 == 0)
			
			cout<<endl;
	
	}
	
}

/*
Function: Deck

Description:

Default constructor for the deck that defines the visuals and values 
of the cards in the deck. Then it goes and makes an array of cards and 
fills them in order by suits. After the constructor is done you are left
with a deck of cards that are ordered.

*/



Deck::Deck()
{
	
	cardStruct faces[13]; 
	cardStruct suits[4];
	
	string face[] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
	string suit[] = {"♣","♠","♦","♥"};
	
	for (int i = 0; i < 13; i++)
	{
		faces[i].visual = face[i];
		faces[i].value = i+1;
	}
	
	for (int i = 0; i < 4; i++)
	{
		suits[i].visual = suit[i];
		suits[i].value = i+1;
	}
	
	deck = new Card[CARDS_PER_DECK];
	currentCard = 0;
	
	for ( int i = 0; i < CARDS_PER_DECK ; i++)
		deck[i] = Card(faces[ i % 13] , suits [ i / 13]);
	
	

}

/*
Function: dealCard

Description:

This functions draws a card from the top of the deck (currentCard) and
gives it to a player. The player is specified outside of the function.
This function just returns the top of the deck and if no card are left 
in the deck it reshuffles itself.

*/

Card Deck::dealCard()
{
	
	if (currentCard < CARDS_PER_DECK)
		return (deck[currentCard++]);			// return card and increment deck
	
	
	this->shuffle();
	currentCard = 0;							//shuffle and start from beginning when you run out of cards
	return deck[currentCard++];
	
	
}
