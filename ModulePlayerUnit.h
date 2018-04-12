#ifndef __MODULEPLAYERUNIT_H__
#define __MODULEPLAYERUNIT_H__

#define MAX_ANIMS 16

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include <math.h>

class ModulePlayerUnit : public Module
{
public:
	struct axisPos
	{
		float x, y;
	} playerPos;

public:

	ModulePlayerUnit();
	~ModulePlayerUnit();
	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

public:
	//some needed vars or specific functions
	SDL_Texture* playerUnitBlue;
	Animation playerUnitAnim[MAX_ANIMS];
	Animation *currentUnitAnim;

	int unitIndex; //stores the index of the last
	float frameIncrement = 0; //stores the index for applicate the speed of the rotation and points to its correct
						      //and current frame
	float lastFrame; //stores last frame to start next position

	bool unitLocked = false;

	int pivotArrayPositionsX[16] = { 1,1,1,1,1,2,6,7,7,7,6,2,1,1,1,1 };

	int pivotArrayPositionsY[16] = { 1,2,6,8,7,8,6,2,1,1,1,1,1,1,1,1 };								

	//values needed to control the circular position movement
	float orbitSpeed = 3.0f;
	float angle = 0;
	float last_tick;
	float delta_time;

};
#endif // !__MODULEPLAYERUNIT_H__
