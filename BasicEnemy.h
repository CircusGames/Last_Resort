#ifndef __BASICENEMY_H__
#define __BASICENEMY_H__

#include "Enemy.h"
#include "Path.h"


class BasicEnemy : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	iPoint original_pos;
	Animation fly;
	Path BasicPath;

public:

	BasicEnemy(int x, int y);

	void Move();
};

#endif // __BASICENEMY_H__