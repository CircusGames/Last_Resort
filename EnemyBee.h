#ifndef __ENEMYBEE_H__
#define __ENEMYBEE_H__

#include "Enemy.h"
#include "ModuleTextures.h"


class EnemyBee : public Enemy
{
private:


	int original_y = 0;
	int original_x = 0;
	Animation flyToRight;
	Animation flyToLeft;
	iPoint original_pos;

	int attackRange;
	int distance;
	bool attack = true;

	int length;


	//times calculation
	int start_time;
	int now;
	int cadence;

	int iSpeed;
	float fSpeed;

public:

	EnemyBee(int x, int y, powerUpTypes type, SDL_Texture* thisTexture = nullptr);

	//OnCollision

	void Move();


};

#endif // __ENEMY__H__