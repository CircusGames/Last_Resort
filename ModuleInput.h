#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
//#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_gamecontroller.h"

#define MAX_KEYS 300
#define MAX_GAMEPADS 2

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
	//SDL_GameController* gamePads[MAX_GAMEPADS] = { nullptr };

	struct gamepadData
	{
		SDL_GameController * gamePadController = nullptr;
		//int joystick_index;
		SDL_JoystickID joyId = -1;
		bool isConnected = false;
		bool up = false;
		bool down = false;
		bool right = false;
		bool left = false;
		Sint16 axisX = 0;
		Sint16 axisY = 0;
		int deadZone = 8000;
		bool shotPressed = false;
		bool lockUnitPressed = false;

	};

	gamepadData gamePadControllers[MAX_GAMEPADS];
};

#endif // __ModuleInput_H__