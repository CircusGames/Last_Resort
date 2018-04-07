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
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	//bool CleanUp(); //returns animation rects memory to system

public:

	SDL_Texture* player = nullptr;
	Animation idle;
	
	iPoint position;

	Animation playerAnim;

	/*bool isUp = false;
	bool isDown = false;
	bool topDown = false; //if player reaches top down screen
	int lastFrame = 0;*/

	float frameIncrement;
	float ignitionSpeed;
	float releaseSpeed;
	
	float playerSpeed;

	//float playerSpeedUp; //individual values for avoid float cast delay when changes direction
	//float playerSpeedDown;

};

#endif