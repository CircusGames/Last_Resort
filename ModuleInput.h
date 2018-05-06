#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
//#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_gamecontroller.h"

#define MAX_KEYS 300

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

typedef unsigned char Uint8;


class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];
	//const Uint8 *keyboard = nullptr;
	SDL_Event Event;

	//gamepad
	//SDL_GameController* gameController; 
};

#endif // __ModuleInput_H__