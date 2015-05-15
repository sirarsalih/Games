/***************************************************************************************************************************************
****************************************************************************************************************************************

This class specifically handles all menu graphics and events that occure in menus (main menu, quick pause window and pause menu). By events
we include keys (and various blittings) as well. This class is mainly called from the game class.

****************************************************************************************************************************************
***************************************************************************************************************************************/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "map.h"

class MenuGraphics
{

public:

	//Default constructor
	MenuGraphics();

	//This function draws the main menu.
	void MenuGraphics::drawMenu(SDL_Surface * screen);

	//Test keys (in main menu) function. This function tests for input keys in main menu, and processes events. 
	void MenuGraphics::testKeys(SDL_Surface * screen, Map map, char * mapPathArray[], char mapGameArray[][40], Pacman &pacmanObject1, Pacman &pacmanObject2,
							Ghost &ghostObject1, Ghost &ghostObject2, Ghost &ghostObject3, Ghost &ghostObject4, SDL_Surface * wallImage, SDL_Surface * pelletsItemsImage, 
							bool &multiplayer, Sound sound);
	
	//Pause menu function. This function shows the ingame pause menu, handles input keys and processes events (quick pause is also included here).
	void MenuGraphics::pauseMenu(SDL_Surface * screen, bool flag, unsigned char * key, SDL_Event keyevent, SDL_Surface * wallImage, SDL_Surface * pelletsItemsImage, char mapGameArray[][40], 
								Map map, char * mapPathArray[], Pacman &pacmanObject1, Pacman &pacmanObject2, Ghost &ghostObject1, Ghost &ghostObject2, Ghost &ghostObject3, Ghost &ghostObject4, bool &multiplayer, 
								SDL_Surface * scoreLifePlayerOne, SDL_Surface * scoreLifePlayerTwo, SDL_Surface * lifePlayerOne, SDL_Surface * lifePlayerTwo, SDL_Rect &scoreLifePlayerOneRect, SDL_Rect &scoreLifePlayerTwoRect,
								SDL_Rect &lifePlayerOneRect, SDL_Rect &lifePlayerTwoRect, SDL_Surface * blankImage, Sound sound);

	//Player life/score function. This function shows the life/score panel of players.
	void MenuGraphics::showLifeScorePlayers(SDL_Surface * screen, bool &multiplayer, SDL_Surface * scoreLifePlayerOne, SDL_Surface * scoreLifePlayerTwo, SDL_Surface * lifePlayerOne, SDL_Surface * lifePlayerTwo, SDL_Rect &scoreLifePlayerOneRect, 
											SDL_Rect &scoreLifePlayerTwoRect, SDL_Rect &lifePlayerOneRect, SDL_Rect &lifePlayerTwoRect, Pacman &pacmanObject1, Pacman &pacmanObject2, SDL_Surface * blankImage);

};

#endif