#ifndef __MODULEPOWERUP_H__
#define __MODULEPOWERUP_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleEnemies.h"
//#include "ModuleCollision.h"
#include "Animation.h"
//#include "ModulePlayerUnit.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_POWERUPS 10
#define MAX_TYPES 6

struct SDL_Texture;

enum powerUpColor
{
	BLUE,
	ORANGE
};

struct powerUpTypeBox
{
	SDL_Texture* texture = nullptr;
	powerUpTypes type;
	Collider* collider = nullptr;
	iPoint position;
};

struct PowerUp
{
	Collider* collider = nullptr;
	Animation anim;
	SDL_Texture* texture = nullptr;
	char* fx;
	iPoint position;
	iPoint speed;
	powerUpTypes type;
	powerUpColor color;
	bool fx_played = false;

	fPoint fspeed; //if we want the powerup movement more slowly/faster than camera/player scroll/mov

	PowerUp();
	//PowerUp(const PowerUp& p);
	~PowerUp();
	bool Update();
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

	PowerUp* active_powerUps[MAX_ACTIVE_POWERUPS];
	SDL_Texture * powerUpUnit;

	SDL_Texture* powerUpTextures;

	void SpawnPowerUp(iPoint position, powerUpTypes type);
	void OnCollision(Collider* c1, Collider* c2);

public:

	//SDL_Texture * powerUpS = nullptr;
	
	SDL_Rect testRect;
	powerUpTypeBox unitBlue;

	//SDL_Rect powerUpS;
	//SDL_Rect powerUpZ;
	PowerUp powerUpS;
	PowerUp powerUpZ;
	PowerUp powerUpH;
	PowerUp powerUpG;
	PowerUp powerUpL;

	powerUpColor color;
	

};
#endif // !__MODULEPOWERUP_H__
