#ifndef __MODULEPOWERUP_H__
#define __MODULEPOWERUP_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleEnemies.h"
//#include "ModuleCollision.h"

#define MAX_ACTIVES 10
#define MAX_TYPES 6

struct SDL_Texture;

struct powerUpTypeBox
{
	SDL_Texture* texture = nullptr;
	powerUpTypes type;
	Collider* collider = nullptr;
	iPoint position;
};

class ModulePowerUp : public Module
{
public:
	
	ModulePowerUp();
	~ModulePowerUp();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	powerUpTypeBox* powerUpActives[MAX_ACTIVES];
	//iPoint coordinate;

	SDL_Texture * powerUpUnit;

	void powerUpSpawn(powerUpTypes type, iPoint coordinate);
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture * test = nullptr;
	SDL_Rect testRect;
	powerUpTypeBox unitBlue;
	

};
#endif // !__MODULEPOWERUP_H__
