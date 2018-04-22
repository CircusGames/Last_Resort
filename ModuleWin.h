#ifndef __MODULEWIN_H__
#define __MODULEWIN_H__

#include "Module.h"
#include "Globals.h"
//#include "Animation.h"
#include "ModuleUI.h"

struct SDL_Texture;


class ModuleWin : public Module
{
public:

	ModuleWin();
	//~ModuleWin();

	bool Start();
	update_status Update();
	bool CleanUp();

	void saveScore(int score);

public:

	
	SDL_Texture * winInterface;
	SDL_Texture* winBackground;

	
public:

	SDL_Rect winInterfaceRect;
	SDL_Rect winBackgroundRect;

	int allScores[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int actualScore;
	int temp;

};
#endif // !__MODULEWIN_H__
