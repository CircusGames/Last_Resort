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

	int iSpeed;
	float fSpeed;

public:

	EnemyBee(int x, int y, powerUpTypes type, SDL_Texture* sprite = nullptr);

	//OnCollision

	void Move();


};

#endif // __ENEMY__H__