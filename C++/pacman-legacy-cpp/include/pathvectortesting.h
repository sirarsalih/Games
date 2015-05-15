/***************************************************************************************************************************************
****************************************************************************************************************************************

This class is for vector (paths) testing of pacman and ghost movements, we wish to have a clean route in the map on which pacman and ghost 
can move. This class is constantly called from the map class.

****************************************************************************************************************************************
***************************************************************************************************************************************/

#ifndef PATHVECTORTESTING_H
#define PATHVECTORTESTING_H

#include <SDL.h>
#include "pacman.h"
#include "ghost.h"

class PathVectorTesting
{
	public:

		//Default constructor
		PathVectorTesting();

		//This function makes it possible for Pacman to move in a clean route (array-route) in map, such that Pacman does not half-eat items
		void checkPacmanVector(Pacman &pacmanObject);
		
		//This function makes it possible for Ghost to move in a clean route (array-route) in map, such that Ghost moves "cleanly" in map like Pacman.
		void checkGhostVector(Ghost &ghostObject);
};
#endif