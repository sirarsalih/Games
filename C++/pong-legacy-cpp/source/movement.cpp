#include "../include/movement.h"
#include "SDL.h"

void movement::moveBall(SDL_Rect &rect, int dx, int dy)
{
	rect.x += dx;
	rect.y += dy;
}

void movement::movePaddleOneUp(SDL_Rect &rect)
{
	rect.y -= 1;
}
	
void movement::movePaddleOneDown(SDL_Rect &rect)
{
	rect.y += 1;
}

void movement::movePaddleTwoUp(SDL_Rect &rect)
{
	rect.y -= 1;
}
	
void movement::movePaddleTwoDown(SDL_Rect &rect)
{
	rect.y += 1;
}