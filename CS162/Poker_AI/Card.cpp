#include "A3.h"


using namespace std;





/*
*Card constructor to set visual and value for face and suit of a card
*/

Card::Card(cardStruct cardface, cardStruct cardsuit)
{
	
	face.visual = cardface.visual;
	suit.visual = cardsuit.visual;
	
	face.value = cardface.value;
	suit.value = cardsuit.value;
	
}

/*
*Pretty print function to display output
*/

string Card::print() const
{
	return (face.visual + " " + suit.visual + "  ");
	
}

/*
*Default constructor
*/
Card::Card()
{
	
}