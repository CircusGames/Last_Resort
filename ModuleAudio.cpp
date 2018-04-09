//for now loads specific audio music, to do: function to load
//specific char pointer array of songs and fx

#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL\include\SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"

#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio() : Module() {}

ModuleAudio::~ModuleAudio() {}

bool ModuleAudio::Init()
{
	LOG("Init Module Audio");

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

	/*if (!music)
	{
		LOG("Music cannot be loaded: %s", SDL_GetError());
		ret = false;
	}*/

	return ret;
}

	Mix_Music* const ModuleAudio::LoadMUS(const char* path, char* name) 
	{

		Mix_Music *music = nullptr;
		char *_name = name;

		music = Mix_LoadMUS(path);

		if (music == nullptr)
		{
			LOG("Unable to load music Mix Error: %s\n", Mix_GetError());
		}
		else
		{
			songsArray[last_song].songs = music;
			songsArray[last_song].name = _name;
			last_song++;
		}
		return music;
	}

	void ModuleAudio::ControlMUS(char* name, audio_state state , float fadeInTimeMs,float fadeOffTimeMs)
	{
		Mix_Music *music = nullptr;
		char *_name = name;
		
		for (int i = 0; i <= last_song; ++i) //here we have some problem, 3-4 loop game Over not sound...
		{
			if (songsArray[i].name == _name) {
				music = songsArray[i].songs;
			}
		}


		if (music == nullptr) {
			LOG("Music not found ControlMUS : %s\n", name);
		}
		else {
			switch (state)
			{
			case PLAY:
				if (!Mix_PlayingMusic())
					Mix_PlayMusic(music, 3);
				else
					LOG("Music is already played : %s\n", name);
				break;
			case STOP:
				if (!Mix_PausedMusic())
					Mix_PauseMusic();
				else
					LOG("Music is already stoped : %s\n", name);
				break;
			case FADEIN:
				if (!Mix_FadingMusic() || !Mix_PlayingMusic)
					Mix_FadeInMusic(music,-1, (int)fadeInTimeMs);
				else
					LOG("Music is already fading or playing : %s\n", name);
				break;
			case FADEOFF:
				if (Mix_PlayingMusic())
					Mix_FadeOutMusic((int)fadeOffTimeMs);
				else
					LOG("Music is already faded out or stoped : %s\n", name);
				break;

			default:
				break;
			}
		}
	}

	void ModuleAudio::UnloadMus(char* name)
	{

		//returns memory
		char *_name = name;

		for (int i = 0; i < MAX_SONGS -1; ++i) 
		{
			if (songsArray[i].name == _name) 
			{
				Mix_FreeMusic(songsArray[i].songs);
				songsArray[i].songs = nullptr;
				songsArray[i].name = nullptr;
			}
		}
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

	//return ret;

//}

bool ModuleAudio::CleanUp()
{
	LOG("stop music");

	/*for (int i = 0; i < MAX_SONGS; ++i)
		if (sfx[i].chunk != nullptr) 
		{
			Mix_FreeChunk(sfx[i].chunk);
			sfxArray[i].fx = nullptr;
			sfxArray[i].name = nullptr;
		}*/

	for (int i = 0; i < MAX_FX -1; ++i)
		if (songsArray[i].songs != nullptr) 
		{
			Mix_FreeMusic(songsArray[i].songs);
			songsArray[i].songs = nullptr;
			songsArray[i].name = nullptr;
		}

	/*while (!Mix_FadeOutMusic(500) && Mix_PlayingMusic()); //fadeOutMusic ???
	Mix_FreeMusic(music);
	music = nullptr;
	//Mix_FreeChunk(fx); //not implemented yet */
	Mix_CloseAudio();
	Mix_Quit();

	return true;
}
