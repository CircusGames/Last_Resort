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
	SDL_Texture* blackScreenTexture = nullptr;
	SDL_Rect gameOverFirstRect;
	SDL_Rect gameOverMidRect;
	SDL_Rect gameOverRect;

	Uint32 now;
	float start_time;
	float total_time;
	float lastFadeFromWhiteTime;
	int timeInWhite;

private:

	enum intro_step
	{
		firstSecuence,
		firstletters,
		secondletters,
		fade_to_white,
		time_in_white,
		fade_from_white,
		lastgameover,
	} current_step = intro_step::firstSecuence;
};

#endif //__MODULEGAMEOVER_H__