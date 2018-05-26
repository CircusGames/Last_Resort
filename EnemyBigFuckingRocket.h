#ifndef __ENEMYBIGFUCKINGROCKET_H__
#define __ENEMYBIGFUCKINGROCKET_H__

#include "Enemy.h"
#include "ModuleTextures.h"

#define NUM_SMOKE_PARTICLES 8


class EnemyBigFuckingRocket : public Enemy
{
private:

	struct smokeTrailParticles
	{
		Animation anim;
		fPoint spawnPosition;
		const float xSpeed = 0.5f; // compensate the foreground speed to slowly follow its velocity
		bool active = false;

	};

	struct projectile
	{
		Animation propulsionFireAnim;
		smokeTrailParticles propulsionSmoke[NUM_SMOKE_PARTICLES]; // max trails at time
		SDL_Rect bfrRect[16]; // num static axis for rocket body draw
		SDL_Rect* current_rect = nullptr;
		Animation* current_animation = nullptr;
		SDL_Rect rect;
		uint playerTargetIndex = 0;
		bool targetReached = false;
		//float angle;
		float distance;
		iPoint position;
		fPoint fposition;
		float xSpeed;
		float ySpeed;
		float targetSpeedX;
		float targetSpeedY;
		bool searching = false;
		// timer for start/stop searching routine
		Uint32 start_cycle_time;
		Uint32 now_alive_time;
		Uint32 search_life_time = 2000; // time wich missile is chasing the player
		Uint32 instantiate_time = 500; // time wich missile waits to start searching the player
		// timer for autodestruction
		bool goodBye = false;
		Uint32 goodBye_start_time;
		Uint32 now_goodBye_time;
		Uint32 total_goodBye_time = 3000; // time wich missile are saying goodbye
		// position to assign the pivot of fire/smoke trails
		fPoint spawnPointPivot;
	};

	// data for always spawn the next trail on correct current position on back of rocket direction vector
	// respect center point
	/*fPoint pivotSmokeTrail[16] = { {23,5}, {20,12}, {17,17}, {12,20}, {5,23}, {-1,20}, {-4,17},{-7,12}, {-9,5}, {21,-2},
								   {17, -4}, {12, -7}, {5, -8}, {-1,-7}, {-4,-4}, {-7,-1} };*/
	// respect sprites x coord.
	fPoint pivotSmokeTrail[16] = { { 23,0 },{ 15,7 },{ 14,14 },{ 9,17 },{ 0,23 },{ -7,15 },{ -9,14 },{ -12,9 },
	                               { -14,0 },{ 17,-7 },{ 13, -9 },{ 7, -12 },{ 0, -15 },{ -7,-12 },{ -9,-9 },{ -12,-6 } };
	// -----
	iPoint pivotFireAnim[6] = { {0,0},{ -1,-1},{ -3,-3},{-5,-5},{-3,-3},{-1,-1} };

	float initialSpeed = 1.0f;
	float projectileSpeed = 2.0f;

	float turnAroundSpeed = 2.0f;

	float decX = 0.10f;//0.05f;
	float decY = 0.10f;//0.03f;

public:

	EnemyBigFuckingRocket(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);

	void Move();
	void Draw();
	void chaseThePlayer();
	void assignAnim();

	projectile missile;

	int scrollSpeed = 0; // foreground speed, 0.5 for the timer before homing is activated
	int pivotIndex = 0;
	int aliveParticles = 1;
};

#endif // __ENEMYBIGFUCKINGROCKET_H__
