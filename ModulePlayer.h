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
	Animation playerDyingAnim;

	float frameIncrement;
	float ignitionSpeed;
	float releaseSpeed;
	
	float playerSpeed;

	Collider* playerCollider;

	int cameraPosition;
};

#endif