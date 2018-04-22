#ifndef _MODULEREADY_H__
#define _MODULEREADY_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleReady : public Module
{
public:

	ModuleReady();
	~ModuleReady();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* readyTexture = nullptr;
	SDL_Rect readyRect;

private:

	Uint32 now;
	float startTime;
	float totalTime;
};
#endif // !_MODULEREADY_H__
