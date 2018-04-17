#ifndef _MODULEPICKUPS_H__
#define _MODULEPICKUOS_H__

#include "Module.h"

enum PICK_UP
{
	H_POWER,
	L_POWER,
	G_POWER,
	S_POWER,
	Z_POWER
};

class ModulePickUps : public Module
{

public:
	ModulePickUps();
	~ModulePickUps();

	bool Start();
	update_status Update();
	bool CleanUp();

};
#endif // !_MODULEPOWERUPS_H__
