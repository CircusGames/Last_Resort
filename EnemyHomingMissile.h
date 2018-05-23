#ifndef __ENEMYHOMINGMISSILE_H__
#define __ENEMYHOMINGMISSILE_H__

#include "Enemy.h"
#include "ModuleTextures.h"


class EnemyHomingMissile : public Enemy
{
private:
	
	struct projectile
	{
		Animation anim[16];
		Animation* current_animation;
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
		// timer for destroy
		Uint32 start_cycle_time;
		Uint32 now_alive_time;
		Uint32 search_life_time = 5000; // time wich missile is chasing the player
		Uint32 instantiate_time = 500; // time wich missile waits to start searching the player
	};

	iPoint pivotAnimation[32] = { 
		{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },
		{ 0,0 },{ 3,0 },{ 2,0 },{ 5,0 },{ 3,0 },{6,0},{ 3,0 },{ 8,0 },//{ 20,0 },

		{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },
		{ 0,0 },{ 3,0 },{ 2,0 },{ 5,0 },{ 3,0 },{ 6,0 }
	
	};

	float initialSpeed = 1.0f;
	float projectileSpeed = 2.0f;

	float turnAroundSpeed = 2.0f;

	float decX = 0.10f;//0.05f;
	float decY = 0.10f;//0.03f;
	

public:

	EnemyHomingMissile(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);

	void Move();
	void Draw();
	void chaseThePlayer();
	void assignAnim();

	projectile missile;

	int scrollSpeed = 0.5; // foreground speed, 0.5 for the timer before homing is activated
	int pivotIndex = 0;
};

#endif // __ENEMYHOMINGMISSILE_H__
