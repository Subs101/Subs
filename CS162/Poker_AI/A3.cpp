
#include <iostream>
#include "A3.h"

/*
*This is the main file provided.
*Uses the function game_choice to select the type of poker you want to play.
*depending on which is selected the poker pointer points to a new object of
*a sub class in poker. ( either StudPoker or go_drawPoker).
*/


using namespace std;
int main() {
	
	Poker *game;
	
	char game_choice;
	
	game_choice = choose_game();
	
	if(game_choice == 's')
		
		game = new StudPoker;
	
	else if(game_choice == 'd')
		
		game = new go_drawPoker;
	
	game->play();
	
	return 0;
} 