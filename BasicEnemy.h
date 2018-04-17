#ifndef __ENEMY_BROWN_COOKIE_H__
#define __ENEMY_BROWN_COOKIE_H__

#include "Enemy.h"

class BasicEnemy : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
	iPoint original_pos;

public:

	BasicEnemy(int x, int y);

	void Move();
};

#endif // __ENEMY_REDBIRD_H__
