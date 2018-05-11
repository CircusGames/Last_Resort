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

	//if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("Failed to initialize gamePad controller ", SDL_GetError());
	}

	//int maxJoysticks = SDL_NumJoysticks();
	
	for (int i = 0; i  < SDL_NumJoysticks() ; ++i)//SDL_NumJoysticks(); i++)
	//for (int i = 0; i < MAX_GAMEPADS - 1; ++i)
	{

		//if (i > maxJoysticks) break;

		if (SDL_IsGameController(i))
		{
			gamePadControllers[i].gamePadController = SDL_GameControllerOpen(i);
		
			SDL_Joystick* j = SDL_GameControllerGetJoystick(gamePadControllers[i].gamePadController);

			gamePadControllers[i].joyId = SDL_JoystickInstanceID(j);
			gamePadControllers[i].isConnected = true;

		}

	}

	/*int MaxJoysticks = SDL_NumJoysticks();
	int ControllerIndex = 0;
	for (int JoystickIndex = 0; JoystickIndex < MaxJoysticks; ++JoystickIndex)
	{
		if (!SDL_IsGameController(JoystickIndex))
		{
			continue;
		}
		if (ControllerIndex >= MAX_GAMEPADS)
		{
			break;
		}
		gamePads[ControllerIndex] = SDL_GameControllerOpen(JoystickIndex);
		ControllerIndex++;
	}*/

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

		if (Event.type == SDL_CONTROLLERDEVICEADDED)
		{

			for (int i = 0; i < MAX_GAMEPADS ; ++i)
			{
				
				//if (!gamePadControllers[i].isConnected)
				if (gamePadControllers[i].gamePadController == nullptr && gamePadControllers[i].joyId == -1)
					{
						gamePadControllers[i].gamePadController = SDL_GameControllerOpen(i);
						gamePadControllers[i].isConnected = true;

						//gamePadControllers[i].joyId = Event.cdevice.which;
						SDL_Joystick* j = SDL_GameControllerGetJoystick(gamePadControllers[i].gamePadController);

						gamePadControllers[i].joyId = SDL_JoystickInstanceID(j);

						LOG("Connected gamepad index: %d", gamePadControllers[i].joyId);
						break;
					}
				
			}
		}

		if (Event.type == SDL_CONTROLLERDEVICEREMOVED)
		{
			for (int i = 0; i < MAX_GAMEPADS ; ++i)
			{
				if (gamePadControllers[i].joyId == Event.cdevice.which)
				{
					SDL_GameControllerClose(gamePadControllers[i].gamePadController);
					gamePadControllers[i].isConnected = false;
					gamePadControllers[i].gamePadController = nullptr;
					gamePadControllers[i].joyId = -1;
					
					LOG("Disconnected gamepad index: %d", i)
					break;
				}
			}
		}
			
		//gamepad buttons input
		
		if (Event.type == SDL_CONTROLLERBUTTONDOWN)
		{
			if (Event.cdevice.which == gamePadControllers[0].joyId)
			{
				if (Event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
					App->input->keyboard[SDL_SCANCODE_SPACE] = KEY_DOWN;
				if (Event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
					App->input->keyboard[SDL_SCANCODE_LSHIFT] = KEY_DOWN;
				if (Event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
					App->input->keyboard[SDL_SCANCODE_RETURN] = KEY_DOWN;
			
				gamePadControllers[0].up = SDL_GameControllerGetButton(gamePadControllers[0].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_UP);
				gamePadControllers[0].down = SDL_GameControllerGetButton(gamePadControllers[0].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
				gamePadControllers[0].right = SDL_GameControllerGetButton(gamePadControllers[0].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
				gamePadControllers[0].left = SDL_GameControllerGetButton(gamePadControllers[0].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
			}
			if (Event.cdevice.which == gamePadControllers[1].joyId)
			{
				if (Event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
					App->input->keyboard[SDL_SCANCODE_RALT] = KEY_DOWN;
				if (Event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
					App->input->keyboard[SDL_SCANCODE_RSHIFT] = KEY_DOWN;
				if (Event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
				{
					App->input->keyboard[SDL_SCANCODE_RETURN] = KEY_DOWN;
					App->input->keyboard[SDL_SCANCODE_P] = KEY_DOWN; //activates second player

				}

				gamePadControllers[1].up = SDL_GameControllerGetButton(gamePadControllers[1].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_UP);
				gamePadControllers[1].down = SDL_GameControllerGetButton(gamePadControllers[1].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
				gamePadControllers[1].right = SDL_GameControllerGetButton(gamePadControllers[1].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
				gamePadControllers[1].left = SDL_GameControllerGetButton(gamePadControllers[1].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
				
			}
		}
		
		else if (Event.type == SDL_CONTROLLERBUTTONUP)
		{
			if (Event.cdevice.which == gamePadControllers[0].joyId)
			{
				//release directions

				gamePadControllers[0].up = SDL_GameControllerGetButton(gamePadControllers[0].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_UP);
				gamePadControllers[0].down = SDL_GameControllerGetButton(gamePadControllers[0].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
				gamePadControllers[0].right = SDL_GameControllerGetButton(gamePadControllers[0].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
				gamePadControllers[0].left = SDL_GameControllerGetButton(gamePadControllers[0].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_LEFT);

			}

			if (Event.cdevice.which == gamePadControllers[1].joyId)
			{

				gamePadControllers[1].up = SDL_GameControllerGetButton(gamePadControllers[1].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_UP);
				gamePadControllers[1].down = SDL_GameControllerGetButton(gamePadControllers[1].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
				gamePadControllers[1].right = SDL_GameControllerGetButton(gamePadControllers[1].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
				gamePadControllers[1].left = SDL_GameControllerGetButton(gamePadControllers[1].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_LEFT);

			}
	
		}
		
	}

	// GamePads dpad and axis inputs ---------------------------------------------
	for (int i = 0; i < MAX_GAMEPADS; ++i)
	{
		if (gamePadControllers[i].gamePadController != nullptr) //&& SDL_GameControllerGetAttached(gamePadControllers[i].gamePadController))
		//if (gamePadControllers[i].joyId == i)

		{
			//dpad directions
			 gamePadControllers[i].up = SDL_GameControllerGetButton(gamePadControllers[i].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_UP);
			 gamePadControllers[i].down = SDL_GameControllerGetButton(gamePadControllers[i].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
			 gamePadControllers[i].right = SDL_GameControllerGetButton(gamePadControllers[i].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
			 gamePadControllers[i].left = SDL_GameControllerGetButton(gamePadControllers[i].gamePadController, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
			 //axis input directions
			 gamePadControllers[i].axisX = SDL_GameControllerGetAxis(gamePadControllers[i].gamePadController, SDL_CONTROLLER_AXIS_LEFTX);
			 gamePadControllers[i].axisY = SDL_GameControllerGetAxis(gamePadControllers[i].gamePadController, SDL_CONTROLLER_AXIS_LEFTY);

		}
	}
	// ----------------------------------------------------------------------------
	
	// dpad events ---------------------------------------------------------------
	// player 1 ----
	if (gamePadControllers[0].up) keyboard[SDL_SCANCODE_W] = KEY_REPEAT;
	if (gamePadControllers[0].down) keyboard[SDL_SCANCODE_S] = KEY_REPEAT;
	if (gamePadControllers[0].right) keyboard[SDL_SCANCODE_D] = KEY_REPEAT;
	if (gamePadControllers[0].left) keyboard[SDL_SCANCODE_A] = KEY_REPEAT;
	// player 2 ----
	if (gamePadControllers[1].up) keyboard[SDL_SCANCODE_UP] = KEY_REPEAT;
	if (gamePadControllers[1].down) keyboard[SDL_SCANCODE_DOWN] = KEY_REPEAT;
	if (gamePadControllers[1].right) keyboard[SDL_SCANCODE_RIGHT] = KEY_REPEAT;
	if (gamePadControllers[1].left) keyboard[SDL_SCANCODE_LEFT] = KEY_REPEAT;

	// ---------------------------------------------------------------------------
	
	// axis ----------------------------------------------------------------------
	// player 1 x axis --------------------------------------------------
	if (gamePadControllers[0].axisX > gamePadControllers[0].deadZone)
		keyboard[SDL_SCANCODE_D] = KEY_REPEAT;
	else if (gamePadControllers[0].axisX < -gamePadControllers[0].deadZone)
		keyboard[SDL_SCANCODE_A] = KEY_REPEAT;
	// player 1 y axis -------------------------------------------------
	if (gamePadControllers[0].axisY < -gamePadControllers[0].deadZone)
		keyboard[SDL_SCANCODE_W] = KEY_REPEAT;
	else if (gamePadControllers[0].axisY > gamePadControllers[0].deadZone)
		keyboard[SDL_SCANCODE_S] = KEY_REPEAT;
	// ------------------------------------------------------------------
	// player 2 x axis -------------------------------------------------
	if (gamePadControllers[1].axisX > gamePadControllers[1].deadZone)
		keyboard[SDL_SCANCODE_RIGHT] = KEY_REPEAT;
	else if (gamePadControllers[1].axisX < -gamePadControllers[1].deadZone)
		keyboard[SDL_SCANCODE_LEFT] = KEY_REPEAT;
	// player 2 y axis -------------------------------------------------
	if (gamePadControllers[1].axisY < -gamePadControllers[1].deadZone)
		keyboard[SDL_SCANCODE_UP] = KEY_REPEAT;
	else if (gamePadControllers[1].axisY > gamePadControllers[1].deadZone)
		keyboard[SDL_SCANCODE_DOWN] = KEY_REPEAT;

	// ------------------------------------------------------------------
	//LOG("AXIS Y: %d", gamePadDirections[0].axisY);
	//LOG("SECOND AXIS Y: %d", gamePadDirections[1].axisY);
	
	//LOG("NUM JOYSTICKS: %d", SDL_NumJoysticks());


	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	LOG("Closing controller----");
	for (int i = 0; i < MAX_GAMEPADS ; ++i)
	{
		if (gamePadControllers[i].gamePadController != nullptr)
			SDL_GameControllerClose(gamePadControllers[i].gamePadController);

		gamePadControllers[i].gamePadController = nullptr;

	}
	return true;
}