/***************************************************************************************************************************************
****************************************************************************************************************************************

This is the collision detection class. Upon calling, this class returns either true or false, in other words all functions in this class
are of bool return type. This class is constantly called from the map class to check collisions and handle events.

****************************************************************************************************************************************
***************************************************************************************************************************************/

#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <SDL.h>
#include "game.h"
#include "pacman.h"
#include "ghost.h"

class CollisionDetection
{

public:

	//Default constructor
	CollisionDetection();

	//This function checks collisions between Pacman, items and wall and returns a boolean value. This function also handles events when Pacman eats an item in the map.
	bool checkPacmanCollisionPelletWall(Pacman &pacmanObject, char mapGameArray[][40]);
	
	//This function checks collisions between Ghost and wall and returns a boolean value.
	bool checkGhostCollision(Ghost &ghostObject, char mapGameArray[][40]);
	
	//This function checks collisions between Pacman objects and Ghost objects and processes appropriate events.  
	bool checkPacmanGhostsCollision(Pacman &pacmanObject, Ghost &ghostObject1, Ghost &ghostObject2, Ghost &ghostObject3, Ghost &ghostObject4, 
									SDL_Surface * screen, SDL_Surface * blankImage, SDL_Surface * pelletsItemsImage, char mapGameArray[][40], SDL_Rect &imgRect, SDL_Rect &blitRect);
	
	//This function checks a Pacman-Pacman collision and processes appropriate events (such as checking power pellets and setting Pacman dead flags).
	bool checkPacmanPacmanCollision(Pacman &pacmanObject1, Pacman &pacmanObject2);

	//Help flag for Pacman-Ghost collision (ghost respawn)
	static bool helpFlag;

	/*Ghost ID flags*/
	static bool ghostOne;
	static bool ghostTwo;
	static bool ghostThree;
	static bool ghostFour;
};

#endif