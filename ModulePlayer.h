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

	/*enum player_powerUps
	{
		BOOST,
		BOMB,
		MISSILE,

	};*/

public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp(); 
	void OnCollision(Collider* collider1, Collider* collider2);

public:

	SDL_Texture* player = nullptr;
	Animation idle;
	
	iPoint position;

	Animation* current_animation;

	Animation playerAnim;
	Animation spawnAnim;
	int pivotsSpawnX[14] = {40,30,30,28,28,28,24,24,30,30,25,24,4,0};
	Animation playerDyingAnim;
	Animation beamSmoke;
	Animation boostAnim;
	bool shooting = false;

	float frameIncrement;
	float ignitionSpeed;
	float releaseSpeed;
	
	float playerSpeed; //actual playerSpeed
	float speed; // for movement and powerup calculations
	const float normalPlayerSpeed = 1.4f;
	const float boostPlayerSpeed = 2.0f;

	Collider* playerCollider;
	bool godMode = false;

	int cameraPosition;

	uint lives = 3;
	Uint32 playerScore = 0;
	bool destroyed = false;

	//condition of the powerup call ---
	powerUpTypes powerUpActive;
	SDL_Texture* powerUpTextures;

	struct activeBuff
	{
		bool boost = false;
		bool boostAnim = false;
		bool bombs = false;
		bool brake = false;
		bool laser = false;

	} activebuff;
	
	

	//time counter variables
	Uint32 start_time;
	Uint32 now;
	Uint32 powerUpTime;

};

#endif