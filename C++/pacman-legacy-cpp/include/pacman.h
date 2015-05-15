/***************************************************************************************************************************************
****************************************************************************************************************************************

This is the pacman class. We initially create 2 pacman objects (in the game class), each with unique player identifier integers. This
class is naturally a very important class in the game.

****************************************************************************************************************************************
***************************************************************************************************************************************/

#ifndef PACMAN_H
#define PACMAN_H

#include <SDL.h>

class Pacman
{
	
public:

	//Default constructor
	Pacman();

	//Custom constructor
	Pacman(int player);

	//Get player (used to identifiy player)
	int getPlayer();
	
	//Get starting position on the x-axis ( in pixels )
	int getX();

	//Set starting position on the x-axis ( in pixels )
	void setX(int x);

	//Get starting position on the y-axis ( in pixels )
	int getY();

	
	//Set starting position on the y-axis ( in pixels )
	void setY(int y);


	//Get current position on the x-axis ( in pixels )
	int getDx();
	
	//Set current position on the x-axis ( in pixels )
	void setDx(int dx);

	//Get current position on the y-axis ( in pixels )
	int getDy();

	//Set current position on the y-axis ( in pixels )
	void setDy(int dy);

	//Get current position on the x-axis ( on the array )
	int getArrayPosX();
	
	//Get current position on the y-axis ( on the array )
	int getArrayPosY();

	//Get number of lives left function
	int getLife();

	//Set amount of lives function
	void setLife(int life);

	//Get current position vector function
	char getPosVector();

	//Set current position vector function
	void setPosVector(char pos);

	//Get next position vector function
	char getNextVector();

	//Set next position vector function
	void setNextVector(char nPos);

	//Check power pellet function
	bool getPowerPellet();

	//Set power pellet function
	void setPowerPellet(bool powerPellet);

	//Get bonus item function ( for sound )
	bool getBonusItem();

	//Set bonus item function ( for sound )
	void setBonusItem(bool bonusItem);

	//Get score function
	int getScore();

	//Set score function
	void setScore(int score);

	//Check Pacman dead function
	bool getPacmanDead();

	//Set Pacman dead function
	void setPacmanDead(bool pacmanDead);
	
	//Check Pacman dead final ( all lives lost )
	bool getPacmanDeadFinal();

	//Set Pacman dead final ( all lives lost )
	void setPacmanDeadFinal(bool pacmanDeadFinal);

private:

	//Position vector
	char posVector; 

	//Next Position vector
	char nextVector;

	//Player ID
	int player;

	//Pacman life
	int life;

	//Start position x ( in pixels )
	int x;
	
	//Start position y ( in pixels )
	int y;
	
	//Current position x ( in pixels )
	int dx;

	//Current position y ( in pixels )
	int dy;

	//Current position x ( in array )
	int arrayPosX;
	
	//Current position y ( in array )
	int arrayPosY;

	//Score
	int score;

	//Power pellet flag
	bool powerPellet;

	//Bonus item flag
	bool bonusItem;
	
	//Pacman dead flag
	bool pacmanDead;

	//Pacman dead final flag
	bool pacmanDeadFinal;

};

#endif