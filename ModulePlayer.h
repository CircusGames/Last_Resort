#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:

	enum player_state
	{
		spawn,
		normal,
		died

	} player_step = player_state::spawn;

public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp(); 

public:

	SDL_Texture* player = nullptr;
	Animation idle;
	
	iPoint position;

	Animation playerAnim;
	Animation spawnAnim;

	float frameIncrement;
	float ignitionSpeed;
	float releaseSpeed;
	
	float playerSpeed;

	//float playerSpeedUp; //individual values for avoid float cast delay when changes direction
	//float playerSpeedDown;

};

#endif