/***************************************************************************************************************************************
****************************************************************************************************************************************

This is the collision detection class. Upon calling, this class returns either true or false, in other words all functions in this class
are of bool return type. This class is constantly called from the map class to check collisions and handle events.

****************************************************************************************************************************************
***************************************************************************************************************************************/

#include <SDL.h>
#include <time.h>
#include "collisiondetection.h"
#include "pacman.h"
#include "ghost.h"

/*Timers for power pellets (10 seconds)*/
clock_t timeOne = 0;
clock_t timeTwo = 0;

//Help flag for Pacman-Ghost collision (ghost respawn)
bool CollisionDetection::helpFlag = true;

/*Ghost ID flags*/
bool CollisionDetection::ghostOne = false;
bool CollisionDetection::ghostTwo = false;
bool CollisionDetection::ghostThree = false;
bool CollisionDetection::ghostFour = false;

//Default constructor
CollisionDetection::CollisionDetection()
{

}

//This function checks collisions between Pacman, items and wall and returns a boolean value. This function also handles events when Pacman eats an item in the map.
bool CollisionDetection::checkPacmanCollisionPelletWall(Pacman &pacmanObject, char mapGameArray[][40])
{
	/**Event handling if/when pacman eats a pellet, power pellet or bonus item**/
	
	//If 20 seconds are out, remove power pellet from pacman 1
	if(clock() >= timeOne)
	{
		if(pacmanObject.getPlayer() == 1)
			pacmanObject.setPowerPellet(false);
	}

	//If 20 seconds are out, remove power pellet from pacman 2
	if(clock() >= timeTwo)
	{
		if(pacmanObject.getPlayer() == 2)
			pacmanObject.setPowerPellet(false);
	}	
	
	SDL_Rect pacmanRect;
	
	double pacmanArrayX;
	double pacmanArrayY;

	pacmanRect.x = pacmanObject.getDx();
	pacmanRect.y = pacmanObject.getDy();
	pacmanRect.w = 20;
	pacmanRect.h = 20;

	pacmanArrayX = pacmanObject.getDx() / 20.0;
	pacmanArrayY = pacmanObject.getDy() / 20.0;

	if(pacmanArrayX - (int)pacmanArrayX == 0.0 && pacmanArrayY - (int)pacmanArrayY == 0.0)
	{
		//Test if pellet is eaten
		if(mapGameArray[(int)pacmanArrayY][(int)pacmanArrayX] == '2')
		{
			//Eaten, set to 0 in array
			mapGameArray[(int)pacmanArrayY][(int)pacmanArrayX] = '0';
			
			//Increment score
			pacmanObject.setScore((pacmanObject.getScore() + 10));
		}

		//Test if power pellet is eaten
		else if (mapGameArray[(int)pacmanArrayY][(int)pacmanArrayX] == '3')
		{
			//Eaten, set to 0 in array
			mapGameArray[(int)pacmanArrayY][(int)pacmanArrayX] = '0';
			
			//Increment score
			pacmanObject.setScore((pacmanObject.getScore() + 50));
			
			//Power pellet on
			pacmanObject.setPowerPellet(true);

			//Power pellet timers on
			if(pacmanObject.getPlayer() == 1)
				timeOne = clock () + 20 * CLOCKS_PER_SEC;				
			
			else if(pacmanObject.getPlayer() == 2)
				timeTwo = clock () + 20 * CLOCKS_PER_SEC;
				

		}

		//Test if bonus item one is eaten
		else if(mapGameArray[(int)pacmanArrayY][(int)pacmanArrayX] == '4')
		{
			//Eaten, set to 0 in array
			mapGameArray[(int)pacmanArrayY][(int)pacmanArrayX] = '0';
			
			//Increment score
			pacmanObject.setScore((pacmanObject.getScore() + 100));

			//A bonus item is eaten
			pacmanObject.setBonusItem(true);
		}

		//Test if bonus item two is eaten
		else if(mapGameArray[(int)pacmanArrayY][(int)pacmanArrayX] == '5')
		{
			//Eaten, set to 0 in array
			mapGameArray[(int)pacmanArrayY][(int)pacmanArrayX] = '0';
			
			//Increment score
			pacmanObject.setScore((pacmanObject.getScore() + 100));

			//A bonus item is eaten
			pacmanObject.setBonusItem(true);
		}
	}

	//Event handling if Pacman collides with wall	
	double xArrayPos = (pacmanObject.getDx() / 20.0);
	double yArrayPos = (pacmanObject.getDy() / 20.0);

	if((xArrayPos - (int)xArrayPos) == 0.0 && (yArrayPos - (int)yArrayPos) == 0.0)
	{ 		
		if(pacmanObject.getPosVector() == 'N')
		{
			if(mapGameArray[(int)yArrayPos - 1][(int)xArrayPos] == '1')
				return true;

			else
				return false;
		}
		
		else if(pacmanObject.getPosVector() == 'S')
		{
			if(mapGameArray[(int)yArrayPos + 1][(int)xArrayPos] == '1')
				return true;
			
			else
				return false;
		}
		
		else if(pacmanObject.getPosVector() == 'W')
		{
			if(mapGameArray[(int)yArrayPos][(int)xArrayPos - 1] == '1')
				return true;
			
			else
				return false;
		}
		
		else if(pacmanObject.getPosVector() == 'E')
		{
			if(mapGameArray[(int)yArrayPos][(int)xArrayPos + 1] == '1')
				return true;
			
			else
				return false;
		}
		
		else 
			return false;
	}
	
	else 
		return false;
}

//This function checks collisions between Ghost and wall and returns a boolean value.
bool CollisionDetection::checkGhostCollision(Ghost &ghostObject, char mapGameArray[][40])
{
	double xArrayPos = (ghostObject.getDx() / 20.0);
	double yArrayPos = (ghostObject.getDy() / 20.0);

	if((xArrayPos - (int)xArrayPos) == 0.0 && (yArrayPos - (int)yArrayPos) == 0.0)
	{ 		
		if(ghostObject.getPosVector() == 'N')
		{
			if(mapGameArray[(int)yArrayPos - 1][(int)xArrayPos] == '1')
				return true;
			
			else
				return false;
		}
		
		else if(ghostObject.getPosVector() == 'S')
		{
			if(mapGameArray[(int)yArrayPos + 1][(int)xArrayPos] == '1')
				return true;
			
			else
				return false;
		}
		
		else if(ghostObject.getPosVector() == 'W')
		{
			if(mapGameArray[(int)yArrayPos][(int)xArrayPos - 1] == '1')
				return true;
			
			else
				return false;
		}
		
		else if(ghostObject.getPosVector() == 'E')
		{
			if(mapGameArray[(int)yArrayPos][(int)xArrayPos + 1] == '1')
				return true;
			
			else
				return false;
		}
		
		else 
			return false;
	}
	
	else 
		return false;
	
}

//This function checks collisions between Pacman objects and Ghost objects and processes appropriate events.  
bool CollisionDetection::checkPacmanGhostsCollision(Pacman &pacmanObject, Ghost &ghostObject1, Ghost &ghostObject2, Ghost &ghostObject3, Ghost &ghostObject4,
													SDL_Surface * screen, SDL_Surface * blankImage, SDL_Surface * pelletsItemsImage, char mapGameArray[][40], SDL_Rect &imgRect, SDL_Rect &blitRect)
{
	int ghostArrayX = 0;
	int ghostArrayY = 0;

	if(!pacmanObject.getPacmanDead())
	{
		imgRect.x = 0;
		imgRect.y = 0;

		/**The following simply tests if Pacman has the same position as ghosts, then we have a collision**/

		//Ghost 1
		if(pacmanObject.getDx() / 20 == ghostObject1.getDx() / 20 && pacmanObject.getDy() / 20 == ghostObject1.getDy() / 20)
		{
			//If power pellet is on, ghost is eaten
			if(pacmanObject.getPowerPellet() == true)
			{

				blitRect.x = ghostObject1.getDx();
				blitRect.y = ghostObject1.getDy();

				//Blank image on the current Ghost 1 position
				SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);


				ghostArrayX = ghostObject1.getDx() / 20;
				ghostArrayY = ghostObject1.getDy() / 20;

				blitRect.x = ghostArrayX * 20;
				blitRect.y = ghostArrayY * 20;

				//Redraw pellet/powerpellet/fruit on the ghost posision if the ghost is eaten by pacman halv-way into a new posision on the array
				if(mapGameArray[ghostArrayY][ghostArrayX] == '2')
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);
		
				else if(mapGameArray[ghostArrayY][ghostArrayX] == '3')
				{
					imgRect.x = 20;
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);
				}
				
				else if(mapGameArray[ghostArrayY][ghostArrayX] == '4')
				{
					imgRect.x = 40;
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);

				}
				
				else if(mapGameArray[ghostArrayY][ghostArrayX] == '5')
				{
					imgRect.x = 60;
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);

				}

				ghostOne = true;

				pacmanObject.setScore(pacmanObject.getScore() + 200);

				ghostObject1.setGhostDead(true);
				
				helpFlag = false;

				return false;
			}
			
			//If power pellet is not on, pacman is eaten
			else
			{
				pacmanObject.setLife(pacmanObject.getLife() - 1);
				pacmanObject.setPacmanDead(true);
				
				helpFlag = true;

				return true;
			}	
		}

		//Ghost 2
		else if(pacmanObject.getDx() / 20 == ghostObject2.getDx() / 20 && pacmanObject.getDy() / 20 == ghostObject2.getDy() / 20)
		{
			//If power pellet is on, ghost is eaten
			if(pacmanObject.getPowerPellet() == true)
			{
				ghostTwo = true;

				blitRect.x = ghostObject2.getDx();
				blitRect.y = ghostObject2.getDy();

				//Blank image on the current Ghost 2 position
				SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);

				ghostArrayX = ghostObject2.getDx() / 20;
				ghostArrayY = ghostObject2.getDy() / 20;

				blitRect.x = ghostArrayX * 20;
				blitRect.y = ghostArrayY * 20;

				// Redraw pellet/powerpellet/fruit on the ghost posision if the ghost is eaten by pacman halv-way into a new posision on the array
				if(mapGameArray[ghostArrayY][ghostArrayX] == '2')
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);
				
				else if(mapGameArray[ghostArrayY][ghostArrayX] == '3')
				{
					imgRect.x = 20;
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);
				}
				
				else if(mapGameArray[ghostArrayY][ghostArrayX] == '4')
				{
					imgRect.x = 40;
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);

				}
				
				else if(mapGameArray[ghostArrayY][ghostArrayX] == '5')
				{
					imgRect.x = 60;
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);

				}

				pacmanObject.setScore(pacmanObject.getScore() + 200);
				ghostObject2.setDx(ghostObject2.getX());
				ghostObject2.setDy(ghostObject2.getY());
				ghostObject2.setGhostDead(true);

				helpFlag = false;
				
				return false;
			}
			
			//If power pellet is not on, pacman is eaten
			else
			{
				pacmanObject.setLife(pacmanObject.getLife() - 1);
				pacmanObject.setPacmanDead(true);

				helpFlag = true;
				
				return true;
			}	

		}

		//Ghost 3
		else if(pacmanObject.getDx() / 20 == ghostObject3.getDx() / 20 && pacmanObject.getDy() / 20 == ghostObject3.getDy() / 20)
		{

			//If power pellet is on, ghost is eaten
			if(pacmanObject.getPowerPellet() == true)
			{
				ghostThree = true;

				blitRect.x = ghostObject3.getDx();
				blitRect.y = ghostObject3.getDy();

				//Blank image on the current Ghost 3 position
				SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);

				ghostArrayX = ghostObject3.getDx() / 20;
				ghostArrayY = ghostObject3.getDy() / 20;

				blitRect.x = ghostArrayX * 20;
				blitRect.y = ghostArrayY * 20;
				
				// Redraw pellet/powerpellet/fruit on the ghost posision if the ghost is eaten by pacman halv-way into a new posision on the array
				if(mapGameArray[ghostArrayY][ghostArrayX] == '2')
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);
				
				else if(mapGameArray[ghostArrayY][ghostArrayX] == '3')
				{
					imgRect.x = 20;
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);
				}
				
				else if(mapGameArray[ghostArrayY][ghostArrayX] == '4')
				{
					imgRect.x = 40;
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);

				}
			
				else if(mapGameArray[ghostArrayY][ghostArrayX] == '5')
				{
					imgRect.x = 60;
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);

				}

				pacmanObject.setScore(pacmanObject.getScore() + 200);
				ghostObject3.setDx(ghostObject3.getX());
				ghostObject3.setDy(ghostObject3.getY());
				ghostObject3.setGhostDead(true);

				helpFlag = false;
				
				return false;
			}

			//If power pellet is not on, pacman is eaten
			else
			{
				pacmanObject.setLife(pacmanObject.getLife() - 1);
				pacmanObject.setPacmanDead(true);

				helpFlag = true;
				
				return true;
			}	

		}

		//Ghost 4
		else if(pacmanObject.getDx() / 20 == ghostObject4.getDx() / 20 && pacmanObject.getDy() / 20 == ghostObject4.getDy() / 20)
		{
			//If power pellet is on, ghost is eaten
			if(pacmanObject.getPowerPellet() == true)
			{
				ghostFour = true;

				blitRect.x = ghostObject4.getDx();
				blitRect.y = ghostObject4.getDy();

				//Blank image on the current Ghost 4 position
				SDL_BlitSurface(blankImage, &imgRect, screen, &blitRect);

				ghostArrayX = ghostObject4.getDx() / 20;
				ghostArrayY = ghostObject4.getDy() / 20;

				blitRect.x = ghostArrayX * 20;
				blitRect.y = ghostArrayY * 20;
				
				// Redraw pellet/powerpellet/fruit on the ghost posision if the ghost is eaten by pacman halv-way into a new posision on the array
				if(mapGameArray[ghostArrayY][ghostArrayX] == '2')
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);
				
				else if(mapGameArray[ghostArrayY][ghostArrayX] == '3')
				{
					imgRect.x = 20;
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);
				}
				
				else if(mapGameArray[ghostArrayY][ghostArrayX] == '4')
				{
					imgRect.x = 40;
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);

				}
				
				else if(mapGameArray[ghostArrayY][ghostArrayX] == '5')
				{
					imgRect.x = 60;
					SDL_BlitSurface(pelletsItemsImage, &imgRect, screen, &blitRect);

				}

				pacmanObject.setScore(pacmanObject.getScore() + 200);
				ghostObject4.setDx(ghostObject4.getX());
				ghostObject4.setDy(ghostObject4.getY());
				ghostObject4.setGhostDead(true);

				helpFlag = false;
				
				return false;
			}

			//If power pellet is not on, pacman is eaten
			else
			{
				pacmanObject.setLife(pacmanObject.getLife() - 1);
				pacmanObject.setPacmanDead(true);

				helpFlag = true;
				
				return true;
			}	
		}
	}	
	
	helpFlag = true;

	return false;
}

//This function checks a Pacman-Pacman collision and processes appropriate events (such as checking power pellets and setting Pacman dead flags).
bool CollisionDetection::checkPacmanPacmanCollision(Pacman &pacmanObject1, Pacman &pacmanObject2)
{
	if(!pacmanObject1.getPacmanDead() && !pacmanObject2.getPacmanDead())
	{
		//Collision
		if(pacmanObject1.getDx() / 20 == pacmanObject2.getDx() / 20 
			&& pacmanObject1.getDy() / 20 == pacmanObject2.getDy() / 20)
		{
			if(pacmanObject1.getPowerPellet() == true && pacmanObject2.getPowerPellet() == true)
			{
				//Do nothing
			}
							
			else if(pacmanObject1.getPowerPellet() == true && pacmanObject2.getPowerPellet() == false)
			{
				pacmanObject2.setPacmanDead(true);
				pacmanObject2.setLife(pacmanObject2.getLife() - 1);

				if(pacmanObject2.getLife() <= 0)
					pacmanObject2.setPacmanDeadFinal(true);

				return true;
			}

			else if (pacmanObject2.getPowerPellet() == true && pacmanObject1.getPowerPellet() == false)
			{
				pacmanObject1.setPacmanDead(true);
				pacmanObject1.setLife(pacmanObject1.getLife() - 1);

				if(pacmanObject1.getLife() <= 0)
					pacmanObject1.setPacmanDeadFinal(true);

				return true;
			}
		}		
	}

	return false;
}