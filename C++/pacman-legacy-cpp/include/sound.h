/***************************************************************************************************************************************
****************************************************************************************************************************************

This is the sound class. All music and sounds are loaded and played from here. 

****************************************************************************************************************************************
***************************************************************************************************************************************/

#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>

class Sound
{

public:

	//Default constructor
	Sound();

	//Load sound files function
	void loadSounds();

	//Play main menu music function
	void playSoundMainMenuMusic();

	//Play Pacman movement sound function
	void playSoundPacmanMove();

	//Play Pacman eat power pellet sound function
	void playSoundPacmanPowerPellet();
	
	//Play Pacman eat bonus item sound function
	void playSoundPacmanBonusItem();
	
	//Play Pacman die sound function
	void playSoundPacmanDie();
	
	//Play Ghost movement sound function
	void playSoundGhostMove();
	
	//Stop main menu music sound function
	void stopMainMenuMusic();
	
	//Free music and chunks function
	void freeChunks();
	
	//Close audio channel function
	void closeSound();
	
	//Get sound function
	static bool getSound();
	
	//Set sound function
	static void setSound(bool sound);

private:
	
	//Sound boolean flag
	static bool sound;

};

#endif