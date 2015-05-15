/***************************************************************************************************************************************
****************************************************************************************************************************************

This class is for vector (paths) testing of pacman and ghost movements, we wish to have a clean route in the map on which pacman and ghost 
can move. This class is constantly called from the map class.

****************************************************************************************************************************************
***************************************************************************************************************************************/

#include <SDL.h>
#include "pathvectortesting.h"
#include "map.h"

//Default constructor
PathVectorTesting::PathVectorTesting()
{

}

//This function makes it possible for Pacman to move in a clean route (array-route) in map, such that Pacman does not half-eat items
void PathVectorTesting::checkPacmanVector(Pacman &pacmanObject)
{
	double xArrayPos = (pacmanObject.getDx() / 20.0);
	double yArrayPos = (pacmanObject.getDy() / 20.0);

	if((xArrayPos - (int)xArrayPos) == 0.0 && (yArrayPos - (int)yArrayPos) == 0.0)
	{
		if(pacmanObject.getNextVector() == 'N')
		{
			pacmanObject.setPosVector('N');
			pacmanObject.setNextVector(' ');
		}
		else if(pacmanObject.getNextVector() == 'S')
		{
			pacmanObject.setPosVector('S');
			pacmanObject.setNextVector(' ');
		}
		else if(pacmanObject.getNextVector() == 'W')
		{
			pacmanObject.setPosVector('W');
			pacmanObject.setNextVector(' ');
		}
		else if(pacmanObject.getNextVector() == 'E')
		{
			pacmanObject.setPosVector('E');
			pacmanObject.setNextVector(' ');
		}
	}
}

//This function makes it possible for Ghost to move in a clean route (array-route) in map, such that Ghost moves "cleanly" in map like Pacman.
void PathVectorTesting::checkGhostVector(Ghost &ghostObject)
{
	double xArrayPos = (ghostObject.getDx() / 20.0);
	double yArrayPos = (ghostObject.getDy() / 20.0);

	if((xArrayPos - (int)xArrayPos) == 0.0 && (yArrayPos - (int)yArrayPos) == 0.0)
	{
		if(ghostObject.getNextVector() == 'N')
		{
			ghostObject.setPosVector('N');
			ghostObject.setNextVector(' ');
		}
		else if(ghostObject.getNextVector() == 'S')
		{
			ghostObject.setPosVector('S');
			ghostObject.setNextVector(' ');
		}
		else if(ghostObject.getNextVector() == 'W')
		{
			ghostObject.setPosVector('W');
			ghostObject.setNextVector(' ');
		}
		else if(ghostObject.getNextVector() == 'E')
		{
			ghostObject.setPosVector('E');
			ghostObject.setNextVector(' ');
		}
	}
}