/***************************************************************************************************************************************
****************************************************************************************************************************************

This is the pacman class. We initially create 2 pacman objects (in the game class), each with unique player identifier integers. This
class is naturally a very important class in the game.

****************************************************************************************************************************************
***************************************************************************************************************************************/

#include <SDL.h>
#include "pacman.h"

//Default constructor
Pacman::Pacman()
{
	/*Initialize data fields*/
	x = 0;
	y = 0;
	dx = 0;
	dy = 0;
	life = 3;
	posVector = 'N';
	nextVector = ' ';
	score = 0;
	powerPellet = false;
	bonusItem = false;
	pacmanDead = false;
	pacmanDeadFinal = false;
	player = 0;
}

//Custom constructor
Pacman::Pacman(int player)
{
	/*Re-initialize data fields to make sure*/
	x = 0;
	y = 0;
	dx = 0;
	dy = 0;
	life = 3;
	posVector = 'N';
	nextVector = ' ';
	score = 0;
	powerPellet = false;
	bonusItem = false;
	pacmanDead = false;
	pacmanDeadFinal = false;
	
	this->player = player;
}

//Get player (used to identifiy player)
int Pacman::getPlayer()
{
	return player;
}

//Get starting position on the x-axis ( in pixels )
int Pacman::getX()
{
	return x;
}

//Set starting position on the x-axis ( in pixels )
void Pacman::setX(int x)
{
	this->x = x;
}

//Get starting position on the y-axis ( in pixels )
int Pacman::getY()
{
	return y;
}

//Set starting position on the y-axis ( in pixels )
void Pacman::setY(int y)
{
	this->y = y;
}

//Get current position on the x-axis ( in pixels )
int Pacman::getDx()
{
	return dx;
}

//Set current position on the x-axis ( in pixels )
void Pacman::setDx(int dx)
{
	this->dx = dx;
}

//Get current position on the y-axis ( in pixels )
int Pacman::getDy()
{
	return dy;
}
	
//Set current position on the y-axis ( in pixels )
void Pacman::setDy(int dy)
{
	this->dy = dy;
}

//Get current position on the x-axis ( on the array )
int Pacman::getArrayPosX()
{
	arrayPosX = dx / 20.0;

	return arrayPosX;
}

//Get current position on the y-axis ( on the array )
int Pacman::getArrayPosY()
{
	arrayPosY = dy / 20.0;

	return arrayPosY;
}

//Get number of lives left function
int Pacman::getLife()
{
	return life;
}

//Set amount of lives function
void Pacman::setLife(int life)
{
	this->life = life;
}

//Get current position vector function
char Pacman::getPosVector()
{
	return posVector;
}

//Set current position vector function
void Pacman::setPosVector(char posVector)
{
	this->posVector = posVector;
}

//Get next position vector function
char Pacman::getNextVector()
{
	return nextVector;
}

//Set next position vector function
void Pacman::setNextVector(char nextVector)
{
	this->nextVector = nextVector;
}

//Check power pellet function
bool Pacman::getPowerPellet()
{
	return powerPellet;
}

//Set power pellet function
void Pacman::setPowerPellet(bool powerPellet)
{
	//Make a timer for removal of powerpellet after 10 sec
	this->powerPellet = powerPellet;
}

//Get bonus item function ( for sound )
bool Pacman::getBonusItem()
{
	return bonusItem;
}

//Set bonus item function ( for sound )
void Pacman::setBonusItem(bool bonusItem)
{
	this->bonusItem = bonusItem;
}

//Get score function
int Pacman::getScore()
{
	return score;
}

//Set score function
void Pacman::setScore(int score)
{
	this->score = score;
}

//Check Pacman dead function
bool Pacman::getPacmanDead()
{
	return pacmanDead;
}

//Set Pacman dead function
void Pacman::setPacmanDead(bool pacmanDead)
{
	this->pacmanDead = pacmanDead;
}

//Check Pacman dead final ( all lives lost )
bool Pacman::getPacmanDeadFinal()
{
	return pacmanDeadFinal;
}

//Set Pacman dead final ( all lives lost )
void Pacman::setPacmanDeadFinal(bool pacmanDeadFinal)
{
	this->pacmanDeadFinal = pacmanDeadFinal;
}