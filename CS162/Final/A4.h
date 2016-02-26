
#ifndef MARKER
#define MARKER

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <cmath>
#include <algorithm>

using namespace std;

struct point
{
	int x;
	int y;
	
};

class Floor
{
	private:
		int visibility[20][30];
		char grid[20][30];
		point ladderA;
		point ladderB;
		point entrance;
		point exit;
		
	public:
	
		Floor();
		//void Print();
		void Print();
		void setGrid(int x,int y ,char c){ grid[x][y] = c; };
		char getGrid(int x,int y){return grid[x][y];};
		
		void setVis(int x, int y, int n){visibility[y][x] = n;};
		int getVis(int x, int y){return visibility[y][x];};
		
		
		void findLadders();
		void findEntrance();
		void findExit();
		
		
		point getEntrance(){return entrance;};
		point getExit(){return exit;};
		point getladderA(){return ladderA;};
		point getladderB(){return ladderB;};
		
		
};



class Character
{
	protected:
	
		int lvl;
		int x;
		int y;
		char symbol;
	
	
	public:
	
		virtual void move(char, Floor&) = 0;
	
	
};



class Player: public Character
{
	private:
	
		int inv_counter;
		int key_counter;
		
		
	public:
	
		int getx(){return x;};
		int gety(){return y;};
		int getlvl(){return lvl;};
		char getsym(){return symbol;};
		int getkey(){return key_counter;};
		int getInv(){return inv_counter;};
		
		
		void setkey(int k){key_counter = k;};
		void setlvl(int l){lvl = l;};
		void setInv(int i){inv_counter = i;};
		void setx(int posx){ x = posx;};
		void sety(int posy){ y = posy;};
		
		
		void move(char, Floor& );
		
		
		Player();
};



class Ghost: public Character
{
	public:
	
		Ghost();
		
		void move(char, Floor&);
		void AImove(int,int);
		void moveToPlayer(Player, int(&)[5]);
		bool chase(Player);
		
		int getlvl(){return lvl;};
		int getx(){return x;};
		int gety(){return y;};
		char getsym(){return symbol;};
		
		void setx(int posx){ x = posx;};
		void sety(int posy){ y = posy;};
		
		
		
		void locateGhost(Floor);
		
};



class Game
{
	private:
		
		Floor Level[3];
		Player P1;
		Ghost npc;
		
	public:
	
		int checkMove(char);
		void mapFloor(int);
		Floor getFloor(int lvl){ return Level[lvl];}
		void play();

};

int getch();

#endif