/***************************************************************************************************************************************
****************************************************************************************************************************************

This class is specifically for blitting pacman and ghost objects, including handling animations and rotations of pacman. Final high score
tables (both singleplayer and multiplayer) for pacmen are also blitted here. This class is constantly called from the map class.

****************************************************************************************************************************************
***************************************************************************************************************************************/

#ifndef PACMANGHOSTBLITTING_H
#define PACMANGHOSTBLITTING_H

#include <SDL.h>
#include "pacman.h"
#include "ghost.h"


class PacmanGhostBlitting
{

public:
		//Default constructor
		PacmanGhostBlitting();

		//This function primarly blits death animation for Pacman if Pacman is dead. If Pacman is not dead, the function calls another function (blitPowerPelletPacman) for further processing.
		void blitPacman(Pacman pacmanObject, SDL_Surface * screen, SDL_Surface * pacmanImage, SDL_Surface * deadPacmanImage, SDL_Rect &blitRect, SDL_Rect &imgRect, int deadAnimationCounterOne, int deathAnimationCounterTwo, SDL_Surface * powerPelletPacmanImage);
		
		//This function blits ghosts and hinders ghosts from eating items (by re-drawing the items). 
		void blitGhost(Ghost ghostObject, SDL_Surface * screen, SDL_Surface * ghostImage, SDL_Rect &blitRect, SDL_Rect &imgRect, char mapGameArray[][40], SDL_Surface * pelletsItemsImage);
		
		//This function is responsible for blitting dummy blanks in map (used to show black spots after Pacman objects are moved around).
		void blitBlanks(SDL_Surface * blankImage, SDL_Surface * screen, Pacman pacmanObject1, Pacman pacmanObject2, SDL_Rect &blitRect, SDL_Rect &imgRect, bool multiplayer);
		
		//This function rotates Pacman in map and checks if Pacman has power pellet. If Pacman has power pellet, Pacman will be blitted with a red color every 5/6 (5 of 6) times to give a blinking effect.
		void blitPowerPelletPacman(SDL_Surface * screen, Pacman &pacmanObject, SDL_Surface * pacmanImage, SDL_Surface * powerPelletPacmanImage, SDL_Rect &blitRect, SDL_Rect &imgRect, SDL_Surface * rotationSurface, int rotationDegree);

		//This function blits the final score image in singleplayer mode.
		static void blitFinalScoreSingleplayer(SDL_Surface * screen, SDL_Surface * scorePlayerOne, SDL_Surface * scorePlayerTwo, SDL_Rect &scorePlayerOneRect, SDL_Rect &scorePlayerTwoRect, Pacman &pacmanObject1, Pacman &pacmanObject2, 
								SDL_Surface * playerOneLabel, SDL_Surface * playerTwoLabel, SDL_Rect &playerOneLabelRect, SDL_Rect &playerTwoLabelRect, SDL_Surface * highScoreImage1, SDL_Surface * highScoreImage2,
								SDL_Surface * continueImage, SDL_Rect &continueImageRect, SDL_Surface * gameOverImage);
		
		//This function blits the final score image in multiplayer mode.
		static void blitFinalScoreMultiplayer(SDL_Surface * screen, SDL_Surface * scorePlayerOne, SDL_Surface * scorePlayerTwo, SDL_Rect &scorePlayerOneRect, SDL_Rect &scorePlayerTwoRect, Pacman &pacmanObject1, Pacman &pacmanObject2, 
								SDL_Surface * playerOneLabel, SDL_Surface * playerTwoLabel, SDL_Rect &playerOneLabelRect, SDL_Rect &playerTwoLabelRect, SDL_Surface * highScoreImage1, SDL_Surface * highScoreImage2,
								SDL_Surface * continueImage, SDL_Rect &continueImageRect, SDL_Surface * gameOverImage);

		//This function is a special callback function for SDL_AddTimer. It manages the Pacman animation.
		static Uint32 callBackFunctionOne(Uint32 interval, void * param);
};

#endif