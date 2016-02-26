#include "A4.h"

using namespace std;
int getch()
{
int ch;
struct termios oldt;
struct termios newt;
tcgetattr(STDIN_FILENO, &oldt); /*store old settings */
newt = oldt; /* copy old settings to new settings */
newt.c_lflag &= ~(ICANON | ECHO); /* make one change to old settings in new settings */
tcsetattr(STDIN_FILENO, TCSANOW, &newt); /*apply the new settings immediatly */
ch = getchar(); /* standard getchar call */
tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /*reapply the old settings */
return ch; /*return received char */
}

void Game::mapFloor(int lvl)
{
	ifstream readfile;
	char c;
	
	
	switch(lvl)
	{
		case 0: readfile.open("FloorA.txt"); break;
		case 1: readfile.open("FloorB.txt"); break;
		case 2: readfile.open("FloorC.txt"); break;
	}
	

	for (int i = 0; i< 20; i++)
	{
		
		for (int j = 0; j < 30 ; j++)
		{
			readfile.get(c);
			Level[lvl].setGrid(i,j,c);
			
		}
		
	}
	
}


void Game::play()
{
	char c;
	int walldoor = 0;
	int ai_step = 0;
	int bestmoves[5];
	int count;
	int switchvar;
	bool ghost_turn = false;
	bool win = false;
	
	for (int i = 0; i < 3 ; i++)
	{
		mapFloor(i);
		Level[i].findLadders();
		
		
		
	}
	
	Level[0].findEntrance();
	Level[2].findExit();
	npc.locateGhost(Level[0]); // set ghost position at lvl 1
	
	
	
	while(win == false)
	{
		
		
		
		walldoor = 0;
		
		
		
		// first check if the move is valid wall or door
		while(walldoor == 0)
		{
			c = getch();
			walldoor = checkMove(c);
		
		}
		// the move was valid so move the character and ghost
		
		
	
		
		switch(walldoor)
		{
			case 1:
			{
				P1.setkey(P1.getkey() - 1 );  
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), ' ');
				P1.move(c,Level[P1.getlvl()]);
				
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), P1.getsym());
				Level[P1.getlvl()].Print();
				
				break;
			}			
			case 2: 
			{
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), ' ');
				P1.move(c, Level[P1.getlvl()]);
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), P1.getsym());
				Level[P1.getlvl()].Print();
				
				//after displaying the player on top of the ladder reset the ladder A 
				Level[P1.getlvl()].setGrid(Level[P1.getlvl()].getladderA().y,Level[P1.getlvl()].getladderA().x, 'A');
				
					
				
				P1.setlvl(P1.getlvl() + 1);
				//teleport to next level
				P1.setx(Level[P1.getlvl()].getladderB().x);
				P1.sety(Level[P1.getlvl()].getladderB().y);
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), P1.getsym());
					
				Level[P1.getlvl()].Print();
				npc.locateGhost(Level[P1.getlvl()]);
					
				
				
				break;
				
				
			}
			case 3:
			{
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), ' ');
				P1.move(c, Level[P1.getlvl()]);
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), P1.getsym());
				Level[P1.getlvl()].Print();
				
				//after displaying the player on top of the ladder reset the ladder A 
				Level[P1.getlvl()].setGrid(Level[P1.getlvl()].getladderB().y,Level[P1.getlvl()].getladderB().x, 'B');
				
					
					
				P1.setlvl(P1.getlvl() - 1);
				//teleport to next level
				P1.setx(Level[P1.getlvl()].getladderA().x);
				P1.sety(Level[P1.getlvl()].getladderA().y);
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), P1.getsym());
				npc.locateGhost(Level[P1.getlvl()]);
				Level[P1.getlvl()].Print();
					
				break;
				
			}
			case 4:
			{
				
				if (P1.getkey() < 3)
				
					P1.setkey(P1.getkey() + 1);
					
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), ' ');	
				P1.move(c, Level[P1.getlvl()]);
				
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), P1.getsym());
				Level[P1.getlvl()].Print();
				
				break;
			}
			case 5:
			{
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), ' ');
				P1.move(c, Level[P1.getlvl()]);
				
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), P1.getsym());
				Level[P1.getlvl()].Print();
				break;
				
			}
			case 6:
			{
				P1.setInv(20); // set inv counter to 20
				
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), ' ');
				P1.move(c, Level[P1.getlvl()]);
				
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), P1.getsym());
				Level[P1.getlvl()].Print();
				
				
				
				
			break;	
			}
			
			case 7:
			{
				
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), ' ');
				P1.setlvl(0); //when you hit the ghost it sends you to lvl 1 entrance
				
				P1.setx(Level[P1.getlvl()].getEntrance().x);
				P1.sety(Level[P1.getlvl()].getEntrance().y);
				Level[P1.getlvl()].setGrid(P1.gety(),P1.getx(), P1.getsym());
				npc.locateGhost(Level[P1.getlvl()]);
				Level[P1.getlvl()].Print();
				
				
				break;
			}
			case 8:
			{
				cout<<endl;
				cout<<"You win!"<<endl;
				usleep(600000);
				cout<<"[̲̅$̲̅(̲̅ιοο̲̅)̲̅$̲̅]"<<endl;
				
				win = true;
				break;
				
				
			}
		
		}
		
		
		if (P1.getlvl() == 0)
			Level[P1.getlvl()].setGrid(Level[P1.getlvl()].getladderA().y,Level[P1.getlvl()].getladderA().x, 'A');
		else if (P1.getlvl() == 2)
			Level[P1.getlvl()].setGrid(Level[P1.getlvl()].getladderB().y,Level[P1.getlvl()].getladderB().x, 'B');
		else
		{
			Level[P1.getlvl()].setGrid(Level[P1.getlvl()].getladderA().y,Level[P1.getlvl()].getladderA().x, 'A');
			Level[P1.getlvl()].setGrid(Level[P1.getlvl()].getladderB().y,Level[P1.getlvl()].getladderB().x, 'B');
		}
		
		
		
		Level[P1.getlvl()].setGrid(npc.gety(),npc.getx(), ' ');
		
		
	if (ghost_turn == true)	
	{
		
	
			
		//ghost move: every other turn
			npc.moveToPlayer(P1,bestmoves);
			if (npc.chase(P1))
			{
					count = 0;
				
				do
				{
					point temp;
					
					
					
					switchvar = bestmoves[count];
					
					switch(switchvar)
					{
						case 0: temp.y = npc.gety(); temp.x = npc.getx(); break;      //base
						case 1: temp.x = npc.getx() + 1 ; temp.y = npc.gety(); break; //d
						case 2: temp.x =(npc.getx() - 1); temp.y = npc.gety(); break;  //a
						case 3: temp.y =(npc.gety() + 1); temp.x = npc.getx(); break;  //s
						case 4: temp.y = (npc.gety() - 1); temp.x = npc.getx(); break;  //w
						default: break;
					}
					
					
					
					if (Level[P1.getlvl()].getGrid(temp.y,temp.x) != '#' &&  Level[P1.getlvl()].getGrid(temp.y,temp.x) != 'D' )
					{
						npc.setx(temp.x);
						npc.sety(temp.y);
						break;
						
					}
					count++;
				}
				while (true);
			
				Level[P1.getlvl()].setGrid(npc.gety(),npc.getx(), npc.getsym());
				
				ghost_turn = false;
			//end ghost move
			}
			else
			{
				srand (time(NULL));
				
				int r = rand()% 4 + 1;
				
				switch(r)
				{
					case 1: npc.move('w',Level[P1.getlvl()]); break; 
					case 2: npc.move('a',Level[P1.getlvl()]); break;
					case 3: npc.move('s',Level[P1.getlvl()]); break;
					case 4: npc.move('d',Level[P1.getlvl()]); break;
					
					
					
				}
				
				
			}
			
			ghost_turn = false;
			
	}
	else 
		ghost_turn = true;
		Level[P1.getlvl()].setGrid(npc.gety(),npc.getx(), npc.getsym());
	}
	
	
}

int Game::checkMove(char input)
{
	
	//return value key 
	// 0 invalid move
	// 1 use key on door
	// 2 up ladder
	// 3 down ladder
	
	
	int tempx, tempy;
	char c;
	tempx = P1.getx();
	tempy = P1.gety();
	
	if (input == 'w')
	{
		tempy--;
	}
	else if(input == 'a')
	{
		tempx--;
	}
	else if (input == 's')
	{
		tempy++;
	}
	else if(input == 'd')
	{
		tempx++;
	}
	else if( input == 'u')
	{
		if ( tempx == Level[P1.getlvl()].getladderA().x  &&  tempy == Level[P1.getlvl()].getladderA().y)
		{
			return 2;
		
		}
		else if (tempx == Level[P1.getlvl()].getladderB().x  &&  tempy == Level[P1.getlvl()].getladderB().y)
		{
			return 3;
		}
		
	}
	else
	{
		return 0;
	}
	
	
	//input has been mapped and character has effectively moved to temporary position
	//now check if that position is valid (not on a wall)
	
	c = Level[P1.getlvl()].getGrid(tempy,tempx);
	
	if (c == '#')
	{
		return 0;
		
	}
	else if (c == 'D')
	{
		
		if (P1.getkey() > 0)
		{
			
			return 1;
		}
		else
		{
			return 0;
		}
		
		
	}
	
	else if (Level[P1.getlvl()].getGrid(tempy,tempx) == 'K' ) //key found
	{
		
		return 4;
			
	}
	else if (Level[P1.getlvl()].getGrid(tempy,tempx) == 'C')
	{
		//cherry found
		
		return 6;
		
		
	}
	else if(tempx == npc.getx() && tempy == npc.gety() )
	{
		if (P1.getInv() > 0)
			return 5;
		
			return 7;
		
	}
	else if (tempx == (npc.getx()+1) && tempy == npc.gety() )
	{
		if (P1.getInv() > 0)
			return 5;
		
		return 7;
	}
		
	else if (tempx == (npc.getx()-1) && tempy == (npc.gety()))
	{
		if (P1.getInv() > 0)
			return 5;
		
		return 7;
	}
	else if(Level[P1.getlvl()].getGrid(tempy,tempx) == 'X' )
	{
		return 8;
	}
	else 
		return 5;
	
	
}


