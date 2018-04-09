#ifndef __MODULEPLAYERUNIT_H__
#define __MODULEPLAYERUNIT_H__

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
	update_status Update();
	bool CleanUp();

public:
	//some needed vars or specific functions
	Animation playerUnitAnim;

};
#endif // !__MODULEPLAYERUNIT_H__
