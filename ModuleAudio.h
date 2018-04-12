#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Globals.h"
#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_SONGS 10
#define MAX_FX 64

enum type
{
	MUSIC,
	SFX
};

enum audio_state
{
	PLAY,
	STOP,
	FADEIN,
	FADEOFF,
};

struct sfx
{
	Mix_Chunk* chunk;
	char* name;
};

struct songsStruct
{
	Mix_Music* songs;
	char* name;
};


class ModuleAudio : public Module
{
private:
	songsStruct songsArray[MAX_SONGS] = { nullptr };
	sfx sfxArray[MAX_FX] = { nullptr };

	int last_chunk = 0;
	int last_song = 0;

public:

	ModuleAudio();
	~ModuleAudio();

	bool Init();
	Mix_Chunk* const LoadSfx(const char* path, char *name);
	Mix_Music* const LoadMUS(const char* path, char *name);
	void UnloadMus(char* name);
	//update_status update(); //not for now
	void ControlAudio(char* name, type type,audio_state state, float fadeInTimeMs = 1000.0f, float fadeOffTimeMs = 500.0f);
	bool CleanUp();



};

#endif