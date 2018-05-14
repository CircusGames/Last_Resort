#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
//#include "Globals.h"
#include "p2Point.h"
#include "SDL\include\SDL_events.h"

#include "ModulePlayer.h"
//#include "Player1.h"

struct SDL_Texture;
struct Collider;
struct Mix_Chunk;

enum player_state
{
	spawn,
	normal,
	died

};//player_step = player_state::spawn;

class ModulePlayer : public Module
{
public:

	player_state player_step = player_state::spawn;
	/*enum player_state
	{
		spawn,
		normal,
		died

	}player_step = player_state::spawn;*/

	/*enum player_powerUps
	{
		BOOST,
		BOMB,
		MISSILE,

	};*/

public:
	ModulePlayer();
	~ModulePlayer();

	//bool Init();

	bool Start();

	update_status PreUpdate();
	update_status Update();
	bool CleanUp(); 
	void OnCollision(Collider* collider1, Collider* collider2);

	virtual void checkInput() {};

public:

	SDL_Texture* player = nullptr;
	SDL_Texture* playerEffectsTexture = nullptr;

	Animation idle;
	
	iPoint position;

	Animation* current_animation;

	Animation playerAnim;
	Animation spawnAnim;
	int pivotsSpawnX[14] = {40,30,30,28,28,28,24,24,30,30,25,24,4,0};
	Animation playerDyingAnim;
	Animation beamSmoke;
	Animation boostAnim;
	Animation laserFlash;
	SDL_Texture* laserFlashTexture = nullptr;
	bool shooting = false;
	bool shootingLaser = false;

	float frameIncrement;
	float ignitionSpeed;
	float releaseSpeed;
	
	float playerSpeed; //actual playerSpeed
	float speed; // for movement and powerup calculations
	const float normalPlayerSpeed = 1.4f;
	const float boostPlayerSpeed = 2.0f;
	const float brakePlayerSpeed = 0.9f;

	Collider* playerCollider;
	bool godMode = false;

	int cameraPosition;

	int lives = 3;
	int playerScore = 0;
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

	bool click = false;

	Module* sceneCallback;

	//public heritance for two players functionality
	struct playerInput
	{
		bool moveLeft = false;
		bool moveRight = false;
		bool moveUp = false;
		bool moveDown = false;
		bool shot = false;
		bool lockUnit = false;
		bool chargedShot = false;
	}playerInput;

	SDL_Texture* playerTexture = nullptr;

	int playerIndex;
};

#endif