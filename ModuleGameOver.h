#ifndef __MODULEGAMEOVER_H__
#define __MODULEGAMEOVER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleGameOver : public Module
{
public:

	ModuleGameOver();
	~ModuleGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* gameOverTexture = nullptr;
	SDL_Rect gameOverRect;
};

#endif //__MODULEGAMEOVER_H__