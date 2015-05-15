/***************************************************************************************************************************************
****************************************************************************************************************************************

This is the map class. Here events such as loading, drawing, updating and changing maps are handled, as well as playing sounds and managing 
ghosts A.I. This makes the map class the most important class in the game.

****************************************************************************************************************************************
***************************************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <math.h>
#include "map.h"
#include "game.h"
#include "pacman.h"
#include "collisiondetection.h"
#include "pathvectortesting.h"
#include "pacmanghostblitting.h"
#include "menugraphics.h"

using namespace std;

//Initialize map level
int Map::mapLevel = 0;

//Initialize timer counters
static int animationCounter = 0;
int Map::deathAnimationCounterOne = 0;
int Map::deathAnimationCounterTwo = 0;

//Initialize callback function counters for death animation
int Map::callBackFunctionCounterOne = 0;
int Map::callBackFunctionCounterTwo = 0;

//Power pellet and bonus item sound flags for both players
bool Map::powerPelletFlagOne = true;
bool Map::powerPelletFlagTwo = true; 
bool Map::bonusItemFlagOne = true;
bool Map::bonusItemFlagTwo = true; 

//Path vector testing class
PathVectorTesting pathVectorTesting;

//Ghost respawn timer flag
static bool ghostRespawnTimerStarted = false;
static bool respawnGhost = false;

//Ghost movement delay (to slow down ghost movements)
int Map::ghostMovementDelay = 0;

//Ghost movement sound delay (to avoid instant sound repetition)
static int ghostSoundDelay = 0;

//Random ghost vectors
char randomVectorOne[2] = {'N', 'S'};
char randomVectorTwo[2] = {'W', 'E'};

//Random index integer
int randomIndex;

//Default constructor
Map::Map()
{
	
}

//This function loads maps from text files and stores these in a 2D array
void Map::loadMap(char * mapPathArray[], char mapGameArray[][40], Pacman &pacmanObject1, Pacman &pacmanObject2, 
				  Ghost &ghostObject, Ghost &ghostObject2, Ghost &ghostObject3, Ghost &ghostObject4, bool multiplayer)
{
	ifstream input;
	ofstream output;

	input.open(mapPathArray[mapLevel]);

	if(input.fail())
	{
		cout << "Map does not exist. Exit.\n" << endl;
		exit(1);
	}

	//Read numbers
	char numbers[1300];
	
	while(!input.eof())
		input.getline(numbers, 1300, 'X');

	int arrayCounter = 0;
	int playerCounter = 0;
	int ghostCounter = 0;

	//Insert values from map txt into 2D array
	for(int i = 0; i < 30; i++)
	{
		for(int j = 0; j < 40; j++)
		{
			if(numbers[arrayCounter] == '\n')
			{
				arrayCounter += 2;
				mapGameArray[i][j] = numbers[arrayCounter];			
			}

			//Ghost objects
			else if(numbers[arrayCounter] == '#')
			{
				ghostCounter++;

				if(ghostCounter == 1)
				{
					ghostObject.setX(j * 20);
					ghostObject.setY(i * 20);
					ghostObject.setDx(j * 20);
					ghostObject.setDy(i * 20);
				}

				else if(ghostCounter == 2)
				{
					ghostObject2.setX(j * 20);
					ghostObject2.setY(i * 20);
					ghostObject2.setDx(j * 20);
					ghostObject2.setDy(i * 20);
				}

				else if(ghostCounter == 3)
				{
					ghostObject3.setX(j * 20);
					ghostObject3.setY(i * 20);
					ghostObject3.setDx(j * 20);
					ghostObject3.setDy(i * 20);
				}

				else if(ghostCounter == 4)
				{
					ghostObject4.setX(j * 20);
					ghostObject4.setY(i * 20);
					ghostObject4.setDx(j * 20);
					ghostObject4.setDy(i * 20);
				}

				arrayCounter++;
			}

			//Pac-Man objects
			else if(numbers[arrayCounter] == '@')
			{				
				playerCounter++;

				//If multiplayer
				if(multiplayer)
				{
					if(playerCounter == 1)
					{
						pacmanObject1.setX(j * 20);
						pacmanObject1.setY(i * 20);
						pacmanObject1.setDx(j * 20);
						pacmanObject1.setDy(i * 20);
					}
					
					else if(playerCounter == 2)
					{
						pacmanObject2.setX(j * 20);
						pacmanObject2.setY(i * 20);
						pacmanObject2.setDx(j * 20);
						pacmanObject2.setDy(i * 20);
					}
				}
				
				//If not multiplayer
				else
				{
					if(playerCounter == 1)
					{
						pacmanObject1.setX(j * 20);
						pacmanObject1.setY(i * 20);
						pacmanObject1.setDx(j * 20);
						pacmanObject1.setDy(i * 20);
					}
					
					else if(playerCounter == 2)
						mapGameArray[i][j] = '2';
				}		

				arrayCounter++;
			}
			
			else
			{
				mapGameArray[i][j] = numbers[arrayCounter];
				arrayCounter++;
			}
		}
	}
	
	input.close();

}

//This function draws maps from a 2D array and shows it on screen.
void Map::drawMap(SDL_Surface * screen, SDL_Surface * wallImage, SDL_Surface * pelletsItemsImage, char mapGameArray[][40])
{
	//Draw tiles
	for(int i = 0; i < 40; i++)
	{ 
		for(int j = 0; j < 30; j++)
		{
			//Choose rect dimensions to blit
			SDL_Rect blitRect;
			blitRect.x = i * 20;
			blitRect.y = j * 20;

			//The source rect, meaning the tile's rect
			SDL_Rect imgRect;
			imgRect.x = 0;
			imgRect.y = 0;
			imgRect.w = 20;
			imgRect.h = 20;
         
			//Test different tiles and blit
			if(mapGameArray[j][i] == WALL)
				SDL_BlitSurface(wallImage, &imgRect, screen, &blitRect);

			else if(mapGameArray[j][i] == PELLET)
				SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);

			else if(mapGameArray[j][i] == POWERPELLET)
			{
				imgRect.x = 20;

				SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);
			}

			else if(mapGameArray[j][i] == BONUSITEM_ONE)
			{
				imgRect.x = 40;

				SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);
			}

			else if(mapGameArray[j][i] == BONUSITEM_TWO)
			{
				imgRect.x = 60;

				SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);
			}

		}
	}

}

/*The following function is the most important function in the game.
Here maps are continiously updated (by calling from the game class).
The function calls the collision detection class to check collision
between the various objects in the map (mainly between Pacman objects, 
Ghost objects and walls, items etc.).
This function also tests Pacman lives and blits Pacman objects and Ghosts
in addition to respawning Ghost objects. Pacman death animations are also
handled here and finally in-game sounds are also played from here.*/
void Map::updateMap(Pacman &pacmanObject, Ghost &ghostObject, Ghost &ghostObject2, Ghost &ghostObject3, Ghost &ghostObject4, SDL_Surface * screen, 
					SDL_Surface * pacmanImage, SDL_Surface * blankImage, SDL_Surface * deadPacmanImage, char mapGameArray[][40], 
					SDL_Surface * lifePlayerOne, SDL_Surface * lifePlayerTwo, SDL_Rect &lifePlayerOneRect, SDL_Rect &lifePlayerTwoRect, 
					SDL_Surface * deadImage, SDL_Rect &deadImageRect, bool multiplayer, char * mapPathArray[], SDL_Surface * wallImage,
					SDL_Surface * scoreLifePlayerOne, SDL_Surface * scoreLifePlayerTwo, SDL_Rect scoreLifePlayerOneRect, SDL_Rect scoreLifePlayerTwoRect, CollisionDetection &collisionDetection, 
					PacmanGhostBlitting &pacmanGhostBlitting, SDL_Surface * powerPelletPacmanImage, SDL_Surface * pelletsItemsImage, Sound sound,
					SDL_Rect &imgRect, SDL_Rect &blitRect)

{

	//Get current position of Pacman
	blitRect.x = pacmanObject.getDx();
	blitRect.y = pacmanObject.getDy();

	//Position blank image rects
	blitRect.w = 20;
	blitRect.h = 20;
		
	imgRect.x = 0;
	imgRect.y = 0;
	imgRect.w = 20;
	imgRect.h = 20;

	//Check vector/path of Pacman, we want a clean movement route in the map (so that Pacman does not half-eat items)
	pathVectorTesting.checkPacmanVector(pacmanObject);
	
	/**Event handling if pacmanObject does not collide with a wall**/
	if(!(collisionDetection.checkPacmanCollisionPelletWall(pacmanObject, mapGameArray)) && !pacmanObject.getPacmanDead() && !pacmanObject.getPacmanDeadFinal())
	{
		/**SOUNDS**/

		if(sound.getSound() == true)
		{
			//Play Pacman move sound
			sound.playSoundPacmanMove();

			/*Power pellet and bonus item sounds for both players*/

			//Player 1 power pellets
			if(pacmanObject.getPlayer() == 1 && pacmanObject.getPowerPellet() == true)
			{
				if(powerPelletFlagOne)
				{
					//Play power pellet sound
					sound.playSoundPacmanPowerPellet();
					
					powerPelletFlagOne = false;
				}
			}

			else if(pacmanObject.getPlayer() == 1 && pacmanObject.getPowerPellet() == false)
				powerPelletFlagOne = true;

			//Player 1 bonus items
			if(pacmanObject.getPlayer() == 1 && pacmanObject.getBonusItem() == true)
			{
				pacmanObject.setBonusItem(false);

				if(bonusItemFlagOne)
				{
					//Play bonus item sound
					sound.playSoundPacmanBonusItem();
					
					powerPelletFlagOne = false;
				}
			}

			else if(pacmanObject.getPlayer() == 1 && pacmanObject.getBonusItem() == false)
				bonusItemFlagOne = true;

			//Player 2 power pellets
			if(pacmanObject.getPlayer() == 2 && pacmanObject.getPowerPellet() == true)
			{
				if(powerPelletFlagTwo)
				{
					//Play power pellet sound
					sound.playSoundPacmanPowerPellet();
					
					powerPelletFlagTwo = false;
				}
			}

			else if(pacmanObject.getPlayer() == 2 && pacmanObject.getPowerPellet() == false)
				powerPelletFlagTwo = true;

			//Player 2 bonus items
			if(pacmanObject.getPlayer() == 2 && pacmanObject.getBonusItem() == true)
			{
				pacmanObject.setBonusItem(false);

				if(bonusItemFlagTwo)
				{
					//Play bonus item sound
					sound.playSoundPacmanBonusItem();
					
					powerPelletFlagTwo = false;
				}
			}

			else if(pacmanObject.getPlayer() == 2 && pacmanObject.getBonusItem() == false)
				bonusItemFlagOne = true;
		}

		//Pacmen movements
		if(pacmanObject.getPosVector() == 'N')
			pacmanObject.setDy(pacmanObject.getDy() - 1);
		
		else if(pacmanObject.getPosVector() == 'S')
			pacmanObject.setDy(pacmanObject.getDy() + 1);
		
		else if(pacmanObject.getPosVector() == 'W')
			pacmanObject.setDx(pacmanObject.getDx() - 1);	
		
		else
			pacmanObject.setDx(pacmanObject.getDx() + 1);

	}

	/**Test Pacmen lives**/
	if(pacmanObject.getPlayer() == 1 && pacmanObject.getLife() == 2)
	{
		lifePlayerOneRect.x = 100;

		SDL_BlitSurface(blankImage, NULL, screen, &lifePlayerOneRect);
	}
	
	if(pacmanObject.getPlayer() == 1 && pacmanObject.getLife() == 1)
	{
		lifePlayerOneRect.x = 80;
		
		SDL_BlitSurface(blankImage, NULL, screen, &lifePlayerOneRect);
	}

	//No more lives, player 1 loses
	if(pacmanObject.getPlayer() == 1 && pacmanObject.getLife() == 0)
	{
		pacmanObject.setPacmanDead(true);
		pacmanObject.setPacmanDeadFinal(true);

		lifePlayerOneRect.x = 60;
		deadImageRect.x = 60;
		
		SDL_BlitSurface(blankImage, NULL, screen, &lifePlayerOneRect);

		SDL_BlitSurface(deadImage, NULL, screen, &deadImageRect);

	}

	if(pacmanObject.getPlayer() == 2 && pacmanObject.getLife() == 2)
	{
		lifePlayerTwoRect.x = 660;

		SDL_BlitSurface(blankImage, NULL, screen, &lifePlayerTwoRect);
	}
	
	if(pacmanObject.getPlayer() == 2 && pacmanObject.getLife() == 1)
	{
		lifePlayerTwoRect.x = 640;
		
		SDL_BlitSurface(blankImage, NULL, screen, &lifePlayerTwoRect);
	}
	
	//No more lives, player 2 loses
	if(pacmanObject.getPlayer() == 2 && pacmanObject.getLife() == 0)
	{
		pacmanObject.setPacmanDead(true);
		pacmanObject.setPacmanDeadFinal(true);

		lifePlayerTwoRect.x = 620;
		deadImageRect.x = 620;
		
		SDL_BlitSurface(blankImage, NULL, screen, &lifePlayerTwoRect);

		SDL_BlitSurface(deadImage, NULL, screen, &deadImageRect);

	}

	//Blit and animate pacman
	pacmanGhostBlitting.blitPacman(pacmanObject, screen, pacmanImage, deadPacmanImage, blitRect, imgRect, deathAnimationCounterOne, deathAnimationCounterTwo, powerPelletPacmanImage);

	/**Check if a Pacman is dead, if it is, do not show it**/
	if(pacmanObject.getPlayer() == 1 && pacmanObject.getPacmanDeadFinal() == true)
	{
		//Remove Pacman from map
		blitRect.x = pacmanObject.getDx();
		blitRect.y = pacmanObject.getDy();
		imgRect.x = 0;
		imgRect.y = 0;

		SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);
	}

	if(pacmanObject.getPlayer() == 2 && pacmanObject.getPacmanDeadFinal() == true)
	{
		//Remove Pacman from map
		blitRect.x = pacmanObject.getDx();
		blitRect.y = pacmanObject.getDy();
		imgRect.x = 0;
		imgRect.y = 0;

		SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);
	}

	
	//If there is a collision with Pacman and Ghost (power pellet OFF), start death animation and remove a Pacman life from score/life panel (GUI)
	if(collisionDetection.checkPacmanGhostsCollision(pacmanObject, ghostObject, ghostObject2, ghostObject3, ghostObject4, screen, blankImage, pelletsItemsImage, mapGameArray, imgRect, blitRect))
	{
		//Play Pacman die sound
		if(sound.getSound() == true)
			sound.playSoundPacmanDie();

		//Check if a Pacman is already dead, if it is, do not show death animation
		if(pacmanObject.getPlayer() == 1 && pacmanObject.getPacmanDeadFinal() == true)
		{
			//Remove Pacman from map
			blitRect.x = pacmanObject.getDx();
			blitRect.y = pacmanObject.getDy();
			imgRect.x = 0;
			imgRect.y = 0;

			SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);

			callBackFunctionCounterOne = 9;
		}

		if(pacmanObject.getPlayer() == 2 && pacmanObject.getPacmanDeadFinal() == true)
		{
			//Remove Pacman from map
			blitRect.x = pacmanObject.getDx();
			blitRect.y = pacmanObject.getDy();
			imgRect.x = 0;
			imgRect.y = 0;

			SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);

			callBackFunctionCounterTwo = 9;
		}

		if(pacmanObject.getPlayer() == 1)
			 SDL_TimerID deathAnimationTimer = SDL_AddTimer(200, callBackFunctionOne, NULL);
		
		if(pacmanObject.getPlayer() == 2)
			 SDL_TimerID deathAnimationTimer = SDL_AddTimer(200, callBackFunctionTwo, NULL);
	}

	//Pacman collision with ghost (power pellet ON)
	else
		//Help flag
		ghostRespawnTimerStarted = true;

	//If power pellet was on in a Pacman-Ghost collision, kill apropriate ghost and wait 5 seconds before respawn
	if(ghostRespawnTimerStarted && !CollisionDetection::helpFlag)
	{
		//Play bonus item sound
		sound.playSoundPacmanBonusItem();

		//Throw correct ghost off map for 10 seconds and start respawn timer
		if(CollisionDetection::ghostOne)
		{
			ghostObject.setDx(2000);
			ghostObject.setDy(2000);

			blitRect.x = ghostObject.getDx();
			blitRect.y = ghostObject.getDy();

			//Blank image on the current Ghost position
			SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);

			//Start respawn timer
			SDL_TimerID ghostRespawnTimer = SDL_AddTimer(10000, callBackFunctionThree, NULL);
		}

		//Throw correct ghost off map for 10 seconds start respawn timer
		if(CollisionDetection::ghostTwo)
		{
			ghostObject2.setDx(2000);
			ghostObject2.setDy(2000);

			blitRect.x = ghostObject2.getDx();
			blitRect.y = ghostObject2.getDy();

			//Blank image on the current Ghost position
			SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);

			//Start respawn timer
			SDL_TimerID ghostRespawnTimer = SDL_AddTimer(10000, callBackFunctionThree, NULL);
		}

		//Throw correct ghost off map for 10 seconds start respawn timer
		if(CollisionDetection::ghostThree)
		{
			ghostObject3.setDx(2000);
			ghostObject3.setDy(2000);

			blitRect.x = ghostObject3.getDx();
			blitRect.y = ghostObject3.getDy();

			//Blank image on the current Ghost position
			SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);

			//Start respawn timer
			SDL_TimerID ghostRespawnTimer = SDL_AddTimer(10000, callBackFunctionThree, NULL);
		}

		//Throw correct ghost off map for 10 seconds start respawn timer
		if(CollisionDetection::ghostFour)
		{
			ghostObject4.setDx(2000);
			ghostObject4.setDy(2000);

			blitRect.x = ghostObject4.getDx();
			blitRect.y = ghostObject4.getDy();

			//Blank image on the current Ghost position
			SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);

			//Start respawn timer
			SDL_TimerID ghostRespawnTimer = SDL_AddTimer(10000, callBackFunctionThree, NULL);
		}

	}

	//Respawn ghost 1
	if(CollisionDetection::ghostOne && respawnGhost)
	{
		CollisionDetection::ghostOne = false;
		CollisionDetection::helpFlag = true;
		respawnGhost = false;
		ghostRespawnTimerStarted = false;

		//Respawn ghost
		ghostObject.setDx(ghostObject.getX());
		ghostObject.setDy(ghostObject.getY());
	}

	//Respawn ghost 2
	if(CollisionDetection::ghostTwo && respawnGhost)
	{
		CollisionDetection::ghostTwo = false;
		CollisionDetection::helpFlag = true;
		respawnGhost = false;
		ghostRespawnTimerStarted = false;

		//Respawn ghost
		ghostObject2.setDx(ghostObject2.getX());
		ghostObject2.setDy(ghostObject2.getY());
	}

	//Respawn ghost 3
	if(CollisionDetection::ghostThree && respawnGhost)
	{
		CollisionDetection::ghostThree = false;
		CollisionDetection::helpFlag = true;
		respawnGhost = false;
		ghostRespawnTimerStarted = false;

		//Respawn ghost
		ghostObject3.setDx(ghostObject3.getX());
		ghostObject3.setDy(ghostObject3.getY());
	}

	//Respawn ghost 4
	if(CollisionDetection::ghostFour && respawnGhost)
	{
		CollisionDetection::ghostFour = false;
		CollisionDetection::helpFlag = true;
		respawnGhost = false;
		ghostRespawnTimerStarted = false;

		//Respawn ghost
		ghostObject4.setDx(ghostObject4.getX());
		ghostObject4.setDy(ghostObject4.getY());
	}

	//Reset death animation after Pacman 1 is dead
	if(deathAnimationCounterOne >= 180 && pacmanObject.getPacmanDead() == true)
	{
		if(pacmanObject.getPlayer() == 1)
		{
			deathAnimationCounterOne = 0;
			pacmanObject.setPacmanDead(false);
			pacmanObject.setDx(pacmanObject.getX());
			pacmanObject.setDy(pacmanObject.getY());

			if(pacmanObject.getPacmanDeadFinal() == true)
			{
				//Bye bye pacman 1, remove off the map
				pacmanObject.setDx(2000);
				pacmanObject.setDy(2000);
			}

		}
	}

	//Reset death animation after Pacman 2 is dead
	if(deathAnimationCounterTwo >= 180 && pacmanObject.getPacmanDead() == true)
	{
		
		if(pacmanObject.getPlayer() == 2)
		{
			deathAnimationCounterTwo = 0;
			pacmanObject.setPacmanDead(false);
			pacmanObject.setDx(pacmanObject.getX());
			pacmanObject.setDy(pacmanObject.getY());

			if(pacmanObject.getPacmanDeadFinal() == true)
			{
				//Bye bye pacman 2, remove off the map
				pacmanObject.setDx(2000);
				pacmanObject.setDy(2000);
			}
		}
	}
}

//This function switches to the next map in the array (map paths are stored in a char array; mapPathArray[10]) and does necessary blitting (such as life/score panels etc.)
void Map::nextMap(char * mapPathArray[], char mapGameArray[][40], Pacman &pacmanObject1, Pacman &pacmanObject2, Ghost &ghostObject, Ghost &ghostObject2, Ghost &ghostObject3, Ghost &ghostObject4, bool multiplayer,
				 SDL_Surface * screen, SDL_Surface * wallImage, SDL_Surface * pelletsItemsImage, SDL_Surface * scoreLifePlayerOne, SDL_Rect &scoreLifePlayerOneRect, SDL_Surface * lifePlayerOne, SDL_Rect &lifePlayerOneRect, 
				 SDL_Surface * scoreLifePlayerTwo, SDL_Rect &scoreLifePlayerTwoRect, SDL_Surface * lifePlayerTwo, SDL_Rect &lifePlayerTwoRect)
{
	//Next level
	Map::mapLevel++;

	//Reset fields
	pacmanObject1.setPowerPellet(false);
	pacmanObject2.setPowerPellet(false);
	pacmanObject1.setPacmanDead(false);
	pacmanObject2.setPacmanDead(false);
	pacmanObject1.setPacmanDeadFinal(false);
	pacmanObject2.setPacmanDeadFinal(false);
	pacmanObject1.setLife(3);
	pacmanObject2.setLife(3);
	Map::deathAnimationCounterOne = 0;
	Map::deathAnimationCounterTwo = 0;

	//Set background colour to black					
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
			
	//Load new map
	loadMap(mapPathArray, mapGameArray, pacmanObject1, pacmanObject2, ghostObject, ghostObject2, ghostObject3, ghostObject4, multiplayer);
			
	//Draw new map on SDL					
	drawMap(screen, wallImage, pelletsItemsImage, mapGameArray);

	//Position player 1 life icons
	lifePlayerOneRect.x = 60;
	lifePlayerOneRect.y = 573;
	lifePlayerOneRect.w = lifePlayerOne->w;
	lifePlayerOneRect.h = lifePlayerOne->h;

	//Blit player 1 score/life panel
	SDL_BlitSurface(scoreLifePlayerOne, NULL, screen, &scoreLifePlayerOneRect);

	//Blit player 1 life icons
	SDL_BlitSurface(lifePlayerOne, NULL, screen, &lifePlayerOneRect);

	if(multiplayer)
	{
		//Position player 2 life icons
		lifePlayerTwoRect.x = 620;
		lifePlayerTwoRect.y = 573;
		lifePlayerTwoRect.w = lifePlayerTwo->w;
		lifePlayerTwoRect.h = lifePlayerTwo->h;

		//Blit player 2 score/life panel
		SDL_BlitSurface(scoreLifePlayerTwo, NULL, screen, &scoreLifePlayerTwoRect);

		//Blit player 2 life icons
		SDL_BlitSurface(lifePlayerTwo, NULL, screen, &lifePlayerTwoRect);
	}
}

//This function resets all item counts in map (pellets, power pellets, bonus items) and does a count up of all current items.
void Map::countMapItems(char mapGameArray[][40], int &pelletsCount, int &powerPelletsCount, int &bonusItemOneCount, int &bonusItemTwoCount)
{
	//Reset counts
	pelletsCount = 0;
	powerPelletsCount = 0;
	bonusItemOneCount = 0;
	bonusItemTwoCount = 0;

	//Count pellets, power pellets and bonus items in map
	for(int i = 0; i < 40; i++)
	{ 
		for(int j = 0; j < 30; j++)
		{
			if(mapGameArray[j][i] == '2')
				pelletsCount++;

			if(mapGameArray[j][i] == '3')
				powerPelletsCount++;
			
			if(mapGameArray[j][i] == '4')
				bonusItemOneCount++;
			
			if(mapGameArray[j][i] == '5')
				bonusItemTwoCount++;
		}
	}
}

//This function calls the pathVectorTesting class to make Ghosts move in clean routes in map. This function then calculates the nearest distance to a Pacman object (using Pythagoras) and calls up the ghostAIDecisionMaking function to move Ghosts.
void Map::ghostAICalculation(Pacman &pacmanObject1, Pacman &pacmanObject2, Ghost &ghostObject, SDL_Surface * screen, SDL_Surface * pelletsItemsImage, 
						  SDL_Surface * ghostImage, SDL_Rect &blitRect, SDL_Rect &imgRect, char mapGameArray[][40], CollisionDetection &collisionDetection, bool &multiplayer, 
						  PacmanGhostBlitting &pacmanGhostBlitting, Sound sound)
{
	//Check vector/path of ghosts objects, we want a clean movement route in which ghosts can move
	pathVectorTesting.checkGhostVector(ghostObject);

	/*SINGLEPLAYER AI*/

	if(!multiplayer)
	{
		//Calculate difference X, Y positions: Ghost, Pacman 1
		int differencePacmanOneGhostX = abs(pacmanObject1.getArrayPosX() - ghostObject.getArrayPosX());
		int differencePacmanOneGhostY = abs(pacmanObject1.getArrayPosY() - ghostObject.getArrayPosY());

		//Pythagoras Pacman 1 Ghost
		int pythPacmanOneGhost = sqrt(pow((double)differencePacmanOneGhostX, 2) + pow((double)differencePacmanOneGhostY, 2));

		//Hunt Pacman 1!
		ghostAIDecisionMaking(pacmanObject1, ghostObject, collisionDetection, differencePacmanOneGhostX, differencePacmanOneGhostY, mapGameArray, sound);
	}

	/*MULTIPLAYER AI*/

	if(multiplayer)
	{
		//Calculate difference X, Y positions: Ghost, Pacman 1
		int differencePacmanOneGhostX = abs(pacmanObject1.getArrayPosX() - ghostObject.getArrayPosX());
		int differencePacmanOneGhostY = abs(pacmanObject1.getArrayPosY() - ghostObject.getArrayPosY());

		//Calculate difference X, Y positions: Ghost, Pacman 2
		int differencePacmanTwoGhostX = abs(pacmanObject2.getArrayPosX() - ghostObject.getArrayPosX());
		int differencePacmanTwoGhostY = abs(pacmanObject2.getArrayPosY() - ghostObject.getArrayPosY());

		//Pythagoras Pacman 1 Ghost
		int pythPacmanOneGhost = sqrt(pow((double)differencePacmanOneGhostX, 2) + pow((double)differencePacmanOneGhostY, 2));

		//Pythagoras Pacman 2 Ghost
		int pythPacmanTwoGhost = sqrt(pow((double)differencePacmanTwoGhostX, 2) + pow((double)differencePacmanTwoGhostY, 2));

		//If Pacman 1 is closest, hunt Pacman 1!
		if(pythPacmanOneGhost < pythPacmanTwoGhost)
			ghostAIDecisionMaking(pacmanObject1, ghostObject, collisionDetection, differencePacmanOneGhostX, differencePacmanOneGhostY, mapGameArray, sound);
		
		//If Pacman 2 is closest, hunt Pacman 2!
		else
			ghostAIDecisionMaking(pacmanObject2, ghostObject, collisionDetection, differencePacmanTwoGhostX, differencePacmanTwoGhostY, mapGameArray, sound);
	}

}

//This function is for A.I. decision making. Basically this function chooses the nearest calculated distance to a Pacman object and sets Ghosts' vectors appropriately. Ghosts then move accordingly to the Pacman objects.
void Map::ghostAIDecisionMaking(Pacman &pacmanObject, Ghost &ghostObject, CollisionDetection &collisionDetection, int differencePacmanGhostX, int differencePacmanGhostY, char mapGameArray[][40],
								Sound &sound)
{

	//Increment Ghost movement sound delay integer
	ghostSoundDelay++;

	//Generate a random index number
	randomIndex = rand() % 2;

	//If ghost doesn't collide with wall, play ghost movement sound and move ghost 
	if(!collisionDetection.checkGhostCollision(ghostObject, mapGameArray))
	{					
		if(ghostSoundDelay % 300 == 0)
		{
			if(sound.getSound() == true)
				//Play Ghost move sound
				sound.playSoundGhostMove();
		}
				
		//Ghost movements
		if(ghostObject.getPosVector() == 'N')
			ghostObject.setDy(ghostObject.getDy() - 1);

		if(ghostObject.getPosVector() == 'S')
			ghostObject.setDy(ghostObject.getDy() + 1);
		
		if(ghostObject.getPosVector() == 'W')
			ghostObject.setDx(ghostObject.getDx() - 1);

		if(ghostObject.getPosVector() == 'E')
			ghostObject.setDx(ghostObject.getDx() + 1);
	
	
	}
	//If ghost collides with wall, set a new random ghost vector
	if(collisionDetection.checkGhostCollision(ghostObject, mapGameArray))
	{
		if(ghostObject.getPosVector() == 'N')
			ghostObject.setNextVector(randomVectorTwo[randomIndex]);
		
		else if(ghostObject.getPosVector() == 'S')
			ghostObject.setNextVector(randomVectorTwo[randomIndex]);
		
		else if(ghostObject.getPosVector() == 'W')
			ghostObject.setNextVector(randomVectorOne[randomIndex]);
		
		else if(ghostObject.getPosVector() == 'E')
			ghostObject.setNextVector(randomVectorOne[randomIndex]);

	}
	//If Pacman is closest to ghost on the X-axis, test the difference of X positions and set appropriate ghost vector  
	if(differencePacmanGhostX < differencePacmanGhostY)
	{
		if(pacmanObject.getArrayPosX() - ghostObject.getArrayPosX() < 0)
		ghostObject.setNextVector('W');

		else if (pacmanObject.getArrayPosX() - ghostObject.getArrayPosX() > 0)
		ghostObject.setNextVector('E');

		else
		{
			if(pacmanObject.getArrayPosY() > ghostObject.getArrayPosY())
				ghostObject.setNextVector('S');

		else
			ghostObject.setNextVector('N');
		}
	}	
	//If Pacman is closest to ghost on the Y-axis, test the difference of Y positions and set appropriate ghost vector  
	else if(differencePacmanGhostX > differencePacmanGhostY)
	{
		if(pacmanObject.getArrayPosY() - ghostObject.getArrayPosY() < 0)
			ghostObject.setNextVector('N');

		else if (pacmanObject.getArrayPosY() - ghostObject.getArrayPosY() > 0)
			ghostObject.setNextVector('S');	

		else
		{
			if(pacmanObject.getArrayPosX() > ghostObject.getArrayPosX())
				ghostObject.setNextVector('E');
		
			else
				ghostObject.setNextVector('W');
		}
	}
	if(collisionDetection.checkGhostCollision(ghostObject, mapGameArray))
	{
		if(ghostObject.getPosVector() == 'N')
		{
			ghostObject.setNextVector(randomVectorTwo[randomIndex]);
			return;
		}
		
		else if(ghostObject.getPosVector() == 'S')
		{
			ghostObject.setNextVector(randomVectorTwo[randomIndex]);
			return;
		}
		
		else if(ghostObject.getPosVector() == 'W')
		{
			ghostObject.setNextVector(randomVectorOne[randomIndex]);
			return;
		}
		
		else if(ghostObject.getPosVector() == 'E')
		{
			ghostObject.setNextVector(randomVectorOne[randomIndex]);
			return;
		}
	}
}
	


//This function is a special callback function for SDL_AddTimer. It manages Pacman 1 death animation.
Uint32 Map::callBackFunctionOne(Uint32 interval, void * param)
{	
	callBackFunctionCounterOne ++;

	deathAnimationCounterOne += 20;

	if(callBackFunctionCounterOne > 8)
	{
		callBackFunctionCounterOne = 0;
		return 0;		
	}
	
	return interval;
}

//This function is a special callback function for SDL_AddTimer. It manages Pacman 2 death animation.
Uint32 Map::callBackFunctionTwo(Uint32 interval, void * param)
{	
	callBackFunctionCounterTwo ++;

	deathAnimationCounterTwo += 20;

	if(callBackFunctionCounterTwo > 8)
	{
		callBackFunctionCounterTwo = 0;
		return 0;		
	}
	
	return interval;
}

//This function is a special callback function for SDL_AddTimer. It manages Ghost respawns.
Uint32 Map::callBackFunctionThree(Uint32 interval, void * param)
{	
	respawnGhost = true;
	
	return 0;
}

//Get map level function
int Map::getMapLevel()
{
	return Map::mapLevel;
}

//Set map level function
void Map::setMapLevel(int level)
{
	mapLevel = level;
}
