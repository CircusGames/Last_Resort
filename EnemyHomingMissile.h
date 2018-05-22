#ifndef __ENEMYHOMINGMISSILE_H__
#define __ENEMYHOMINGMISSILE_H__

#include "Enemy.h"
#include "ModuleTextures.h"


class EnemyHomingMissile : public Enemy
{
private:
	
	struct projectile
	{
		Animation anim;
		Animation* current_animation;
		SDL_Rect rect;
		uint playerTargetIndex = 0;
		bool targetReached = false;
		float angle;
		float distance;
		iPoint position;
		fPoint fposition;
		float xSpeed;
		float ySpeed;
		float targetSpeedX;
		float targetSpeedY;
		bool xflip = false;
		bool searching = false;
		// timer for destroy
		Uint32 start_cycle_time;
		Uint32 now_alive_time;
		Uint32 search_life_time = 5000; // time wich missile is chasing the player
		Uint32 instantiate_time = 500; // time wich missile waits to start searching the player
	};

	iPoint pivotAnimation[16] = {};

	float initialSpeed = 1.0f;
	float projectileSpeed = 2.0f;

	float turnAroundSpeed = 1.5f;

	float decX = 0.10f;//0.05f;
	float decY = 0.10f;//0.03f;
	

public:

	EnemyHomingMissile(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);

	void Move();
	void Draw();
	void chaseThePlayer();

	projectile missile;

	int scrollSpeed = 0.5; // foreground speed
};

#endif // __ENEMYHOMINGMISSILE_H__
