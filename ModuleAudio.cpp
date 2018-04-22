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

	Mix_AllocateChannels(48);

	return ret;
}

void ModuleAudio::UnloadAudio(const char* name, type type)
{
	if (type == type::MUSIC)
	{
		for (int i = 0; i < MAX_SONGS - 1; ++i)
		{
			if (songsArray[i].name == name)
			{
				Mix_FreeMusic(songsArray[i].songs);
				songsArray[i].songs = nullptr;
				songsArray[i].name = nullptr;
				break;
			}
		}
	}
	else if (type == type::SFX)
	{
		for (int i = 0; i < MAX_FX - 1; ++i)
		{
			if (sfxArray[i].name == name)
			{
				Mix_FreeChunk(sfxArray[i].chunk);
				sfxArray[i].chunk = nullptr;
				sfxArray[i].name = nullptr;
				break;
			}
		}
	}
	else LOG("Error: no type specified, freeing nothing");
}


bool ModuleAudio::LoadAudio(const char* path, char* name, type type)
{
	bool ret = true;

	Mix_Music *ogg = nullptr;
	Mix_Chunk* wav = nullptr;

	if (type == type::MUSIC)
	{
		ogg = Mix_LoadMUS(path);

		if (ogg == nullptr)
		{
			LOG("Unable to load music Mix Error: %s\n", Mix_GetError());
			ret = false;
		}
		else
		{
			for (int i = 0; i < MAX_SONGS; ++i)
			{
				if (songsArray[i].songs == nullptr)
				{
					songsArray[i].songs = ogg;
					songsArray[i].name = name;
					break;
				}
			}
		}
	}
	else if (type == type::SFX)
	{
		wav = Mix_LoadWAV(path);

		if (wav != nullptr)
		{
			for (int i = 0; i < MAX_FX; ++i)
			{
				if (sfxArray[i].chunk == nullptr)
				{
					sfxArray[i].chunk = wav;
					sfxArray[i].name = name;
					break;
				}
			}
		}
	}
	else
	{
		LOG("bad parameters for audio load");
		ret = false;
	}

	return ret;
}


void ModuleAudio::ControlAudio(char* name, type type, audio_state state ,int loops, float fadeInTimeMs,float fadeOffTimeMs)
{

	Mix_Chunk* wav = nullptr;		
	Mix_Music *music = nullptr;
	char *_name = name;
		
	if (type == type::MUSIC)
	{
		for (int i = 0; i < MAX_SONGS; ++i) // here is the problem? 
		{
			if (songsArray[i].name == _name) 
			{
					music = songsArray[i].songs;
			}
		}
		if (music == nullptr) {
			LOG("Music not found ControlAudio : %s\n", name);
		}
		else
		{
			switch (state)
			{
			case PLAY:
				if (!Mix_PlayingMusic())
					Mix_PlayMusic(music, loops);
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
					Mix_FadeInMusic(music, loops, (int)fadeInTimeMs);
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
	else if(type == type::SFX)
	{
		for (int i = 0; i < MAX_FX; ++i) 
		{
			if (sfxArray[i].name == _name) {
				wav = sfxArray[i].chunk;
			}
		}
		switch (state)
		{
		case PLAY:
			//Mix_PlayChannel(-1, wav, loops);
			if (Mix_PlayChannel(-1, wav, loops) == -1) {
				LOG("Mix_PlayChannel Error: %s", Mix_GetError());
			}
			break;

		default:
			break;
		
			//more to come
		}
	}	
}


bool ModuleAudio::CleanUp()
{
	LOG("Freeing music and effects");

	//unloading fx
	for (int i = 0; i < MAX_FX; ++i)
		if (sfxArray[i].chunk != nullptr) 
		{
			Mix_FreeChunk(sfxArray[i].chunk);
			sfxArray[i].chunk = nullptr;
			sfxArray[i].name = nullptr;
		}
	//unloading music ogg's
	for (int i = 0; i < MAX_SONGS -1; ++i)
		if (songsArray[i].songs != nullptr) 
		{
			Mix_FreeMusic(songsArray[i].songs);
			songsArray[i].songs = nullptr;
			songsArray[i].name = nullptr;
		}

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}
