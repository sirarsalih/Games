#include "SDL.h"

class movement{

public:
	void moveBall(SDL_Rect &rect, int dx, int dy);
	void movePaddleOneUp(SDL_Rect &rect);
	void movePaddleOneDown(SDL_Rect &rect);
	void movePaddleTwoUp(SDL_Rect &rect);
	void movePaddleTwoDown(SDL_Rect &rect);

};