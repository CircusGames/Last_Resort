#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
//#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;
struct Mix_Chunk;

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
	void OnCollision(Collider* collider1, Collider* collider2);

public:

	SDL_Texture* player = nullptr;
	Animation idle;
	
	iPoint position;

	Animation playerAnim;
	Animation spawnAnim;
	int pivotsSpawnX[14] = {40,30,30,28,28,28,24,24,30,30,25,24,4,0};
	Animation playerDyingAnim;
	Animation beamSmoke;
	bool shooting = false;

	float frameIncrement;
	float ignitionSpeed;
	float releaseSpeed;
	
	float playerSpeed;

	Collider* playerCollider;
	bool godMode = false;

	int cameraPosition;

	uint lives = 3;
	Uint32 playerScore = 0;
	bool destroyed = false;
};

#endif