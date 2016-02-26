using namespace std;
#ifndef MARKER
#define MARKER

#include <iostream>
#include <cstdlib>
#include <time.h>  
#include <unistd.h>
#include <string>



/**************************************************************
struct: cardStruct

Description:

	This structure holds two pieces of data that each card
has, the visual and the value. The visual is what is displayed
on the screen and looks like a standard playing card. The value
of the card is what is used in logical comparisons to determine 
the strength of the poker hand.

*Example:  The 2 of hearts data members.
			
			string visual = '2 ♥' 
			int value = 1

************************************************************/
struct cardStruct
{
	string visual;
	int value;

};

/**************************************************************
class: Card

Description:

	Card contains a face and a suit that both have visual and value
members. Card has a print function to output the visuals to the screen
of both the face and suit. The card objects significance is when it is
instantiated in the Deck class.
	

************************************************************/

class Card
{
	public:
	
		Card();
		Card(cardStruct,cardStruct);
		string print() const;
		
		cardStruct getFace(){return face;};
		cardStruct getSuit(){return suit;};
		
		void setFace(cardStruct f){face.visual = f.visual; face.value = f.value;};
		void setSuit(cardStruct s){ suit.visual = s.visual; suit.value = s.value;};
		
	private:
	
		cardStruct face;
		cardStruct suit;
		
};

/**************************************************************
class: Deck

Description:

	This is the deck class that is used in both stud poker and 
	draw poker games. It has a few basic functions that can be used
	in any card game. Shuffle uses a RNG swap the first card in the 
	deck with a card at a random position in the deck.
	
	dealCard will take the top card off of the deck and give it to a player.
	If the deck runs out of cards a new deck is automatically created and 
	shuffled.
	
	Deck has-a Card

************************************************************/

class Deck
{
	private:
	
		Card *deck;
		int currentCard;
	
	
	public:
	
		static const int CARDS_PER_DECK = 52;

		Deck();
	
		void shuffle();
		Card dealCard();
		void printDeck() const;
		

};
/**************************************************************
class: Player

Description:

	Each player in a Poker game has money, a hand of 5 cards and a status.
	
	The money is what a player uses to bet. Negative money is allowed in 
	these games because that was part of the assignment description.
	
	The hand points an array of up to 5 cards.
	
	The status of a player is either true or false, false means the player
	has folded and can't participate for the rest of the round.

	
************************************************************/

class Player
{
	private:
		
		int Money;
		Card *Hand;
		bool Status;
		
		
	public:
	
		Player();
		
		int Bet(int);
		int AIBet(int);
		
		void PrintHand(int);
		int evaluateHand();
	
		
		Card getHand(int h) {return Hand[h];}
		bool getStatus() {return Status;}
		int  getMoney() {return Money;}
		
		
		void setHand(int h, Card c){Hand[h] = c;}
		void setMoney(int m) {Money = m;};
		void setStatus(bool s) { Status = s;}
		
		
	
	
};

/**************************************************************
class: Poker

Description: 

Poker is the base class for the specific poker games. It holds the 
protected members of needed for both poker games such as number of
rounds, number of players, and number of games.

It also has access to a deck and a pot. The pot holds the sum of the 
players bets for a given round then transfers to the winning players 
money when the round is over.

It also holds functions to see if a player has won the round and game
since winning has the same conditions for both poker types.

Poker has-a Deck
Poker has-a Player

	

	
************************************************************/



class Poker
{
	protected:
	
		int numRounds;
		int numPlayers;
		int numGames;
		
		Deck deck1;
		int Pot;
		
		
	public:
	
		virtual void play() = 0;
		virtual bool PlayRound(Player[], int) = 0;
		
		
		virtual void set_numPlayers(int n) = 0;
		virtual void dealRound(Player[], int) = 0;
		

		bool CheckForfeit(Player[]);
		int CheckWin(Player[]);
		int OverallWinner(Player[]);
		
		
};

/*********************************************************************
class: StudPoker

Description: 

	This poker game allows players from 1 to 1000. It is a derived class
from Poker and overrides the virtual functions of Poker to follow the 
rules of StudPoker. Players are given 1 card each round for 5 rounds
and must bet each round. At the end of the 5 rounds whoever has the 
highest hand wins the pot. Repeat for n games.

**********************************************************************/





class StudPoker: public Poker
{
	public:
		
		void play();
		bool PlayRound(Player[], int);
		void set_numPlayers(int n){ numPlayers = n; };
		void dealRound(Player[] ,int);
		

};



/*********************************************************************
class: go_drawPoker

Description: 

	Basically same thing as StudPoker except now you only have 2 rounds 
	and you get 5 cards the first round. You have an option to swap up to 4
	cards after the first betting round. At the end of the 2nd round the 
	winner is determined.

**********************************************************************/

class go_drawPoker: public Poker
{
	
	public:
		
		void play();
		bool PlayRound(Player[], int);
	
		void set_numPlayers(int n){ numPlayers = n; };
		void dealRound(Player[],int);
		void exchangeCards(Player[]);
	
};



char choose_game();

string HandType(Player StudPlayer[], int winner);

int compareCards(const void *card1, const void *card2);

#endif