/***************************************************************************************************************************************
****************************************************************************************************************************************

This is the ghost class. We initially create 4 ghost objects (in the game class), each with unique ghost identifier integers. This
class is naturally a very important class in the game.

****************************************************************************************************************************************
***************************************************************************************************************************************/

#include <time.h>
#include "ghost.h"
#include "pacman.h"

//Default constructor
Ghost::Ghost()
{
	/*Initialize data fields*/
	x = 0;
	y = 0;
	dx = 0;
	dy = 0;
	posVector = ' ';
	nextVector = 'N';
	srand (time(NULL));
}

//Custom constructor
Ghost::Ghost(int ghost)
{
	/*Re-initialize data fields to make sure*/
	x = 0;
	y = 0;
	dx = 0;
	dy = 0;
	posVector = ' ';
	nextVector = 'N';
	srand (time(NULL));
	this->ghost = ghost;
}

//Get starting position on the x-axis ( in pixels )
int Ghost::getX()
{
	return x;
}

//Set starting position on the x-axis ( in pixels )
void Ghost::setX(int x)
{
	this->x = x;
}

//Get starting position on the y-axis ( in pixels )
int Ghost::getY()
{
	return y;
}

//Set starting position on the y-axis ( in pixels )
void Ghost::setY(int y)
{
	this->y = y;
}

//Get current position on the x-axis ( in pixels )
int Ghost::getDx()
{
	return dx;
}

//Set current position on the x-axis ( in pixels )
void Ghost::setDx(int dx)
{
	this->dx = dx;
}

//Get current position on the y-axis ( in pixels )
int Ghost::getDy()
{
	return dy;
}

//Set current position on the y-axis ( in pixels )
void Ghost::setDy(int dy)
{
	this->dy = dy;
}

//Get current position on the x-axis ( on the array )
int Ghost::getArrayPosX()
{
	arrayPosX = dx / 20.0;
	
	return arrayPosX;
}

//Get current position on the y-axis ( on the array )
int Ghost::getArrayPosY()
{
	arrayPosY = dy / 20.0;

	return arrayPosY;
}

//Get Ghost (used to identifiy Ghost)
int Ghost::getGhost()
{
	return ghost;
}

//Get current position vector function
char Ghost::getPosVector()
{
	return posVector;
}

//Set current position vector function
void Ghost::setPosVector(char posVector)
{
	this->posVector = posVector;
}

//Get next position vector function
char Ghost::getNextVector()
{
	return nextVector;
}

//Set next position vector function
void Ghost::setNextVector(char nextVector)
{
	this->nextVector = nextVector;
}

//Check Ghost dead function
bool Ghost::getGhostDead()
{
	return ghostDead;
}

//Set Ghost dead function
void Ghost::setGhostDead(bool ghostDead)
{

	this->ghostDead = ghostDead;
}