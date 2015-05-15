/***************************************************************************************************************************************
****************************************************************************************************************************************

This is the game class. *Only* in-game events are directly handled here (including score/life panel of players). The game class constantly 
calls up the map class to update the maps of the game (and to move ghosts A.I.). The class also handles a special situation in the game; 
basicaly when both Pacman objects collide with each other (I.E. a Pacman-Pacman collision). In-game key events are also handled here. 
By in-game we mean when a player is playing in a map in real time, thus we exclude game menus (these are handled in their own class).

****************************************************************************************************************************************
***************************************************************************************************************************************/

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <fstream>
#include "game.h"
#include "map.h"
#include "menugraphics.h"
#include "collisiondetection.h"
#include "pacmanghostblitting.h"
#include "sound.h"



//Initialize screen surface
SDL_Surface * screen = SDL_SetVideoMode(800, 600, 32, SDL_FULLSCREEN);

/*In-game surfaces*/
SDL_Surface * pacmanImage = SDL_LoadBMP("../gfx/game/pacman.bmp");
SDL_Surface * pacmanImage2 = SDL_LoadBMP("../gfx/game/pacman2.bmp");
SDL_Surface * deadPacmanImage = SDL_LoadBMP("../gfx/game/deadpacman.bmp");
SDL_Surface * deadPacmanImage2 = SDL_LoadBMP("../gfx/game/deadpacman2.bmp");
SDL_Surface * ghostImage;
SDL_Surface * wallImage;
SDL_Surface * pelletsItemsImage;
SDL_Surface * blankImage;
SDL_Surface * scoreLifePlayerOne;
SDL_Surface * scoreLifePlayerTwo;
SDL_Surface * lifePlayerOne;
SDL_Surface * lifePlayerTwo;
SDL_Surface * gameOverImage;
SDL_Surface * deadImage;
SDL_Surface * continueImage;
SDL_Surface * highScoreImage1;
SDL_Surface * highScoreImage2;
SDL_Surface * scorePlayerOne;
SDL_Surface * scorePlayerTwo;
SDL_Surface * powerPelletPacmanImage;
SDL_Surface * levelImage;
SDL_Surface * levelNumber;

/*High score board labels*/
SDL_Surface * playerOneLabel;
SDL_Surface * playerTwoLabel;

/*Blank image rects (dummies used to cover previous Pacman position)*/
SDL_Rect blitRect;
SDL_Rect imgRect;

/*In-game rects (score/life panel)*/
SDL_Rect scoreLifePlayerOneRect;
SDL_Rect scoreLifePlayerTwoRect;
SDL_Rect lifePlayerOneRect;
SDL_Rect lifePlayerTwoRect;
SDL_Rect deadImageRect;
SDL_Rect continueImageRect;
SDL_Rect scorePlayerOneRect;
SDL_Rect scorePlayerTwoRect;
SDL_Rect levelImageRect;
SDL_Rect levelNumberRect;

/*High score board rects*/
SDL_Rect playerOneLabelRect;
SDL_Rect playerTwoLabelRect;

/*Objects*/
MenuGraphics menuGraphics;
Map map;
Sound sound;
CollisionDetection collisionDetection;
PacmanGhostBlitting pacmanGhostBlitting;
Pacman pacmanObject1(1);	//Player 1
Pacman pacmanObject2(2);	//Player 2
Ghost ghostObject1(1);		//Ghost 1
Ghost ghostObject2(2);		//Ghost 2
Ghost ghostObject3(3);		//Ghost 3
Ghost ghostObject4(4);		//Ghost 4

//SDL_TTF score font
TTF_Font * font;

/*SDL_TTF foreground colors*/
SDL_Color YELLOW = {254, 241, 0, 0};
SDL_Color GREEN = {168, 230, 29, 0};

//SDL_TTF background color
SDL_Color BLACK = {0, 0, 0};

//Buffer for SDL_TTF (integer -> char)
char buffer[100] = {NULL};

//Key event
SDL_Event keyevent;

//Key
unsigned char * key;

//Initialize multiplayer flag
bool Game::multiplayer = false;

//Initialize maps
static char * mapPathArray[10] = {"..\\maps\\map01.txt", "..\\maps\\map02.txt", "..\\maps\\map03.txt", "..\\maps\\map04.txt", "..\\maps\\map05.txt",
								"..\\maps\\map06.txt", "..\\maps\\map07.txt", "..\\maps\\map08.txt", "..\\maps\\map09.txt", "..\\maps\\map10.txt"};
//Initialize map array
static char mapGameArray[30][40];


/*Item counters*/
int pelletsCount;
int powerPelletsCount;
int bonusItemOneCount;
int bonusItemTwoCount;

//Default constructor
Game::Game()
{
	//Remove mouse cursor
	SDL_ShowCursor(0);

	//Initialize all SDL controls
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
		exit(1);

	//Initialize SDL_mixer (sound)
	if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096) == -1)
		exit(1);

	//Initialize SDL_TTF (text)
	if (TTF_Init() == -1) 
		exit(1);

	//Allocate sound channels
	Mix_AllocateChannels(6);

	//Load sound files
	sound.loadSounds();

	//Load SDL_TTF font
	font = TTF_OpenFont("../fonts/bellb.ttf", 18);

	//Load starting graphic objects (minus Pacman object)
	ghostImage = SDL_LoadBMP("../gfx/game/ghost.bmp");
	wallImage = SDL_LoadBMP("../gfx/game/wall.bmp");
	pelletsItemsImage = SDL_LoadBMP("../gfx/game/pelletsitems.bmp");
	blankImage = SDL_LoadBMP("../gfx/game/blank.bmp");
	powerPelletPacmanImage = SDL_LoadBMP("../gfx/game/powerpelletpacman.bmp");

	//Load score/life panel of players
	scoreLifePlayerOne = SDL_LoadBMP("../gfx/game/scorelifeplayer1.bmp");
	scoreLifePlayerTwo = SDL_LoadBMP("../gfx/game/scorelifeplayer2.bmp");
	lifePlayerOne = SDL_LoadBMP("../gfx/game/lifeplayer1.bmp");
	lifePlayerTwo = SDL_LoadBMP("../gfx/game/lifeplayer2.bmp");
	levelImage =  SDL_LoadBMP("../gfx/game/level.bmp");

	//Load game over, dead icon and continue screens
	gameOverImage = SDL_LoadBMP("../gfx/menu/gameover.bmp");
	deadImage = SDL_LoadBMP("../gfx/game/dead.bmp");
	continueImage = SDL_LoadBMP("../gfx/game/continue.bmp");

	//Load high score screens
	highScoreImage1 = SDL_LoadBMP("../gfx/game/highscore1.bmp");
    highScoreImage2 = SDL_LoadBMP("../gfx/game/highscore2.bmp");
	playerOneLabel = SDL_LoadBMP("../gfx/game/player1label.bmp");
	playerTwoLabel = SDL_LoadBMP("../gfx/game/player2label.bmp");

	//Position player 1 score/life panel
	scoreLifePlayerOneRect.x = 10;
	scoreLifePlayerOneRect.y = 550;
	scoreLifePlayerOneRect.w = scoreLifePlayerOne->w;
	scoreLifePlayerOneRect.h = scoreLifePlayerOne->h;
	
	lifePlayerOneRect.x = 60;
	lifePlayerOneRect.y = 573;
	lifePlayerOneRect.w = lifePlayerOne->w;
	lifePlayerOneRect.h = lifePlayerOne->h;

	//Position player 2 score/life panel
	scoreLifePlayerTwoRect.x = 570;
	scoreLifePlayerTwoRect.y = 550;
	scoreLifePlayerTwoRect.w = scoreLifePlayerTwo->w;
	scoreLifePlayerTwoRect.h = scoreLifePlayerTwo->h;
	
	lifePlayerTwoRect.x = 620;
	lifePlayerTwoRect.y = 573;
	lifePlayerTwoRect.w = lifePlayerTwo->w;
	lifePlayerTwoRect.h = lifePlayerTwo->h;

	//Position player 1 and player 2 score rects in life/score panel (width and height of score are dynamic, they are constantly changed in the run function)
	scorePlayerOneRect.x = 160;
	scorePlayerOneRect.y = 553;

	scorePlayerTwoRect.x = 723;
	scorePlayerTwoRect.y = 552;

	//Position dead icon (x position is dynamic, it is changed in the map class)
	deadImageRect.y = 573;
	deadImageRect.w = deadImage->w;
	deadImageRect.h = deadImage->h;

	//Position continue image
	continueImageRect.x = 240;
	continueImageRect.y = 563;
	continueImageRect.w = continueImage->w;
	continueImageRect.h = continueImage->h;

	//Position level number rect (width and hight of level number is dynamic, it is changed when a new map is loaded) 
	levelNumberRect.x = 410;
	levelNumberRect.y = 546;

	//Position level image rect
	levelImageRect.x = 330;
	levelImageRect.y = 545;
	levelImageRect.w = levelImage->w;
	levelImageRect.h = levelImage->h;

	//Position player 1 and player 2 labels in high score board
	playerOneLabelRect.w = playerOneLabel->w;
	playerOneLabelRect.h = playerOneLabel->h;

	playerTwoLabelRect.w = playerTwoLabel->w;
	playerTwoLabelRect.h = playerTwoLabel->h;

	//Make color transparency
	SDL_SetColorKey(ghostImage, SDL_SRCCOLORKEY, 0xff00ff);
	SDL_SetColorKey(pelletsItemsImage, SDL_SRCCOLORKEY, 0xff00ff);
	SDL_SetColorKey(gameOverImage, SDL_SRCCOLORKEY, 0xff00ff);
	SDL_SetColorKey(pacmanImage, SDL_SRCCOLORKEY, 0xff00ff);
	SDL_SetColorKey(pacmanImage2, SDL_SRCCOLORKEY, 0xff00ff);
	SDL_SetColorKey(powerPelletPacmanImage, SDL_SRCCOLORKEY, 0xff00ff);
	SDL_SetColorKey(deadPacmanImage, SDL_SRCCOLORKEY, 0xff00ff);
	SDL_SetColorKey(deadPacmanImage2, SDL_SRCCOLORKEY, 0xff00ff);

	//Initialize item counters
	pelletsCount = 0;
	powerPelletsCount = 0;
	bonusItemOneCount = 0;
	bonusItemTwoCount = 0;
}


//Run function. This function starts the game.
void Game::run()
{
	//Draw main menu
	menuGraphics.drawMenu(screen);

    //Test keys in main menu and process events
	menuGraphics.testKeys(screen, map, mapPathArray, mapGameArray, pacmanObject1, pacmanObject2, ghostObject1, ghostObject2, ghostObject3, ghostObject4, 
						  wallImage, pelletsItemsImage, multiplayer, sound);

	//Blit player 1 score/life panel
	SDL_BlitSurface(scoreLifePlayerOne, NULL, screen, &scoreLifePlayerOneRect);

	//Blit player 1 life icons
	SDL_BlitSurface(lifePlayerOne, NULL, screen, &lifePlayerOneRect);

	if(multiplayer)
	{
		//Blit player 2 score/life panel
		SDL_BlitSurface(scoreLifePlayerTwo, NULL, screen, &scoreLifePlayerTwoRect);

		//Blit player 2 life icons
		SDL_BlitSurface(lifePlayerTwo, NULL, screen, &lifePlayerTwoRect);
	}
	
	bool quit = false;

	//In-game
	while(!quit)
	{
		//Set a delay so that the game doesn't process too fast (the better the PC, the faster the game processes)
		if(!multiplayer)
			SDL_Delay(5);

		else
			SDL_Delay(6);

		//Convert map level number to char
		sprintf(buffer, "%d", (map.getMapLevel()) + 1);

		//Render text surface
		levelNumber = TTF_RenderText_Shaded(font, buffer, YELLOW, BLACK);

		//Assign new width and height of level number
		levelNumberRect.w = levelNumber->w;
		levelNumberRect.h = levelNumber->h;

		//Blit level image
		SDL_BlitSurface(levelImage, NULL, screen, &levelImageRect);

		//Blit level number
		SDL_BlitSurface(levelNumber, NULL, screen, &levelNumberRect);

		//Free surface to avoid memory leak
		SDL_FreeSurface(levelNumber);

		//Increment Ghost movement delay integer
		Map::ghostMovementDelay++;	

		//Blit blanks for pacman 1 & pacman 2
		pacmanGhostBlitting.blitBlanks(blankImage, screen, pacmanObject1, pacmanObject2, blitRect, imgRect, multiplayer);
		
		//Slow down ghost speed to 50 % of max
		if(Map::ghostMovementDelay % 2 == 0)
		{
			//Start ghosts AI movement in map
			map.ghostAICalculation(pacmanObject1, pacmanObject2, ghostObject1, screen, pelletsItemsImage, 
									  ghostImage, blitRect, imgRect, mapGameArray, collisionDetection , multiplayer, pacmanGhostBlitting, sound);
		
			map.ghostAICalculation(pacmanObject1, pacmanObject2, ghostObject2, screen, pelletsItemsImage, 
									  ghostImage, blitRect, imgRect, mapGameArray, collisionDetection , multiplayer, pacmanGhostBlitting, sound);

			map.ghostAICalculation(pacmanObject1, pacmanObject2, ghostObject3, screen, pelletsItemsImage, 
									  ghostImage, blitRect, imgRect, mapGameArray, collisionDetection , multiplayer, pacmanGhostBlitting, sound);

			map.ghostAICalculation(pacmanObject1, pacmanObject2, ghostObject4, screen, pelletsItemsImage, 
									  ghostImage, blitRect, imgRect, mapGameArray, collisionDetection , multiplayer, pacmanGhostBlitting, sound);
		}
		
		//Blit ghosts
		pacmanGhostBlitting.blitGhost(ghostObject1, screen, ghostImage, blitRect, imgRect, mapGameArray, pelletsItemsImage);
		pacmanGhostBlitting.blitGhost(ghostObject2, screen, ghostImage, blitRect, imgRect, mapGameArray, pelletsItemsImage);
		pacmanGhostBlitting.blitGhost(ghostObject3, screen, ghostImage, blitRect, imgRect, mapGameArray, pelletsItemsImage);
		pacmanGhostBlitting.blitGhost(ghostObject4, screen, ghostImage, blitRect, imgRect, mapGameArray, pelletsItemsImage);

		if(!multiplayer)
		{
			//Convert player 1 score integer to char
			sprintf(buffer, "%d", pacmanObject1.getScore());

			//Render text surface
			scorePlayerOne = TTF_RenderText_Shaded(font, buffer, YELLOW, BLACK);

			//Assign new width and height of score
			scorePlayerOneRect.w = scorePlayerOne->w;
			scorePlayerOneRect.h = scorePlayerOne->h;
			
			//Get current pacman position
			blitRect.x = pacmanObject1.getDx();
			blitRect.y = pacmanObject1.getDy();

			//Update the map with player 1
			map.updateMap(pacmanObject1, ghostObject1, ghostObject2, ghostObject3, ghostObject4, screen, pacmanImage, blankImage, 
				deadPacmanImage, mapGameArray, lifePlayerOne, lifePlayerTwo, lifePlayerOneRect, lifePlayerTwoRect, deadImage, deadImageRect, 
				multiplayer, mapPathArray, wallImage, scoreLifePlayerOne, scoreLifePlayerTwo, scoreLifePlayerOneRect, scoreLifePlayerTwoRect, 
				collisionDetection, pacmanGhostBlitting, powerPelletPacmanImage, pelletsItemsImage, sound, imgRect, blitRect);

			//Count items in map
			map.countMapItems(mapGameArray, pelletsCount, powerPelletsCount, bonusItemOneCount, bonusItemTwoCount);

			//Check if all items in map are eaten
			if(pelletsCount == 0 && powerPelletsCount == 0 && bonusItemOneCount == 0 && bonusItemTwoCount == 0)
			{
				//Game over
				if(map.getMapLevel() >= 9)
				{
					//Show singleplayer score
					pacmanGhostBlitting.blitFinalScoreSingleplayer(screen, scorePlayerOne, scorePlayerTwo, scorePlayerOneRect, scorePlayerTwoRect, pacmanObject1, pacmanObject2, 
														playerOneLabel, playerTwoLabel, playerOneLabelRect, playerTwoLabelRect, highScoreImage1, highScoreImage2,
														continueImage, continueImageRect, gameOverImage);
				}

				else
				{
					//Load next map
					map.nextMap(mapPathArray, mapGameArray, pacmanObject1, pacmanObject2, ghostObject1, ghostObject2, ghostObject3, ghostObject4, multiplayer,
								screen, wallImage, pelletsItemsImage,  scoreLifePlayerOne, scoreLifePlayerOneRect, lifePlayerOne, lifePlayerOneRect, 
								 scoreLifePlayerTwo, scoreLifePlayerTwoRect, lifePlayerTwo, lifePlayerTwoRect);
				}
			}

			//If Pacman is dead, show singleplayer score
			if(pacmanObject1.getPacmanDeadFinal() == true)
					 pacmanGhostBlitting.blitFinalScoreSingleplayer(screen, scorePlayerOne, scorePlayerTwo, scorePlayerOneRect, scorePlayerTwoRect, pacmanObject1, pacmanObject2, 
														playerOneLabel, playerTwoLabel, playerOneLabelRect, playerTwoLabelRect, highScoreImage1, highScoreImage2,
														continueImage, continueImageRect, gameOverImage);

			//Blit text surface
			SDL_BlitSurface(scorePlayerOne, NULL, screen, &scorePlayerOneRect);
			
			//Free surface to avoid memory leak
			SDL_FreeSurface(scorePlayerOne);
		}

		//Update the map with multiplayer
		if(multiplayer)
		{
			//Convert player 1 score integer to char
			sprintf(buffer, "%d", pacmanObject1.getScore());

			//Render text surface
			scorePlayerOne = TTF_RenderText_Shaded(font, buffer, YELLOW, BLACK);

			//Assign new width and height of score
			scorePlayerOneRect.w = scorePlayerOne->w;
			scorePlayerOneRect.h = scorePlayerOne->h;

			//Convert player 2 score integer to char
			sprintf(buffer, "%d", pacmanObject2.getScore());

			//Render text surface
			scorePlayerTwo = TTF_RenderText_Shaded(font, buffer, GREEN, BLACK);

			//Assign new width and height of score
			scorePlayerTwoRect.w = scorePlayerTwo->w;
			scorePlayerTwoRect.h = scorePlayerTwo->h;

			//Update the map with player 1
			map.updateMap(pacmanObject1, ghostObject1, ghostObject2, ghostObject3, ghostObject4, screen, pacmanImage, blankImage, 
				deadPacmanImage, mapGameArray, lifePlayerOne, lifePlayerTwo, lifePlayerOneRect, lifePlayerTwoRect, deadImage, deadImageRect, 
				multiplayer, mapPathArray, wallImage, scoreLifePlayerOne, scoreLifePlayerTwo, scoreLifePlayerOneRect, scoreLifePlayerTwoRect, 
				collisionDetection, pacmanGhostBlitting, powerPelletPacmanImage, pelletsItemsImage, sound, imgRect, blitRect);

			//Update the map with player 2
			map.updateMap(pacmanObject2, ghostObject1, ghostObject2, ghostObject3, ghostObject4, screen, pacmanImage2, blankImage, 
							deadPacmanImage2, mapGameArray, lifePlayerOne, lifePlayerTwo, lifePlayerOneRect, lifePlayerTwoRect, deadImage, deadImageRect, 
							multiplayer, mapPathArray, wallImage, scoreLifePlayerOne, scoreLifePlayerTwo, scoreLifePlayerOneRect, scoreLifePlayerTwoRect, 
							collisionDetection, pacmanGhostBlitting, powerPelletPacmanImage, pelletsItemsImage, sound, imgRect, blitRect);

			//Count items in map
			map.countMapItems(mapGameArray, pelletsCount, powerPelletsCount, bonusItemOneCount, bonusItemTwoCount);

			//Check if all items in map are eaten
			if(pelletsCount == 0 && powerPelletsCount == 0 && bonusItemOneCount == 0 && bonusItemTwoCount == 0)
			{
				//Game over
				if(map.getMapLevel() >= 9)
				{
					//Show multiplayer score
					pacmanGhostBlitting.blitFinalScoreMultiplayer(screen, scorePlayerOne, scorePlayerTwo, scorePlayerOneRect, scorePlayerTwoRect, pacmanObject1, pacmanObject2, 
													playerOneLabel, playerTwoLabel, playerOneLabelRect, playerTwoLabelRect, highScoreImage1, highScoreImage2,
													continueImage, continueImageRect, gameOverImage);
				}

				else
				{
					//Load next map
					map.nextMap(mapPathArray, mapGameArray, pacmanObject1, pacmanObject2, ghostObject1, ghostObject2, ghostObject3, ghostObject4, multiplayer,
								screen, wallImage, pelletsItemsImage,  scoreLifePlayerOne, scoreLifePlayerOneRect, lifePlayerOne, lifePlayerOneRect, 
								 scoreLifePlayerTwo, scoreLifePlayerTwoRect, lifePlayerTwo, lifePlayerTwoRect);
				}
			}

			//If both Pacmen are dead, show multiplayer score
			if(pacmanObject1.getPacmanDeadFinal() == true && pacmanObject2.getPacmanDeadFinal() == true)
				pacmanGhostBlitting.blitFinalScoreMultiplayer(screen, scorePlayerOne, scorePlayerTwo, scorePlayerOneRect, scorePlayerTwoRect, pacmanObject1, pacmanObject2, 
													playerOneLabel, playerTwoLabel, playerOneLabelRect, playerTwoLabelRect, highScoreImage1, highScoreImage2,
													continueImage, continueImageRect, gameOverImage);
				

			//Blit text surfaces
			SDL_BlitSurface(scorePlayerOne, NULL, screen, &scorePlayerOneRect);
			SDL_BlitSurface(scorePlayerTwo, NULL, screen, &scorePlayerTwoRect);
			
			//Free surfaces to avoid memory leak
			SDL_FreeSurface(scorePlayerOne);
			SDL_FreeSurface(scorePlayerTwo);

			//Check if we have a special collision; Pacman-Pacman
			if(collisionDetection.checkPacmanPacmanCollision(pacmanObject1, pacmanObject2))
			{
				imgRect.x = 0;
				imgRect.y = 0;

				if(pacmanObject1.getPacmanDead() == true)
				{
					//Play pacman die sound
					sound.playSoundPacmanDie();

					//Get current Pacman 1 position
					blitRect.x = pacmanObject1.getDx();
					blitRect.y = pacmanObject1.getDy();

					//Blank image on the current Pacman 1 position
					SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);

					pacmanObject1.setPacmanDead(false);
					pacmanObject1.setDx(pacmanObject1.getX());
					pacmanObject1.setDy(pacmanObject1.getY());
					
					//Definitely dead, all 3 lives lost
					if(pacmanObject1.getPacmanDeadFinal() == true)
					{
						//Bye bye Pacman 1, remove off map
						pacmanObject1.setDx(2000);
						pacmanObject1.setDy(2000);
					}
					
				}

				else if(pacmanObject2.getPacmanDead() == true)
				{
					//Play pacman die sound
					sound.playSoundPacmanDie();

					//Get current Pacman 2 position
					blitRect.x = pacmanObject2.getDx();
					blitRect.y = pacmanObject2.getDy();

					//Blank image on the current Pacman 2 position
					SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);

					pacmanObject2.setPacmanDead(false);
					pacmanObject2.setDx(pacmanObject2.getX());
					pacmanObject2.setDy(pacmanObject2.getY());
				
					//Definitely dead, all 3 lives lost
					if(pacmanObject2.getPacmanDeadFinal() == true)
					{
						//Bye bye Pacman 2, remove off map
						pacmanObject2.setDx(2000);
						pacmanObject2.setDy(2000);
					}
				}
			}
		}

		/**In-game keys**/

		//Get key state
		key = SDL_GetKeyState(0);

		while(SDL_PollEvent(&keyevent))
		{
			if(keyevent.type == SDL_QUIT)
				exit(1);

			//CHEAT! NEXT MAP
			if(key[SDLK_n])
			{
				if(map.getMapLevel() == 9)
					exit(1);

				map.nextMap(mapPathArray, mapGameArray, pacmanObject1, pacmanObject2, ghostObject1, ghostObject2, ghostObject3, ghostObject4, multiplayer,
									screen, wallImage, pelletsItemsImage,  scoreLifePlayerOne, scoreLifePlayerOneRect, lifePlayerOne, lifePlayerOneRect, 
									 scoreLifePlayerTwo, scoreLifePlayerTwoRect, lifePlayerTwo, lifePlayerTwoRect);
			}
		}

		//Quick pause window
		if(key[SDLK_p])
		{
			//Help flag to assist on logical operation
			bool flag = true;

			menuGraphics.pauseMenu(screen, flag, key, keyevent, wallImage, pelletsItemsImage, mapGameArray, map, mapPathArray, pacmanObject1, pacmanObject2, 
				ghostObject1, ghostObject2, ghostObject3, ghostObject4, multiplayer, scoreLifePlayerOne, scoreLifePlayerTwo, lifePlayerOne, lifePlayerTwo, 
				scoreLifePlayerOneRect, scoreLifePlayerTwoRect, lifePlayerOneRect, lifePlayerTwoRect, blankImage, sound);
		}

		//Pause menu
		if(key[SDLK_ESCAPE])
		{
			//Help flag to assist on logical operation
			bool flag = false;

			menuGraphics.pauseMenu(screen, flag, key, keyevent, wallImage, pelletsItemsImage, mapGameArray, map, mapPathArray, pacmanObject1, pacmanObject2, 
				ghostObject1, ghostObject2, ghostObject3, ghostObject4, multiplayer, scoreLifePlayerOne, scoreLifePlayerTwo, lifePlayerOne, lifePlayerTwo, 
				scoreLifePlayerOneRect, scoreLifePlayerTwoRect, lifePlayerOneRect, lifePlayerTwoRect, blankImage, sound);

		}

		if(key[SDLK_s])
			pacmanObject1.setNextVector('S');

		else if(key[SDLK_w])
			pacmanObject1.setNextVector('N');

		else if(key[SDLK_a])
			pacmanObject1.setNextVector('W');

		else if(key[SDLK_d])
			pacmanObject1.setNextVector('E');
		
		if(multiplayer)
		{
			if(key[SDLK_DOWN])			
			pacmanObject2.setNextVector('S');

			if(key[SDLK_UP])		
				pacmanObject2.setNextVector('N');

			else if(key[SDLK_LEFT])
				pacmanObject2.setNextVector('W');

			else if(key[SDLK_RIGHT])
				pacmanObject2.setNextVector('E');
		}

		//Flip the screen
		SDL_Flip(screen);
	}
}