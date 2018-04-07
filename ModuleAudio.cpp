//for now loads specific audio music, to do: function to load
//specific char pointer array of songs and fx

#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL\include\SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"

#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

bool ModuleAudio::Init()
{
	bool ret = true;
	if (SDL_Init(SDL_INIT_AUDIO) == -1) //initializes SDL audio
	{
		LOG("SDL failed at initialize audio subsystem %s", SDL_GetError());
		ret = false;
	};

	int flags = MIX_INIT_OGG;
	int initted = Mix_Init(flags); //load support for ogg format (sdl init audio must be called before this)
	if (initted&&flags != flags)
	{
		LOG("Mix Init failed to init required ogg: %s", Mix_GetError());
		ret = false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		LOG("Mix OpenAudio Failed at open audio channel %s", Mix_GetError());
		ret = false;
	};


	music = Mix_LoadMUS("assets/song1.ogg");

	if (!music)
	{
		LOG("Music cannot be loaded: %s", SDL_GetError());
		ret = false;
	}


	/*if (Mix_FadeInMusic(music, -1, 1000) == -1) //play music with fadeIn
	{
		LOG("Fade in Music failed: %s", Mix_GetError());
		ret = false;
	}*/

	/*if (Mix_PlayMusic(music, -1) == -1) //play music without fade in
	{
	LOG("Mix_PlayMusic failed: %s", Mix_GetError());
	ret = false;
	};*/

	//here should be initialized the FX audio
	//...... nothing for now : )

	return ret;

}

bool ModuleAudio::CleanUp()
{
	while (!Mix_FadeOutMusic(500) && Mix_PlayingMusic()); //fadeOutMusic ???
	Mix_FreeMusic(music);
	music = nullptr;
	//Mix_FreeChunk(fx); //not implemented yet
	Mix_CloseAudio();
	Mix_Quit();

	return true;
}
