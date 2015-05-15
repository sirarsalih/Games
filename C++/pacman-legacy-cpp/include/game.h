/***************************************************************************************************************************************
****************************************************************************************************************************************

This is the game class. *Only* in-game events are directly handled here (including score/life panel of players). The game class constantly 
calls up the map class to update the maps of the game (and to move ghosts A.I.). The class also handles a special situation in the game; 
basicaly when both Pacman objects collide with each other (I.E. a Pacman-Pacman collision). In-game key events are also handled here. 
By in-game we mean when a player is playing in a map in real time, thus we exclude game menus (these are handled in their own class).

****************************************************************************************************************************************
***************************************************************************************************************************************/

#ifndef GAME_H
#define GAME_H

class Game
{

public:

	//Default constructor
	Game();

	//Run function. This function starts the game.
	static void run();

	//Multiplayer flag
	static bool multiplayer;

private:

	/*Screen dimensions*/
	static const int SCREENWIDTH = 800;
	static const int SCREENHIGHT = 600;
	static const int SCREENBPP = 32;
};

#endif