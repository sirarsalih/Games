#include "SDL.h"

class game{

private:

	static const int screenWidth = 640;
	static const int screenHeight = 480;
	static const int screenBpp = 32;
	char * files[3];
	char * score[10];
	char * win[2];
	char * sound[2];
	int scoreCount1;
	int scoreCount2;
	int counter;
	int randomDx;
	int randomDy;
	int randomNum[2];
	bool showScoreOne;
	bool showScoreTwo;
	bool flag;
	bool flag2;
	bool paddleOneHit;
	bool paddleTwoHit;
	bool upWallHit;
	bool downWallHit;
	bool wallCollision;
	bool quit;

public:

	game();
	void run();
	void blitAndFlip(SDL_Surface * graphicObjects[3], SDL_Rect rects[3]);
	void playSound(char * sound[2], const int element);
	void doEvents(SDL_Rect rects[3]);

};