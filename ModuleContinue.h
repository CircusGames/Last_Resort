#ifndef _MODULECONTINUE_H__
#define _MODULECONTINUE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleContinue : public Module
{
public:
	
	ModuleContinue();
	~ModuleContinue();

	bool Start();
	update_status Update();
	bool CleanUp();

private:

	Animation numbersAnim;
	Animation fireAnim[8];

	SDL_Rect backgroundRect;
	SDL_Rect continueRect;
	
	int number = NULL;
	bool cycle = NULL;
	float normalized = NULL;
	float alpha = NULL;

	SDL_Texture* backgroundTexture;
	SDL_Texture* continueTexture;

	Uint32 timeBetweenNumbers;
	Uint32 fireProgessionCounter;

};
#endif // !_MODULECONTINUE_H__
