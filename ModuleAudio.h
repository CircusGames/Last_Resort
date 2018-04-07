#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Globals.h"
#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"

class ModuleAudio : public Module
{
public:

	bool Init();
	//here method to load array of songs

	//update_status update(); //not for now
	bool CleanUp();

public:

	Mix_Music* music = nullptr;
	Mix_Chunk* fx = nullptr;

};

#endif