/***************************************************************************************************************************************
****************************************************************************************************************************************

This class specifically handles all menu graphics and events that occure in menus (main menu, quick pause window and pause menu). By events
we include keys (and various blittings) as well. This class is mainly called from the game class.

****************************************************************************************************************************************
***************************************************************************************************************************************/

#include <SDL.h>
#include "menugraphics.h"
#include "map.h"
#include "game.h"
#include "sound.h"

/****Main menu surfaces****/
SDL_Surface * chooseOption;
SDL_Surface * menuTitle;
SDL_Surface * menuSinglePlayer;
SDL_Surface * menuSinglePlayerActive;
SDL_Surface * menuMultiPlayer;
SDL_Surface * menuMultiPlayerActive;
SDL_Surface * menuSoundOn;
SDL_Surface * menuSoundOff;
SDL_Surface * menuGameInstructions;
SDL_Surface * menuGameInstructionsActive;
SDL_Surface * menuCredits;
SDL_Surface * menuCreditsActive;
SDL_Surface * menuQuit;
SDL_Surface * menuQuitActive;
SDL_Surface * menuDot;
SDL_Surface * menuBlank;
SDL_Surface * gameInstructionsPage;
SDL_Surface * creditsPage;
SDL_Surface * icon;

/****Main menu rects****/
SDL_Rect chooseOptionRect;
SDL_Rect menuTitleRect;
SDL_Rect menuSinglePlayerRect;
SDL_Rect menuSinglePlayerActiveRect;
SDL_Rect menuMultiPlayerRect;
SDL_Rect menuMultiPlayerActiveRect;
SDL_Rect menuSoundOnRect;
SDL_Rect menuSoundOffRect;
SDL_Rect menuGameInstructionsRect;
SDL_Rect menuGameInstructionsActiveRect;
SDL_Rect menuCreditsRect;
SDL_Rect menuCreditsActiveRect;
SDL_Rect menuQuitRect;
SDL_Rect menuQuitActiveRect;
SDL_Rect menuDotRect;
SDL_Rect menuBlankRect;

/***Pause menu surfaces****/
SDL_Surface * menuPause;
SDL_Surface * menuPause2;
SDL_Surface * menuPause2Active;

/****Pause menu rects****/
SDL_Rect menuPause2ContinueNotActiveBlitRect;
SDL_Rect menuPause2ContinueNotActiveImgRect;

SDL_Rect menuPause2RestartNotActiveBlitRect;
SDL_Rect menuPause2RestartNotActiveImgRect;

SDL_Rect menuPause2SoundOnBlitRect;
SDL_Rect menuPause2SoundOnImgRect;

SDL_Rect menuPause2QuitToMainMenuNotActiveBlitRect;
SDL_Rect menuPause2QuitToMainMenuNotActiveImgRect;

SDL_Rect menuPause2QuitNotActiveBlitRect;
SDL_Rect menuPause2QuitNotActiveImgRect;

SDL_Rect menuPause2ContinueActiveBlitRect;
SDL_Rect menuPause2ContinueActiveImgRect;

SDL_Rect menuPause2RestartActiveBlitRect;
SDL_Rect menuPause2RestartActiveImgRect;

SDL_Rect menuPause2SoundOffBlitRect;
SDL_Rect menuPause2SoundOffImgRect;

SDL_Rect menuPause2QuitToMainMenuActiveBlitRect;
SDL_Rect menuPause2QuitToMainMenuActiveImgRect;

SDL_Rect menuPause2QuitActiveBlitRect;
SDL_Rect menuPause2QuitActiveImgRect;

//Menu sound flags
static bool mainMenuSoundOff = false;
static bool mainMenuSoundOn = true;
static bool pauseMenuSoundOff = false;
static bool soundFlag = false;

//Default constructor
MenuGraphics::MenuGraphics()
{
	/****Load main menu graphics****/
	chooseOption = SDL_LoadBMP("../gfx/menu/chooseoption.bmp");
	menuTitle = SDL_LoadBMP("../gfx/menu/menutitle.bmp");
	menuSinglePlayer = SDL_LoadBMP("../gfx/menu/menusingleplayer.bmp");
	menuMultiPlayer = SDL_LoadBMP("../gfx/menu/menumultiplayer.bmp");
	menuSoundOn = SDL_LoadBMP("../gfx/menu/menusoundon.bmp");
	menuDot = SDL_LoadBMP("../gfx/menu/menudot.bmp");
	menuSinglePlayerActive = SDL_LoadBMP("../gfx/menu/menusingleplayeractive.bmp");
	menuMultiPlayerActive = SDL_LoadBMP("../gfx/menu/menumultiplayeractive.bmp");
	menuSoundOff = SDL_LoadBMP("../gfx/menu/menusoundoff.bmp");
	menuGameInstructions = SDL_LoadBMP("../gfx/menu/menugameinstructions.bmp");
	menuGameInstructionsActive = SDL_LoadBMP("../gfx/menu/menugameinstructionsactive.bmp");
	menuCredits = SDL_LoadBMP("../gfx/menu/menucredits.bmp");
	menuCreditsActive = SDL_LoadBMP("../gfx/menu/menucreditsactive.bmp");	
	menuQuit = SDL_LoadBMP("../gfx/menu/menuquit.bmp");
	menuQuitActive = SDL_LoadBMP("../gfx/menu/menuquitactive.bmp");
	menuBlank = SDL_LoadBMP("../gfx/menu/menublank.bmp");
	gameInstructionsPage = SDL_LoadBMP("../gfx/menu/gameinstructions.bmp");
	creditsPage = SDL_LoadBMP("../gfx/menu/credits.bmp");
	icon = SDL_LoadBMP("../gfx/menu/application_icon.bmp");

	/****Load pause menu graphics****/
	menuPause = SDL_LoadBMP("../gfx/menu/menupause1.bmp");
	menuPause2 = SDL_LoadBMP("../gfx/menu/menupause2.bmp");
	menuPause2Active = SDL_LoadBMP("../gfx/menu/menupause2active.bmp");

	//Make color transparency
	SDL_SetColorKey(menuPause, SDL_SRCCOLORKEY, 0xff00ff);
	SDL_SetColorKey(menuPause2, SDL_SRCCOLORKEY, 0xff00ff);
	SDL_SetColorKey(menuPause2Active, SDL_SRCCOLORKEY, 0xff00ff);
	SDL_SetColorKey(icon, SDL_SRCCOLORKEY, 0xff00ff);

	//Set screen caption
	SDL_WM_SetCaption("Pac-Man", NULL);

	//Set taskbar icon
	SDL_WM_SetIcon(icon, NULL);



}

//This function draws the main menu.
void MenuGraphics::drawMenu(SDL_Surface * screen)
{
	/****Position main menu rects****/

	//Choose option
	chooseOptionRect.x = 220;
	chooseOptionRect.y = 540;
	chooseOptionRect.w = chooseOption->w;
	chooseOptionRect.h = chooseOption->h;

	//Menu dot
	menuDotRect.x = 200;
	menuDotRect.y = 185;
	menuDotRect.w = menuDot->w;
	menuDotRect.h = menuDot->h;

	//Menu title
	menuTitleRect.x = 200;
	menuTitleRect.y = 50;
	menuTitleRect.w = menuTitle->w;
	menuTitleRect.h = menuTitle->h;

	/**ACTIVE FIELDS**/
	menuSinglePlayerRect.x = 240;
	menuSinglePlayerRect.y = 170;
	menuSinglePlayerRect.w = menuSinglePlayer->w;
	menuSinglePlayerRect.h = menuSinglePlayer->h;

	menuMultiPlayerRect.x = 240;
	menuMultiPlayerRect.y = 220;
	menuMultiPlayerRect.w = menuMultiPlayer->w;
	menuMultiPlayerRect.h = menuMultiPlayer->h;

	menuSoundOnRect.x = 240;
	menuSoundOnRect.y = 270;
	menuSoundOnRect.w = menuSoundOn->w;
	menuSoundOnRect.h = menuSoundOn->h;

	menuGameInstructionsRect.x = 240;
	menuGameInstructionsRect.y = 320;
	menuGameInstructionsRect.w = menuGameInstructions->w;
	menuGameInstructionsRect.h = menuGameInstructions->h;

	menuCreditsRect.x = 240;
	menuCreditsRect.y = 370;
	menuCreditsRect.w = menuCredits->w;
	menuCreditsRect.h = menuCredits->h;

	menuQuitRect.x = 240;
	menuQuitRect.y = 420;
	menuQuitRect.w = menuQuit->w;
	menuQuitRect.h = menuQuit->h;
	
	/**NOT ACTIVE FIELDS**/
	menuSinglePlayerActiveRect.x = 240;
	menuSinglePlayerActiveRect.y = 170;
	menuSinglePlayerActiveRect.w = menuSinglePlayerActive->w;
	menuSinglePlayerActiveRect.h = menuSinglePlayerActive->h;

	menuMultiPlayerActiveRect.x = 240;
	menuMultiPlayerActiveRect.y = 220;
	menuMultiPlayerActiveRect.w = menuMultiPlayerActive->w;
	menuMultiPlayerActiveRect.h = menuMultiPlayerActive->h;

	menuSoundOffRect.x = 240;
	menuSoundOffRect.y = 270;
	menuSoundOffRect.w = menuSoundOff->w;
	menuSoundOffRect.h = menuSoundOff->h;

	menuGameInstructionsActiveRect.x = 240;
	menuGameInstructionsActiveRect.y = 320;
	menuGameInstructionsActiveRect.w = menuGameInstructionsActive->w;
	menuGameInstructionsActiveRect.h = menuGameInstructionsActive->h;

	menuCreditsActiveRect.x = 240;
	menuCreditsActiveRect.y = 370;
	menuCreditsActiveRect.w = menuCreditsActive->w;
	menuCreditsActiveRect.h = menuCreditsActive->h;

	menuQuitActiveRect.x = 240;
	menuQuitActiveRect.y = 420;
	menuQuitActiveRect.w = menuQuitActive->w;
	menuQuitActiveRect.h = menuQuitActive->h;

	//Menu blank image dummy
	menuBlankRect.x = 200;
	menuBlankRect.w = menuBlank->w;
	menuBlankRect.h = menuBlank->h;
	
	/****Position pause menu rects****/

	/**NOT ACTIVE FIELDS**/

	//Tile's blit rect
	menuPause2ContinueNotActiveBlitRect.x = 305;
	menuPause2ContinueNotActiveBlitRect.y = 145;
	menuPause2ContinueNotActiveBlitRect.w = 181;
	menuPause2ContinueNotActiveBlitRect.h = 33;

	//Tile's physical image
	menuPause2ContinueNotActiveImgRect.x = 305;
	menuPause2ContinueNotActiveImgRect.y = 145;
	menuPause2ContinueNotActiveImgRect.w = 181;
	menuPause2ContinueNotActiveImgRect.h = 33;

	//Tile's blit rect
	menuPause2RestartNotActiveBlitRect.x = 305;
	menuPause2RestartNotActiveBlitRect.y = 182;
	menuPause2RestartNotActiveBlitRect.w = 181;
	menuPause2RestartNotActiveBlitRect.h = 33;

	//Tile's physical image
	menuPause2RestartNotActiveImgRect.x = 305;
	menuPause2RestartNotActiveImgRect.y = 182;
	menuPause2RestartNotActiveImgRect.w = 181;
	menuPause2RestartNotActiveImgRect.h = 33;

	//Tile's blit rect
	menuPause2SoundOnBlitRect.x = 305;
	menuPause2SoundOnBlitRect.y = 219;
	menuPause2SoundOnBlitRect.w = 266;
	menuPause2SoundOnBlitRect.h = 23;

	//Tile's physical image
	menuPause2SoundOnImgRect.x = 305;
	menuPause2SoundOnImgRect.y = 219;
	menuPause2SoundOnImgRect.w = 266;
	menuPause2SoundOnImgRect.h = 23;

	//Tile's blit rect
	menuPause2QuitToMainMenuNotActiveBlitRect.x = 228;
	menuPause2QuitToMainMenuNotActiveBlitRect.y = 256;
	menuPause2QuitToMainMenuNotActiveBlitRect.w = 341;
	menuPause2QuitToMainMenuNotActiveBlitRect.h = 28;

	//Tile's physical image
	menuPause2QuitToMainMenuNotActiveImgRect.x = 228;
	menuPause2QuitToMainMenuNotActiveImgRect.y = 256;
	menuPause2QuitToMainMenuNotActiveImgRect.w = 341;
	menuPause2QuitToMainMenuNotActiveImgRect.h = 28;

	//Tile's blit rect
	menuPause2QuitNotActiveBlitRect.x = 340;
	menuPause2QuitNotActiveBlitRect.y = 290;
	menuPause2QuitNotActiveBlitRect.w = 80;
	menuPause2QuitNotActiveBlitRect.h = 23;

	//Tile's physical image
	menuPause2QuitNotActiveImgRect.x = 340;
	menuPause2QuitNotActiveImgRect.y = 290;
	menuPause2QuitNotActiveImgRect.w = 80;
	menuPause2QuitNotActiveImgRect.h = 23;
	
	/**ACTIVE FIELDS**/

	//Tile's blit rect
	menuPause2ContinueActiveBlitRect.x = 305;
	menuPause2ContinueActiveBlitRect.y = 145;
	menuPause2ContinueActiveBlitRect.w = 181;
	menuPause2ContinueActiveBlitRect.h = 33;

	//Tile's physical image
	menuPause2ContinueActiveImgRect.x = 305;
	menuPause2ContinueActiveImgRect.y = 145;
	menuPause2ContinueActiveImgRect.w = 181;
	menuPause2ContinueActiveImgRect.h = 33;

	//Tile's blit rect
	menuPause2RestartActiveBlitRect.x = 305;
	menuPause2RestartActiveBlitRect.y = 182;
	menuPause2RestartActiveBlitRect.w = 181;
	menuPause2RestartActiveBlitRect.h = 33;

	//Tile's physical image
	menuPause2RestartActiveImgRect.x = 305;
	menuPause2RestartActiveImgRect.y = 182;
	menuPause2RestartActiveImgRect.w = 181;
	menuPause2RestartActiveImgRect.h = 33;

	//Tile's blit rect
	menuPause2SoundOffBlitRect.x = 305;
	menuPause2SoundOffBlitRect.y = 219;
	menuPause2SoundOffBlitRect.w = 266;
	menuPause2SoundOffBlitRect.h = 23;

	//Tile's physical image
	menuPause2SoundOffImgRect.x = 305;
	menuPause2SoundOffImgRect.y = 219;
	menuPause2SoundOffImgRect.w = 266;
	menuPause2SoundOffImgRect.h = 23;

	//Tile's blit rect
	menuPause2QuitToMainMenuActiveBlitRect.x = 228;
	menuPause2QuitToMainMenuActiveBlitRect.y = 256;
	menuPause2QuitToMainMenuActiveBlitRect.w = 341;
	menuPause2QuitToMainMenuActiveBlitRect.h = 28;

	//Tile's physical image
	menuPause2QuitToMainMenuActiveImgRect.x = 228;
	menuPause2QuitToMainMenuActiveImgRect.y = 256;
	menuPause2QuitToMainMenuActiveImgRect.w = 341;
	menuPause2QuitToMainMenuActiveImgRect.h = 28;

	//Tile's blit rect
	menuPause2QuitActiveBlitRect.x = 340;
	menuPause2QuitActiveBlitRect.y = 290;
	menuPause2QuitActiveBlitRect.w = 80;
	menuPause2QuitActiveBlitRect.h = 23;

	//Tile's physical image
	menuPause2QuitActiveImgRect.x = 340;
	menuPause2QuitActiveImgRect.y = 290;
	menuPause2QuitActiveImgRect.w = 80;
	menuPause2QuitActiveImgRect.h = 23;

	/****Blit main menu surfaces****/
	SDL_BlitSurface(chooseOption, NULL, screen, &chooseOptionRect);
	SDL_BlitSurface(menuTitle, NULL, screen, &menuTitleRect);
	SDL_BlitSurface(menuSinglePlayer, NULL, screen, &menuSinglePlayerRect);
	SDL_BlitSurface(menuMultiPlayer, NULL, screen, &menuMultiPlayerRect);
	SDL_BlitSurface(menuSoundOn, NULL, screen, &menuSoundOnRect);
	SDL_BlitSurface(menuGameInstructions, NULL, screen, &menuGameInstructionsRect);
	SDL_BlitSurface(menuCredits, NULL, screen, &menuCreditsRect);
	SDL_BlitSurface(menuQuit, NULL, screen, &menuQuitRect);
	SDL_BlitSurface(menuDot, NULL, screen, &menuDotRect);

	SDL_Flip(screen);
}

//Test keys (in main menu) function. This function tests for input keys in main menu, and processes events. 
void MenuGraphics::testKeys(SDL_Surface * screen, Map map, char * mapPathArray[], char mapGameArray[][40], Pacman &pacmanObject1, Pacman &pacmanObject2, 
						Ghost &ghostObject1, Ghost &ghostObject2, Ghost &ghostObject3, Ghost &ghostObject4, SDL_Surface * wallImage, SDL_Surface * pelletsItemsImage, 
						bool &multiplayer, Sound sound)
{
	if(mainMenuSoundOn)
	{
		mainMenuSoundOn = false;

		//Play music
		sound.playSoundMainMenuMusic();
	}

	bool menu = true;

	/***MAIN MENU***/
	while(menu)
	{
		SDL_Delay(5);

		//Key event
		SDL_Event keyevent;

		//Get key state
		unsigned char * key = SDL_GetKeyState(0);

		//SinglePlayer field active
		if(menuDotRect.y == 185)
		{
			SDL_BlitSurface(menuSinglePlayerActive, NULL, screen, &menuSinglePlayerActiveRect);
			SDL_Flip(screen);
		}
		
		//Test keys
		while(SDL_PollEvent(&keyevent))
		{
			if(key[SDLK_ESCAPE] || keyevent.type == SDL_QUIT)
                exit(1);

			if(key[SDLK_DOWN])
			{
				//Clear menu dot
				menuBlankRect.y = menuDotRect.y;

				//Blit blank image
				SDL_BlitSurface(menuBlank, NULL, screen, &menuBlankRect);

				//Menu dot limit
                if(menuDotRect.y >= 435)
				{
					menuDotRect.y = 435;

					SDL_BlitSurface(menuDot, NULL, screen, &menuDotRect);

					break;
				}

				//Move menu dot downwards
				menuDotRect.y += 50;

				//Blit menu dot
				SDL_BlitSurface(menuDot, NULL, screen, &menuDotRect);

				//SinglePlayer field not active
				SDL_BlitSurface(menuSinglePlayer, NULL, screen, &menuSinglePlayerRect);

				//MultiPlayer field active
				if(menuDotRect.y == 235)
					SDL_BlitSurface(menuMultiPlayerActive, NULL, screen, &menuMultiPlayerActiveRect);

				//MultiPlayer field not active
				if(menuDotRect.y != 235)
					SDL_BlitSurface(menuMultiPlayer, NULL, screen, &menuMultiPlayerRect);

				//Game Instructions field active
				if(menuDotRect.y == 335)
					SDL_BlitSurface(menuGameInstructionsActive, NULL, screen, &menuGameInstructionsActiveRect);

				//Game Instructions field not active
				if(menuDotRect.y != 335)
					SDL_BlitSurface(menuGameInstructions, NULL, screen, &menuGameInstructionsRect);

				//Credits field active
				if(menuDotRect.y == 385)
					SDL_BlitSurface(menuCreditsActive, NULL, screen, &menuCreditsActiveRect);

				//Credits field not active
				if(menuDotRect.y != 385)
					SDL_BlitSurface(menuCredits, NULL, screen, &menuCreditsRect);

				//Quit field active
				if(menuDotRect.y == 435)
					SDL_BlitSurface(menuQuitActive, NULL, screen, &menuQuitActiveRect);

				//Quit field not active
				if(menuDotRect.y != 435)
					SDL_BlitSurface(menuQuit, NULL, screen, &menuQuitRect);
			}

			if(key[SDLK_UP])
			{
				//Menu dot limit
				if(menuDotRect.y <= 185)
				{
					menuDotRect.y = 185;

					SDL_BlitSurface(menuDot, NULL, screen, &menuDotRect);

					break;
				}
				
				//Clear menu dot
				menuBlankRect.y = menuDotRect.y;

				//Blit blank image
				SDL_BlitSurface(menuBlank, NULL, screen, &menuBlankRect);

				//Move menu dot upwards
				menuDotRect.y -= 50;

				//Blit menu dot
				SDL_BlitSurface(menuDot, NULL, screen, &menuDotRect);

				//MultiPlayer field active
				if(menuDotRect.y == 235)
					SDL_BlitSurface(menuMultiPlayerActive, NULL, screen, &menuMultiPlayerActiveRect);

				//MultiPlayer field not active
				if(menuDotRect.y != 235)
					SDL_BlitSurface(menuMultiPlayer, NULL, screen, &menuMultiPlayerRect);

				//Game Instructions field active
				if(menuDotRect.y == 335)
					SDL_BlitSurface(menuGameInstructionsActive, NULL, screen, &menuGameInstructionsActiveRect);

				//Game Instructions field not active
				if(menuDotRect.y != 335)
					SDL_BlitSurface(menuGameInstructions, NULL, screen, &menuGameInstructionsRect);

				//Credits field active
				if(menuDotRect.y == 385)
					SDL_BlitSurface(menuCreditsActive, NULL, screen, &menuCreditsActiveRect);

				//Credits field not active
				if(menuDotRect.y != 385)
					SDL_BlitSurface(menuCredits, NULL, screen, &menuCreditsRect);

				//Quit field active
				if(menuDotRect.y == 435)
					SDL_BlitSurface(menuQuitActive, NULL, screen, &menuQuitActiveRect);

				//Quit field not active
				if(menuDotRect.y != 435)
					SDL_BlitSurface(menuQuit, NULL, screen, &menuQuitRect);
			}

			if(key[SDLK_RIGHT])
			{
				if(menuDotRect.y == 285)
				{
					SDL_BlitSurface(menuSoundOff, NULL, screen, &menuSoundOffRect);
					sound.stopMainMenuMusic();
				}

				mainMenuSoundOff = true;
				mainMenuSoundOn = false;
				soundFlag = false;
			}

			if(key[SDLK_LEFT])
			{
				if(menuDotRect.y == 285)
				{
					SDL_BlitSurface(menuSoundOn, NULL, screen, &menuSoundOnRect);

					if(mainMenuSoundOff)
						sound.playSoundMainMenuMusic();
				}

				mainMenuSoundOff = false;
			}

			SDL_Flip(screen);		
		}

		if(key[SDLK_SPACE] || key[SDLK_RETURN])
		{
			//Sound field
			if(menuDotRect.y == 285)
			{
				//Sound default on
				if(soundFlag)
				{
					soundFlag = false;

					if(mainMenuSoundOff)
					{
						mainMenuSoundOff = false;
						
						sound.playSoundMainMenuMusic();
					}
				}

			}
			
			else
				break;
		}
	}

	/**Test which option player chooses in main menu**/

	//Singleplayer or multiplayer
	if(menuDotRect.y == 185 || menuDotRect.y == 235)
	{
		soundFlag = true;

		mainMenuSoundOff = true;

		//Stop main menu music
		sound.stopMainMenuMusic();

		if(menuDotRect.y == 185)
			multiplayer = false;

		if(menuDotRect.y == 235)
			multiplayer = true;

		//Set background colour to black					
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
				
		//Load map
		map.loadMap(mapPathArray, mapGameArray, pacmanObject1, pacmanObject2, ghostObject1, ghostObject2, ghostObject3, ghostObject4, multiplayer);
				
		//Draw map on SDL					
		map.drawMap(screen, wallImage, pelletsItemsImage, mapGameArray);	
				
		SDL_Flip(screen);
	}

	//Game instructions
	if(menuDotRect.y == 335)
	{
		soundFlag = true;

		//Key event
		SDL_Event keyevent;

		//Get key state
		unsigned char * key = SDL_GetKeyState(0);

		SDL_BlitSurface(gameInstructionsPage, NULL, screen, NULL);

		bool newPage = true;
		bool gameInstructionsPageNow = false;

		while(newPage)
		{
			SDL_Delay(5);

			while(SDL_PollEvent(&keyevent))
			{
				if(key[SDLK_ESCAPE])
				{
					//Set background color to black
					SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

					//Show main menu
					Game::run();
					
					newPage = false;

					break;
				}

				if(keyevent.type == SDL_QUIT)
					exit(1);

			}

			SDL_Flip(screen);
		}
	}

	//Credits
	if(menuDotRect.y == 385)
	{
		soundFlag = true;

		//Key event
		SDL_Event keyevent;

		//Get key state
		unsigned char * key = SDL_GetKeyState(0);

		SDL_BlitSurface(creditsPage, NULL, screen, NULL);

		bool newPage = true;
		bool gameInstructionsPageNow = false;

		while(newPage)
		{
			SDL_Delay(5);

			while(SDL_PollEvent(&keyevent))
			{
				if(key[SDLK_ESCAPE])
				{
					//Set background color to black
					SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

					//Show main menu
					Game::run();
					
					newPage = false;

					break;
				}

				if(keyevent.type == SDL_QUIT)
					exit(1);

			}

			SDL_Flip(screen);
		}
	}

	//Quit
	if(menuDotRect.y == 435)
		exit(1);
}

//Pause menu function. This function shows the ingame pause menu, handles input keys and processes events (quick pause is also included here).
void MenuGraphics::pauseMenu(SDL_Surface * screen, bool flag, unsigned char * key, SDL_Event keyevent, SDL_Surface * wallImage, SDL_Surface * pelletsItemsImage, char mapGameArray[][40], Map map, char * mapPathArray[], 
							 Pacman &pacmanObject1, Pacman &pacmanObject2, Ghost &ghostObject1, Ghost &ghostObject2, Ghost &ghostObject3, Ghost &ghostObject4, bool &multiplayer, SDL_Surface * scoreLifePlayerOne, 
							 SDL_Surface * scoreLifePlayerTwo, SDL_Surface * lifePlayerOne, SDL_Surface * lifePlayerTwo, SDL_Rect &scoreLifePlayerOneRect, SDL_Rect &scoreLifePlayerTwoRect,
							 SDL_Rect &lifePlayerOneRect, SDL_Rect &lifePlayerTwoRect, SDL_Surface * blankImage, Sound sound)
{

	if(flag)
	{		
		bool isPaused = true;

		//Blit quick pause window
		SDL_BlitSurface(menuPause, NULL, screen, NULL);

		bool continueNow = false;

		/***QUICK PAUSE WINDOW***/
		while(isPaused)
		{	
			SDL_Delay(5);

			while(SDL_PollEvent(&keyevent))
			{
				if(key[SDLK_p])
					continueNow = true;

				else if(continueNow)
				{
					//Set background color to black
					SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

					//Re-draw map
					map.drawMap(screen, wallImage, pelletsItemsImage, mapGameArray);

					//Re-show player life/score panel
					showLifeScorePlayers(screen, multiplayer, scoreLifePlayerOne, scoreLifePlayerTwo, lifePlayerOne, lifePlayerTwo, scoreLifePlayerOneRect, scoreLifePlayerTwoRect,
											lifePlayerOneRect, lifePlayerTwoRect, pacmanObject1, pacmanObject2, blankImage);

					isPaused = false;

					break;
				}

				SDL_Flip(screen);
			}

		}
	}

	else if(!flag)
	{
			bool isPaused = true;

			//Blit pause menu
			SDL_BlitSurface(menuPause2, NULL, screen, NULL);

			//Blit pause menu, continue field active
			SDL_BlitSurface(menuPause2Active, &menuPause2ContinueActiveImgRect, screen, &menuPause2ContinueActiveBlitRect);

			//Re-position menu dot
			menuDotRect.x = 208;
			menuDotRect.y = 147;

			//Blit menu dot
			SDL_BlitSurface(menuDot, NULL, screen, &menuDotRect);
				
			bool exitNow = false;
			bool continueNow = false;

			/***PAUSE MENU***/
			while(isPaused)
			{		
				SDL_Delay(5);

				while(SDL_PollEvent(&keyevent))
				{
					if(key[SDLK_ESCAPE])
						exitNow = true;

					else if(exitNow == true)
					{
						//Set background color to black
						SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

						map.drawMap(screen, wallImage, pelletsItemsImage, mapGameArray);

						//Re-show player life/score panel
						showLifeScorePlayers(screen, multiplayer, scoreLifePlayerOne, scoreLifePlayerTwo, lifePlayerOne, lifePlayerTwo, scoreLifePlayerOneRect, scoreLifePlayerTwoRect,
													lifePlayerOneRect, lifePlayerTwoRect, pacmanObject1, pacmanObject2, blankImage);
						
						isPaused = false;
						
						break;
					}

					if(key[SDLK_DOWN])
					{
						//Clear menu dot
						menuBlankRect.x = menuDotRect.x;
						menuBlankRect.y = menuDotRect.y;

						SDL_BlitSurface(menuBlank, NULL, screen, &menuBlankRect);

						//Dot limit
						if(menuDotRect.y >= 295)
						{
							menuDotRect.y = 295;

							SDL_BlitSurface(menuDot, NULL, screen, &menuDotRect);

							break;
						}

						//Move dot downwards
						menuDotRect.y += 37;					

						SDL_BlitSurface(menuDot, NULL, screen, &menuDotRect);

						//Continue field not active
						SDL_BlitSurface(menuPause2, &menuPause2ContinueNotActiveImgRect, screen, &menuPause2ContinueNotActiveBlitRect);

						//Restart field active
						if(menuDotRect.y == 184)
							SDL_BlitSurface(menuPause2Active, &menuPause2RestartActiveImgRect, screen, &menuPause2RestartActiveBlitRect);

						//Restart field not active
						if(menuDotRect.y != 184)
							SDL_BlitSurface(menuPause2, &menuPause2RestartNotActiveImgRect, screen, &menuPause2RestartNotActiveBlitRect);

						//Quit to main menu field active
						if(menuDotRect.y == 258)
							SDL_BlitSurface(menuPause2Active, &menuPause2QuitToMainMenuActiveImgRect, screen, &menuPause2QuitToMainMenuActiveBlitRect);

						//Quit to main menu field not active
						if(menuDotRect.y != 258)
							SDL_BlitSurface(menuPause2, &menuPause2QuitToMainMenuNotActiveImgRect, screen, &menuPause2QuitToMainMenuNotActiveBlitRect);

						//Quit field active
						if(menuDotRect.y == 295)
							SDL_BlitSurface(menuPause2Active, &menuPause2QuitActiveImgRect, screen, &menuPause2QuitActiveBlitRect);
						
						//Quit field not active
						if(menuDotRect.y != 295)
							SDL_BlitSurface(menuPause2, &menuPause2QuitNotActiveImgRect, screen, &menuPause2QuitNotActiveBlitRect);
					}

					if(key[SDLK_UP])
					{
						//Clear menu dot
						menuBlankRect.x = menuDotRect.x;
						menuBlankRect.y = menuDotRect.y;

						SDL_BlitSurface(menuBlank, NULL, screen, &menuBlankRect);

						//Dot limit
						if(menuDotRect.y <= 147)
						{
							menuDotRect.y = 147;

							SDL_BlitSurface(menuDot, NULL, screen, &menuDotRect);

							break;
						}

						//Move dot upwards
						menuDotRect.y -= 37;

						SDL_BlitSurface(menuDot, NULL, screen, &menuDotRect);

						//Continue field active
						if(menuDotRect.y == 147)
							SDL_BlitSurface(menuPause2Active, &menuPause2ContinueActiveImgRect, screen, &menuPause2ContinueActiveBlitRect);

						//Continue field not active
						if(menuDotRect.y != 147)
							SDL_BlitSurface(menuPause2, &menuPause2ContinueNotActiveImgRect, screen, &menuPause2ContinueNotActiveBlitRect);

						//Restart field active
						if(menuDotRect.y == 184)
							SDL_BlitSurface(menuPause2Active, &menuPause2RestartActiveImgRect, screen, &menuPause2RestartActiveBlitRect);

						//Restart field not active
						if(menuDotRect.y != 184)
							SDL_BlitSurface(menuPause2, &menuPause2RestartNotActiveImgRect, screen, &menuPause2RestartNotActiveBlitRect);

						//Quit to main menu field active
						if(menuDotRect.y == 258)
							SDL_BlitSurface(menuPause2Active, &menuPause2QuitToMainMenuActiveImgRect, screen, &menuPause2QuitToMainMenuActiveBlitRect);

						//Quit to main menu field not active
						if(menuDotRect.y != 258)
							SDL_BlitSurface(menuPause2, &menuPause2QuitToMainMenuNotActiveImgRect, screen, &menuPause2QuitToMainMenuNotActiveBlitRect);

						//Quit field active
						if(menuDotRect.y == 295)
							SDL_BlitSurface(menuPause2Active, &menuPause2QuitActiveImgRect, screen, &menuPause2QuitActiveBlitRect);
						
						//Quit field not active
						if(menuDotRect.y != 295)
							SDL_BlitSurface(menuPause2, &menuPause2QuitNotActiveImgRect, screen, &menuPause2QuitNotActiveBlitRect);
					}

					if(key[SDLK_RIGHT])
					{
						if(menuDotRect.y == 221)
							SDL_BlitSurface(menuPause2Active, &menuPause2SoundOnImgRect, screen, &menuPause2SoundOnBlitRect);

						pauseMenuSoundOff = true;
					}

					if(key[SDLK_LEFT])
					{
						if(menuDotRect.y == 221)
							SDL_BlitSurface(menuPause2, &menuPause2SoundOffImgRect, screen, &menuPause2SoundOffBlitRect);
					}

					if(key[SDLK_SPACE] || key[SDLK_RETURN])	
						continueNow = true;

					else if(continueNow)
					{
						//Flag to help on logical operation
						flag = true;

						/**Test which option player chooses**/

						//Continue game
						if(menuDotRect.y == 147)
						{		
							//Set background color to black
							SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

							//Re-draw map
							map.drawMap(screen, wallImage, pelletsItemsImage, mapGameArray);

							//Re-show player life/score panel
							showLifeScorePlayers(screen, multiplayer, scoreLifePlayerOne, scoreLifePlayerTwo, lifePlayerOne, lifePlayerTwo, scoreLifePlayerOneRect, scoreLifePlayerTwoRect,
								lifePlayerOneRect, lifePlayerTwoRect, pacmanObject1, pacmanObject2, blankImage);

							break;
						}

						//Restart game
						if(menuDotRect.y == 184)
						{
							//Empty game array
							for(int i = 0; i < 30; i++)
							{
								for(int j = 0; j < 40; j++)
								{
									mapGameArray[i][j] = 0;
								}
							}

							//Reset fields							
							pacmanObject1.setPowerPellet(false);
							pacmanObject2.setPowerPellet(false);
							pacmanObject1.setPacmanDead(false);
							pacmanObject2.setPacmanDead(false);
							pacmanObject1.setLife(3);
							pacmanObject2.setLife(3);
							pacmanObject1.setScore(0);
							pacmanObject2.setScore(0);
							pacmanObject1.setPacmanDeadFinal(false);
							pacmanObject2.setPacmanDeadFinal(false);
							Map::deathAnimationCounterOne = 0;
							Map::deathAnimationCounterTwo = 0;

							//Set background colour to black					
							SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
					
							//Re-load map				
							map.loadMap(mapPathArray, mapGameArray, pacmanObject1, pacmanObject2, ghostObject1, ghostObject2, ghostObject3, ghostObject4, multiplayer);
					
							//Re-draw map on SDL					
							map.drawMap(screen, wallImage, pelletsItemsImage, mapGameArray);

							//Re-show player life/score panel
							showLifeScorePlayers(screen, multiplayer, scoreLifePlayerOne, scoreLifePlayerTwo, lifePlayerOne, lifePlayerTwo, scoreLifePlayerOneRect, scoreLifePlayerTwoRect,
												lifePlayerOneRect, lifePlayerTwoRect, pacmanObject1, pacmanObject2, blankImage);
		
							break;
						}

						//Sound Off
						if(menuDotRect.y == 221 && pauseMenuSoundOff == true)
						{
							pauseMenuSoundOff = false;
							
							sound.setSound(false);

							//Set background color to black
							SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

							//Re-draw map
							map.drawMap(screen, wallImage, pelletsItemsImage, mapGameArray);

							//Re-show player life/score panel
							showLifeScorePlayers(screen, multiplayer, scoreLifePlayerOne, scoreLifePlayerTwo, lifePlayerOne, lifePlayerTwo, scoreLifePlayerOneRect, scoreLifePlayerTwoRect,
								lifePlayerOneRect, lifePlayerTwoRect, pacmanObject1, pacmanObject2, blankImage);

							break;
						}

						//Sound default on
						if(menuDotRect.y == 221)
						{
							sound.setSound(true);

							//Set background color to black
							SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

							//Re-draw map
							map.drawMap(screen, wallImage, pelletsItemsImage, mapGameArray);

							//Re-show player life/score panel
							showLifeScorePlayers(screen, multiplayer, scoreLifePlayerOne, scoreLifePlayerTwo, lifePlayerOne, lifePlayerTwo, scoreLifePlayerOneRect, scoreLifePlayerTwoRect,
								lifePlayerOneRect, lifePlayerTwoRect, pacmanObject1, pacmanObject2, blankImage);

							break;
						}

						//Quit to main menu
						if(menuDotRect.y == 258)
						{
							mainMenuSoundOn = true;
							soundFlag = false;
							flag = false;						
							
							//Reset map level
							Map::setMapLevel(0);

							//Empty game array
							for(int i = 0; i < 30; i++)
							{
								for(int j = 0; j < 40; j++)
								{
									mapGameArray[i][j] = 0;
								}
							}

							//Reset fields
							pacmanObject1.setPowerPellet(false);
							pacmanObject2.setPowerPellet(false);
							pacmanObject1.setPacmanDead(false);
							pacmanObject2.setPacmanDead(false);
							pacmanObject1.setLife(3);
							pacmanObject2.setLife(3);
							pacmanObject1.setScore(0);
							pacmanObject2.setScore(0);
							multiplayer = false;
							pacmanObject1.setPacmanDeadFinal(false);
							pacmanObject2.setPacmanDeadFinal(false);
							Map::deathAnimationCounterOne = 0;
							Map::deathAnimationCounterTwo = 0;

							//Set background color to black
							SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

							//Show main menu
							Game::run();

							//Re-show player life/score panel
							showLifeScorePlayers(screen, multiplayer, scoreLifePlayerOne, scoreLifePlayerTwo, lifePlayerOne, lifePlayerTwo, scoreLifePlayerOneRect, scoreLifePlayerTwoRect,
								lifePlayerOneRect, lifePlayerTwoRect, pacmanObject1, pacmanObject2, blankImage);

							flag = true;

							break;						
						}

						//Quit
						if(menuDotRect.y == 295)
							exit(1);
					}

				SDL_Flip(screen);
			}

			if(flag)
				break;
		}

	}
}

//Player life/score function. This function shows the life/score panel of players.
void MenuGraphics::showLifeScorePlayers(SDL_Surface * screen, bool &multiplayer, SDL_Surface * scoreLifePlayerOne, SDL_Surface * scoreLifePlayerTwo, SDL_Surface * lifePlayerOne, SDL_Surface * lifePlayerTwo, SDL_Rect &scoreLifePlayerOneRect, 
											SDL_Rect &scoreLifePlayerTwoRect, SDL_Rect &lifePlayerOneRect, SDL_Rect &lifePlayerTwoRect, Pacman &pacmanObject1, Pacman &pacmanObject2, SDL_Surface * blankImage)
{	
	//Position player 1 life icons
	lifePlayerOneRect.x = 60;
	lifePlayerOneRect.y = 573;
	lifePlayerOneRect.w = lifePlayerOne->w;
	lifePlayerOneRect.h = lifePlayerOne->h;

	//Blit player 1 score/life panel
	SDL_BlitSurface(scoreLifePlayerOne, NULL, screen, &scoreLifePlayerOneRect);

	/*Test Pacman 1 lives*/

	//3 lives
	if(pacmanObject1.getLife() == 3)
	{
		//Just to be safe, re-assign x coordinate
		lifePlayerOneRect.x = 60;

		SDL_BlitSurface(lifePlayerOne, NULL, screen, &lifePlayerOneRect);
	}

	//2 lives
	if(pacmanObject1.getLife() == 2)
	{
		SDL_BlitSurface(lifePlayerOne, NULL, screen, &lifePlayerOneRect);

		lifePlayerOneRect.x = 100;

		SDL_BlitSurface(blankImage, NULL, screen, &lifePlayerOneRect);
	}
	
	//1 life
	if(pacmanObject1.getLife() == 1)
	{
		SDL_BlitSurface(lifePlayerOne, NULL, screen, &lifePlayerOneRect);

		lifePlayerOneRect.x = 100;

		SDL_BlitSurface(blankImage, NULL, screen, &lifePlayerOneRect);

		lifePlayerOneRect.x = 80;
		
		SDL_BlitSurface(blankImage, NULL, screen, &lifePlayerOneRect);
	}

	if(multiplayer)
	{
		//Position player 2 life icons		
		lifePlayerTwoRect.x = 620;
		lifePlayerTwoRect.y = 573;
		lifePlayerTwoRect.w = lifePlayerTwo->w;
		lifePlayerTwoRect.h = lifePlayerTwo->h;

		//Blit player 2 score/life panel
		SDL_BlitSurface(scoreLifePlayerTwo, NULL, screen, &scoreLifePlayerTwoRect);

		/*Test Pacman 2 lives*/
	
		//3 lives
		if(pacmanObject2.getLife() == 3)
		{	
			//Just to be safe, re-assign x coordinate
			lifePlayerTwoRect.x = 620;			

			SDL_BlitSurface(lifePlayerTwo, NULL, screen, &lifePlayerTwoRect);
		}

		//2 lives
		if(pacmanObject2.getLife() == 2)
		{
			SDL_BlitSurface(lifePlayerTwo, NULL, screen, &lifePlayerTwoRect);

			lifePlayerTwoRect.x = 660;

			SDL_BlitSurface(blankImage, NULL, screen, &lifePlayerTwoRect);
		}
		
		//1 life
		if(pacmanObject2.getLife() == 1)
		{
			SDL_BlitSurface(lifePlayerTwo, NULL, screen, &lifePlayerTwoRect);

			lifePlayerTwoRect.x = 660;

			SDL_BlitSurface(blankImage, NULL, screen, &lifePlayerTwoRect);

			lifePlayerTwoRect.x = 640;
			
			SDL_BlitSurface(blankImage, NULL, screen, &lifePlayerTwoRect);
		}	
	}
}