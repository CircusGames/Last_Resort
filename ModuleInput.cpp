#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

#include "ModuleSceneLvl1.h" //for now scene lv1 spawn enemies debug mode

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	//controller
	LOG("Initializing controller-----------");

	//#define SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS 1

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("Failed to initialize gamePad controller ", SDL_GetError());
	}

	int maxJoysticks = SDL_NumJoysticks();
	
	for (int i = 0; i  < maxJoysticks ; ++i)//SDL_NumJoysticks(); i++)
	{

		//if (i > maxJoysticks) break;

		if (SDL_IsGameController(i))
		{
			gamePads[i] = SDL_GameControllerOpen(i);

		}

	}
	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	//LOG(SDL_GameControllerMapping(controller));

	

	// Keyboard input
	SDL_PumpEvents();
	
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	//keyboard = SDL_GetKeyboardState(NULL);

	if(keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	while (SDL_PollEvent(&Event)) //close window with mouse
	{
		if (Event.type == SDL_QUIT)
			return update_status::UPDATE_STOP;

		if (Event.type == SDL_MOUSEBUTTONDOWN)
		{
			App->scene_lvl1->spawnEnemies(Event.button.x, Event.button.y);
		}

		//detection at runtime if a gamepad is added or removed

		/*if (Event.type == SDL_CONTROLLERDEVICEADDED)
		{
			if (Event.cdevice.which > MAX_GAMEPADS -1)
			{
				LOG("Add controller failed: Max controllers simultaneously reached");
				break;
			}

			else if (SDL_IsGameController(Event.cdevice.which))
			{
				gamePads[Event.cdevice.which] = SDL_GameControllerOpen(Event.cdevice.which);
				LOG("Added controller: %d", Event.cdevice.which);
			}

		}*/

		//gamepad buttons input
		if (Event.cbutton.type == SDL_CONTROLLERBUTTONDOWN)
		{
			if (Event.cbutton.which == 0)
			{
			
				if (Event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
					App->input->keyboard[SDL_SCANCODE_SPACE] = KEY_DOWN;

				else if (Event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
					App->input->keyboard[SDL_SCANCODE_LSHIFT] = KEY_DOWN;
			}
			else //if (Event.cdevice.which == 0)
			{
				if (Event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
					App->input->keyboard[SDL_SCANCODE_RALT] = KEY_DOWN;

				else if (Event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
					App->input->keyboard[SDL_SCANCODE_RSHIFT] = KEY_DOWN;
			}
		}

		
	}

	// GamePads dpad and axis inputs ---------------------------------------------
	for (int i = 0; i < MAX_GAMEPADS; ++i)
	{
		if (gamePads[i] != nullptr)
		{
			//dpad directions
			 gamePadDirections[i].up = SDL_GameControllerGetButton(gamePads[i], SDL_CONTROLLER_BUTTON_DPAD_UP);
			 gamePadDirections[i].down = SDL_GameControllerGetButton(gamePads[i], SDL_CONTROLLER_BUTTON_DPAD_DOWN);
			 gamePadDirections[i].right = SDL_GameControllerGetButton(gamePads[i], SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
			 gamePadDirections[i].left = SDL_GameControllerGetButton(gamePads[i], SDL_CONTROLLER_BUTTON_DPAD_LEFT);
			 //axis input directions
			 gamePadDirections[i].axisX = SDL_GameControllerGetAxis(gamePads[i], SDL_CONTROLLER_AXIS_LEFTX);
			 gamePadDirections[i].axisY = SDL_GameControllerGetAxis(gamePads[i], SDL_CONTROLLER_AXIS_LEFTY);
		}
	}
	// ----------------------------------------------------------------------------

	// dpad events ---------------------------------------------------------------
	// player 1 ----
	if (gamePadDirections[0].up) keyboard[SDL_SCANCODE_W] = KEY_REPEAT;
	if (gamePadDirections[0].down) keyboard[SDL_SCANCODE_S] = KEY_REPEAT;
	if (gamePadDirections[0].right) keyboard[SDL_SCANCODE_D] = KEY_REPEAT;
	if (gamePadDirections[0].left) keyboard[SDL_SCANCODE_A] = KEY_REPEAT;
	// player 2 ----
	if (gamePadDirections[1].up) keyboard[SDL_SCANCODE_UP] = KEY_REPEAT;
	if (gamePadDirections[1].down) keyboard[SDL_SCANCODE_DOWN] = KEY_REPEAT;
	if (gamePadDirections[1].right) keyboard[SDL_SCANCODE_RIGHT] = KEY_REPEAT;
	if (gamePadDirections[1].left) keyboard[SDL_SCANCODE_LEFT] = KEY_REPEAT;

	// ---------------------------------------------------------------------------
	
	// axis ----------------------------------------------------------------------
	// player 1 x axis --------------------------------------------------
	if (gamePadDirections[0].axisX > gamePadDirections[0].deadZone)
		keyboard[SDL_SCANCODE_D] = KEY_REPEAT;
	else if (gamePadDirections[0].axisX < -gamePadDirections[0].deadZone)
		keyboard[SDL_SCANCODE_A] = KEY_REPEAT;
	// player 1 y axis -------------------------------------------------
	if (gamePadDirections[0].axisY < -gamePadDirections[0].deadZone)
		keyboard[SDL_SCANCODE_W] = KEY_REPEAT;
	else if (gamePadDirections[0].axisY > gamePadDirections[0].deadZone)
		keyboard[SDL_SCANCODE_S] = KEY_REPEAT;
	// ------------------------------------------------------------------
	// player 2 x axis -------------------------------------------------
	if (gamePadDirections[1].axisX > gamePadDirections[1].deadZone)
		keyboard[SDL_SCANCODE_RIGHT] = KEY_REPEAT;
	else if (gamePadDirections[1].axisX < -gamePadDirections[1].deadZone)
		keyboard[SDL_SCANCODE_LEFT] = KEY_REPEAT;
	// player 1 y axis -------------------------------------------------
	if (gamePadDirections[1].axisY < -gamePadDirections[1].deadZone)
		keyboard[SDL_SCANCODE_UP] = KEY_REPEAT;
	else if (gamePadDirections[1].axisY > gamePadDirections[1].deadZone)
		keyboard[SDL_SCANCODE_DOWN] = KEY_REPEAT;

	// ------------------------------------------------------------------
	//LOG("AXIS Y: %d", gamePadDirections[0].axisY);
	//LOG("SECOND AXIS Y: %d", gamePadDirections[1].axisY);
	


	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	LOG("Closing controller----");
	for (int i = 0; i < MAX_GAMEPADS; ++i)
	{
		if (gamePads[i] != nullptr)
			SDL_GameControllerClose(gamePads[i]);

		gamePads[i] = nullptr;

	}
	return true;
}