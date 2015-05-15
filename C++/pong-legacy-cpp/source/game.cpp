#include <cmath>
#include "../include/game.h"
#include "../include/movement.h"
#include "../include/checkcollision.h"
#include "SDL.h"
#include "SDL_mixer.h"

movement * mv;
game * gm;

SDL_Surface * screen;
SDL_Surface * graphicObjects[3];
SDL_Surface * scorePlayer[10];
SDL_Surface * winPlayer[2];
unsigned char * key;

SDL_Rect rects[3];
SDL_Rect scoreRect1[10];
SDL_Rect scoreRect2[10];
SDL_Rect winRect[2];

Mix_Chunk * music;

game::game()
{
	//Initialize our variables
	scoreCount1 = 0;
	scoreCount2 = 0;
	files[0] = "./gfx/paddleOne.bmp", files[1] = "./gfx/ball.bmp", files[2] = "./gfx/paddleTwo.bmp";
	score[0] = "./gfx/dummy.bmp", score[1] = "./gfx/number1.bmp", score[2] = "./gfx/number2.bmp", score[3] = "./gfx/number3.bmp", score[4] = "./gfx/number4.bmp", score[5] = "./gfx/number5.bmp", score[6] = "./gfx/number6.bmp", score[7] = "./gfx/number7.bmp", score[8] = "./gfx/number8.bmp", score[9] = "./gfx/number9.bmp";
	win[0] = "./gfx/player1win.bmp", win[1] = "./gfx/player2win.bmp";	
	sound[0] = "./sound/ping.wav", sound[1] = "./sound/pong.wav";
	counter = 0;
	flag = false;
	flag2 = false;
	paddleOneHit = false;
	paddleTwoHit = false;
	upWallHit = false;
	downWallHit = false;
	wallCollision = false;
	showScoreOne = false;
	showScoreTwo = false;
	randomNum[0] = -1, randomNum[1] = 1;
	randomDx = randomNum[rand () % 2];
	randomDy = randomNum[rand () % 2];
	quit = false;

	//Initialize all SDL controls
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
		exit(1);
	
	//Create our screen
	screen = SDL_SetVideoMode(screenWidth, screenHeight, screenBpp, SDL_SWSURFACE);

	//Set background color to black
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

	SDL_WM_SetCaption("Pong", NULL);
	
	//Load player score bmps
	for(int i = 0; i < 10; i++)
		scorePlayer[i] = SDL_LoadBMP(score[i]);

	//Make color transparency
	for(int i = 0; i < 10; i++)
		SDL_SetColorKey(scorePlayer[i], SDL_SRCCOLORKEY, 0xff00ff);

	//Position rects
	for(int i = 0; i < 10; i++)
	{
		scoreRect1[i].x = 0;
		scoreRect1[i].y = 0;
		scoreRect1[i].w = scorePlayer[i]->w;
		scoreRect1[i].h = scorePlayer[i]->h;

		scoreRect2[i].x = (screenWidth-35);
		scoreRect2[i].y = 0;
		scoreRect2[i].w = scorePlayer[i]->w;
		scoreRect2[i].h = scorePlayer[i]->h;
	}

	//Load paddles, ball bmps
	for(int i = 0; i < 3; i++)
		graphicObjects[i] = SDL_LoadBMP(files[i]);

	//Make color transparency
	for(int i = 0; i < 3; i++)
		SDL_SetColorKey(graphicObjects[i], SDL_SRCCOLORKEY, 0xff00ff);

	//Position rects
	for(int i = 0; i < 3; i++)
	{	
		rects[i].x = 62 * pow((double)i+1, (double)i);

		//Position ball object
		if(counter == 1)
		{
			rects[i].x = (screenWidth/2);
			rects[i].y = ((graphicObjects[0]->h/2));
		}

		else
			rects[i].y = 50;
		
		rects[i].w = graphicObjects[i]->w;
		rects[i].h = graphicObjects[i]->h;

		counter++;
	}

	//Load player win bmps
	for(int i = 0; i < 2; i++)
		winPlayer[i] = SDL_LoadBMP(win[i]);

	//Make color transparency
	for(int i = 0; i < 2; i++)
		SDL_SetColorKey(winPlayer[i], SDL_SRCCOLORKEY, 0xff00ff);

	//Position rects
	for(int i = 0; i < 2; i++)
	{
		winRect[i].x = (screenWidth/2-100);
		winRect[i].y = ((graphicObjects[0]->h/2));
		winRect[i].w = winPlayer[i]->w;
		winRect[i].h = winPlayer[i]->h;
	}
}

void game::run()
{
	//Call movement class
	mv = new movement();
	
	//Call check collision class
	checkCollision * checkCol = new checkCollision();

	//Call game class
	gm = new game();

	//Game starts
	while(!quit)
	{
		//We will be calling doEvents through out the program, to make sure events are handled at all times
		gm->doEvents(rects);

		SDL_Flip(screen);
		//SDL_Delay(7);

		if(!flag)
		{
			if((randomDx == -1 && randomDy == 1) || (randomDx == 1 && randomDy == -1))
				randomDx, randomDy = 1;

			mv->moveBall(rects[1], randomDx, randomDy);
		}

		if(rects[1].x >= screenWidth)
		{
			rects[1].x = (screenWidth/2);
			rects[1].y = ((graphicObjects[0]->h/2));

			//Player one scores
			scoreCount1++;

			showScoreOne = true;
		
		}

		if(paddleTwoHit && downWallHit)
		{
			//PaddleOne, post-collision: positive X negative Y
			if(checkCol->checkCol(rects[0], rects[1]))
			{
				downWallHit = false;
				paddleTwoHit = false;

				flag2 = false;

				while(!flag2)
				{
					mv->moveBall(rects[1], 1, -1);

					gm->doEvents(rects);

					if(rects[1].y <= 0)
						flag2 = true;
				
					SDL_Delay(2);

					//Refill background color
					SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

					SDL_BlitSurface(scorePlayer[scoreCount1], NULL, screen, &scoreRect1[scoreCount1]);
					SDL_BlitSurface(scorePlayer[scoreCount2], NULL, screen, &scoreRect2[scoreCount2]);

					gm->blitAndFlip(graphicObjects, rects);
				}

				paddleOneHit = true;
			}
		}

		else if(paddleTwoHit && upWallHit)
		{
			//PaddleOne, post-collision: positive X positive Y
			if(checkCol->checkCol(rects[0], rects[1]))
			{	
				upWallHit = false;
				paddleTwoHit = false;

				flag2 = false;

				while(!flag2)
				{
					mv->moveBall(rects[1], 1, 1);

					gm->doEvents(rects);

					if(rects[1].y <= 0)
						flag2 = true;
				
					SDL_Delay(2);

					//Refill background color
					SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

					SDL_BlitSurface(scorePlayer[scoreCount1], NULL, screen, &scoreRect1[scoreCount1]);
					SDL_BlitSurface(scorePlayer[scoreCount2], NULL, screen, &scoreRect2[scoreCount2]);

					gm->blitAndFlip(graphicObjects, rects);
				}

				paddleOneHit = true;
			}

		}

		else
		{
			//PaddleOne, post-collision: positive X negative Y
			if(checkCol->checkCol(rects[0], rects[1]))
			{	
				//gm->playSound(sound, 0);

				flag = false;

				while(!flag)
				{
					mv->moveBall(rects[1], 1, -1);

					gm->doEvents(rects);

					if(rects[1].y <= 0)
						flag = true;
				
					SDL_Delay(2);

					//Refill background color
					SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

					SDL_BlitSurface(scorePlayer[scoreCount1], NULL, screen, &scoreRect1[scoreCount1]);
					SDL_BlitSurface(scorePlayer[scoreCount2], NULL, screen, &scoreRect2[scoreCount2]);

					gm->blitAndFlip(graphicObjects, rects);
				}

				paddleOneHit = true;
			}
		}

		if(paddleOneHit && downWallHit)
		{
			//PaddleTwo, post-collision: negative X negative Y
			if(checkCol->checkCol(rects[1], rects[2]))
			{	
				downWallHit = false;
				paddleOneHit = false;

				flag2 = false;
				
				while(!flag2)
				{
					mv->moveBall(rects[1], -1, -1);

					gm->doEvents(rects);
					
					if(rects[1].y <= 0)
						flag2 = true;

					SDL_Delay(2);

					//Refill background color
					SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

					SDL_BlitSurface(scorePlayer[scoreCount1], NULL, screen, &scoreRect1[scoreCount1]);
					SDL_BlitSurface(scorePlayer[scoreCount2], NULL, screen, &scoreRect2[scoreCount2]);

					gm->blitAndFlip(graphicObjects, rects);
				}

				paddleTwoHit = true;
			}
		}
		
		else if(paddleOneHit && upWallHit)
		{
			//PaddleTwo, post-collision: negative X positive Y
			if(checkCol->checkCol(rects[1], rects[2]))
			{
				upWallHit = false;
				paddleOneHit = false;

				flag2 = false;
				
				while(!flag2)
				{
					mv->moveBall(rects[1], -1, 1);

					gm->doEvents(rects);
					
					if(rects[1].y > screenHeight)
						flag2 = true;

					SDL_Delay(2);

					//Refill background color
					SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

					SDL_BlitSurface(scorePlayer[scoreCount1], NULL, screen, &scoreRect1[scoreCount1]);
					SDL_BlitSurface(scorePlayer[scoreCount2], NULL, screen, &scoreRect2[scoreCount2]);

					gm->blitAndFlip(graphicObjects, rects);
				}

				paddleTwoHit = true;
			}
		}

		else
		{
			//PaddleTwo, post-collision: negative X positive Y
			if(checkCol->checkCol(rects[1], rects[2]))
			{
				//gm->playSound(sound, 1);

				flag = false;

				while(!flag)
				{
					mv->moveBall(rects[1], -1, 1);

					gm->doEvents(rects);

					if(rects[1].y > screenHeight)
						flag = true;

					SDL_Delay(2);

					//Refill background color
					SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

					SDL_BlitSurface(scorePlayer[scoreCount1], NULL, screen, &scoreRect1[scoreCount1]);
					SDL_BlitSurface(scorePlayer[scoreCount2], NULL, screen, &scoreRect2[scoreCount2]);

					gm->blitAndFlip(graphicObjects, rects);
				}

				paddleTwoHit = true;
			}
		}

		//Test wall collisions
		if(!wallCollision)
		{
			//Test down wall
			if(rects[1].y > screenHeight)
			{
				flag = false;
				wallCollision = true;
				downWallHit = true;

				if(paddleTwoHit)
				{
					//gm->playSound(sound, 1);

					while(!flag)
					{
						mv->moveBall(rects[1], -1, -1);

						gm->doEvents(rects);

						//Collision with paddle one
						if(checkCol->checkCol(rects[0], rects[1]))
						{
							//gm->playSound(sound, 0);
							flag = true;
						}
						
						else if(rects[1].x <= 0)
						{
							rects[1].x = (screenWidth/2);
							rects[1].y = ((graphicObjects[0]->h/2));

							//Player two scores
							scoreCount2++;
							showScoreTwo = true;
							break;
						}

						SDL_Delay(2);
						
						//Refill background color
						SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

						SDL_BlitSurface(scorePlayer[scoreCount1], NULL, screen, &scoreRect1[scoreCount1]);
						SDL_BlitSurface(scorePlayer[scoreCount2], NULL, screen, &scoreRect2[scoreCount2]);

						gm->blitAndFlip(graphicObjects, rects);

						wallCollision = false;
						
						//Collision with paddle one, coming from: paddle two -> down wall 
						paddleTwoHit = true;
					}
				}

				else if(paddleOneHit)
				{
					//gm->playSound(sound, 0);

					while(!flag)
					{
						mv->moveBall(rects[1], 1, 1);

						gm->doEvents(rects);

						//Collision with paddle two
						if(checkCol->checkCol(rects[1], rects[2]))
						{
							//gm->playSound(sound, 1);
							flag = true;
						}
						
						else if(rects[1].y >= screenWidth)
						{
							rects[1].x = (screenWidth/2);
							rects[1].y = ((graphicObjects[0]->h/2));

							//Player one scores
							scoreCount1++;
							showScoreOne = true;
							break;
						}

						SDL_Delay(2);

						//Refill background color
						SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

						SDL_BlitSurface(scorePlayer[scoreCount1], NULL, screen, &scoreRect1[scoreCount1]);
						SDL_BlitSurface(scorePlayer[scoreCount2], NULL, screen, &scoreRect2[scoreCount2]);

						gm->blitAndFlip(graphicObjects, rects);

						wallCollision = false;
						
						//Collision with paddle two, coming from: paddle one -> down wall 
						paddleOneHit = true;
					}
				}
			}

			//Test up wall
			if(rects[1].y <= 0)
			{
				flag = false;
				wallCollision = true;
				upWallHit = true;

				if(paddleTwoHit)
				{
					while(!flag)
					{	
						mv->moveBall(rects[1], -1, 1);

						gm->doEvents(rects);
						
						//Collision with paddle one
						if(checkCol->checkCol(rects[0], rects[1]))
							flag = true;

						else if(rects[1].x <= 0)
						{
							rects[1].x = (screenWidth/2);
							rects[1].y = ((graphicObjects[0]->h/2));

							//Player two scores
							scoreCount2++;
							showScoreTwo = true;

							break;
						}

						SDL_Delay(2);

						//Refill background color
						SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

						SDL_BlitSurface(scorePlayer[scoreCount1], NULL, screen, &scoreRect1[scoreCount1]);
						SDL_BlitSurface(scorePlayer[scoreCount2], NULL, screen, &scoreRect2[scoreCount2]);

						gm->blitAndFlip(graphicObjects, rects);

						wallCollision = false;
						
						//Collision with paddle one, coming from: paddle two -> up wall 
						paddleTwoHit = true;
					}
				}

				else if(paddleOneHit)
				{
					while(!flag)
					{
						mv->moveBall(rects[1], 1, 1);

						gm->doEvents(rects);

						//Collision with paddle two
						if(checkCol->checkCol(rects[1], rects[2]))
							flag = true;

						else if(rects[1].y >= screenWidth)
						{
							rects[1].x = (screenWidth/2);
							rects[1].y = ((graphicObjects[0]->h/2));

							//Player one scores
							scoreCount1++;
							showScoreOne = true;

							break;
						}

						SDL_Delay(2);

						//Refill background color
						SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
	
						SDL_BlitSurface(scorePlayer[scoreCount1], NULL, screen, &scoreRect1[scoreCount1]);
						SDL_BlitSurface(scorePlayer[scoreCount2], NULL, screen, &scoreRect2[scoreCount2]);

						gm->blitAndFlip(graphicObjects, rects);
				
						wallCollision = false;
						
						//Collision with paddle two, coming from: paddle one -> up wall
						paddleOneHit = true;
					}
				}
			}		
		}	

		//Refill background color
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

		if(showScoreOne || showScoreTwo)
		{
			if(scoreCount1 == 9)
			{
				//Player 1 wins, blit all necessary surfaces and exit
				SDL_BlitSurface(winPlayer[0], NULL, screen, &winRect[0]);
				SDL_BlitSurface(scorePlayer[scoreCount1], NULL, screen, &scoreRect1[scoreCount1]);
				SDL_BlitSurface(scorePlayer[scoreCount2], NULL, screen, &scoreRect2[scoreCount2]);	

				SDL_BlitSurface(graphicObjects[0], NULL, screen, &rects[0]);
				SDL_BlitSurface(graphicObjects[2], NULL, screen, &rects[2]);
				
				SDL_Flip(screen);
				SDL_Delay(3000);
				exit(1);
			}

			if(scoreCount2 == 9)
			{
				//Player 2 wins, blit all necessary surfaces and exit
				SDL_BlitSurface(winPlayer[1], NULL, screen, &winRect[1]);
				SDL_BlitSurface(scorePlayer[scoreCount1], NULL, screen, &scoreRect1[scoreCount1]);
				SDL_BlitSurface(scorePlayer[scoreCount2], NULL, screen, &scoreRect2[scoreCount2]);	

				SDL_BlitSurface(graphicObjects[0], NULL, screen, &rects[0]);
				SDL_BlitSurface(graphicObjects[2], NULL, screen, &rects[2]);
				
				SDL_Flip(screen);
				SDL_Delay(3000);
				exit(1);
			}

			SDL_BlitSurface(scorePlayer[scoreCount1], NULL, screen, &scoreRect1[scoreCount1]);
			SDL_BlitSurface(scorePlayer[scoreCount2], NULL, screen, &scoreRect2[scoreCount2]);	
		}

		for(int i = 0; i < 3; i++)
			SDL_BlitSurface(graphicObjects[i], NULL, screen, &rects[i]);
		
		SDL_Flip(screen);
	}

}

void game::blitAndFlip(SDL_Surface * graphicObjects[3], SDL_Rect rects[3])
{				
		//Blit graphic objects
		for(int i = 0; i < 3; i++)
			SDL_BlitSurface(graphicObjects[i], NULL, screen, &rects[i]);

		SDL_Flip(screen);
}

void game::playSound(char * sound[2], const int element)
{
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
    music = Mix_LoadWAV(sound[element]);
    Mix_PlayChannel(1, music, 0);
}

void game::doEvents(SDL_Rect rects[3])
{
		key = SDL_GetKeyState(0);

		SDL_Event keyevent;

		//Control movement
		if(key[SDLK_w])
		{
			mv->movePaddleOneUp(rects[0]);
				
			if(rects[0].y <= 0)
			{
				rects[0].y = 0;			
					
				SDL_BlitSurface(graphicObjects[0], NULL, screen, &rects[0]);
			}
		}

		if(key[SDLK_s])
		{
			mv->movePaddleOneDown(rects[0]);
			
			if(rects[0].y > (screenHeight-134))
			{
				rects[0].y = (screenHeight-134);
					
				SDL_BlitSurface(graphicObjects[0], NULL, screen, &rects[0]);
			}
		}

		if(key[SDLK_UP])
		{
			mv->movePaddleTwoUp(rects[2]);
				
			if(rects[2].y <= 0)
			{
				rects[2].y = 0;			
					
				SDL_BlitSurface(graphicObjects[2], NULL, screen, &rects[2]);
			}
		}

		if(key[SDLK_DOWN])
		{
            mv->movePaddleTwoDown(rects[2]);

			if(rects[2].y > (screenHeight-134))
			{
				rects[2].y = (screenHeight-134);
					
				SDL_BlitSurface(graphicObjects[2], NULL, screen, &rects[2]);
			}
		}

		while(SDL_PollEvent(&keyevent))
		{
			if(key[SDLK_ESCAPE] || keyevent.type == SDL_QUIT)
                exit(1);
		}
}