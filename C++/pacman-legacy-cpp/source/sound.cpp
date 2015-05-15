/***************************************************************************************************************************************
****************************************************************************************************************************************

This is the sound class. All music and sounds are loaded and played from here. 

****************************************************************************************************************************************
***************************************************************************************************************************************/

#include <SDL.h>
#include <SDL_mixer.h>
#include "sound.h"

/*Initialize music and chunks*/
Mix_Music * music = NULL;
Mix_Chunk * pacmanMove = NULL;
Mix_Chunk * pacmanPowerPellet = NULL;
Mix_Chunk * pacmanBonusItem = NULL;
Mix_Chunk * pacmanDie = NULL;
Mix_Chunk * ghostMove = NULL;

//Initialize sound flag
bool Sound::sound = true;

//Default constructor
Sound::Sound()
{
	
}

//Load sound files function
void Sound::loadSounds()
{
	//Load music/sound files
	music = Mix_LoadMUS("../sound/music.wav");
	pacmanMove = Mix_LoadWAV("../sound/pacman_move.wav");
	pacmanPowerPellet = Mix_LoadWAV("../sound/pacman_eat_powerpellet.wav");
	pacmanBonusItem = Mix_LoadWAV("../sound/pacman_eat_bonus_item.wav");
	pacmanDie = Mix_LoadWAV("../sound/pacman_die.wav");
	ghostMove = Mix_LoadWAV("../sound/ghost_move.wav");
}

//Play main menu music function
void Sound::playSoundMainMenuMusic()
{
	//Play music
	Mix_PlayMusic(music, -1);
}

//Play Pacman movement sound function
void Sound::playSoundPacmanMove()
{
	//Play sound
	Mix_PlayChannel(1, pacmanMove, 0);
}		

//Play Pacman eat power pellet sound function
void Sound::playSoundPacmanPowerPellet()
{
	//Play sound
	Mix_PlayChannel(2, pacmanPowerPellet, 0);
}

//Play Pacman eat bonus item sound function
void Sound::playSoundPacmanBonusItem()
{
	//Play sound
	Mix_PlayChannel(3, pacmanBonusItem, 0);
}

//Play Pacman die sound function
void Sound::playSoundPacmanDie()
{
	//Play sound
	Mix_PlayChannel(4, pacmanDie, 0);
}

//Play Ghost movement sound function
void Sound::playSoundGhostMove()
{
	//Play sound
	Mix_PlayChannel(5, ghostMove, 0);
}

//Stop main menu music sound function
void Sound::stopMainMenuMusic()
{
	//Stop music
	Mix_HaltMusic();
}

//Free music and chunks function
void Sound::freeChunks()
{
	//Free music/chunks
	Mix_FreeMusic(music);
	Mix_FreeChunk(pacmanMove);
	Mix_FreeChunk(pacmanPowerPellet);
	Mix_FreeChunk(pacmanBonusItem);
	Mix_FreeChunk(pacmanDie);
}

//Close audio channel function
void Sound::closeSound()
{
	//Close sound
	Mix_CloseAudio();
}

//Get sound function
bool Sound::getSound()
{
	return sound;
}

//Set sound function
void Sound::setSound(static bool sound)
{
	Sound::sound = sound;
}
