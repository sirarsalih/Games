/***************************************************************************************************************************************
****************************************************************************************************************************************

This is the map class. Here events such as loading, drawing, updating and changing maps are handled, as well as playing sounds and managing 
ghosts A.I. This makes the map class the most important class in the game.

****************************************************************************************************************************************
***************************************************************************************************************************************/

#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include "pacman.h"
#include "ghost.h"
#include "collisiondetection.h"
#include "pacmanghostblitting.h"
#include "sound.h"

class Map
{

public:
	
	//Default constructor
	Map();

	//This function loads maps from text files and stores these in a 2D array
	void loadMap(char * mapPathArray[], char mapGameArray[][40], Pacman &pacmanObject1, Pacman &pacmanObject2, Ghost &ghostObject1, Ghost &ghostObject2, Ghost &ghostObject3, Ghost &ghostObject4, bool multiplayer);
	
	//This function draws maps from a 2D array and shows it on screen.
	void drawMap(SDL_Surface * screen, SDL_Surface * wallImage, SDL_Surface * pelletsItemsImage, char mapGameArray[][40]);
	
	/*The following function is the most important function in the game.
	Here maps are continiously updated (by calling from the game class).
	The function calls the collision detection class to check collision
	between the various objects in the map (mainly between Pacman objects, 
	Ghost objects and walls, items etc.
	This function also tests Pacman lives and blits Pacman objects and Ghosts
	in addition to respawning Ghost objects. Pacman death animations are also
	handled here and finally in-game sounds are also played from here.*/
	void updateMap(Pacman &pacmanObject, Ghost &ghostObject1, Ghost &ghostObject2, Ghost &ghostObject3, Ghost &ghostObject4, SDL_Surface * screen, SDL_Surface * pacmanImage, 
					SDL_Surface * blankImage, SDL_Surface * deadpacmanImage, char mapGameArray[][40], SDL_Surface * lifePlayerOne, SDL_Surface * lifePlayerTwo, SDL_Rect &lifePlayerOneRect, SDL_Rect &lifePlayerTwoRect,
					SDL_Surface * deadImage, SDL_Rect &deadImageRect, bool multiplayer, char * mapPathArray[], SDL_Surface * wallImage,
					SDL_Surface * scoreLifePlayerOne, SDL_Surface * scoreLifePlayerTwo, SDL_Rect scoreLifePlayerOneRect, SDL_Rect scoreLifePlayerTwoRect, 
					CollisionDetection &collisionDetection, PacmanGhostBlitting &pacmanGhostBlitting, SDL_Surface * powerPelletPacmanImage, SDL_Surface * pelletsItemsImage, Sound sound, 
					SDL_Rect &imgRect, SDL_Rect &blitRect);
	
	//This function switches to the next map in the array (map paths are stored in a char array; mapPathArray[10]) and does necessary blitting (such as life/score panels etc.)
	void nextMap(char * mapPathArray[], char mapGameArray[][40], Pacman &pacmanObject1, Pacman &pacmanObject2, Ghost &ghostObject1, Ghost &ghostObject2, Ghost &ghostObject3, Ghost &ghostObject4, bool multiplayer,
				 SDL_Surface * screen, SDL_Surface * wallImage, SDL_Surface * pelletsItemsImage, SDL_Surface * scoreLifePlayerOne, SDL_Rect &scoreLifePlayerOneRect, SDL_Surface * lifePlayerOne, SDL_Rect &lifePlayerOneRect, 
				 SDL_Surface * scoreLifePlayerTwo, SDL_Rect &scoreLifePlayerTwoRect, SDL_Surface * lifePlayerTwo, SDL_Rect &lifePlayerTwoRect);

	//This function resets all item counts in map (pellets, power pellets, bonus items) and does a count up of all current items.
	void countMapItems(char mapGameArray[][40], int &pelletsCount, int &powerPelletsCount, int &bonusItemOneCount, int &bonusItemTwoCount);

	//This function calls the pathVectorTesting class to make Ghosts move in clean routes in map. This function then calculates the nearest distance to a Pacman object (using Pythagoras) and calls up the ghostAIDecisionMaking function to move Ghosts.
	void ghostAICalculation(Pacman &pacmanObject1, Pacman &pacmanObject2 , Ghost &ghostObject, SDL_Surface * screen, SDL_Surface * pelletsItemsImage, 
						   	SDL_Surface * ghostImage, SDL_Rect &blitRect, SDL_Rect &imgRect, char mapGameArray[][40], CollisionDetection &collisionDetection, bool &multiplayer, 
							PacmanGhostBlitting &pacmanGhostBlitting, Sound sound);

	//This function is for A.I. decision making. Basically this function chooses the nearest calculated distance to a Pacman object and sets Ghosts' vectors appropriately. Ghosts then move accordingly to the Pacman objects.
	void Map::ghostAIDecisionMaking(Pacman &pacmanObject, Ghost &ghostObject, CollisionDetection &collisionDetection, int differencePacmanGhostX, int differencePacmanGhostY, char mapGameArray[][40], Sound &sound);

	//This function is a special callback function for SDL_AddTimer. It manages Pacman 1 death animation.
	static Uint32 callBackFunctionOne(Uint32 interval, void * param);
	
	//This function is a special callback function for SDL_AddTimer. It manages Pacman 2 death animation.
	static Uint32 callBackFunctionTwo(Uint32 interval, void * param);

	//This function is a special callback function for SDL_AddTimer. It manages Ghost respawns.
	static Uint32 callBackFunctionThree(Uint32 interval, void * param);

	//Get map level function
	static int getMapLevel();

	//Set map level function
	static void setMapLevel(int level);

	//Ghost movement delay integer (to slow down ghost movements)
	static int ghostMovementDelay;
	
	/*Timer counters for Pacmen death animations*/
	static int deathAnimationCounterOne;
	static int deathAnimationCounterTwo;

	/*Callback function counters for Pacmen death animations*/
	static int callBackFunctionCounterOne;
	static int callBackFunctionCounterTwo;


private:

	//Item tiles for map
	enum Tiles
	{
	WALL = '1',
	PELLET = '2',
	POWERPELLET = '3',
	BONUSITEM_ONE = '4',
	BONUSITEM_TWO = '5'
	};

	/*Power pellet and bonus item sound flags for both players*/
	static bool powerPelletFlagOne;
	static bool powerPelletFlagTwo;
	static bool bonusItemFlagOne;
	static bool bonusItemFlagTwo; 

	//Map level
	static int mapLevel;

};

#endif