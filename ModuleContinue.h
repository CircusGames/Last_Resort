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

	Animation countAnim;
	Animation fireAnim();

	SDL_Rect background;
	SDL_Rect cont;

	SDL_Texture* continueBack = nullptr;

};
#endif // !_MODULECONTINUE_H__
