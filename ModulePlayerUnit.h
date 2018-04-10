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
private:
	struct axisPos
	{
		int x, y;
	};

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
	//Animation playerUnit1Basic;
	//Animation playerUnit1Extra;
	//Animation playerUnit2Basic;

	int pivotArrayPositionsX[128] = { 1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1, //
									  2,2,2,2,2,2,2,2,
									  6,6,6,6,6,6,6,6,
									  7,7,7,7,7,7,7,7,
									  7,7,7,7,7,7,7,7,
									  7,7,7,7,7,7,7,7,
									  6,6,6,6,6,6,6,6,
									  2,2,2,2,2,2,2,2,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1
	};

	int pivotArrayPositionsY[128] = { 1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
								      1,1,1,1,1,1,1,1, //
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  1,1,1,1,1,1,1,1,
									  2,2,2,2,2,2,2,2,
									  6,6,6,6,6,6,6,6,
									  8,8,8,8,8,8,8,8,
									  7,7,7,7,7,7,7,7,
									  8,8,8,8,8,8,8,8,
									  6,6,6,6,6,6,6,6,
									  2,2,2,2,2,2,2,2,
									  1,1,1,1,1,1,1,1
	};

	float orbitSpeed = 3.0f;
	float angle = 0;
	int numFullCircles;
	float last_tick;
	float delta_time;

	bool newLap = false;

};
#endif // !__MODULEPLAYERUNIT_H__
