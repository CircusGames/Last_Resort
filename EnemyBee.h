#ifndef __ENEMYBEE_H__
#define __ENEMYBEE_H__

#include "Enemy.h"
#include "ModuleTextures.h"


class EnemyBee : public Enemy
{
private:

	float wave = -1.0f;
	bool going_up = true;
	//int original_y = 0;

	int original_y = 0;
	int original_x = 0;
	Animation flyToRight;
	Animation flyToLeft;
	Animation flyRotationRight;
	Animation flyRotationLeft;
	iPoint original_pos;

	int attackRange;
	float distance;
	bool attack = true;

	int length;


	//movement calculations ----------------------------
	//times calculation
	int start_time;
	int now;
	int cadence;

	int iSpeed;
	float fSpeed;

	float tx;
	float ty;

	float velX;
	float velY;

	Uint32 last_tick;
	float angle = 0;
	float delta_time;

	bool rotEntryDir = false;

	bool rotateCounterClock = false;
	bool rotateClock = false;

	bool firstEncounter = true;

	//int lastX;
	//int lastY;
	// ---------------------------------------------------
public:

	EnemyBee(int x, int y, powerUpTypes type, SDL_Texture* thisTexture = nullptr);

	//OnCollision

	void Move();


};

#endif // __ENEMY__H__