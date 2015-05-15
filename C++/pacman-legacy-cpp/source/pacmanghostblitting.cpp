/***************************************************************************************************************************************
****************************************************************************************************************************************

This class is specifically for blitting pacman and ghost objects, including handling animations and rotations of pacman. Final high score
tables (both singleplayer and multiplayer) for pacmen are also blitted here. This class is constantly called from the map class.

****************************************************************************************************************************************
***************************************************************************************************************************************/

#include <SDL.h>
#include "pacmanghostblitting.h"
#include "rotozoom.h"

static int animationCounter = 0;

//Surface for rotation
SDL_Surface * rotationSurface;

//Counters for Pacmen when power pellet is eaten
static int pacmanOneCounter = 1;
static int pacmanTwoCounter = 1;

//Default constructor
PacmanGhostBlitting::PacmanGhostBlitting()
{
	
}

//This function primarly blits death animation for Pacman if Pacman is dead. If Pacman is not dead, the function calls another function (blitPowerPelletPacman) for further processing.
void PacmanGhostBlitting::blitPacman(Pacman pacmanObject, SDL_Surface * screen, SDL_Surface * pacmanImage, SDL_Surface * deadPacmanImage, SDL_Rect &blitRect, SDL_Rect &imgRect, 
									 int deathAnimationCounterOne, int deathAnimationCounterTwo, SDL_Surface * powerPelletPacmanImage)
{
	//Timer for Pacman animation
	static SDL_TimerID animationTimer = SDL_AddTimer(100, callBackFunctionOne, NULL);

	//Test the posVector of the pacman object here, given Pacman is alive
	if(pacmanObject.getPacmanDead() == false && pacmanObject.getPacmanDeadFinal() == false)
	{
		if(pacmanObject.getPosVector() == 'N')
			blitPowerPelletPacman(screen, pacmanObject, pacmanImage, powerPelletPacmanImage, blitRect, imgRect, rotationSurface, 90);
		
		else if(pacmanObject.getPosVector() == 'S')
			blitPowerPelletPacman(screen, pacmanObject, pacmanImage, powerPelletPacmanImage, blitRect, imgRect, rotationSurface, -90);
		
		else if (pacmanObject.getPosVector() == 'W')
			blitPowerPelletPacman(screen, pacmanObject, pacmanImage, powerPelletPacmanImage, blitRect, imgRect, rotationSurface, 180);
		
		else 
			blitPowerPelletPacman(screen, pacmanObject, pacmanImage, powerPelletPacmanImage, blitRect, imgRect, rotationSurface, 0);
	}

	else
	{
		//Blit death animation for player 1
		if(pacmanObject.getPlayer() == 1)
		{
			blitRect.x = pacmanObject.getDx();
			blitRect.y = pacmanObject.getDy();

			imgRect.x = deathAnimationCounterOne;
			imgRect.y = 0;
		
			//Blit surfaces
			SDL_BlitSurface(deadPacmanImage, &imgRect, screen, &blitRect);
		}

		//Blit death animation for player 2
		else if(pacmanObject.getPlayer() == 2)
		{
			blitRect.x = pacmanObject.getDx();
			blitRect.y = pacmanObject.getDy();

			imgRect.x = deathAnimationCounterTwo;
			imgRect.y = 0;
		
			//Blit surfaces
			SDL_BlitSurface(deadPacmanImage, &imgRect, screen, &blitRect);
		}
		else
			return;
	}
}

//This function blits ghosts and hinders ghosts from eating items (by re-drawing the items). 
void PacmanGhostBlitting::blitGhost(Ghost ghostObject, SDL_Surface * screen, SDL_Surface * ghostImage, SDL_Rect &blitRect, SDL_Rect &imgRect,
									char mapGameArray[][40], SDL_Surface * pelletsItemsImage)
{
		//Array X and Y positions
		double xArrayPos = 0;
		double yArrayPos = 0;

		imgRect.x = 0;
		imgRect.y = 0;

		//Test to hinder ghosts from eating items in map
		if(ghostObject.getPosVector() == 'N')
		{
			xArrayPos = (ghostObject.getDx() / 20.0);
			yArrayPos = (ghostObject.getDy() / 20.0 + 1);
		}

		if(ghostObject.getPosVector() == 'S')
		{
			xArrayPos = (ghostObject.getDx() / 20.0);
			yArrayPos = (ghostObject.getDy() / 20.0 - 0.5);
		}

		else if(ghostObject.getPosVector() == 'E')
		{
			xArrayPos = (ghostObject.getDx() / 20.0);
			yArrayPos = (ghostObject.getDy() / 20.0);
		}

		else if(ghostObject.getPosVector() == 'W')
		{
			xArrayPos = (ghostObject.getDx() / 20.0 + 1);
			yArrayPos = (ghostObject.getDy() / 20.0);
		}

		if(mapGameArray[(int)yArrayPos][(int)xArrayPos] == '2')
		{
			blitRect.x = (int)xArrayPos * 20;
			blitRect.y = (int)yArrayPos * 20;
			
			imgRect.x = 0;
			
			SDL_BlitSurface(pelletsItemsImage,&imgRect, screen, &blitRect);
			
		}

		else if(mapGameArray[(int)yArrayPos][(int)xArrayPos] == '3')
		{
			blitRect.x = (int)xArrayPos * 20;
			blitRect.y = (int)yArrayPos * 20;
			
			imgRect.x = 20;
			
			SDL_BlitSurface(pelletsItemsImage,&imgRect, screen, &blitRect);
			
		}
			
		else if(mapGameArray[(int)yArrayPos][(int)xArrayPos] == '4')
		{
			blitRect.x = (int)xArrayPos * 20;
			blitRect.y = (int)yArrayPos * 20;
			
			imgRect.x = 40;
			
			SDL_BlitSurface(pelletsItemsImage,&imgRect, screen, &blitRect);
			
		}

		else if(mapGameArray[(int)yArrayPos][(int)xArrayPos] == '5')
		{
			blitRect.x = (int)xArrayPos * 20;
			blitRect.y = (int)yArrayPos * 20;
			
			imgRect.x = 60;
			
			SDL_BlitSurface(pelletsItemsImage,&imgRect, screen, &blitRect);
			
		}

		//Get current position of ghost object
		blitRect.x = ghostObject.getDx();
		blitRect.y = ghostObject.getDy();
		
		//Get correct ghost from ghost image tile
		if(ghostObject.getGhost() == 1)
			imgRect.x = 0;
		
		else if(ghostObject.getGhost() == 2)
			imgRect.x = 20;
		
		else if(ghostObject.getGhost() == 3)
			imgRect.x = 40;
		
		else if(ghostObject.getGhost() == 4)
			imgRect.x = 60;

		imgRect.y = 0;
		
		SDL_BlitSurface(ghostImage, &imgRect, screen, &blitRect);
}

//This function is responsible for blitting dummy blanks in map (used to show black spots after Pacman objects are moved around).
void PacmanGhostBlitting::blitBlanks(SDL_Surface * blankImage, SDL_Surface * screen, Pacman pacmanObject1, Pacman pacmanObject2, SDL_Rect &blitRect, SDL_Rect &imgRect, bool multiplayer)
{
	imgRect.x = 0;

	if(!multiplayer)
	{
		//blank out the pacman 1 image
		blitRect.x = pacmanObject1.getDx();
		blitRect.y = pacmanObject1.getDy();
		SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);
	}
	
	if(multiplayer)
	{
		//blank out the pacman 1 image
		blitRect.x = pacmanObject1.getDx();
		blitRect.y = pacmanObject1.getDy();
		SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);

		//blank out the pacman 2 image
		blitRect.x = pacmanObject2.getDx();
		blitRect.y = pacmanObject2.getDy();
		SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);


	}
}

//This function rotates Pacman in map and checks if Pacman has power pellet. If Pacman has power pellet, Pacman will be blitted with a red color every 5/6 (5 of 6) times to give a blinking effect.
void PacmanGhostBlitting::blitPowerPelletPacman(SDL_Surface * screen, Pacman &pacmanObject, SDL_Surface * pacmanImage, SDL_Surface * powerPelletPacmanImage, 
												SDL_Rect &blitRect, SDL_Rect &imgRect, SDL_Surface * rotationSurface, int rotationDegree)
{
	//Current position
	blitRect.x = pacmanObject.getDx();
	blitRect.y = pacmanObject.getDy();

	/**Rotate Pacmen with power pellet OFF**/
	if(pacmanObject.getPowerPellet() == false && pacmanObject.getPlayer() == 1)
	{
		rotationSurface = rotozoomSurface(pacmanImage, rotationDegree, 1, 0);
		pacmanOneCounter = 0;
	}

	else if(pacmanObject.getPowerPellet() == false && pacmanObject.getPlayer() == 2)
	{
		rotationSurface = rotozoomSurface(pacmanImage, rotationDegree, 1, 0);
		pacmanTwoCounter = 0;
	}

	/**Test Pacman and rotate with power pellet ON**/
	else if(pacmanObject.getPlayer() == 1)
	{

		if(pacmanOneCounter % 6 != 0)
		{
			rotationSurface = rotozoomSurface(powerPelletPacmanImage, rotationDegree, 1, 0);
			pacmanOneCounter++;
		}

		else if(pacmanOneCounter % 6 == 0)
		{
			rotationSurface = rotozoomSurface(pacmanImage, rotationDegree, 1, 0);
			pacmanOneCounter++;
		}
	}
	
	else if(pacmanObject.getPlayer() == 2)
	{
		if(pacmanTwoCounter % 6 != 0)
		{
			rotationSurface = rotozoomSurface(powerPelletPacmanImage, rotationDegree, 1, 0);
			pacmanTwoCounter++;
		}

		else if(pacmanTwoCounter % 6 == 0)
		{
			rotationSurface = rotozoomSurface(pacmanImage, rotationDegree, 1, 0);
			pacmanTwoCounter++;
		}	
	}

	if(pacmanObject.getPosVector() == 'N' || pacmanObject.getPosVector() == 'S')
	{
		imgRect.x = 0;
		imgRect.y = animationCounter;
	}

	if(pacmanObject.getPosVector() == 'W' || pacmanObject.getPosVector() == 'E')
	{
		imgRect.x = animationCounter;
		imgRect.y = 0;
	}

	SDL_BlitSurface(rotationSurface, &imgRect, screen, &blitRect);

	//Free rotation surface
	SDL_FreeSurface(rotationSurface);
}

//This function blits the final score image in singleplayer mode.
void PacmanGhostBlitting::blitFinalScoreSingleplayer(SDL_Surface * screen, SDL_Surface * scorePlayerOne, SDL_Surface * scorePlayerTwo, SDL_Rect &scorePlayerOneRect, SDL_Rect &scorePlayerTwoRect, Pacman &pacmanObject1, Pacman &pacmanObject2, 
								SDL_Surface * playerOneLabel, SDL_Surface * playerTwoLabel, SDL_Rect &playerOneLabelRect, SDL_Rect &playerTwoLabelRect, SDL_Surface * highScoreImage1, SDL_Surface * highScoreImage2,
								SDL_Surface * continueImage, SDL_Rect &continueImageRect, SDL_Surface * gameOverImage)
{

			//Blit game over and continue images
			SDL_BlitSurface(gameOverImage, NULL, screen, NULL);
			SDL_BlitSurface(continueImage, NULL, screen, &continueImageRect);

			//Key event
			SDL_Event keyevent;

			//Get key state
			unsigned char * key = SDL_GetKeyState(0);

			bool gameOver = true;

			while(gameOver)
			{	
				SDL_Delay(5);

				while(SDL_PollEvent(&keyevent))
				{
					if(key[SDLK_SPACE] || key[SDLK_RETURN])
					{
						//Blit high score image
						SDL_BlitSurface(highScoreImage1, NULL, screen, NULL);

						//Position player 1 label
						playerOneLabelRect.x = 15;
						playerOneLabelRect.y = 142;

						//Position player 1 score
						scorePlayerOneRect.x = 590;
						scorePlayerOneRect.y = 142;

						//Blit player 1 label
						SDL_BlitSurface(playerOneLabel, NULL, screen, &playerOneLabelRect);

						//Blit player 1 score
						SDL_BlitSurface(scorePlayerOne, NULL, screen, &scorePlayerOneRect);
					}

					if(key[SDLK_ESCAPE] || keyevent.type == SDL_QUIT)
						exit(1);
				}
						
				SDL_Flip(screen);
			}

}

//This function blits the final score image in multiplayer mode.
void PacmanGhostBlitting::blitFinalScoreMultiplayer(SDL_Surface * screen, SDL_Surface * scorePlayerOne, SDL_Surface * scorePlayerTwo, SDL_Rect &scorePlayerOneRect, SDL_Rect &scorePlayerTwoRect, Pacman &pacmanObject1, Pacman &pacmanObject2, 
								SDL_Surface * playerOneLabel, SDL_Surface * playerTwoLabel, SDL_Rect &playerOneLabelRect, SDL_Rect &playerTwoLabelRect, SDL_Surface * highScoreImage1, SDL_Surface * highScoreImage2,
								SDL_Surface * continueImage, SDL_Rect &continueImageRect, SDL_Surface * gameOverImage)
{
	//Blit game over and continue images
	SDL_BlitSurface(gameOverImage, NULL, screen, NULL);
	SDL_BlitSurface(continueImage, NULL, screen, &continueImageRect);

	//Key event
	SDL_Event keyevent;

	//Get key state
	unsigned char * key = SDL_GetKeyState(0);

	bool gameOver = true;
	bool returnToMainMenu = false;
	
	while(gameOver)
	{
		SDL_Delay(5);

		while(SDL_PollEvent(&keyevent))
		{
			if(key[SDLK_SPACE] || key[SDLK_RETURN])
			{
				//Blit high score image
				SDL_BlitSurface(highScoreImage2, NULL, screen, NULL);		

				//Player 1 wins
				if(pacmanObject1.getScore() > pacmanObject2.getScore())
				{
					//Position player 1 label on top
					playerOneLabelRect.x = 15;
					playerOneLabelRect.y = 142;

					//Position player 1 score on top
					scorePlayerOneRect.x = 590;
					scorePlayerOneRect.y = 142;

					//Position player 2 label on bottom
					playerTwoLabelRect.x = 15;
					playerTwoLabelRect.y = 188;

					//Position player 2 score on bottom
					scorePlayerTwoRect.x = 590;
					scorePlayerTwoRect.y = 188;
				}

				//Player 2 wins
				else if(pacmanObject1.getScore() < pacmanObject2.getScore())
				{
					//Position player 2 label on top
					playerTwoLabelRect.x = 15;
					playerTwoLabelRect.y = 142;

					//Position player 2 score on top
					scorePlayerTwoRect.x = 590;
					scorePlayerTwoRect.y = 142;

					//Position player 1 label on bottom
					playerOneLabelRect.x = 15;
					playerOneLabelRect.y = 188;

					//Position player 1 score on bottom
					scorePlayerOneRect.x = 590;
					scorePlayerOneRect.y = 188;
				}

				//Draw
				else
				{
					//Position player 1 label on top
					playerOneLabelRect.x = 15;
					playerOneLabelRect.y = 142;

					//Position player 1 score on top
					scorePlayerOneRect.x = 590;
					scorePlayerOneRect.y = 142;

					//Position player 2 label on bottom
					playerTwoLabelRect.x = 15;
					playerTwoLabelRect.y = 188;

					//Position player 2 score on bottom
					scorePlayerTwoRect.x = 590;
					scorePlayerTwoRect.y = 188;
				}

				//Blit player 1 label
				SDL_BlitSurface(playerOneLabel, NULL, screen, &playerOneLabelRect);

				//Blit player 2 label
				SDL_BlitSurface(playerTwoLabel, NULL, screen, &playerTwoLabelRect);

				//Blit player 1 score
				SDL_BlitSurface(scorePlayerOne, NULL, screen, &scorePlayerOneRect);

				//Blit player 2 score
				SDL_BlitSurface(scorePlayerTwo, NULL, screen, &scorePlayerTwoRect);

				SDL_Flip(screen);
			}

			if(key[SDLK_ESCAPE] || keyevent.type == SDL_QUIT)
				exit(1);	
		}
				
		SDL_Flip(screen);
	}
}

//This function is a special callback function for SDL_AddTimer. It manages the Pacman animation.
Uint32 PacmanGhostBlitting::callBackFunctionOne(Uint32 interval, void * param)
{
	animationCounter += 20;
	
	if(animationCounter > 40)
		animationCounter = 0;

	return interval;
}