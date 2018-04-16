#ifndef __MODULEPLAYER2_H__
#define __MODULEPLAYER2_H__

#include "Module.h"
#include "Animation.h"
//#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;
struct Mix_Chunk;

class ModulePlayer2 : public Module
{
public:

	enum player_state
	{
		spawn,
		normal,
		died

	} player_step = player_state::spawn;

public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* collider1, Collider* collider2);

public:

	SDL_Texture* player2 = nullptr;
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