/***************************************************************************************************************************************
****************************************************************************************************************************************

This is the ghost class. We initially create 4 ghost objects (in the game class), each with unique ghost identifier integers. This
class is naturally a very important class in the game.

****************************************************************************************************************************************
***************************************************************************************************************************************/

#ifndef GHOST_H
#define GHOST_H

class Ghost
{
public:

	//Default constructor
	Ghost();
	
	//Custom constructor
	Ghost(int ghost);

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

	//Get Ghost (used to identifiy Ghost)
	int getGhost();

	//Get current position vector function
	char getPosVector();
	
	//Set current position vector function
	void setPosVector(char pos);

	//Get next position vector function
	char getNextVector();

	//Set next position vector function
	void setNextVector(char nPos);

	//Check Ghost dead function
	bool getGhostDead();
	
	//Set Ghost dead function
	void setGhostDead(bool ghostDead);

private:

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

	//Position vector
	char posVector; 

	//Next position vector
	char nextVector;
	
	//Ghost dead flag
	bool ghostDead;

	//Ghost ID
	int ghost;

};

#endif