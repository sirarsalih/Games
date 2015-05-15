#include "../include/checkCollision.h"
#include "SDL.h"

bool checkCollision::checkCol(SDL_Rect &A, SDL_Rect &B)
{
	//The sides of the rectangles 
	int leftA, leftB; 
	int rightA, rightB; 
	int topA, topB; 
	int bottomA, bottomB; 
	
	//Calculate the sides of rect A 
	leftA = A.x; 
	rightA = A.x + A.w; 
	topA = A.y; 
	bottomA = A.y + A.h; 
	
	//Calculate the sides of rect B 
	leftB = B.x; 
	rightB = B.x + B.w; 
	topB = B.y; 
	bottomB = B.y + B.h;

	//Check to see if any of the sides from A are outside of B 
	if(bottomA <= topB) 
	{		
		return false;	
	}

	if(topA >= bottomB) 
	{ 
		return false; 
	} 

	if(rightA <= leftB) 
	{ 
		return false; 
	}

	if(leftA >= rightB) 
	{ 
		return false; 
	} 
	
	//If none of the sides from A are outside B 
	return true;
}